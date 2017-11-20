#pragma once
#include "Picture.h"
#include <fstream>
#include <string>
namespace cge
{
	class ConsolePictureReader
	{
	public:
		static std::shared_ptr<Picture> get(std::string path)
		{
			std::ifstream fileReader(path, std::ios::binary);
			char width, height,temp;
			fileReader.read(&width, sizeof(char));
			fileReader.read(&height, sizeof(char));
			std::vector<std::vector<Color>> picture;
			for (int i = 0; i < height; ++i)
			{
				std::vector<Color>line;
				for (int j = 0; j < width; ++j)
				{
					fileReader.read(&temp,sizeof(char));
					unsigned char brightness = ((unsigned char)(temp&0x8_uc)>>3)*127_uc+128_uc;
					line.emplace_back(Color(((((unsigned char)temp & 0x4_uc) >> 2) * brightness),
						((((unsigned char)temp & 0x2_uc) >> 1) * brightness),
						(((unsigned char)temp & 0x1_uc) * brightness), ((temp & 0x10_uc) >> 4)));
					//std::cout<<(int)temp<<" " << (int)line[j].r << " " << (int)line[j].g << " " << (int)line[j].b << " "<< line[j].transparent << std::endl;
				}
				picture.push_back(line);
			}
			return std::make_shared<Picture>(width,height, picture);
		}
	};
}