#ifndef TESTDID_H
#define TESTDID_H

#pragma once
#include <string>
#include <iostream>
#include "Identity.h"
#include "Key.h"
using namespace std;

class TestDID : public Identity 
{
private:
    Key key;

public:
    TestDID(string id, Key key);

    Key getKey();
    void setKey(Key key);
    string toJSON() override;
    static TestDID fromJSON(nlohmann::json json);
};
#endif