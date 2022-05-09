(cd solver && make)
python3 npuzzle-gen.py $1 > ./files/gen.txt
cat ./files/gen.txt | head -1
#./solver/test ./files/npuzzle-4-1.txt 0
#valgrind ./solver/test ./files/npuzzle-3-1.txt 2
#./solver/test ./files/4-snake.txt 2
#./solver/test ./files/3-easy.txt 2
#./solver/test ./files/simple.txt
./solver/test ./files/gen.txt 2
cat ./files/gen.txt | head -1
