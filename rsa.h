#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include "boost_serialization.h"
#include <ctime>
#include <cassert>
#include <vector>


#define KEY_SIZE 1024 //en bits, à prendre supérieur à 512
#define WORD_SIZE_C ((KEY_SIZE)/8)
#define WORD_SIZE (WORD_SIZE_C-1)
#define PRIM_SIZE (KEY_SIZE/2)

typedef char byte;

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
    mpz_class sign(mpz_class M);
    byte*  deCrypt(byte*  c_message); //c_message doit faire WORD_SIZE_C de long
    byte* sign(byte*  message);
    std::vector <byte>  deCrypt(std::vector <byte>  c_message);
    std::vector <byte>  sign(std::vector <byte>  message);
};

class rsaPubKey : public rsaKey
{
public:
    mpz_class crypt(mpz_class M);
    mpz_class authenticate(mpz_class S);
    byte*  crypt(byte*  message); //message doit faire WORD_SIZE de long
    byte*  authenticate(byte*  certificate);
    std::vector <byte>  crypt(std::vector <byte>  message);
    std::vector <byte>  authenticate(std::vector <byte>  certificate);
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);
