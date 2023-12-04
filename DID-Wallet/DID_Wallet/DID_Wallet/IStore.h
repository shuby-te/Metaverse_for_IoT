#ifndef ISTORE_H
#define ISTORE_H

#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct IStore
{
    virtual bool put(string label, string data) = 0;
    virtual string get(string label) = 0;
    virtual vector<string> list() = 0;
    virtual bool exists(string label) = 0;
    virtual bool remove(string label) = 0;
};
#endif