#include "header.h"
#include "blockchain.h"

inline void ecrire (std::vector <byte> str)
{
        for(int i = 0; i < str.size(); i++)
            std::cout << str[i];
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    {

    rsaPrivKey A;
    rsaPubKey B;
        std::cout << "\ngenerating keys" << std::endl;
        rsaGenKeys(A, B);

        std::ofstream ofs("lolkeys", std::ios::out | std::ios::binary);
        boost::archive::binary_oarchive oa(ofs);
        // write class instance to archive
        oa << A << B;
    	// archive and stream closed when destructors are called
    }

    rsaPrivKey privKey;
    rsaPubKey pubKey;

    {
        // create and open an archive for input
        std::ifstream ifs("lolkeys", std::ios::in | std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        // read class state from archive
        ia >> privKey>> pubKey;
        // archive and stream closed when destructors are called
    }
    int A = 349;


    std::cout << "int : "  << serializedString(A) << "\nKey" << serializedString(pubKey);

    std::vector <byte> message;
    char* text = "Brett: He... he's black... \nJules: Go on...\nBrett: He's bald\nJules: Does he look like a bitch?\nBrett: What?\nJules: [Shoots Brett in the shoulder] DOES HE LOOK LIKE A BITCH?\nBrett: No!\nJules: Then why you try to fuck him like a bitch?\nBrett: I didn't...\nJules: Yes you did. Yes you did! You tried to fuck him. And Marcellus Wallace don't like to be fucked by anybody except Mrs. Wallace.";
    //char* text = "hello";
    for(int i = 0; text[i] != '\0'; i++)
        message.push_back(text[i]);
    /*for(int i = 0; i<WORD_SIZE; i++)
        message.data.push_back('a');*/
    /*std::cout << "\nCoder\nI : ";
    ecrire(message);
    std::cout << "\nO : ";
    ecrire( privKey.deCrypt(pubKey.enCrypt(message)));*/

    std::cout << "\nSigner\nI : ";
    ecrire(message);
    std::cout << "\nO : ";
    ecrire(pubKey.verify(privKey.sign(message)));
    MD5 md5Hash;
    std::cout << "\nHash md5 : " << md5Hash(message.data(), message.size());

	return 0;
}
