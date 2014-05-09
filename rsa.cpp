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
    }while(mpz_sizeinbase(N.get_mpz_t(), 2) != KEY_SIZE );

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
    std::cout << "\nlongueur en bits du module des cles :" << mpz_sizeinbase(N.get_mpz_t(), 2);
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


    byte*  crypt(byte*  message)
    {
        return c_message;
    } //message doit faire WORD_SIZE de long
    byte*  authenticate(byte*  certificate)
    {
        return NULL;
    }

    byte*  deCrypt(byte*  c_message)
    {
        return message;
    } //c_message doit faire WORD_SIZE_C de long
    byte* sign(byte*  message)
    {
        return NULL;
    }

std::vector <byte> rsaPubKey::crypt(std::vector <byte> message)
{
    std::cout << "\nmessage en clair :"<< std::string(&message[0], message.size());
    mpz_class numb;
    mpz_import(numb.get_mpz_t(), WORD_SIZE, -1, 1, -1, 0, &message[0]);
    numb = crypt(numb);
    byte* data = new byte[WORD_SIZE_C]();
    mpz_export(data, NULL, -1,1,-1,0,numb.get_mpz_t());

    std::vector <byte> c_message;
    for (int i = 0; i < WORD_SIZE_C; i++)
        c_message.push_back(data[i]);
    std::cout << "\n crypte : " << std::string(data, WORD_SIZE_C);
    std::cout << "\n crypte & stocke : " << std::string(&c_message[0], WORD_SIZE);

    return c_message;
}
std::vector <byte> rsaPrivKey::deCrypt(std::vector <byte> c_message)
{
    mpz_class numb;
    mpz_import(numb.get_mpz_t(), WORD_SIZE_C, -1,1,-1,0, &c_message[0]);
    numb = deCrypt(numb);

    byte* data = new byte[WORD_SIZE]();
    mpz_export(data, NULL, -1,1,-1,0,numb.get_mpz_t());
    std::vector <byte> message;
    for(int i = 0; i < WORD_SIZE; i++)
        message.push_back(data[i]);

    std::cout << "\n decrypte & stocke : " << std::string(&message[0], WORD_SIZE);
    return message;
}



std::vector <byte> rsaPrivKey::sign(std::vector <byte> message)
{
    std::vector <byte> certificate;
    return certificate;
}
std::vector <byte> rsaPubKey::authenticate(std::vector <byte> certificate)
{
    std::vector <byte> message;
    return message;
}

