#include <cstdlib>
#include "Image.h"
#include "Option.h"
int main ( int argc, char** argv )
{
        char* input_file  = getOptChar ( argc, argv, "-i", NULL );
        char* output_file = getOptChar ( argc, argv, "-o", NULL );

        Image inImage;
        if ( !inImage.read ( input_file ) ) return EXIT_FAILURE;
        const int width  = inImage.getWidth();
        const int height = inImage.getHeight();

        Image outImage ( width, height );
        for ( int y = 0 ; y < height ; y++ ) {
                for ( int x = 0 ; x < width ; x++ ) {
                        Pixel p = inImage.getPixel ( x, y );
                        // TODO : add your code here.
                        const int r = 255 - p.getR();
                        const int g = 255 - p.getG();
                        const int b = 255 - p.getB();
                        p.set ( r, g, b );
                        outImage.setPixel ( x, y, p );
                }
        }
        if ( !outImage.write ( output_file ) ) return EXIT_FAILURE;
        return EXIT_SUCCESS;
}
