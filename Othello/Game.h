#pragma once
#include <Siv3D.hpp>

#include "Map.h"

#define TROUT 8

class Game {
public:
	Game::Game();
	void update();
	void draw();

	bool IsMapNull();
private:
	std::shared_ptr<Map> map;
	int putTurn;
};