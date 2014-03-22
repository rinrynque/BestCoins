#include "rsa.h"

keyPair generateKeys()
{
    keyPair keys;

    uint8_t raw_P[64];
    uint8_t raw_Q[64];
    for(int i = 1; i <= 128; i++)
    {
        raw_P[i] = rand()%256;
        raw_Q[i] = rand()%256;
    }

    mpz_class  P, Q, phi;
    mpz_import(P.get_mpz_t(), sizeof(raw_P), 1, sizeof(raw_P[0]), 0, 0, raw_P);
    mpz_import(Q.get_mpz_t(), sizeof(raw_Q), 1, sizeof(raw_Q[0]), 0, 0, raw_Q);

    mpz_nextprime(P.get_mpz_t(), P.get_mpz_t());
    mpz_nextprime(Q.get_mpz_t(), Q.get_mpz_t());
    keys.rsaModulus = P * Q;
    phi = (P-1)*(Q-1);

    bool isPrimeWithPhi = false;
    keys.rsaPrivateKey = 65535;

    while(!isPrimeWithPhi)
    {
        keys.rsaPrivateKey += 2;
        mpz_class gcd;
        mpz_gcd(gcd.get_mpz_t(), keys.rsaPrivateKey.get_mpz_t(), phi.get_mpz_t());

        isPrimeWithPhi = (gcd == 1);
    }
    mpz_invert(keys.rsaPublicKey.get_mpz_t(), keys.rsaPrivateKey.get_mpz_t(), phi.get_mpz_t());

    return keys;
}

mpz_class crypt(mpz_class M, keyPair keys)
{
    mpz_class C;
    mpz_powm(C.get_mpz_t(), M.get_mpz_t(), keys.rsaPublicKey.get_mpz_t(), keys.rsaModulus.get_mpz_t());
    return C;
}

mpz_class deCrypt(mpz_class C, keyPair keys)
{
    mpz_class M;
    mpz_powm(M.get_mpz_t(), C.get_mpz_t(), keys.rsaPrivateKey.get_mpz_t(), keys.rsaModulus.get_mpz_t());
    return M;
}


mpz_class sign(mpz_class M, keyPair keys)
{
    mpz_class S;
    mpz_powm(S.get_mpz_t(), M.get_mpz_t(), keys.rsaPrivateKey.get_mpz_t(), keys.rsaModulus.get_mpz_t());
    return S;
}
mpz_class authenticate(mpz_class S, keyPair keys)
{
    mpz_class M;
    mpz_powm(M.get_mpz_t(), S.get_mpz_t(), keys.rsaPublicKey.get_mpz_t(), keys.rsaModulus.get_mpz_t());
    return M;
}
