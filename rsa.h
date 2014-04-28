#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/gmpxx_boost_serialization.hpp>
#include <ctime>

#define KEY_SIZE 1024 //en bits, à prendre supérieur à 512
#define WORD_SIZE ((KEY_SIZE)/8-1)
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
    std::string deCrypt(std::string c_message);
    std::string sign(std::string message);
};

class rsaPubKey : public rsaKey
{
public:
    mpz_class crypt(mpz_class M);
    mpz_class authenticate(mpz_class S);
    std::string crypt(std::string message);
    std::string authenticate(std::string certificate);
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);
