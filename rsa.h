#include <gmpxx.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/gmpxx_boost_serialization.hpp>

#define KEY_SIZE 2048 //en bits, à prendre supérieur à 512
#define PRIM_SIZE KEY_SIZE/2
typedef unsigned char byte;

class rsaPrivKey
{

public :
    rsaPrivKey();
    virtual ~rsaPrivKey();

    inline void setValue(mpz_class E, mpz_class N)
    {
        if(N != 0)
            mod = N;
        value = E;
    }

    mpz_class deCrypt(mpz_class C);
    mpz_class sign(mpz_class M);


private:
    mpz_class mod;
    mpz_class value;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        /*std::string  s_mod = mod.get_str(26);
        std::string  s_value = value.get_str(26);

        ar & s_mod & s_value;

        mod.set_str(s_mod,26);
        value.set_str(s_value,26);*/

        ar & mod & value;
    }
    /*template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        byte* raw_key = new byte[value.get_mpz_t()->_mp_size];
        mpn_get_str(raw_key, 2,value.get_mpz_t()->_mp_d, value.get_mpz_t()->_mp_size);
//        std::string s_data(raw_key);
        ar & raw_key;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        byte* s1;
        ar & s1;
        mpn_set_str(value.get_mpz_t()->_mp_d, s1, value.get_mpz_t()->_mp_size, 2);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()*/

};

class rsaPubKey
{
public:
    rsaPubKey();
    virtual ~rsaPubKey();

    inline void setValue(mpz_class D, mpz_class N=0)
    {
        if(N != 0)
            mod = N;
        value = D;
    }

    mpz_class crypt(mpz_class M);
    mpz_class authenticate(mpz_class S);

private :
    mpz_class mod;
    mpz_class value;
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);
