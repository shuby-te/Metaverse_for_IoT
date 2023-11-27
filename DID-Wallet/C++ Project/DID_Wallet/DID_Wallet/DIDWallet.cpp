#include "DIDWallet.h"

DIDWallet::DIDWallet()
{
    store = new InMemoryStore();
}

DIDWallet::DIDWallet(IStore* store)
{
    this->store = store;
}

DIDWallet::~DIDWallet()
{
    delete store;
}

void DIDWallet::put(string label, Identity* id)
{
    string data = id->toJSON();
    //cout << "wallet put\n";
    store->put(label, data);
}

Identity* DIDWallet::get(string label)
{
    string data = store->get(label);

    json obj = json::parse(data);

    string type = obj["type"].dump();

    Identity* id = nullptr;
    //cout << "stored data type: " + type + "\n";
    switch (StringToIdentityType(type))
    {
    case Test:
        id = new TestDID(TestDID::fromJSON(obj));
        break;

    default:
        cout << "Unsupported type: " << type << endl;
        break;
    }

    return id;
}

void DIDWallet::remove(string label)
{
    store->remove(label);
}

bool DIDWallet::exists(string label)
{
    return store->exists(label);
}

vector<string> DIDWallet::list()
{
    return store->list();
}

IdentityType DIDWallet::StringToIdentityType(string type)
{
    if (type == "\"Test\"")
        return IdentityType::Test;

    return IdentityType::NullType;
}
