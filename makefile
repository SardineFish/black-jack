compile:
	g++ -std=c++11 black-jack.cpp CSI.cpp -o black-jack -lncurses
debug:
	g++ -std=c++11 -g -lncurses black-jack.cpp CSI.cpp -o black-jack
