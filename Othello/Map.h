#pragma once
#include <vector> 

class Map{
public:
	enum State{
		NUL,
		BLACK,
		WHITE,
	};
	Map::Map();
	void clear();

	bool put(int height, int width, int color);
	void draw();

	//CPU
	void putCPU();
	int CountCanPut(int height, int width, int y, int x, int deep);

	int getSumBlack();
	int getSumWhite();
	bool IsNulTrout();
private:
	int putY, putX;
	std::vector<std::vector<State> > map;
	bool reverse(int height, int width, int y, int x, State state, int deep);
};