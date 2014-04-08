#include <time.h>
#include <fstream>
#include <iostream>
#include "rsa.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    std::cout << "generating keys" << std::endl;

    rsaPrivKey privKey;
    rsaPubKey pubKey;

    rsaGenKeys(privKey, pubKey);

    mpz_class M = 349;
    mpz_class C = pubKey.crypt(M);

    std::cout << "\n------------\nnombre a chiffrer : " << M << "\nnombre chiffre : " << C << "\ndechiffre : " << privKey.deCrypt(C);
    mpz_class S = privKey.sign(M);
    std::cout << "\n------------\nnombre a signer : " << M << "\nsignature : " << S << "\nverification : \n" << pubKey.authenticate(S);

	return 0;
}
