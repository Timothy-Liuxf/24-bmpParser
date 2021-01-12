#include "BmpReader.h"

bool BmpReader::Reset(const ::std::string &fileName)
{
	bmp.clear();
	::std::ifstream fin(fileName, ::std::ios::in | ::std::ios::binary);
	if (!fin)
	{
		return false;
	}

	char buf8_1, buf8_2;

	//检查开头两个字母是否是B和M
	fin.read(&buf8_1, 1);
	fin.read(&buf8_2, 1);
	if (!fin || buf8_1 != 'B' || buf8_2 != 'M')
	{
		return false;
	}

	//读取文件大小
	uint32_t bmpSize;
	fin.read((char*)&bmpSize, sizeof(bmpSize));
	if (!fin) return false;

	//读取像素点开始位置
	uint32_t dataPos;
	fin.seekg(sizeof(uint32_t), ::std::ios::cur);	//跳过保留字	
	fin.read((char*)&dataPos, sizeof(dataPos));
	if (!fin || dataPos == 0) return false;

	//读取信息块大小
	uint32_t infoPos;
	fin.read((char*)&infoPos, sizeof(infoPos));
	if (!fin || infoPos != 0x28) return false;

	uint32_t width, height;
	fin.read((char*)&width, sizeof(width));
	fin.read((char*)&height, sizeof(height));
	if (!fin) return false;

	uint16_t buf16;
	//读取，恒为1
	fin.read((char*)&buf16, sizeof(buf16));
	if (!fin || buf16 != 1) return false;

	//读取位图的位数，恒为24
	fin.read((char*)&buf16, sizeof(buf16));
	if (!fin || buf16 != 24) return false;

	fin.seekg(dataPos, ::std::ios::beg);

	//计算每一行的像素数
	unsigned int rowSize = width * (uint64_t)3;
	int remainder;	//每行的补足字节
	if (rowSize % 4)
	{
		remainder = 4 - rowSize % 4;
		rowSize += 4 - (rowSize % 4);
	}
	else remainder = 0;

	//读入像素信息
	unsigned int bufSize = rowSize * height + 4;
	char *bmpBuf = new char[bufSize];
	fin.read(bmpBuf, bmpSize - dataPos);
	if (!fin)
	{
		delete[] bmpBuf;
		return false;
	}

	try
	{
		bmp.resize(height, OneRowBmpMap(width));
	}
	catch (...)
	{
		delete[] bmpBuf;
		return false;
	}

	char *tmp = bmpBuf;
	for (int i = height - 1; i >= 0; --i)
	{
		for (int j = 0; j < width; ++j)
		{
			bmp[i][j].b = *tmp++;
			bmp[i][j].g = *tmp++;
			bmp[i][j].r = *tmp++;
		}
		tmp += remainder;
	}

	delete[] bmpBuf;
	fin.close();
	return true;
}
