#include "common.h"

class BitReader
{
public:
	BitReader(const uint8_t *pData, int nSize, bool isChangeEndianness = true);

   bool readBit(bool isChangePosition = true);
	uint8_t readByte(bool isChangePosition = true);
	uint32_t readBits(int nBits, bool isChangePosition = true); /* Read up to a maximum of 32 bits */

   inline int getPositionBits()
      { return m_nPosition; }

   inline int getPosition()
      { return m_nPosition / 8; }

public :
	static uint32_t changeEndianness(uint32_t x);
	static int64_t changeEndianness(int64_t x);

private:
	int m_nDataSize;
	const uint8_t *m_pData;
	bool m_isChangeEndianness;

	int m_nPosition;
};