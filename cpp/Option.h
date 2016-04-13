#ifndef __OPTION_H__
#define __OPTION_H__ 1
#include <cstdlib>
//#ifdef __CYGWIN__
#include <cstring>
//#else
#include <string>
//#endif
bool isKeyExisted ( int argc, char** argv, std::string key )
{
        for ( int i = 1 ; i < argc ; i++ ) {
                if ( strcmp ( argv[i], key.c_str() ) == 0 ) return true;
        }
        return false;
}
int getOptInt ( int argc, char** argv, std::string key , int defaultValue = 0 )
{
        for ( int i = 1 ; i < argc - 1; i++ ) {
                if ( strcmp ( argv[i], key.c_str() ) == 0 ) return atoi ( argv[i+1] );

        }
        return defaultValue;
}
short getOptShort ( int argc, char** argv, std::string key , short defaultValue = 0 )
{
        for ( int i = 1 ; i < argc - 1; i++ ) {
                if ( strcmp ( argv[i], key.c_str() ) == 0 ) return static_cast<short> ( atoi ( argv[i+1] ) );

        }
        return defaultValue;
}
double getOptDouble ( int argc, char** argv, std::string key, int defaultValue = 0.0 )
{
        for ( int i = 1 ; i < argc - 1; i++ ) {
                if ( strcmp ( argv[i], key.c_str() ) == 0 ) return atof ( argv[i+1] );
        }
        return defaultValue;
}
char* getOptChar ( int argc, char** argv, std::string key , char* defaultValue = NULL )
{
        for ( int i = 1 ; i < argc - 1; i++ ) {
                if ( strcmp ( argv[i], key.c_str() ) == 0 ) return argv[i+1];
        }
        return defaultValue;
}
#endif //__OPTION_H__
