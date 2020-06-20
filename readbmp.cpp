
#pragma warning(disable:4996)
#include "readbmp.h"

INT readBmp()
{
	delete[] bmpBuf; 
	bmpBuf = NULL; 
	std::ifstream fin(inputBmpName, std::ios::in | std::ios::binary); 
	if (!fin) return READ_FAILURE; 
	UINT8 buf8_1, buf8_2; 
	UINT16 buf16; 
	UINT32 bmpSize; //位图大小
	UINT32 dataPos;	//像素数据开始位置
	UINT32 buf32; 
	UINT32 width, height; //位图宽度和高度

	//检验开头两个字节是否是'B''M'
	fin.read((CHAR*)&buf8_1, 1); 
	fin.read((CHAR*)&buf8_2, 1);
	if (fin.eof()) 
	{
		fin.close();  
		return NOT_TWENTY_FOUR_BITMAP;
	}
	if (!(buf8_1 == 'B' && buf8_2 == 'M')) 
	{
		fin.close();
		return NOT_TWENTY_FOUR_BITMAP;
	}

	//读取文件大小
	fin.read((CHAR*)&bmpSize, sizeof(UINT32)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}
	
	//读取像素点开始的位置
	fin.seekg(sizeof(UINT32), std::ios::cur);
	fin.read((CHAR*)&dataPos, sizeof(UINT32)); 
	if (fin.eof() || dataPos == 0)
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//读取信息块大小
	fin.read((CHAR*)&buf32, sizeof(UINT32)); 
	if (fin.eof() || buf32 != 0x28) 
	{
		fin.close(); 
		return BITMAP_DESTROYED; 
	}

	//读取位图宽度和高度
	fin.read((CHAR*)&width, sizeof(UINT32)); 
	fin.read((CHAR*)&height, sizeof(UINT32)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//读取，恒为1
	fin.read((CHAR*)&buf16, sizeof(UINT16)); 
	if (fin.eof() || buf16 != 1) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//读取位图的位数，应为24
	fin.read((CHAR*)&buf16, sizeof(UINT16)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}
	if (buf16 != 24) 
	{
		fin.close();
		return NOT_TWENTY_FOUR_BITMAP;
	}

	//分配缓冲内存
	try
	{
		bmpBuf = new UCHAR[bmpSize - dataPos + 2 * sizeof(UINT32) + 5];
	}
	catch (std::bad_alloc)
	{
		bmpBuf = NULL; 
		fin.close(); 
		if (bmpSize - dataPos + 2 * sizeof(UINT32) < 0) return BITMAP_DESTROYED; 
		return BITMAP_TOO_LARGE; 
	}

	//将位图宽度和高度写入缓冲区
	UCHAR* tmp = bmpBuf; 
	memcpy((void*)tmp, (const void*)&width, sizeof(width)); 
	tmp += sizeof(width); 
	memcpy((void*)tmp, (const void*)&height, sizeof(height));
	tmp += sizeof(height); 

	//将位图像素信息写入缓冲区
	fin.read((CHAR*)tmp, bmpSize - dataPos); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//判断文件是否已经结束
	fin.read((CHAR*)&buf8_1, 1); 
	/*if (!fin.eof()) return BITMAP_DESTROYED; 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}*/
	fin.close(); 

	return READ_SUCCESS; 
}
