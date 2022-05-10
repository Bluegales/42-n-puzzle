import 'dart:async';
import 'dart:collection';
import 'dart:html';

import 'dart:math';

enum eCommands { up, down, left, right }

bool isSquare(int x) {
  for (int i = 0; i < 20; i++) {
    if (i * i == x) return true;
  }
  return false;
}

class Puzzle {
  final HtmlElement _dom;
  late final int _size;
  final List<HtmlElement> elements = [];
  final List<eCommands> _commands = [];
  int _position = 0;

  int hole = 0;

  void swap(int id1, int id2) {
    print(elements[id1].style.top);
    print(elements[id1].style.left);
    print(elements[id2].style.top);
    print(elements[id2].style.left);
    var temp1 = elements[id1].style.top;
    var temp2 = elements[id1].style.left;
    elements[id1].style.top = elements[id2].style.top;
    elements[id1].style.left = elements[id2].style.left;
    elements[id2].style.top = temp1;
    elements[id2].style.left = temp2;
    var temp = elements[id1];
    elements[id1] = elements[id2];
    elements[id2] = temp;
  }

  void move(eCommands cmd) {
    int loc = hole;
    if (cmd == eCommands.up) loc -= _size;
    if (cmd == eCommands.down) loc += _size;
    if (cmd == eCommands.left) loc--;
    if (cmd == eCommands.right) loc++;
    swap(loc, hole);
    hole = loc;
  }

  int execute() {
    if (_commands.isEmpty) return 1;
    if (_position >= _commands.length) return 2;
    move(_commands[_position]);
    _position++;
    return 0;
  }

  void play(Duration speed) {
    Timer _playTimer =
        Timer.periodic(speed, (timer) => {if (execute() != 0) timer.cancel()});
  }

  int addCommands() {
    final uri = Uri.parse(window.location.href);
    final commandString = uri.queryParameters["cmd"];
    print(commandString);
    if (commandString == null) return (1);
    final commandRunes = commandString.runes;
    final firstCommand = "0".runes.first;
    for (int c in commandRunes) {
      c -= firstCommand;
      if (c < 0 || c > 3) return 1;
      _commands.add(eCommands.values[c]);
    }
    print(_commands);
    return (0);
  }

  Puzzle(this._dom) {
    final uri = Uri.parse(window.location.href);
    final numbers = uri.queryParameters["nbr"]?.split(",");
    if (numbers == null) return;
    final hole_str = uri.queryParameters["hole"];
    if (hole_str != null) {
      hole = int.parse(hole_str);
    }
    final count = numbers.length;
    _size = (sqrt(count)).round();
    if (!isSquare(count)) return;
    //_dom.style.gridTemplateRows = "repeat(" + _size.toString() + ", 1fr)";
    //_dom.style.gridTemplateColumns = "repeat(" + _size.toString() + ", 1fr)";
    for (var i = 0; i < numbers.length; i++) {
      HtmlElement newDiv = document.createElement("div") as HtmlElement;
      newDiv.classes.add("element");
      //newDiv.style.backgroundSize = (_size * 100).toString() + "vw";
      newDiv.style.width = (99 / _size).toString() + "vh";
      newDiv.style.height = (99 / _size).toString() + "vh";
      final column = (i % _size).floor();
      final row = (i / _size).floor();
      //newDiv.style.top = (100 / column).floor().toString() + "%";
      newDiv.style.top = (row / _size * 100).toString() + "vh";
      newDiv.style.left = (column / _size * 100).toString() + "vh";
      final picColumn = (int.parse(numbers[i]) % _size).floor();
      final picRow = (int.parse(numbers[i]) / _size).floor();
      newDiv.style.backgroundPosition =
          (99 * picColumn / (_size - 1)).toString() +
              "% " +
              (99 * picRow / (_size - 1)).toString() +
              "%";
      if (i == hole) {
        newDiv.classes.add("empty-element");
      }
      newDiv.appendText((picColumn + picRow * _size).toString());
      newDiv.style.textShadow = "0 0 20px #ff0000, 0 0 10px #0000ff";
      newDiv.style.color = "green";
      newDiv.style.fontSize = (90 / _size).toString() + "vh";
      elements.add(newDiv);
      //newDiv.style.backgroundPositionY = (int.parse(n) % _size * 100).round().toString() + "% left";
      //"top " + (int.parse(n) / _size).toString() + " px";
      _dom.append(newDiv);
    }
  }
}

int main() {
  var dom = querySelector("#puzzle") as HtmlElement;
  Puzzle puzzle = Puzzle(dom);
  puzzle.addCommands();
  puzzle.play(Duration(milliseconds: 100));
  return (0);
}
