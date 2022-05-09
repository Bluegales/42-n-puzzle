(cd solver && make)
python3 npuzzle-gen.py 3 > ./files/gen.txt
#./solver/test ./files/npuzzle-4-1.txt 0
#valgrind ./solver/test ./files/npuzzle-3-1.txt
./solver/test ./files/gen.txt 2
#./solver/test ./files/simple.txt
cat ./files/gen.txt | head -1
