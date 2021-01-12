#ifndef BMP_READER_H

#define BMP_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <cstdint>

class GetNullBmp : ::std::exception
{
public:
	virtual const char *what() const override
	{
		return "Try to get null bitmap!";
	}
};

class BmpReader
{
public:

	struct Rgb
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

private:

	using OneRowBmpMap = ::std::vector<Rgb>;
	using BmpMap = ::std::vector<OneRowBmpMap>;

public:

	BmpReader(const ::std::string &bmpName) { Reset(bmpName); }

	BmpReader(const BmpReader &src) : bmp(src.bmp) {}

	BmpReader(BmpReader &&src) noexcept : bmp(::std::move(src.bmp)) {}

	bool Reset(const ::std::string &bmpName);

	const BmpMap &GetBmp() const { if (!Valid()) throw GetNullBmp(); return bmp; }

	bool Valid() const { return bmp.size(); }

	auto Width() const { if (!Valid()) throw GetNullBmp(); return bmp[0].size(); }

	auto Height() const { if (!Valid()) throw GetNullBmp(); return bmp.size(); }

private:
	
	BmpMap bmp;
};

#endif //!BMP_READER_H
