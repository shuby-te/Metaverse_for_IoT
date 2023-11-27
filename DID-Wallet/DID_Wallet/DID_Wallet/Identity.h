#ifndef IDENTITY_H
#define IDENTITY_H

#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "IdentityType.h"
using namespace std;

class Identity
{
private:
    int version;
    IdentityType type;
    string id;

public:
    Identity();
    Identity(int version, IdentityType type, string id);
    virtual ~Identity();

    int getVersion();
    void setVersion(int version);

    IdentityType getType();
    void setType(IdentityType type);

    string getId();
    void setId(string id);

    virtual string toJSON();
};
#endif