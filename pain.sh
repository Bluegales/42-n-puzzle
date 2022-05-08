(cd solver && make)
python3 npuzzle-gen.py 4 > ./files/gen.txt
#./solver/test ./files/npuzzle-4-1.txt
#valgrind ./solver/test ./files/npuzzle-3-1.txt
./solver/test ./files/gen.txt
#./solver/test ./files/simple.txt
cat ./files/gen.txt | head -1
