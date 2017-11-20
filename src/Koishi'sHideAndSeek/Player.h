#pragma once
#include <iostream>
#include <vector>
#include <GirdMap.hpp>
class Player
{
private:
	Vec2i position;
	virtual bool movementIsLegal(size_t movement)
	{
		return movement >= 0 && movement <= 4;
	}
public:
	virtual void setPosition(Vec2i position_)
	{
		position = position_;
	}
	virtual Vec2i getPosition()
	{
		return position;
	}
};