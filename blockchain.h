#pragma once

#include <gmpxx.h>
#include <db_cxx.h>
#include <string>
#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "protocol.h"
#include "rsa.h"
#include "md5.h"

//std::string serializedString (const rsaPubKey object);
template<typename type> std::string serializedString (const type object);
template<typename type> std::string serializedString (const type object)
{
    std::stringstream stream;
    boost::archive::text_oarchive oa(stream);
    oa << object;
    return stream.str();
}

class BlockChain
{
public:
    BlockChain();
    ~BlockChain();

//    bool validateTx(Tx);
    bool validateBlock();
    void open();

private:
    Db blockChain;
};
