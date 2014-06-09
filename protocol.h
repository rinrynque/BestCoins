#pragma once
#include <vector>
#include <string>
#include "rsa.h"

struct OutPoint
{
    std::string txHash;
    uint32_t index;
};

struct Tx_in
{
    OutPoint previous_output; //le lien vers l'output (ie l'endroit ou est le grisbi)
    rsaCData sig; /*la signature (cf algorithme RSA) qui prouve que l'envoyeur
    (de la transaction dans laquelle l'input se trouve) a le droit d'utiliser le grisbi en question*/
};

struct Tx_out
{
    int64_t value; // valeur de l'output, en 'satoshi' (ie la quantité de grisbi contenue dans l'output)
    rsaPubKey destination;
};

struct Tx
{
  //  std::string getHash();
    std::vector <Tx_in> inputs;
    std::vector <Tx_out> outputs;

};

struct Block
{
    std::string getHash();
    std::string prevHash;
    uint32_t timestamp;
    uint32_t nonce;
    std::vector <Tx> txns;
};
