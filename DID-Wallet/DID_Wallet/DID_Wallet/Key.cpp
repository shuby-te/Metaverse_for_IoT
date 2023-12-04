#include "Key.h"

Key::Key() {}

Key::Key(string id, KeyType type, string privateKeyHex, string publicKeyHex)
    : id(id), type(type), privateKeyHex(privateKeyHex), publicKeyHex(publicKeyHex) {}

void Key::setId(string id) {
    this->id = id;
}

string Key::getId() {
    return id;
}

void Key::setType(KeyType type) {
    this->type = type;
}

KeyType Key::getType() {
    return type;
}

void Key::setPrivateKeyHex(string privateKeyHex) {
    this->privateKeyHex = privateKeyHex;
}

string Key::getPrivateKeyHex() {
    return privateKeyHex;
}

void Key::setPublicKeyHex(string publicKeyHex) {
    this->publicKeyHex = publicKeyHex;
}

string Key::getPublicKeyHex() {
    return publicKeyHex;
}

string Key::toJSON()
{
    json jsonKey;
    jsonKey["id"] = id;
    jsonKey["type"] = to_string(static_cast<int>(type));
    jsonKey["privateKeyHex"] = privateKeyHex;
    jsonKey["publicKeyHex"] = publicKeyHex;
    //cout << "ket toJson\n";
    return jsonKey.dump();
}

Key Key::fromJSON(string jsonStr) 
{       
    size_t found = jsonStr.find("\\\"");
    while (found != std::string::npos) {
        jsonStr.replace(found, 2, "\"");
        found = jsonStr.find("\\\"");
    }
    jsonStr = jsonStr.substr(1, jsonStr.size() - 2);

    json jsonKey = json::parse(jsonStr);

    string id = jsonKey["id"].dump();
    string typeValue = jsonKey["type"].dump();
    typeValue = typeValue.substr(1, typeValue.size() - 2);
    KeyType type = static_cast<KeyType>(stoi(typeValue));
    string privateKeyHex = jsonKey["privateKeyHex"].dump();
    string publicKeyHex = jsonKey["publicKeyHex"].dump();


    return Key(id, type, privateKeyHex, publicKeyHex);
}