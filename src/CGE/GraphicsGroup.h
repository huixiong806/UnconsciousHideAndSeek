#ifndef GraphicsGroup_h__
#define GraphicsGroup_h__
#include <map>
#include <memory>
#include "Graphic.h"
namespace cge
{
	class DisplayBuffer;
	class GraphicsGroup : public Graphic {
	public:
		GraphicsGroup() noexcept {};
		virtual ~GraphicsGroup() {}
		virtual void draw(DisplayBuffer& buffer) override;
		virtual void update() override;

		void add(std::shared_ptr<Graphic>& graphic, int x, int y, int layer = 0, std::string tag = "");
		void add(std::shared_ptr<Graphic>&& graphic, int x, int y, int layer = 0, std::string tag = "");

		void setFocus(const Graphic* target, bool focus) override
		{
			for (auto iter = _graphics.begin(); iter != _graphics.end(); ++iter) {
				iter->second->setFocus(target, focus);
			}
		}
		virtual void bind(Scene* s) override;
		/**
		* @brief ����һ��Graphic
		* @param[in] tag Ҫ���ҵ�Graphic��tag
		* @return ���ҵ���Graphic��shared_ptrָ�룬���Ҳ���������nullָ��
		*/
		std::shared_ptr<Graphic> getGraphicByTag(const std::string& tag);
	private:
		std::multimap<int, std::shared_ptr<Graphic>> _graphics;
	};
}
#endif // GraphicsGroup_h__
