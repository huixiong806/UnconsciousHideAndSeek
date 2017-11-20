﻿#include "Scene.h"
#include "Graphic.h"
#include "Console.h"
#include "Color.h"
#include "DisplayBuffer.h"
#include <chrono>
#include <Windows.h>
namespace cge
{
	void Scene::addGraphic(std::shared_ptr<Graphic>& graphic, int x, int y, int layer, std::string tag)
	{
		graphic->setX(x);
		graphic->setY(y);
		graphic->setTag(tag);
		graphic->bind(this);
		_graphics.insert({ layer,std::move(graphic) });
	}

	void Scene::addGraphic(std::shared_ptr<Graphic>&& graphic, int x, int y, int layer, std::string tag)
	{
		graphic->setX(x);
		graphic->setY(y);
		graphic->setTag(tag);
		graphic->bind(this);
		_graphics.insert({ layer,std::move(graphic) });
	}

	std::shared_ptr<Graphic> Scene::getGraphicByTag(const std::string& tag)
	{
		for (const auto& g : _graphics) {
			if (g.second->getTag() == tag) return g.second;
		}
		return nullptr;
	}

	void Scene::flush()
	{
		auto timeBeforeDraw = std::chrono::system_clock::now();
		auto oldBuffer = buffer.clone();
		buffer.clear();
		for (auto callback : events) {
			callback();
		}
		kem.listen(); //监听按键信息
		for (auto graphic : _graphics) {
			graphic.second->update();
			graphic.second->draw(buffer);
		}
		for (int y = 0; y != buffer.getH(); y++)
		{
			for (int x = 0; x != buffer.getW(); x++)
			{
				auto pixel = buffer.getPixel(x, y);	//获得像素
				auto oldPixel = oldBuffer.getPixel(x, y);
				if (pixel != oldPixel) {
					Console::printPixel(pixel, x, y);
				}
			}
		}
		auto timeAfterDraw = std::chrono::system_clock::now();
		auto diff = (timeAfterDraw - timeBeforeDraw).count();
		fps = 1.0 / (diff == 0 ? 1 : diff) * 10000000;
	}

	void Scene::reDraw()
	{
		auto timeBeforeDraw = std::chrono::system_clock::now();
		buffer.clear();
		for (auto callback : events) {
			callback();
		}
		for (auto graphic : _graphics) {
			graphic.second->update();
			graphic.second->draw(buffer);
		}
		Console::printDisplayBuffer(buffer);
		auto timeAfterDraw = std::chrono::system_clock::now();
		auto diff = (timeAfterDraw - timeBeforeDraw).count();
		fps = 1.0 / (diff == 0 ? 1 : diff) * 10000000;
	}

	double Scene::getFPS()
	{
		return fps;
	}

	void Scene::addEvent(Event e) {
		events.emplace_back(e);
	}

	void Scene::addKeyboardEvent(KeyboardEventManager::KeyEvent k, bool monopolize, int priority)
	{
		kem.bind(k, monopolize, priority);
	}

	void Scene::setFocus(const Graphic * target, bool focus)
	{
		for (auto iter = _graphics.begin(); iter != _graphics.end(); ++iter) {
			iter->second->setFocus(target, focus);
		}
	}
}
