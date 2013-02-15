#ifndef __BMP_H__
#define __BMP_H__ 1
//http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx
typedef struct tagBITMAPFILEHEADER {
        unsigned short bfType;
        unsigned int	 bfSize;
        unsigned short bfReserved1;
        unsigned short bfReserved2;
        unsigned int	 bfOffBits;
} BITMAPFILEHEADER;

//http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx
typedef struct tagBITMAPINFOHEADER {
        unsigned int biSize;
        int  biWidth;
        int  biHeight;
        unsigned short  biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        int  biXPelsPerMeter;
        int  biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
} BITMAPINFOHEADER;
#endif// __BMP_H__
