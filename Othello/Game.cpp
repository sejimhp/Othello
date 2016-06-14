#include "Game.h"

Game::Game(){
	map = std::make_shared<Map>();
	map->clear();
}

void Game::update(){
	if (Input::KeySpace.clicked){
		map->clear();
		putTurn = 0;
	}
	if (map->IsNulTrout()){
		if (Input::MouseL.clicked && Mouse::Pos().y >= 0 && Mouse::Pos().x >= 0 && Mouse::Pos().y < 530 && Mouse::Pos().x < 530){
			int height = (Mouse::Pos().y - 50) / 60;
			int width = (Mouse::Pos().x - 50) / 60;
			if (putTurn % 2 == 0 && map->put(height, width, 0)){
				putTurn++;
			}
		}
		else{
			if (putTurn % 2 == 1){
				System::Sleep(1000);
				map->putCPU();
				putTurn++;
			}
		}
	}
}

void Game::draw(){
	static Font font(30);
	Rect(0, 0, 600, 600).draw(Palette::Green);
	for (int i = 0; i < TROUT + 1; i++){
		Line(50 + i * 60, 50, 50 + i * 60, 530).draw();
		Line(50, 50 + i * 60, 530, 50 + i * 60).draw();
	}
	if (putTurn % 2 == 0){
		font(L"”’").draw();
	}
	else{
		font(L"•").draw();
	}
	map->draw();
}