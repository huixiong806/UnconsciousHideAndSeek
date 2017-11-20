#ifndef Scene_h__
#define Scene_h__
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "Event.h"
#include "Settings.h"
#include "DisplayBuffer.h"
#include "KeyboardEventManager.h"
namespace cge
{
	class Graphic;
	class Scene {
	public:

		/**
		* @brief ��������
		*/
		template<class... Ts>
		static std::shared_ptr<Scene> create(Ts&&... args)
		{
			initCheck();
			return std::shared_ptr<Scene>(new Scene(std::forward<Ts>(args)...));
		}

		/**
		* @brief ���Graphic
		* @param[in] Graphic Ҫ�����Graphic
		* @param[in] x Ҫ�����Graphic����Ļ��Xλ��
		* @param[in] y Ҫ�����Graphic����Ļ��Yλ��
		* @param[in] tag Ҫ�����Graphic��tag(���ڲ��Ҹ�Graphic)��ע��ͬһ��Scene��tag�����ظ�
		* @param[in] layer Ҫ�����Graphic��layer, layer���ͼ�ο��Ը���layerС��ͼ��, ��ͬlayer��ͼ�εĸ���˳���޶���
		* @note ����ϵ����y+,����x+,Graphic��Scene��ԭ�㶼�����Ͻ�
		*/
		void addGraphic(std::shared_ptr<Graphic>& graphic, int x, int y, int layer = 0, std::string tag = "");
		void addGraphic(std::shared_ptr<Graphic>&& graphic, int x, int y, int layer = 0, std::string tag = "");

		/**
		* @brief ����һ��Graphic
		* @param[in] tag Ҫ���ҵ�Graphic��tag
		* @return ���ҵ���Graphic��shared_ptrָ�룬���Ҳ���������nullָ��
		*/
		std::shared_ptr<Graphic> getGraphicByTag(const std::string& tag);

		/**
		* @brief ˢ����ʾ
		*/
		void reDraw(); ///ǿ���ػ�������ʾ����������˸��
		void flush();  ///ֻˢ���޸Ĳ���

		/**
		* @brief ��õ�ǰ��fps
		* @return ���ص�ǰ��fps
		*/
		double getFPS();

		void addEvent(Event e);

		void addKeyboardEvent(KeyboardEventManager::KeyEvent k, bool monopolize = false, int priority = 0);

		void setFocus(const Graphic* target, bool focus);
		
		virtual void init(){}
		/**
		* @brief ����ÿ֡�Ĳ���
		* @return ��
		*/
		virtual void update(){}
	protected:
		DisplayBuffer buffer;
		std::multimap<int, std::shared_ptr<Graphic>> _graphics;
		std::vector<Event> events;
		KeyboardEventManager kem;
		Scene() :buffer(resolutionW, resolutionH) {};
	private:
		double fps;
	};

}
#endif // Scene_h__
