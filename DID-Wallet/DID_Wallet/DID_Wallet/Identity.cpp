#include "Identity.h"

Identity::Identity() {}

Identity::Identity(int version, IdentityType type, string id)
    : version(version), type(type), id(id) {}

Identity::~Identity() {}

int Identity::getVersion() 
{
    return version;
}

void Identity::setVersion(int version) 
{
    this->version = version;
}

IdentityType Identity::getType() 
{
    return type;
}

void Identity::setType(IdentityType type) 
{
    this->type = type;
}

string Identity::getId() 
{
    return id;
}

void Identity::setId(string id) 
{
    this->id = id;
}

string Identity::toJSON()
{
    nlohmann::json jsonIdentity;
    jsonIdentity["version"] = version;
    jsonIdentity["type"] = static_cast<int>(type);
    jsonIdentity["id"] = id;
    return jsonIdentity.dump();
}