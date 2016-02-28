#include "common.h"

class Decoder
{
	public :
		Decoder();
		void decode(uint8_t *pBuffer, int nBufferSize);

	private :
      typedef enum {
         SEQUENCE_EXTENSION_ID = 1,
         SEQUENCE_DISPLAY_EXTENSION_ID = 2,
         QUANT_MATRIX_EXTENSION_ID = 3,
         SEQUENCE_SCALABLE_EXTENSION_ID = 5,
         PICTURE_DISPLAY_EXTENSION_ID = 7,
         PICTURE_CODING_EXTENSION_ID = 8,
         PICTURE_SPATIAL_SCALABLE_EXTENSION_ID = 9,
         PICTURE_TEMPORAL_SCALABLE_EXTENSION_ID = 10,
      } MPEG2_EXTENSION_START_CODE;

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
			uint8_t intra_quantiser_matrix[64];
         bool load_non_intra_quantiser_matrix;
			uint8_t non_intra_quantiser_matrix[64];

		} MPEG2_SEQUENCE_HEADER;

      typedef struct
      {
         int extension_start_code_identifier;
         uint8_t profile_and_level_indication;
         bool progressive_sequence;
         uint8_t chroma_format;
         uint8_t horizontal_size_extension;
         uint8_t vertical_size_extension;
         int bit_rate_extension;
         uint8_t marker_bit;
         int vbv_buffer_size_extension;
         bool low_delay;
         uint8_t frame_rate_extension_n;
         uint8_t frame_rate_extension_d;

      } MPEG2_SEQUENCE_EXTENSION;

      typedef struct
      {
         uint8_t video_format;
         bool colour_description;
         uint8_t colour_primaries;
         uint8_t transfer_characteristics;
         uint8_t matrix_coefficients;
         int display_horizontal_size;
         int display_vertical_size;
      } MPEG2_SEQUENCE_DISPLAY_EXTENSION;

	private :
		bool decodeSequenceHeader(const uint8_t *pBuffer, int nBufferSize, int& nSequenceSize);
      bool decodeExtensionAndUserData(const uint8_t *pBuffer, int nBufferSize, int& nSequenceSize);
      bool decodeSequenceExtension(const uint8_t *pBuffer, int nBufferSize, int& nSequenceSize);
      bool decodeSequenceDisplayExtension(const uint8_t *pBuffer, int nBufferSize, int& nSequenceSize);
      bool decodeExtension(const uint8_t *pBuffer, int nBufferSize, int& nSequenceSize);

	private :
		int m_nDataSize;
		uint8_t *m_pData;

      int m_nExtensionAndUserDataCounter;
};