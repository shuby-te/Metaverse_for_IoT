#ifndef DIDWALLET_H
#define DIDWALLET_H

#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "TestDID.h"
#include "FileSystemStore.h"
#include "InMemoryStore.h"
#include "IStore.h"
#include "Identity.h"
#include "IdentityType.h"
using namespace std;

using json = nlohmann::json;

class DIDWallet
{
private:
    IStore* store;

public:
    DIDWallet();
    DIDWallet(IStore* store);
    ~DIDWallet();

    void put(string label, Identity* id);

    Identity* get(string label);

    void remove(string label);

    bool exists(string label);

    vector<string> list();

    IdentityType StringToIdentityType(string type);
};
#endif