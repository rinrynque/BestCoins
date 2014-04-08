/*#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED
*/
#include <gmpxx.h>

#define KEY_SIZE 1024 //en bits, à prendre supérieur à 512
#define PRIM_SIZE KEY_SIZE/2

class rsaPrivKey
{
public :
    rsaPrivKey();
    ~rsaPrivKey();

    mpz_class deCrypt(const mpz_class C);
    mpz_class sign(const mpz_class M);

    void setValue(mpz_class E, mpz_class N = -1);

private:
    mpz_class mod;
    mpz_class value;
};

class rsaPubKey
{
public:
    rsaPubKey();
    ~rsaPubKey();

    mpz_class crypt(const mpz_class M);
    mpz_class authenticate(const mpz_class S);

    void setValue(mpz_class D, mpz_class N = -1);

private :
    mpz_class mod;
    mpz_class value;
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);


//#endif // RSA_H_INCLUDED
