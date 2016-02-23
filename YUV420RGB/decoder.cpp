#include "decoder.h"
#include "BitReader.h"

int contains(const uint8_t pBuffer[], int nBufferSize, const uint8_t sequence[], int nSequenceSize)
{
	int nCurrOffset = 0;

	for (int nPosition = 0; nPosition < nBufferSize; ++nPosition)
	{
		uint8_t b = pBuffer[nPosition];
		if (b == sequence[nCurrOffset])
		{
			if (nCurrOffset == nSequenceSize - 1) 
				return nPosition - (nSequenceSize - 1);
			nCurrOffset++;
			continue;
		}

		if (nCurrOffset == 0) 
			continue;

		nPosition -= nCurrOffset;
		nCurrOffset = 0;
	}

	return -1;
}

Decoder::Decoder() : m_nDataSize(0), m_pData(nullptr)
{ }

void Decoder::decode(uint8_t *pBuffer, int nBufferSize)
{
	const uint8_t startSequence[3] = { 0x00, 0x00, 0x01 };

	int index = contains(pBuffer, nBufferSize, startSequence, sizeof(startSequence));

	if (index >= 0)
	{
		std::cout << "Found start sequence !" << std::endl;
	}

	uint8_t bStartCode = pBuffer[index + 3];

	switch (bStartCode)
	{
	case 0x00: //picture_start_code
		break;
	case 0xB0: //reserved
		break;
	case 0xB1: //reserved
		break;
	case 0xB2: //user_data_start_code
		break;
	case 0xB3: //sequence_header_code
		decodeSequenceHeader(pBuffer + index, nBufferSize - index);
		break;
	case 0xB4: //sequence_error_code
		break;
	case 0xB5: //extension_start_code
		break;
	case 0xB6: //reserved
		break;
	case 0xB7: //sequence_end_code
		break;
	case 0xB8: //group_start_code
		break;
	}
	
}

bool Decoder::decodeSequenceHeader(const uint8_t *pBuffer, int nBufferSize)
{
	MPEG2_SEQUENCE_HEADER seqHeader;
	memset(&seqHeader, 0, sizeof(seqHeader));

	const uint8_t startSequenceHeader[4] = { 0x00, 0x00, 0x01, 0xB3 };

	if (!pBuffer || nBufferSize <= 4 || memcmp(pBuffer, startSequenceHeader, 4))
		return false;

	BitReader bitReader(pBuffer + 4, nBufferSize - 4);


	seqHeader.horizontal_size_value = bitReader.readBits(12);
	seqHeader.vertical_size_value = bitReader.readBits(12);
	seqHeader.aspect_ratio_information = bitReader.readBits(4);
	seqHeader.frame_rate_code = bitReader.readBits(4);
	seqHeader.bit_rate_value = bitReader.readBits(18);
	seqHeader.marker_bit = bitReader.readBit();
	seqHeader.vbv_buffer_size_value = bitReader.readBits(10);
	seqHeader.constrained_parameters_flag = bitReader.readBit();
	seqHeader.load_intra_quantiser_matrix = bitReader.readBit();

	return false;
}