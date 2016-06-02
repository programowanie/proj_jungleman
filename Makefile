all:
	g++ *.cpp -std=c++0x -o proj_jungleman
	./proj_jungleman jungle.csv jungle2.csv 100