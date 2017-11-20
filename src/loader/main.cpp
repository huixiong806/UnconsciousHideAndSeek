#include <CGE.h>
#include <Console.h>
#include <sstream>
#include <memory>
#include <iostream>
#include "ModLoader.hpp"
#include "SharedLibrary.hpp"
#include "menuScene.h"
using namespace cge;
using namespace std;
using json = nlohmann::json;
typedef void(*ApiInit)(json,string);
typedef void(*ApiStart)();
string selectGame()
{
	auto menu = menuScene::create();
	menu->init();
	while (!menu->haveGotTarget())
		menu->update();
	return menu->getTargetMod();
}
json setGameParameter(const string& gamePath)
{
	return json();
}
void playGame(const string& gamePath,json parameter)
{
	SharedLibrary lib = SharedLibrary(gamePath + "/main.dll");
	ApiInit initgame = (ApiInit)lib.get("initGame");
	ApiStart startGame = (ApiStart)lib.get("startGame");
	initgame(parameter, gamePath);
	startGame();
}
int main()
{
	initCGE();
	Console::setCharSize(25);
	while (true)
	{
		string game = selectGame();
		playGame(game, setGameParameter(game));
	}
}