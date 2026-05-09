#include "Game.h"

int main()
{
	hideCursor();

	try
	{
		Game game;
		game.run();
	}
	catch (const std::exception& e)
	{
		Game::printErrorMessage(e.what());
		return 1;
	}
	catch (...)
	{
		Game::printErrorMessage("An unknown error occurred.");
		return 1;
	}

	return 0;
}