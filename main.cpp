#include <time.h>
#include <fstream>
#include <iostream>
#include "rsa.h"
#include <stdio.h>
#include <string.h>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

int main(int argc, char **argv)
{
    srand(time(NULL));
    {

    rsaPrivKey A;
    rsaPubKey B;
        std::cout << "\ngenerating keys" << std::endl;
        rsaGenKeys(A, B);

        std::ofstream ofs("lolkeys", std::ios::out | std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        // write class instance to archive
        oa << A << B;
    	// archive and stream closed when destructors are called
    }

    rsaPrivKey privKey;
    rsaPubKey pubKey;

    {
        // create and open an archive for input
        std::ifstream ifs("lolkeys", std::ios::in | std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        // read class state from archive
        ia >> privKey>> pubKey;
        // archive and stream closed when destructors are called
    }

    mpz_class A("475612384651329864512864513246512846512346513286512346513264513246513486513");
    std::cout <<"\n47 : " << privKey.deCrypt(pubKey.crypt(A));

    std::vector <byte> str;
    for(int i = 0; i < WORD_SIZE_C; i++)
        str.push_back('a');
    str = pubKey.crypt(str);
    str = privKey.deCrypt(str);

	return 0;
}
