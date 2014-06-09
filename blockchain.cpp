#include "blockchain.h"

//std::string serializedString (const rsaPubKey object)


BlockChain::BlockChain():blockChain(NULL, 0)
{

}
BlockChain::~BlockChain()
{
    try
    {
        // Close the database
        blockChain.close(0);
// DbException is not subclassed from std::exception, so
// need to catch both of these.
    }
    catch(DbException &e)
    {
        // Error handling code goes here
    }
    catch(std::exception &e)
    {
        // Error handling code goes here
    }
}

void BlockChain::open()
{
    try
    {
// Open the database
        blockChain.open(NULL, // Transaction pointer
                        "blockchain.db", // Database file name
                        NULL, // Optional logical database name
                        DB_HASH, // Database access method
                        DB_CREATE, // Open flags
                        0); // File mode (using defaults)
// DbException is not subclassed from std::exception, so
// need to catch both of these.
    }
    catch(DbException &e)
    {
        std::cout << "\nErreur a l'ouverture de la base : ";
    }
    catch(std::exception &e)
    {
// Error handling code goes here
    }
}

bool BlockChain::validateBlock()
{
    Block block;
    for (int i = 0; i<= block.txns.size(); i++)
    {
        /*if(!(block.txns)[i])
            return false;*/
    }
    return true;
}

/*bool BlockChain::validateTx(Tx transaction)
{
    int outSum = 0, inSum = 0;

    /*for (int i = 0; i < transaction.inputs.size(); i++)
    {
        inSum += inputs[i];
        ///Check signature
        if(inputs[i].sig != )
            return false;
    }*/
/*for(int i = 0; i < transaction.outputs.size(); i++)
{
    outSum += transaction.outputs[i].value;
}
if(inSum < outSum)
    return false;

return true;
}
*/
