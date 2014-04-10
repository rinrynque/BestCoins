#include <gmpxx.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include "boost_serialization.h"

#define KEY_SIZE 2048 //en bits, à prendre supérieur à 512
#define PRIM_SIZE KEY_SIZE/2


class rsaPrivKey
{

public :
    rsaPrivKey();
    virtual ~rsaPrivKey();

    void setValue(mpz_class E, mpz_class N);

    mpz_class deCrypt(mpz_class C);
    mpz_class sign(mpz_class M);


private:
    mpz_class mod;
    mpz_class value;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        std::string  s_mod = mod.get_str(26);
        std::string  s_value = value.get_str(26);

        ar & s_mod & s_value;

        mod.set_str(s_mod,26);
        value.set_str(s_value,26);
    }
    /*template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        char raw_key[2*KEY_SIZE]= "";
        char raw_mod[2*KEY_SIZE] = "";
        size_t l_key = 0, l_mod = 0;

        mpz_export (raw_key, &l_key, 1, 1, 1, 0, value.get_mpz_t());
        mpz_export (raw_mod, &l_mod, 1, 1, 1, 0, mod.get_mpz_t());
        std::string s_data(raw_mod, l_mod);

        ar << s_data;
        s_data.assign(raw_key, l_key);
        ar << s_data;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        std::string s1,s2;
        ar >> s1;
        mpz_import(mod.get_mpz_t(), s1.length(), 1, 1, 1, 0, s1.c_str());

        ar >> s2;
        mpz_import(value.get_mpz_t(), s1.length(), 1, 1, 1, 0, s2.c_str());
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()*/

};

class rsaPubKey
{
public:
    rsaPubKey();
    virtual ~rsaPubKey();

    void setValue(mpz_class D, mpz_class N);

    mpz_class crypt(mpz_class M);
    mpz_class authenticate(mpz_class S);

private :
    mpz_class mod;
    mpz_class value;
};

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey);
