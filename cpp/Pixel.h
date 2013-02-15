#ifndef __PIXEL_H__
#define __PIXEL_H__ 1
#include <sstream>
#include <cstdlib>
class Pixel
{
private:
        unsigned char _r;
        unsigned char _g;
        unsigned char _b;
public:
        Pixel ( const unsigned char r = 0x00, const unsigned char g = 0x00, const unsigned char b = 0x00 ) {
                this->set ( r, g, b );
                return;
        }
        Pixel ( const Pixel& that ) {
                this->copy ( that );
                return;
        }
        Pixel& operator = ( const Pixel& that ) {
                this->copy ( that ) ;
                return *this;
        }
        virtual ~Pixel ( void ) {
                return;
        }
        void set  (  const int r,  const int g,  const int b ) {
                this->_r = static_cast<unsigned char>(r);
                this->_g = static_cast<unsigned char>(g);
                this->_b = static_cast<unsigned char>(b);
                return;
        }
        void get ( int& r, int& g, int& b ) {
                r = this->getR();
                g = this->getG();
                b = this->getB();
        }
        int getR ( void ) const {
                return this->_r;
        }
        int getG ( void ) const {
                return this->_g;
        }
        int  getB ( void ) const {
                return this->_b;
        }
        void copy ( const Pixel& that ) {
                this->_r = that._r;
                this->_g = that._g;
                this->_b = that._b;
                return;
        }
        std::string toString ( void ) {
                std::stringstream ss;
                ss << "(" <<  this->getR()  << ", " << this->getG()  << ", " << this->getB() << ")";
                return ss.str();
        }
};

Pixel operator + ( const Pixel& rhs, const Pixel& lhs )
{
        return Pixel ( rhs.getR() + lhs.getR(), rhs.getG() + lhs.getG(), rhs.getB() + lhs.getB() );
}

Pixel operator - ( const Pixel& rhs, const Pixel& lhs )
{
        return Pixel ( rhs.getR() - lhs.getR(), rhs.getG() - lhs.getG(), rhs.getB() - lhs.getB() );
}
#endif // __PIXEL_H__
