#ifndef __IMAGE_H__
#define __IMAGE_H__ 1
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Bmp.h"
#include "Pixel.h"
// 画像を読み書きするクラス
class Image
{
private:
        std::vector< std::vector<Pixel> > _pixels;
        int _width;
        int _height;
public:
        Image ( const int width = 0, const int height = 0 ) {
                this->init ( width, height );
                return;
        }
        // コピーコンストラクタ
        Image ( const Image& that ) {
                this->copy ( that );
                return;
        }
        virtual ~Image ( void ) {
                return;
        }
        // =オペレータ
        Image& operator = ( const Image& that ) {
                this->copy ( that );
                return *this;
        }

        //(width, height)の大きさの画像用配列を確保(中はすべて0)
        void init ( const int width, const int height ) {
                this->_width = width;
                this->_height = height;
                this->_pixels.assign ( this->getHeight(), std::vector<Pixel> ( this->getWidth() , Pixel() ) );
                return;
        }
        // 配列を削除する
        void clear ( void ) {
                this->_width = 0;
                this->_height = 0;
                this->_pixels.clear();
                return;
        }

        // 画像の高さを得る
        int getHeight ( void ) const {
                return this->_height;
        }
        // 画像の幅を得る
        int getWidth ( void ) const {
                return this->_width;
        }

        Pixel getPixel ( const int w, const int h ) const {
                return this->_pixels[h][w];
        }

        void setPixel ( const int w, const int h, const Pixel& p ) {
                this->_pixels[h][w] = p;
                return;
        }

        bool isValid ( const int w , const int h ) const {
                if ( w < 0 ) return false;
                if ( this->getWidth() <= w ) return false;
                if ( h < 0 ) return false;
                if ( this->getHeight() <= h ) return false;
                return true;
        }

        bool read ( const char* filename ) {
		if( filename == NULL) {
			std::cerr<<"No filename is given for input image."<<std::endl;
			return false;
		}
                std::ifstream fin ( filename, std::ios::binary ); // バイナリモードで開く

                if ( !fin.is_open() ) {
                        std::cerr << filename << " cannot be opened. Exit." << std::endl;
                        return false;
                }

                int width, height;
                bool isMirrored;
                if ( !this->read_header ( fin, width, height, isMirrored ) ) {
                        std::cerr << "Invalid Header" << std::endl;
                        return false;
                }
                this->init ( width, height );
                const int bytePerLine = static_cast<int> ( ( this->getWidth() * 3 + 3 ) / 4 * 4 );

                if ( width <= 0 || height <= 0 ) {
                        std::cerr << "Invalid width and height" << std::endl;
                        return false;
                }

                std::vector<unsigned char> line ( bytePerLine, 0x00 );
                for ( int y = 0 ; y < height ; y++ ) {
                        fin.read ( ( char* ) & ( line[0] ), bytePerLine );
                        for ( int x = 0 ; x < width  ; x++ ) {
                                const Pixel p ( line[3*x+2], line[3*x+1], line[3*x+0] );
                                this->setPixel ( x, y, p );
                        }
                }
                return fin.good();
        }

        bool write ( const char* filename ) {
		if( filename == NULL) {
			std::cerr<<"No filename is given for the output image."<<std::endl;
			return false;
		}
                std::ofstream fout ( filename, std::ios::binary ); // バイナリモードで開く

                if ( !fout.is_open() ) {
                        std::cerr << filename << " cannot be opened. Exit." << std::endl;
                        return false;
                }

                if ( !this->write_header ( fout, this->getWidth(), this->getHeight() ) ) {
                        std::cerr << "Invalid Header" << std::endl;
                        return false;
                }

                const int bytePerLine = static_cast<int> ( ( this->getWidth() * 3 + 3 ) / 4 * 4 );
                std::vector<unsigned char> line ( bytePerLine, 0x00 );
                for ( int y = 0 ; y < this->getHeight() ; y++ ) {
                        for ( int x = 0 ; x < this->getWidth() ; x++ ) {
                                Pixel p = this->getPixel ( x, y );
                                line[3*x+2] = p.getR();
                                line[3*x+1] = p.getG();
                                line[3*x+0] = p.getB();
                        }
                        fout.write ( ( char* ) & ( line[0] ), bytePerLine );
                }
                return fout.good();
        }
private:
        //以下見なくてもOK
        bool read_header ( std::ifstream& fin, int& width, int& height, bool& isMirrored ) {
                BITMAPFILEHEADER fileheader;
                fin.read ( ( char* ) ( &fileheader.bfType ), 2 );
                fin.read ( ( char* ) ( &fileheader.bfSize ), 4 );
                fin.read ( ( char* ) ( &fileheader.bfReserved1 ), 2 );
                fin.read ( ( char* ) ( &fileheader.bfReserved2 ), 2 );
                fin.read ( ( char* ) ( &fileheader.bfOffBits ), 4 );
                if ( fileheader.bfType != 0x4D42 ) return false; //'BM'

                BITMAPINFOHEADER infoheader;
                fin.read ( ( char* ) ( &infoheader.biSize ), 4 );
                fin.read ( ( char* ) ( &infoheader.biWidth ), 4 );
                fin.read ( ( char* ) ( &infoheader.biHeight ), 4 );
                fin.read ( ( char* ) ( &infoheader.biPlanes ), 2 );
                fin.read ( ( char* ) ( &infoheader.biBitCount ), 2 );
                fin.read ( ( char* ) ( &infoheader.biCompression ), 4 );
                fin.read ( ( char* ) ( &infoheader.biSizeImage ), 4 );
                fin.read ( ( char* ) ( &infoheader.biXPelsPerMeter ), 4 );
                fin.read ( ( char* ) ( &infoheader.biYPelsPerMeter ), 4 );
                fin.read ( ( char* ) ( &infoheader.biClrUsed ), 4 );
                fin.read ( ( char* ) ( &infoheader.biClrImportant ), 4 );

                width = infoheader.biWidth;
                height = infoheader.biHeight;

                if ( infoheader.biSize != 40 ) {
                        std::cerr << "Header size is not 40 " << std::endl;
                        return false;
                }
                if ( height < 0 ) {
                        isMirrored = 1;
                        height *= -1; //
                } else {
                        isMirrored = 0;
                }

                if ( infoheader.biBitCount != 24 ) {
                        std::cerr << infoheader.biBitCount << "-bit image not supported" << std::endl;
                        return false;
                }
                if ( infoheader.biCompression != 0 ) {
                        std::cerr << "Compressed images not supported" << std::endl;
                        return false;
                }
                return fin.good();
        }

        bool write_header ( std::ofstream& fout, const int width, const int height ) {

                // file header
                BITMAPFILEHEADER fileheader;
                fileheader.bfType = 0x4D42;//'BM'
                int size = 54 + height * static_cast<int> ( ( width * 3 + 3 ) / 4 * 4 );
                fileheader.bfSize = static_cast<unsigned int> ( size );
                fileheader.bfReserved1 = 0;
                fileheader.bfReserved2 = 0;
                fileheader.bfOffBits = 54;
                fout.write ( ( char* ) ( &fileheader.bfType ), 2 );
                fout.write ( ( char* ) ( &fileheader.bfSize ), 4 );
                fout.write ( ( char* ) ( &fileheader.bfReserved1 ), 2 );
                fout.write ( ( char* ) ( &fileheader.bfReserved2 ), 2 );
                fout.write ( ( char* ) ( &fileheader.bfOffBits ), 4 );


                BITMAPINFOHEADER infoheader;
                infoheader.biSize	= 40;
                infoheader.biWidth	= width;
                infoheader.biHeight	= height;
                infoheader.biPlanes	= 1;
                infoheader.biBitCount	= 24;
                infoheader.biSizeImage	= width * height * 3;
                infoheader.biClrImportant = 0;
                infoheader.biClrUsed	= 0;
                infoheader.biCompression = 0;
                infoheader.biXPelsPerMeter = 0;
                infoheader.biYPelsPerMeter = 0;

                fout.write ( ( char* ) ( &infoheader.biSize ), 4 );
                fout.write ( ( char* ) ( &infoheader.biWidth ), 4 );
                fout.write ( ( char* ) ( &infoheader.biHeight ), 4 );
                fout.write ( ( char* ) ( &infoheader.biPlanes ), 2 );
                fout.write ( ( char* ) ( &infoheader.biBitCount ), 2 );
                fout.write ( ( char* ) ( &infoheader.biCompression ), 4 );
                fout.write ( ( char* ) ( &infoheader.biSizeImage ), 4 );
                fout.write ( ( char* ) ( &infoheader.biXPelsPerMeter ), 4 );
                fout.write ( ( char* ) ( &infoheader.biYPelsPerMeter ), 4 );
                fout.write ( ( char* ) ( &infoheader.biClrUsed ), 4 );
                fout.write ( ( char* ) ( &infoheader.biClrImportant ), 4 );
                return fout.good();
        }
        void copy ( const Image& that ) {
                this->_pixels.insert ( this->_pixels.end(), that._pixels.begin(), that._pixels.end() );
                this->_width = that._width;
                this->_height = that._height;
                return;
        }
};
#endif // __IMAGE_H__
