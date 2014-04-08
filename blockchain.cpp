#include "blockchain.h"

bool Block::validate()
{
    bool valid = true;
    for (int i = 0; i<= (this->txns).size(); i++)
    {
        valid = (this->txns)[i].validate();
    }
}

bool Tx::validate()
{

}
