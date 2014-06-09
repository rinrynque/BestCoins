#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "boost_serialization.h"

#define KEY_SIZE 1024 //en bits, à prendre supérieur à 512
#define WORD_SIZE_C ((KEY_SIZE)/8)
#define WORD_SIZE (WORD_SIZE_C-1)
#define PRIM_SIZE (KEY_SIZE/2)

typedef char byte;

struct rsaCData
{
    uint32_t length;
    std::vector <mpz_class> data;
};

class rsaKey
{
public :
    rsaKey();
    ~rsaKey();
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & mod & value;
    }
    inline void setValue(mpz_class E, mpz_class N)
    {
        if(N != 0)
            mod = N;
        value = E;
    }

protected :
    mpz_class mod;
    mpz_class value;
};

class rsaPrivKey : public rsaKey
{
public :
    mpz_class deCrypt(mpz_class C);
    std::vector <byte>  deCrypt(rsaCData  c_message);
    rsaCData  sign(std::vector <byte>  c_message);
   // rsaCData  sign(std::vector <byte>  message);
};

class rsaPubKey : public rsaKey
{
public:
    mpz_class enCrypt(mpz_class M);
    rsaCData  enCrypt(std::vector <byte>  message);
    std::vector <byte>  verify(rsaCData  message);
    //std::vector <byte>  verify(rsaCData  certificate);
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);
