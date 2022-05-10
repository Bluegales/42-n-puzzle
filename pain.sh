(cd solver && make)
python3 npuzzle-gen.py $1 > ./files/gen.txt
#./solver/test ./files/npuzzle-4-1.txt 0
#valgrind ./solver/test ./files/npuzzle-3-1.txt 2
#./solver/test ./files/4-snake.txt 2
#./solver/test ./files/3-easy.txt 2
#./solver/test ./files/simple.txt
./solver/n-puzzle ./files/gen.txt $2 $3
cat ./files/gen.txt | head -1
