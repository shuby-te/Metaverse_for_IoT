#include "InMemoryStore.h"

InMemoryStore::InMemoryStore() 
{
    storage = map<string, string>();
}

bool InMemoryStore::put(string label, string data) 
{
    storage[label] = data;
    return true;
}

string InMemoryStore::get(string label) 
{
    return storage[label];
}

vector<string> InMemoryStore::list() 
{
    vector<string> keys;
    for (const auto& entry : storage) 
    {
        keys.push_back(entry.first);
    }
    sort(keys.begin(), keys.end());
    return keys;
}

bool InMemoryStore::exists(string label) 
{
    return storage.find(label) != storage.end();
}

bool InMemoryStore::remove(string label) 
{
    storage.erase(label);
    return true;
}