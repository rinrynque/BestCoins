#ifndef BLOCKCHAIN_H_INCLUDED
#define BLOCKCHAIN_H_INCLUDED

#include <vector>
#include <iostream>
#include <gmpxx.h>
#include "rsa.h"

struct OutPoint
{
    uint64_t txNumber;
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
    uint32_t in_count;
    std::vector <Tx_in> inputs;
    uint32_t out_count;
    std::vector <Tx_out> outputs;

};

struct Block
{
    uint64_t prevBlock;
    uint32_t timestamp;
    uint32_t nonce;
    std::vector <Tx> txns;
};


#endif // BLOCKCHAIN_H_INCLUDED
