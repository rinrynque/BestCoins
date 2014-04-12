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




    /*{

    rsaPrivKey A;
    rsaPubKey B;
        std::cout << "generating keys\n" << std::endl;
        rsaGenKeys(A, B);

        std::ofstream ofs("lolkeys", std::ios::out | std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        // write class instance to archive
        oa << A << B;
    	// archive and stream closed when destructors are called
    }*/

    rsaPrivKey privKey;
    rsaPubKey pubKey;
    mpz_class A(0);
    privKey.setValue(A, A);
    pubKey.setValue(A,A);

    {
        // create and open an archive for input
        std::ifstream ifs("lolkeys", std::ios::in | std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        // read class state from archive
        ia >> privKey>> pubKey;
        // archive and stream closed when destructors are called
    }

    mpz_class M = 349;
    mpz_class C = pubKey.crypt(M);

    std::cout << "\n------------\nnombre a chiffrer : " << M << "\nnombre chiffre : " << C << "\ndechiffre : " << privKey.deCrypt(C);
    mpz_class S = privKey.sign(M);
    std::cout << "\n------------\nnombre a signer : " << M << "\nsignature : " << S << "\nverification : \n" << pubKey.authenticate(S);

	return 0;
}
