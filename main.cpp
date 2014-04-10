#include <time.h>
#include <fstream>
#include <iostream>
#include "rsa.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    std::cout << "generating keys" << std::endl;

    rsaPrivKey privKey;
    rsaPubKey pubKey;

    rsaGenKeys(privKey, pubKey);

    std::ofstream ofs("lolkeys");
    {
        std::cout << "lol ca plante pas\n" ;
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << privKey;
    	// archive and stream closed when destructors are called
    }
    mpz_class A(6235);
    privKey.setValue(A, 0);
    {
        std::cout << "lol ca plante" ;
        // create and open an archive for input
        std::ifstream ifs("lolkeys");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> privKey;
        // archive and stream closed when destructors are called
    }

    mpz_class M = 349;
    mpz_class C = pubKey.crypt(M);

    std::cout << "\n------------\nnombre a chiffrer : " << M << "\nnombre chiffre : " << C << "\ndechiffre : " << privKey.deCrypt(C);
    mpz_class S = privKey.sign(M);
    std::cout << "\n------------\nnombre a signer : " << M << "\nsignature : " << S << "\nverification : \n" << pubKey.authenticate(S);

	return 0;
}
