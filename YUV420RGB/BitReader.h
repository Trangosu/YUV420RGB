#include "common.h"

class BitReader
{
public:
	BitReader(const uint8_t *pData, int nSize, bool isChangeEndianness = true);

	bool readBit();
	uint8_t readByte();
	uint32_t readBits(int nBits); /* Read up to a maximum of 32 bits */

public :
	static uint32_t changeEndianness(uint32_t x);
	static int64_t changeEndianness(int64_t x);

private:
	int m_nDataSize;
	const uint8_t *m_pData;
	bool m_isChangeEndianness;

	int m_nPosition;
};