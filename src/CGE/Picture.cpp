#include "Picture.h"
#include "DisplayBuffer.h"
namespace cge
{
	void Picture::draw(DisplayBuffer& buffer)
	{
		if (!_visibility) return;
		for (int drawX = _x,arrayX=0; drawX != _x + _w; drawX++, arrayX++) {
			for (int drawY = _y,arrayY=0; drawY != _y + _h; drawY++, arrayY++) {
				buffer.setPixel(drawX, drawY, getColorFromColorID(White), _picture[arrayY][arrayX], ' ');
			}
		}
	}
}