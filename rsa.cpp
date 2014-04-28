#include "rsa.h"

rsaKey::rsaKey()
{
    mod =0 ;
    value = 0;
}
rsaKey::~rsaKey()
{

}

void rsaGenKeys(rsaPrivKey& privKey, rsaPubKey& pubKey)
{
    static gmp_randclass rndState(gmp_randinit_mt);
    static bool initialized = false;
        if( !initialized )
        {
            rndState.seed(time(NULL));
            initialized = true;
        }

    mpz_class  P, Q, phi, N, E, D;

    do
    {
        P = rndState.get_z_bits(PRIM_SIZE);
        Q = rndState.get_z_bits(PRIM_SIZE);


    mpz_nextprime(P.get_mpz_t(), P.get_mpz_t());
    mpz_nextprime(Q.get_mpz_t(), Q.get_mpz_t());

    N = P * Q;
    }while(mpz_sizeinbase(N.get_mpz_t(), 2)/8 > WORD_SIZE );

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
    std::cout << "\n longueur en bits du module des cles :" << mpz_sizeinbase(N.get_mpz_t(), 2);
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


std::string rsaPrivKey::deCrypt(std::string c_message)
{
    mpz_class numb(0);
    std::string d_message;
    std::cout << "\ndechiffre : "<< c_message;
    for(int i = 0; i < c_message.length()/WORD_SIZE+1; i++)
    {
        char word[WORD_SIZE]= "";
        strcpy(word,(c_message.substr(i*WORD_SIZE, WORD_SIZE)).data());
        std::cout << "i : " << i << " word : " << word;

        size_t len = c_message.substr(i*WORD_SIZE, WORD_SIZE).length();
        mpz_import (numb.get_mpz_t(), 1, 1, len, 1, 0, word);

        numb = deCrypt(numb);
        mpz_export (word, NULL, 1,WORD_SIZE, 1, 0, numb.get_mpz_t());
        d_message.append(word, WORD_SIZE);
    }
    std::cout << "\nfin dechiffre : " << d_message;
    return d_message;
}

std::string rsaPrivKey::sign(std::string message)
{
    std::string certificate;
    return certificate;
}

std::string rsaPubKey::crypt(std::string message)
{
    mpz_class numb(0);
    std::string c_message;
    std::cout << "\nchiffre : "<< message;
    for(int i = 0; i < c_message.length()/WORD_SIZE+1; i++)
    {
        char word[WORD_SIZE]= "";
        strcpy(word,(message.substr(i*WORD_SIZE, WORD_SIZE)).data());
        size_t len = message.substr(i*WORD_SIZE, WORD_SIZE).length();
        std::cout << "\n" << word;
        mpz_import (numb.get_mpz_t(), 1, 1, len, 1, 0, word);
        numb = crypt(numb);
        mpz_export (word, NULL, 1,WORD_SIZE, 1, 0, numb.get_mpz_t());
        c_message.append(word, WORD_SIZE);
    }
    std::cout << "\nfin chiffre : "<< c_message.length() << c_message;
    return c_message;
}
std::string rsaPubKey::authenticate(std::string certificate)
{
    std::string message;
    return message;
}
