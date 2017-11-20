#pragma once
#include <sstream>
#include <File.hpp>
#include "menuScene.h"
#include "BackGround.h"
#include "ModLoader.hpp"
using namespace std;
using namespace cge;
void menuScene::init()
{
	this->_haveGotTarget = false;
	string modPath = "mods";
	_mods = FileManager::getFolder(modPath);
	auto backGround = make_shared<GraphicsGroup>();
	backGround->add(make_shared<cge::Rectangle>(80, 25, ' ', getColorFromColorID(Green), getColorFromColorID(White), true), 0, 0, 0);
	for (int i = 0; i < 4; ++i)
		backGround->add(make_shared<Textbox>(BackGround_Title[i], Textbox::FillWidth, getColorFromColorID(Green), getColorFromColorID(Transparent)), 12, i + 1, 2);
	backGround->add(ConsolePictureReader::get("image/koishi_3rdeye.cp"), 1, 11, 1);
	backGround->add(ConsolePictureReader::get("image/koishi_head.cp"), 72, 15, 1);
	this->addGraphic(backGround, 0, 0, 0, "backGround");
	//打印menu
	auto menu = make_shared<GraphicsGroup>();
	stringstream menuInfo;
	_curPage = 1, _maxPage = ((int)_mods.size() - 1) / 10 + 1;
	_cursor = 0;
	for (int i = 0; i < 10; ++i)
	{
		menuInfo = stringstream();
		menuInfo << "label" << i;
		if (i<_mods.size())menu->add(make_shared<Textbox>(ModLoader::getModName(_mods[i]), cge::Textbox::FillWidth, getColorFromColorID(Black)), 29, 10 + i, 3, menuInfo.str());
		else menu->add(make_shared<Textbox>("...............", cge::Textbox::FillWidth, getColorFromColorID(Black)), 29, 10 + i, 3, menuInfo.str());
	}
	this->addGraphic(menu, 0, 0, 0, "menu");
	auto cursorItem=make_shared<cge::Rectangle>(2, 1, ' ', getColorFromColorID(Green), getColorFromColorID(BrightBlue), true);
	this->addGraphic(cursorItem, 28, 10 + _cursor, 3, "cursor");
	menuInfo = stringstream();
	menuInfo << "Page: 1/" << _maxPage;
	this->addGraphic(make_shared<Textbox>(menuInfo.str(), cge::Textbox::FillWidth, getColorFromColorID(Black)), 32, 7, 3, "page");
	//光标移动
	this->addKeyboardEvent({ [this](char)->bool {return this->selectUp(); }, string(1,(char)80) });
	this->addKeyboardEvent({ [this](char)->bool {return this->selectDown(); }, string(1,(char)72) });
	//翻页
	this->addKeyboardEvent({ [this](char)->bool {return this->nextPage(); }, string(1,(char)77) });
	this->addKeyboardEvent({ [this](char)->bool {return this->previousPage(); }, string(1,(char)75) });
	//Z键确认
	this->addKeyboardEvent({
		[this](char)->bool {
		if (((_curPage - 1) * 10 + _cursor)<_mods.size())
		{
			_haveGotTarget = true;
			_targetMod = _mods[(_curPage - 1) * 10 + _cursor];
		}
		return false;
	}, string("z") });
	//FPS
	auto fpsViewer= make_shared<Textbox>("Test1", cge::Textbox::FillWidth, getColorFromColorID(Black));
	this->addGraphic(fpsViewer, 70, 24, 3, "fps");
}
void menuScene::update()
{
	stringstream ss;
	ss << "fps:" << this->getFPS();
	((Textbox*)this->getGraphicByTag("fps").get())->setText(ss.str());
	this->flush();
}
bool menuScene::selectUp()
{
	auto cursorItem = this->getGraphicByTag("cursor");
	_cursor = (_cursor == 9) ? 0 : _cursor + 1; 
	cursorItem->setY(10 + _cursor);
	return false;
}
bool menuScene::selectDown()
{
	auto cursorItem = this->getGraphicByTag("cursor");
	_cursor = (_cursor == 0) ? 9 : _cursor - 1;
	cursorItem->setY(10 + _cursor);
	return false;
}
bool menuScene::previousPage()
{
	_curPage = (_curPage == 1) ? _maxPage : _curPage - 1;
	stringstream info;
	info << "Page: " << _curPage << "/" << _maxPage;
	((cge::Textbox*)this->getGraphicByTag("page").get())->setText(info.str());
	GraphicsGroup* menu = (GraphicsGroup*)this->getGraphicByTag("menu").get();
	for (int i = 0; i < 10; ++i)
	{
		info = stringstream();
		info << "label" << i;
		if ((_curPage - 1) * 10 + i<_mods.size())((cge::Textbox*)menu->getGraphicByTag(info.str()).get())->setText(ModLoader::getModName(_mods[(_curPage - 1) * 10 + i]));
		else ((Textbox*)menu->getGraphicByTag(info.str()).get())->setText("...............");
	}
	return false;
}
bool menuScene::nextPage()
{
	_curPage = (_curPage == _maxPage) ? 1 : _curPage + 1;
	stringstream info;
	info << "Page: " << _curPage << "/" << _maxPage;
	((cge::Textbox*)this->getGraphicByTag("page").get())->setText(info.str());
	GraphicsGroup* menu = (GraphicsGroup*)this->getGraphicByTag("menu").get();
	for (int i = 0; i < 10; ++i)
	{
		info = stringstream();
		info << "label" << i;
		if ((_curPage - 1) * 10 + i<_mods.size())((cge::Textbox*)menu->getGraphicByTag(info.str()).get())->setText(ModLoader::getModName(_mods[(_curPage - 1) * 10 + i]));
		else ((Textbox*)menu->getGraphicByTag(info.str()).get())->setText("...............");
	}
	return false;
}