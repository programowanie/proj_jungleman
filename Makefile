all:
	g++ *.cpp -std=c++0x -o jungleman
	./jungleman jungle.csv 100