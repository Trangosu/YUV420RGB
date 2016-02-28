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
	std::ifstream file("grb_2.mpg", std::ios::binary);
	
	Decoder decoder;

	if (!file.is_open())
		return;

   //TODO: This will be an issue with big files, but we'll see later

   std::streampos nFileSize;
   
   nFileSize = file.tellg();
   file.seekg(0, std::ios::end);
   nFileSize = file.tellg() - nFileSize;

   file.seekg(0);

   uint8_t *pData = new uint8_t[nFileSize];

	file.read(reinterpret_cast<char *>(pData), nFileSize);
		
	decoder.decode(pData, nFileSize);

   file.close();
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