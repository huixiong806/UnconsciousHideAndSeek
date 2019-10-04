#pragma once
#include <CGE.h>
#include <Console.h>
#include <sstream>
#include <Windows.h>
#include <Constant.h>
#include <File.hpp>
#include "KoishiHideAndSeek.h"
using json = nlohmann::json;
using namespace cge;
using namespace std;
string curPath;
bool Game::timeUp()
{
	return (round >= roundLimit && roundLimit >= 0);
}
GetMovementResult Game::getMovementForSatori()
{
	ofstream output("satori.in");
	output << map.size().x << " " << map.size().y << " " << startPositionSatori.x << " " << startPositionSatori.y << " " << startPositionKoishi.x << " " << startPositionKoishi.y << " " << roundLimit << endl;
	for (int32_t i = 0; i < map.size().x; ++i)
	{
		for (int32_t j = 0; j < map.size().y; ++j)
			output << (int)map.getGird(i, j) << " ";
		output << endl;
	}
	output << round + 1 << endl;
	for (int32_t i = 0; i < round; ++i)
		output << movementSetSatori[i] << endl;
	bool timeLimitExceeded = FileManager::openEXE(curPath + "\\AI\\satori.exe", 1500);
	if (timeLimitExceeded)return { -1,1,0,0 };
	ifstream input("satori.out");
	int32_t newMovement = 5;
	input >> newMovement;
	movementSetSatori.push_back(newMovement);
	return { newMovement,0,0,!movementIsLegal(satori, newMovement) };
}
GetMovementResult Game::getMovementForKoishi()
{
	ofstream output("koishi.in");
	output << map.size().x << " " << map.size().y << " " << startPositionSatori.x << " " << startPositionSatori.y << " " << startPositionKoishi.x << " " << startPositionKoishi.y << " " << roundLimit << endl;
	for (int32_t i = 0; i < map.size().x; ++i)
	{
		for (int32_t j = 0; j < map.size().y; ++j)
			output << (int)map.getGird(i, j) << " ";
		output << endl;
	}
	output << round + 1 << endl;
	for (int32_t i = 0; i < round; ++i)
		output << movementSetSatori[i] << " " << movementSetKoishi[i] << endl;
	bool timeLimitExceeded = FileManager::openEXE(curPath + "\\AI\\koishi.exe", 1500);
	if (timeLimitExceeded)return { -1,1,0,0 };
	ifstream input("koishi.out");
	int32_t newMovement = 5;
	input >> newMovement;
	movementSetKoishi.push_back(newMovement);
	return { newMovement,0,0,!movementIsLegal(koishi, newMovement) };
}
bool Game::catchUp(int32_t movementSatori, int32_t movementKoishi)
{
	Vec2i newPositionSatori = satori->getPosition() + cns::delta[movementSatori];
	Vec2i newPositionKoishi = koishi->getPosition() + cns::delta[movementKoishi];
	if (newPositionSatori == koishi->getPosition() && satori->getPosition() == newPositionKoishi)
		return true;
	if (newPositionKoishi == newPositionSatori)
		return true;
	return false;
}
bool Game::roundFinish(int32_t movementSatori, int32_t movementKoishi)
{
	round++;
	bool catchUp = this->catchUp(movementSatori, movementKoishi);
	satori->setPosition(satori->getPosition() + cns::delta[movementSatori]);
	koishi->setPosition(koishi->getPosition() + cns::delta[movementKoishi]);
	if (catchUp)return true;
	if (timeUp())
	{
		round++;
		return true;
	}
	return false;
}
bool Game::movementIsLegal(std::shared_ptr<Player> player, int32_t movement)
{
	if (movement > 4)return false;
	Vec2i newPosition = player->getPosition() + cns::delta[movement];
	if (newPosition.x >= map.size().x || newPosition.x < 0)return false;
	if (newPosition.y >= map.size().y || newPosition.y < 0)return false;
	if (map[newPosition.x][newPosition.y] == Gird01::WALL)return false;
	return true;
}
void Game::printMap()
{
	for (int32_t i = 0; i < map.size().x; ++i)
	{
		for (int32_t j = 0; j < map.size().y; ++j)
		{
			if (Vec2i(i, j) == satori->getPosition())
				cout << "S";
			else if (Vec2i(i, j) == koishi->getPosition())
				cout << "K";
			else cout << ((int)map.getGird(i, j)==0?".":"#");
		}
		cout << endl;
	}
}
void Game::runGame()
{
	bool satoribadmoveflag = false;
	bool koishibadmoveflag = false;
	bool satoriTLEflag = false;
	bool koishiTLEflag = false;
	cout << "Game Start" << endl;
	GetMovementResult movementSatori, movementKoishi;
	if (!(roundLimit == 0 || startPositionSatori == startPositionKoishi))
	{
		do
		{
			printMap();
			cout << endl << "round " << round + 1 << ":" << endl;
			movementSatori = getMovementForSatori();
			if (movementSatori.badMove)satoribadmoveflag = true;
			if (movementSatori.timeLimitExceeded)satoriTLEflag = true;
			movementKoishi = getMovementForKoishi();
			if (movementKoishi.badMove)koishibadmoveflag = true;
			if (movementKoishi.timeLimitExceeded)koishiTLEflag = true;
			if (satoribadmoveflag || koishibadmoveflag || satoriTLEflag || koishiTLEflag)break;
		} while (!roundFinish(movementSatori.movement, movementKoishi.movement));
		printMap();
	}
	cout << "Game Over" << endl;
	if (satoriTLEflag&&koishiTLEflag)cout << "Both TLE." << endl;
	else if (satoriTLEflag)cout << "Satori TLE." << endl;
	else if (koishiTLEflag)cout << "Koishi TLE." << endl;
	else if (satoribadmoveflag&&koishibadmoveflag)cout << "Both bad move." << endl;
	else if (satoribadmoveflag)cout << "Satori bad move,movement:" << movementSatori.movement << endl;
	else if (koishibadmoveflag)cout << "Koishi bad move,movement:" << movementKoishi.movement << endl;
	else cout << "Koishi lived " << round << " rounds." << endl;
	FileManager::deleteFile("satori.in");
	FileManager::deleteFile("satori.out");
	FileManager::deleteFile("koishi.in");
	FileManager::deleteFile("koishi.out");
	FileManager::deleteFile("koishi.tmp");
	FileManager::deleteFile("satori.tmp");
}
void Game::initGame(json parameter)
{
	ifstream input(curPath + "/map/map1.txt");
	Vec2u mapSize;
	input >> mapSize.x >> mapSize.y >> startPositionSatori.x >> startPositionSatori.y >> startPositionKoishi.x >> startPositionKoishi.y >> roundLimit;
	cout << "time limit:" << roundLimit << endl;
	map.resize(mapSize);
	round = 0;
	satori = make_shared<Player>();
	koishi = make_shared<Player>();
	satori->setPosition(startPositionSatori);
	koishi->setPosition(startPositionKoishi);
	for (int32_t i = 0; i <map.size().x; ++i)
	{
		for (int32_t j = 0; j < map.size().y; ++j)
		{
			int32_t temp;
			input >> temp;
			map.setGird(i, j, (Gird01)temp);
		}
	}
}

std::shared_ptr<Game> game;
extern "C"
{
	APIEXPORT void APICALL initGame(json parameter,string modPath)
	{
		Console::clear();
		curPath = modPath;
		cout << "loading parameters" << endl;
		game = make_unique<Game>();
		game->initGame(parameter);
		cout << "successful" << endl;
	}
	APIEXPORT void APICALL startGame()
	{
		game->runGame();
		while (getchar() != 'q');
		Console::clear();
	}
}