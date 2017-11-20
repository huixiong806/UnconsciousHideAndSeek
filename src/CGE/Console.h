﻿#ifndef Console_h__
#define Console_h__
#include <cstdio>
namespace cge
{
	struct Color;
	struct PixelData;
	class DisplayBuffer;
	/*!
	 * \class Console
	 *
	 * \brief 平台相关的控制台API
	 *
	 * \author Null
	 * \date 四月 2016
	 */
	class Console {
	public:
		/**
		* @brief 输出文字到控制台
		* @param[in] text 要输出的文字
		*/
		static void print(const char* text)
		{
			puts(text);
		}
		/**
		* @brief 打印单个字符
		* @param[in] c 要打印的字符
		*/
		static void printChar(const unsigned char c)
		{
			putchar(c);
		}
		/**
		* @brief 打印单个像素
		* @param[in] pixel 要打印的像素
		*/
		static void printPixel(PixelData pixel, int x, int y);

		/**
		* @brief 显示buffer内的内容
		* @param[in] buffer 要显示的DisplayBuffer
		*/
		static void printDisplayBuffer(const DisplayBuffer& buffer);

		/**
		* @brief 设置控制台大小
		* @param[in] w 宽
		* @param[in] h 高
		*/
		static void resize(int w, int h);

		/**
		* @brief 清屏
		*/
		static void clear();

		/**
		* @brief 设置颜色
		* @param[in] foreColor 前景色
		* @param[in] backColor 背景色
		*/
		static void setColor(Color foreColor, Color backColor);

		/**
		* @brief 设置光标位置
		* @param[in] x x位置
		* @param[in] y y位置
		*/
		static void setCursorPos(short x, short y);

		/**
		* @brief 显示隐藏光标
		* @param[in] show 是否显示光标
		*/
		static void setCursorShow(bool show);

		/**
		* @brief 无回显无缓冲非堵塞地从控制台读取一个字符
		* @return 读取到的字符
		* @note 如果调用时无输入字符，则返回0
		*/
		static char getchar();
		/**
		* @brief 设置控制台字符大小
		*/
		static void setCharSize(short size);
	};
}
#endif // Console_h__