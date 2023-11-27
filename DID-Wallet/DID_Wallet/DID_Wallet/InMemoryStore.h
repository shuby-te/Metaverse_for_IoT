#ifndef INMEMORYSTORE_H
#define INMEMORYSTORE_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "IStore.h";
using namespace std;

class InMemoryStore : public IStore 
{
private:
    map<string, string> storage;    //<label, data>

public:
    InMemoryStore();

    bool put(string label, string data) override;

    string get(string label) override;

    vector<string> list() override;

    bool exists(string label) override;

    bool remove(string label) override;
};
#endif