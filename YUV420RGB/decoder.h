#include "common.h"

class Decoder
{
	public :
		Decoder();
		void decode(uint8_t *pBuffer, int nBufferSize);

	private :
		typedef struct
		{
			unsigned int horizontal_size_value;
			unsigned int vertical_size_value;
			int aspect_ratio_information;
			int frame_rate_code;
			int bit_rate_value;
			bool marker_bit;
			int vbv_buffer_size_value;
			bool constrained_parameters_flag;
			bool load_intra_quantiser_matrix;
			uint8_t load_non_intra_quantiser_matrix[64];
			uint8_t non_intra_quantiser_matrix[64];

		} MPEG2_SEQUENCE_HEADER;

	private :
		bool decodeSequenceHeader(const uint8_t *pBuffer, int nBufferSize);

	private :
		int m_nDataSize;
		uint8_t *m_pData;

};