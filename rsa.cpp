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
    }
    while(mpz_sizeinbase(N.get_mpz_t(), 2) != KEY_SIZE );

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

mpz_class rsaPubKey::enCrypt(const mpz_class M)
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

rsaCData rsaPubKey::enCrypt(std::vector <byte> message)
{
    rsaCData c_message;
    c_message.length = message.size();
    while(message.size()%WORD_SIZE != 0)
        message.push_back(0);

    for(int i = 0; i < message.size()/WORD_SIZE; i++)
    {
        mpz_class numb;
        mpz_import(numb.get_mpz_t(), WORD_SIZE, -1, 1, -1, 0, &(message[i*WORD_SIZE]));
        c_message.data.push_back(enCrypt(numb));
    }

    return c_message;
}
std::vector <byte> rsaPrivKey::deCrypt(rsaCData c_message)
{
    std::vector <byte> message;

    for (int i = 0; i < c_message.data.size(); i++)
    {
        mpz_class numb = deCrypt(c_message.data[i]);

        byte* data = new byte[WORD_SIZE]();
        size_t len;
        mpz_export(data, &len, -1,1,-1,0,numb.get_mpz_t());
        if(len > WORD_SIZE)
            std::cout << "\nalerte 2 " << len << ":" << WORD_SIZE;

        for(int j = 0; j < WORD_SIZE; j++)
            message.push_back(data[j]);
        delete data;
    }
    while(message.size() > c_message.length)
        message.pop_back();

    return message;
}

std::vector <byte>  rsaPubKey::verify(rsaCData  c_message)
{
    std::vector <byte> message;

    for (int i = 0; i < c_message.data.size(); i++)
    {
        mpz_class numb = enCrypt(c_message.data[i]);

        byte* data = new byte[WORD_SIZE]();
        size_t len;
        mpz_export(data, &len, -1,1,-1,0,numb.get_mpz_t());
        if(len > WORD_SIZE)
            std::cout << "\nalerte 2 " << len << ":" << WORD_SIZE;

        for(int j = 0; j < WORD_SIZE; j++)
            message.push_back(data[j]);
        delete data;
    }
    while(message.size() > c_message.length)
        message.pop_back();

    return message;
}

rsaCData  rsaPrivKey::sign(std::vector <byte>  message)
{
    rsaCData c_message;
    c_message.length = message.size();
    while(message.size()%WORD_SIZE != 0)
        message.push_back(0);

    for(int i = 0; i < message.size()/WORD_SIZE; i++)
    {
        mpz_class numb;
        mpz_import(numb.get_mpz_t(), WORD_SIZE, -1, 1, -1, 0, &(message[i*WORD_SIZE]));
        c_message.data.push_back(deCrypt(numb));
    }

    return c_message;
}
