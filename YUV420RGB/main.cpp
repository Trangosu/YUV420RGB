#include "common.h"
#include "lodepng.h"
#include "yuvConverter.h"
#include "decoder.h"
#include "BitReader.h"

void pngFile(std::string pszFilename, VideoBuffer rgb)
{
	std::vector<uint8_t> pngBuffer(rgb.nWidth * rgb.nHeight * 4);

	for (int32_t i = 0; i < rgb.nHeight; ++i)
	{
		for (int32_t j = 0; j < rgb.nWidth; ++j)
		{
			std::size_t OldPos = i * rgb.nWidth * 3 + j * 3;
			std::size_t NewPos = i * rgb.nWidth * 4 + j * 4;
			pngBuffer[NewPos + 0] = rgb.pData[OldPos + 0];
			pngBuffer[NewPos + 1] = rgb.pData[OldPos + 1];
			pngBuffer[NewPos + 2] = rgb.pData[OldPos + 2];
			pngBuffer[NewPos + 3] = 255;
		}
	}

	std::vector<std::uint8_t> imageBuffer;
	lodepng::encode(imageBuffer, pngBuffer, rgb.nWidth, rgb.nHeight);
	lodepng::save_file(imageBuffer, pszFilename);
}

void decoder(uint8_t *pBuffer)
{

}

void main()
{
	static const int nBufferSize = 50000;
	std::ifstream file("grb_2.mpg", std::ios::binary);
	uint8_t *pData = new uint8_t[nBufferSize];
	Decoder decoder;

	if (!file.is_open())
		abort();

	while (!file.eof())
	{
		file.read(reinterpret_cast<char *>(pData), nBufferSize);
		
		uint8_t a = pData[4];
		uint8_t b = pData[5];
		uint8_t c = pData[6];
		uint8_t d = pData[7];

		uint32_t test;
		memcpy(&test, &pData[4], 4);

		test = BitReader::changeEndianness(test);
		test = test >> 20;
		
		decoder.decode(pData, nBufferSize);
	}

	delete pData;
}

/*void main()
{
   std::ifstream file("tulips_yuv420_prog_planar_qcif.yuv", std::ios::binary);
   const static int nImageSize = 228096;
   uint8_t *yuv420, *pImages;

   if (!file.is_open())
      abort();

   pImages = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * nImageSize));

   yuv420 = pImages;

   file.read(reinterpret_cast<char *>(yuv420), nImageSize);

   VideoBuffer image;
   memset(&image, 0, sizeof(VideoBuffer));

   image.format = YUV420;
   image.nHeight = 144;
   image.nWidth = 176;
   image.nSize = image.nHeight * image.nWidth * 3 / 2;
   image.pData = pImages;

   for (int k = 0; k < 5; ++k)
   {
	   VideoBuffer rgb;

	   if (!toRgb(image, &rgb))
		   break;

	   pngFile("test" + std::to_string(k) + ".png", rgb);

	  image.pData = image.pData + image.nSize;
	  free(rgb.pData);
   }

   free(pImages);
   file.close();
} */