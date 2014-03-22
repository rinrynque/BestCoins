#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <gmpxx.h>

struct keyPair
{
    mpz_class rsaModulus;
    mpz_class rsaPublicKey;
    mpz_class rsaPrivateKey;
};

keyPair generateKeys();

mpz_class crypt(mpz_class M, keyPair keys);
mpz_class deCrypt(mpz_class C, keyPair keys);

mpz_class sign(mpz_class M, keyPair keys);
mpz_class authenticate(mpz_class S, keyPair keys);


#endif // RSA_H_INCLUDED
