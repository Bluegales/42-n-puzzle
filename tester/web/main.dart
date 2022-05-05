import 'dart:async';
import 'dart:collection';
import 'dart:html';

import 'dart:math';

class Element {}

enum Movement { left, right, up, down }

bool isSquare(int x) {
  for (int i = 0; i < 20; i++) {
    if (i * i == x) return true;
  }
  return false;
}

class Puzzle {
  final HtmlElement _dom;
  late final int _size;
  final List<List<HtmlElement>> elements = [[]];

  var holeX = 0;
  var holeY = 0;

  void move(Movement move) {
    var locX = holeX;
    var locY = holeY;
    if (move == Movement.left) locX--;
    if (move == Movement.right) locX++;
    if (move == Movement.up) locY--;
    if (move == Movement.down) locY++;
    assert(locX >= 0 && locY >= 0 && locX < _size && locY < _size);
    elements[locX][locY].style.top = (holeX / _size * 100).toString() + "vh";
    elements[locX][locY].style.left =
        (holeY / _size * 100).toString() + "vh";
    holeX = locX;
    holeY = locY;
  }

  void setPosition(int id, int x, int y) {
    assert(x >= 0 && y >= 0 && x < _size && y < _size);
    elements[x][y].style.top = (x / _size * 100).toString() + "vh";
    elements[x][y].style.left = (y / _size * 100).toString() + "vh";
  }

  Puzzle(this._dom) {
    final uri = Uri.parse(window.location.href);
    final numbers = uri.queryParameters["nbr"]?.split(",");
    if (numbers == null) return;
    final count = numbers.length;
    _size = (sqrt(count)).round();
    if (!isSquare(count)) return;
    //_dom.style.gridTemplateRows = "repeat(" + _size.toString() + ", 1fr)";
    //_dom.style.gridTemplateColumns = "repeat(" + _size.toString() + ", 1fr)";
    for (var n in numbers) {
      HtmlElement newDiv = document.createElement("div") as HtmlElement;
      newDiv.classes.add("element");
      //newDiv.style.backgroundSize = (_size * 100).toString() + "vw";
      final column = int.parse(n) % _size;
      final row = (int.parse(n) / _size).floor();
      newDiv.style.width = (99 / _size).toString() + "vh";
      newDiv.style.height = (99 / _size).toString() + "vh";
      //newDiv.style.top = (100 / column).floor().toString() + "%";
      newDiv.style.top = (row / _size * 100).toString() + "vh";
      newDiv.style.left = (column / _size * 100).toString() + "vh";
      newDiv.style.backgroundPosition = (99 * column / (_size - 1)).toString() +
          "% " +
          (99 * row / (_size - 1)).toString() +
          "%";
      //newDiv.style.backgroundPositionY = (int.parse(n) % _size * 100).round().toString() + "% left";
      //"top " + (int.parse(n) / _size).toString() + " px";
      _dom.append(newDiv);
    }
  }
}

int main() {
  var dom = querySelector("#puzzle") as HtmlElement;
  Puzzle puzzle = Puzzle(dom);

  return (0);
}
