#ifndef Picture_h__
#define Picture_h__
#include <vector>
#include "Graphic.h"
#include "Color.h"
namespace cge
{
	class DisplayBuffer;
	class Picture : public Graphic 
	{
	public:
		/**
		* @brief 图片的构造函数
		* @param[in] w 宽
		* @param[in] h 高
		* @param[in] picture 由w*h个像素组成的图片
		*/
		Picture(int w, int h, const std::vector<std::vector<Color>>& picture) noexcept
			: _w(w), _h(h), _picture(picture){}
		virtual ~Picture() {}
		virtual void draw(DisplayBuffer& buffer) override;
		virtual void update() override {};
	private:
		int _w, _h;
		std::vector<std::vector<Color>> _picture;
	};
}
#endif // Picture_h__
