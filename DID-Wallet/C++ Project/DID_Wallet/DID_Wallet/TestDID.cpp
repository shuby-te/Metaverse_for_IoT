#include "TestDID.h"

TestDID::TestDID(string id, Key key) : Identity(1, IdentityType::Test, id), key(key) {}  //1은 임의의 값

Key TestDID::getKey() 
{
    return key;
}

void TestDID::setKey(Key key) 
{
    this->key = key;
}

string TestDID::toJSON()
{
    json jsonTestDID;
    jsonTestDID["id"] = getId();
    jsonTestDID["type"] = "Test";
    jsonTestDID["key"] = key.toJSON();
    //cout << "testDID toJson\n";
    return jsonTestDID.dump();
}

TestDID TestDID::fromJSON(json jsonData) 
{
    string id = jsonData["id"].dump();
    Key key = Key::fromJSON(jsonData["key"].dump());

    return TestDID(id, key);
}