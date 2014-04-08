#include "rsa.h"

rsaPrivKey::rsaPrivKey()
{
    mod =0 ;
    value = 0;
}
rsaPrivKey::~rsaPrivKey()
{

}

rsaPubKey::rsaPubKey()
{
    mod =0 ;
    value = 0;
}
rsaPubKey::~rsaPubKey()
{

}

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey)
{

    uint8_t raw_P[PRIM_SIZE/8];
    uint8_t raw_Q[PRIM_SIZE/8];
    for(int i = 1; i <= PRIM_SIZE/8; i++)
    {
        raw_P[i] = rand()%256;
        raw_Q[i] = rand()%256;
    }

    mpz_class  P, Q, phi;
    mpz_import(P.get_mpz_t(), sizeof(raw_P), 1, sizeof(raw_P[0]), 0, 0, raw_P);
    mpz_import(Q.get_mpz_t(), sizeof(raw_Q), 1, sizeof(raw_Q[0]), 0, 0, raw_Q);

    mpz_nextprime(P.get_mpz_t(), P.get_mpz_t());
    mpz_nextprime(Q.get_mpz_t(), Q.get_mpz_t());
    mpz_class N, E, D;

    N = P * Q;

    phi = (P-1)*(Q-1);

    bool isPrimeWithPhi = false;
    D = 65535;

    while(!isPrimeWithPhi)
    {
        D += 2;
        mpz_class gcd;
        mpz_gcd(gcd.get_mpz_t(), D.get_mpz_t(), phi.get_mpz_t());

        isPrimeWithPhi = (gcd == 1);
    }
    mpz_invert(E.get_mpz_t(), D.get_mpz_t(), phi.get_mpz_t());

    pubKey.setValue(D,N);
    privKey.setValue(E,N);
}

void rsaPrivKey::setValue(mpz_class E, mpz_class N)
{
    value = E;
    if(N != 0)
        mod = N;
}

void rsaPubKey::setValue(mpz_class D, mpz_class N)
{
    value = D;
    if(N != 0)
        mod = N;
}

mpz_class rsaPubKey::crypt(const mpz_class M)
{
    mpz_class C;
    mpz_powm(C.get_mpz_t(), M.get_mpz_t(), value.get_mpz_t(), mod.get_mpz_t());
    return C;
}

mpz_class rsaPrivKey::deCrypt(const mpz_class C)
{
    mpz_class M;
    mpz_powm(M.get_mpz_t(), C.get_mpz_t(), value.get_mpz_t(), mod.get_mpz_t());
    return M;
}


mpz_class rsaPrivKey::sign(const mpz_class M)
{
    mpz_class S;
    mpz_powm(S.get_mpz_t(), M.get_mpz_t(), value.get_mpz_t(), mod.get_mpz_t());
    return S;
}

mpz_class rsaPubKey::authenticate(const mpz_class S)
{
    mpz_class M;
    mpz_powm(M.get_mpz_t(), S.get_mpz_t(), value.get_mpz_t(), mod.get_mpz_t());
    return M;
}
