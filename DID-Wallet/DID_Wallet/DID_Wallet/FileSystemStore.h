#ifndef FILESYSTEMSTORE_H
#define FILESYSTEMSTORE_H 

#pragma once
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "IStore.h";

using namespace std;

namespace fs = std::filesystem;

class FileSystemStore : public IStore
{
private:
    static const string fileExtension;
    string path;

public:
    FileSystemStore(string path);

    bool put(string label, string data) override;

    string get(string label) override;

    vector<string> list() override;

    bool exists(string label) override;

    bool remove(string label) override;

private:
    string getFilename(string label);
};
#endif
