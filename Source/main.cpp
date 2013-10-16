#include "Game.hpp"

#include <iostream>
using namespace std;

int main()
	{
	Game game;
	if ( game.Init() )
		return game.Run();
	else
		return 1;
	}

