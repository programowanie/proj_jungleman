all:
	g++ *.cpp -std=c++0x -o proj_jungleman
	./proj_jungleman jungle.csv 100