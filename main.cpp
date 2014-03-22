#include <time.h>
#include <fstream>
#include "blockchain.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    std::cout << "generating keys" << std::endl;
    keyPair keys = generateKeys();
    std::cout << "\n\n---------------\nkeys : \nmodulus : " << keys.rsaModulus <<  "\nprivate : " << keys.rsaPrivateKey
    << "\npublic : " << keys.rsaPublicKey << "\n---------------\n\n";
    mpz_class M = 349;
    mpz_class C = crypt(M, keys);

    std::cout << "\n------------\nnombre a chiffrer : " << M << "\nnombre chiffre : " << C << "\ndechiffre : " << deCrypt(C, keys);
    mpz_class S = sign(M, keys);
    std::cout << "\n------------\nnombre a signer : " << M << "\nsignature : " << S << "\nverification : \n" << authenticate(S, keys);

	return 0;
}
