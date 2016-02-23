#include "yuvConverter.h"


bool yuv420ToRgb(const VideoBuffer& input, VideoBuffer *output)
{
	/* -- Sanity checks -- */

	if (!input.pData)
		return false;

	if (input.nWidth % 2 != 0 || input.nHeight % 2 != 0)
	{
		assert(!"Width and height must be multiples of 2 in yuv420");
		return false;
	}

	if (static_cast<int64_t>(input.nWidth) * input.nHeight * 3 / 2 != input.nSize)
	{
		assert(!"Unexpected size of buffer");
		return false;
	}

	/* -- Init VideoBuffer structure -- */

	output->nHeight = input.nHeight;
	output->nWidth = input.nWidth;
	output->nSize = output->nWidth * output->nHeight * 3;
	output->pData = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * output->nSize));

	if (!output->pData)
	{
		assert(!"Malloc of " + output->nSize + "bytes failed: Not enough memory");
		return false;
	}

	/* -- Do the actual conversion -- */

	double r, g, b;
	int y, cr, cb;

	for (int i = 0; i < output->nHeight; ++i)
	{
		for (int j = 0; j < output->nWidth; ++j)
		{
			y = input.pData[i * input.nWidth + j];
			cr = input.pData[input.nWidth * input.nHeight + j / 2 + i / 2 * input.nWidth];
			cb = input.pData[input.nWidth * input.nHeight * 3 / 2 + j / 2 + i / 2 * input.nWidth];


			r = y + (1.4065 * (cr - 128));
			g = y - (0.3455 * (cb - 128)) - (0.7169 * (cr - 128));
			b = y + (1.7790 * (cb - 128));

			r = CLIP(r, 0, 255);
			g = CLIP(g, 0, 255);
			b = CLIP(b, 0, 255);

			output->pData[(i * input.nWidth + j) * 3] = static_cast<uint8_t>(r);
			output->pData[(i * input.nWidth + j) * 3 + 1] = static_cast<uint8_t>(g);
			output->pData[(i * input.nWidth + j) * 3 + 2] = static_cast<uint8_t>(b);
		}
	}

	return true;
}

bool toRgb(const VideoBuffer& input, VideoBuffer *output)
{
	memset(output, 0, sizeof(VideoBuffer));

	switch (input.format)
	{
	case YUV420:
		return yuv420ToRgb(input, output);
	default:
		assert(!"Unsupported format");
		return false;
	}
}
