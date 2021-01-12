#include "CharShower.h"

const ::std::vector<char> CharShower::hashChar
{
	' ', '.', ',', '\'', '_', ':', ';', '\"', '\\', '/', '*', '!', '~', '^', '`', '+', '-', '=', '*', '&', '%', '(', ')', '#', '@', '<', '>', '?', '!', '[', ']', '{', '}', '|',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

constexpr int CharShower::HashFunc(int r, int g, int b)
{
	return r * r + g * g + b * b;
}

bool CharShower::Print()
{
	if (!bmpRr.Valid()) return false;
	if (rows == 0) return false;
	int rowItv = bmpRr.Height() / rows;
	int colItv = 0;
	if (cols == 0) colItv = rowItv;
	else colItv = bmpRr.Width() / cols;

	if (rowItv == 0) rowItv = 1;
	if (colItv == 0) colItv = 1;

	auto& bmp = bmpRr.GetBmp();

	constexpr int maxModu = CharShower::HashFunc(255, 255, 255);

	for (int i = 0; i < bmpRr.Height(); i += rowItv)
	{
		for (int j = 0; j < bmpRr.Width(); j += colItv)
		{
			//int modu = bmp[i][j].r * bmp[i][j].r + bmp[i][j].g * bmp[i][j].g + bmp[i][j].b * bmp[i][j].b;
			int modu = HashFunc(bmp[i][j].r, bmp[i][j].g, bmp[i][j].b);
			int num = modu * hashChar.size() / maxModu;
			if (num == hashChar.size()) --num;
			out.put(hashChar[num]);
		}
		out.put('\n');
	}

	out.flush();
	return true;
}
