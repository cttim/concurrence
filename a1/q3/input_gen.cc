#include <iostream>
using namespace std;

int main() {
    char bytes[] = {
	0x23, '\n',					// valid
	0x23, 0x23, '\n',				// valid, extra byte
	0xd7, 0x90, '\n',				// valid
	0xd7, '\n',					// invalid, missing a byte
	0xc2, 0xa3, '\n',				// valid
	'\n',						// empty line
	0xb0, '\n',					// invalid, value too large
	0xe0, 0xe3, '\n',				// invalid, second byte wrong, missing a byte
	0xe9, 0x80, 0x80, '\n',				// valid
	0xe9, 0x80, 0x80, 0xff, 0xf8, '\n',		// valid, extra 2 bytes
	0xe0, 0x93, 0x90, '\n',				// invalid, value encoded in wrong range
	0xff, 0x9A, 0x84, '\n',				// invalid, first byte, extra 2 bytes 
	0xf0, 0x90, 0x89, '\n',				// invalid, missing byte
	0xf0, 0x90, 0x89, 0x80, '\n',			// valid
	0x01, '\n',					// valid

	0xa0,'\n',                                      //invalid format error
	0x0,'\n',                                       //valid boundary case for t1
	0x7f, '\n',                                     //valid boundary case for t1

	0xdf, '\n',					//invalid missing second byte
	0xdf, 0xbf, '\n',				//valid boundary case for t2
	0xc0, 0x80, '\n',				//invalid boundary case for t2 but unicode value is not right
	0xdf, 0x40, '\n',				//invalid second byte format error

	0xef, 0x80, '\n',				//invalid missing third byte
	0xe0, 0xbf, 0x80, '\n',				//valid boundary case for t3
	0xef, 0xbf, 0x40, '\n',				//invalid third byte format error


	0xf7, 0x80, 0x80, '\n',				//invalid missing fourth byte
	0xf0, 0x80, 0x80, 0x40, '\n',			//invalid fourth byte format error 
    };
    for ( int i = 0; i < sizeof( bytes ); i += 1 ) {
	cout << bytes[i];
    }
}
