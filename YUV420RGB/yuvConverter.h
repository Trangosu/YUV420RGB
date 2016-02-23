#include "common.h"

typedef enum
{
	RGB = 0,
	YUV420,
	NUM_FORMATS
} FORMAT;

typedef struct
{
	int nWidth;
	int nHeight;
	FORMAT format;
	int64_t nSize;
	uint8_t *pData;
} VideoBuffer;


bool toRgb(const VideoBuffer& input, VideoBuffer *output);
