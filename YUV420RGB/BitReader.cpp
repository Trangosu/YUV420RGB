#include "BitReader.h"

BitReader::BitReader(const uint8_t *pData, int nDataSize, bool isChangeEndianness)
	: m_nDataSize(nDataSize), m_pData(pData), m_isChangeEndianness(isChangeEndianness), m_nPosition(0)
{

}

bool BitReader::readBit()
{
	return !!readBits(1);
}

uint8_t BitReader::readByte()
{
	return static_cast<uint8_t>(readBits(8));
}

uint32_t BitReader::readBits(int nBits)
{
	static const int nMaxBits = 32;

	if (nBits > nMaxBits)
	{
		assert(!"Cannot exceed " + nMaxBits + "bits at once");
		return 0;
	}


	if (m_nPosition + nBits >= m_nDataSize)
	{
		assert(!"That's too far ! Offset asked = " + (m_nPosition + nBits) + ", max offset = " + m_nDataSize);
		m_nPosition = m_nDataSize;
		return 0;
	}

	uint32_t nValue = 0;

	memcpy(&nValue, m_pData + m_nPosition / 8, nMaxBits / 8);
	int nRemoveBits = m_nPosition - m_nPosition / 8 * 8;
	
	if (nRemoveBits + nBits > 32)
		assert(!"It's time to fix this function");
	
	m_nPosition += nBits;


	if (m_isChangeEndianness)
		nValue = changeEndianness(nValue);

	nValue = nValue << nRemoveBits;
	nValue = nValue >> (nMaxBits - nBits);


	return nValue;
}

uint32_t BitReader::changeEndianness(uint32_t x)
{
	unsigned char *s = reinterpret_cast<unsigned char *>(&x);
	return static_cast<uint32_t>(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
}

int64_t BitReader::changeEndianness(int64_t x)
{
	//const int high_part = changeEndianness(static_cast<int>(x >> 32));
	//const int low_part = changeEndianness(static_cast<int>(x & 0xFFFFFFFFLL));

	//return (static_cast<int64_t>(low_part) << 32) | high_part;
	return  0;
}