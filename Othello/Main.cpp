
#include <memory>
#include "Game.h"

void Main()
{
	Window::Resize(580, 580);
	
	auto game = std::make_unique<Game>();
	while (System::Update())
	{
		game->update();
		game->draw();
	}
}
