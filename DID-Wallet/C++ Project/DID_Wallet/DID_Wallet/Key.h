#ifndef KEY_H
#define KEY_H

#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "KeyType.h"
using namespace std;

using json = nlohmann::json;

class Key
{
private:
    string id;
    KeyType type;
    string privateKeyHex;
    string publicKeyHex;

public:
    Key();
    Key(string id, KeyType type, string privateKeyHex, string publicKeyHex);

    void setId(string id);
    string getId();

    void setType(KeyType type);
    KeyType getType();

    void setPrivateKeyHex(string privateKeyHex);
    string getPrivateKeyHex();

    void setPublicKeyHex(string publicKeyHex);
    string getPublicKeyHex();

    string toJSON();
    static Key fromJSON(string jsonKey);
};
#endif