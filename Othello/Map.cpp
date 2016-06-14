#include "Map.h"

#include "Game.h"

Map::Map(){
	map.resize(TROUT);
	for (int i = 0; i < TROUT; i++){
		map[i].resize(TROUT);
	}
}

void Map::clear(){
	putY = 99;
	putX = 99;
	map.clear();

	map.resize(TROUT);
	for (int i = 0; i < TROUT; i++){
		map[i].resize(TROUT);
		for (int j = 0; j < TROUT; j++){
			map[i][j] = State::NUL;
		}
	}

	map[3][3] = map[4][4] = State::WHITE;
	map[3][4] = map[4][3] = State::BLACK;
}

bool Map::IsNulTrout(){
	for (int i = 0; i < TROUT; i++){
		for (int j = 0; j < TROUT; j++){
			if (map[i][j] == State::NUL){
				return true;
			}
		}
	}
	return false;
}

void Map::draw(){
	Rect(50 + putX * 60, 50 + putY * 60, 60, 60).draw({ Palette::Orange, 120 });
	for (int i = 0; i < TROUT; i++){
		for (int j = 0; j < TROUT; j++){
			if (map[i][j] == State::BLACK){
				Circle(80 + j * 60, 80 + i * 60, 23).draw(Palette::Black);
			}
			else if (map[i][j] == State::WHITE){
				Circle(80 + j * 60, 80 + i * 60, 23).draw(Palette::White);
			}
		}
	}
}

bool Map::put(int height, int width, int color){
	if (map[height][width] != State::NUL){
		return false;
	}
	State state;
	int sum = 0;
	int y[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int x[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	//�F�̑I��
	if (color == 0){
		state = State::WHITE;
	}
	else {
		state = State::BLACK;
	}

	//���]����
	for (int i = 0; i < 8; i++){
		if (reverse(height + y[i], width + x[i], y[i], x[i], state, 0)){
			sum++;
		}
	}

	//�u�����ture
	if (sum){
		map[height][width] = state;
		putY = height;
		putX = width;
		return true;
	}
	else {
		return false;
	}
}

bool Map::reverse(int height, int width, int y, int x, State state, int deep){
	if (height >= TROUT || width >= TROUT || height < 0 || width < 0 || map[height][width] == State::NUL){
		//�͈͊O or NULL
		return false;
	}
	else if (state == map[height][width]){
		//1�O�������F�Ȃ��false
		if (deep < 1){
			return false;
		}
		//�����F�ł����ture��Ԃ�
		return true;
	}
	else {
		//�Ⴄ�F�ł���Α�����
		bool t = reverse(height + y, width + x, y, x, state, deep + 1);
		if (t){
			if (map[height][width] == State::BLACK){
				map[height][width] = State::WHITE;
			}
			else{
				map[height][width] = State::BLACK;
			}
		}
		return t;
	}
}

void Map::putCPU(){
	int y = 0, x = 0, sum = 0;

	int Y[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int X[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	//���������̂Ƃ����T��
	for (int i = 0; i < TROUT; i++){
		for (int j = 0; j < TROUT; j++){
			if (map[i][j] == State::NUL){
				int t = 0;
				//8��������
				for (int k = 0; k < 8; k++){
					t += CountCanPut(i+Y[k], j+X[k], Y[k], X[k], 0);
				}
				//max
				if (sum < t){
					sum = t;
					y = i;
					x = j;
				}
			}
		}
	}
	//�ł��Ԃ����������Ƃ���ɒu��
	put(y, x, 1);
}

int Map::CountCanPut(int height, int width, int y, int x, int deep){
	if (height >= TROUT || width >= TROUT || height < 0 || width < 0 || map[height][width] == State::NUL){
		//�͈͊O or NULL
		return 0;
	}
	else if (map[height][width] == State::BLACK){
		//1�O�������F�Ȃ��0
		if (deep < 1){
			return 0;
		}
		//�����F�ł����-1��Ԃ�
		return -1;
	}
	else {
		//�Ⴄ�F�ł���Α�����
		//0�������甽�]�ł��Ȃ� -1�Asum > 0�������甽�]�ł���
		int sum = CountCanPut(height + y, width + x, y, x, deep+1);
		if (sum < 0) sum *= -1;
		if (sum){
			sum++;
		}
		return sum;
	}
}