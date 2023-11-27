#include "FileSystemStore.h"

const string FileSystemStore::fileExtension = ".id";

FileSystemStore::FileSystemStore(string path) : path(path)
{
    fs::create_directory(path);
}

bool FileSystemStore::put(string label, string data)
{
    bool result = false;

    try
    {
        ofstream file(getFilename(label));
        file << data;
        file.close();
        result = true;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
        result = false;
    }

    return result;
}

string FileSystemStore::get(string label)
{
    string data;
    try
    {
        ifstream file(getFilename(label));
        data = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }

    return data;
}

vector<string> FileSystemStore::list()
{
    vector<string> labels;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (fs::is_regular_file(entry.path()) && fs::path(entry.path()).extension() == fileExtension)
        {
            labels.push_back(fs::path(entry.path()).stem().string());
        }
    }

    sort(labels.begin(), labels.end());
    return labels;
}

bool FileSystemStore::exists(string label)
{
    fs::path filePath = getFilename(label);
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}

bool FileSystemStore::remove(string label)
{
    fs::path filePath = getFilename(label);
    return fs::remove(filePath);
}

string FileSystemStore::getFilename(string label)
{
    fs::path filePath = fs::path(path) / (label + fileExtension);
    return filePath.string();
    //return path + fs::path::preferred_separator + label + fileExtension;
}

