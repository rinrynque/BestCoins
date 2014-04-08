#ifndef BLOCKCHAIN_H_INCLUDED
#define BLOCKCHAIN_H_INCLUDED

#include <vector>
#include <iostream>
#include <gmpxx.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


struct OutPoint
{
    uint64_t txHash;
    uint32_t index;
};

struct Tx_in
{
    OutPoint previous_output; //le lien vers l'output (ie l'endroit ou est le grisbi)
    mpz_class sig; /*la signature (cf algorithme RSA) qui prouve que l'envoyeur
    (de la transaction dans laquelle l'input se trouve) a le droit d'utiliser le grisbi en question*/
};

struct Tx_out
{
    int64_t value; // valeur de l'output, en 'satoshi' (ie la quantité de grisbi contenue dans l'output)
    mpz_class pubKey;
};

struct Tx
{
    bool validate();

    std::vector <Tx_in> inputs;
    std::vector <Tx_out> outputs;

};

struct Block
{
    bool validate();

    uint64_t prevHash;
    uint32_t timestamp;
    uint32_t nonce;
    std::vector <Tx> txns;
};

#endif // BLOCKCHAIN_H_INCLUDED
