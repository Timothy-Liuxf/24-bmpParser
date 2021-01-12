#ifndef CHAR_SHOWER_H

#define CHAR_SHOWER_H

#include "BmpReader.h"
#include <iostream>

class CharShower
{
public:

	CharShower(const ::std::string &bmpName, unsigned int rows, unsigned int cols = 0, ::std::ostream &out = ::std::cout) : out(out), bmpRr(bmpName), rows(rows), cols(cols) {}

	bool Print();

	bool Reset(const ::std::string &bmpName) { return bmpRr.Reset(bmpName); }

	const BmpReader &GetBmpReader() const { return bmpRr; }

private:

	unsigned int rows;
	unsigned int cols;
	BmpReader bmpRr;
	::std::ostream &out;

	constexpr static int HashFunc(int r, int g, int b);

	static const ::std::vector<char> hashChar;

};

#endif //!CHAR_SHOWER_H
