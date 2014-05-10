#include <time.h>
#include <fstream>
#include <iostream>
#include "rsa.h"
#include <stdio.h>
#include <string.h>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
inline void ecrire (std::vector <byte> str)
{
        for(int i = 0; i < str.size(); i++)
            std::cout << str[i];
}

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

    std::vector <byte> str;
    byte* rstr = "lolilol j ecris n";
    std::cout << "\nmessage de base : ";
    for(int i = 0; rstr[i] != '\0'; i++)
        {str.push_back(rstr[i]); std::cout<<rstr[i];}

    str = pubKey.enCrypt(str);
    std::cout << "\nChiffrement : ";
    ecrire(str);
    str = privKey.deCrypt(str);
    std::cout << "\ndechiffre : ";
    ecrire(str);

    std::cout << "\n\n\nSignature : ";
    str = privKey.deCrypt(str);
    ecrire(str);
    str = pubKey.enCrypt(str);
    std::cout << "\nVerification : ";
    ecrire(str);

	return 0;
}
