#pragma once
#include <vector>
#include "Vector2.h"
template<class GirdType>
class GridMap
{
private:
	std::vector<std::vector<GirdType>>gird;
	Vec2u girdSize;
public:
	std::vector<GirdType> operator [](size_t index)
	{
		return gird[index];
	}
	void resize(Vec2u size)
	{
		girdSize = size;
		gird.resize(size.x);
		for (auto&& item : gird)
			item.resize(size.y);
	}
	Vec2u size()
	{
		return girdSize;
	}
	void setMap(const std::vector<std::vector<GirdType>>& map)
	{
		gird = map;
		girdSize = Vec2u(map.size(), map[0].size());
	}
	void setGird(size_t r, size_t c, GirdType gird_)
	{
		gird[r][c] = gird_;
	}
	GirdType& getGird(size_t r, size_t c)
	{
		return gird[r][c];
	}
};
enum class Gird01 :bool
{
	EMPTY,
	WALL
};
