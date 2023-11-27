#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "DIDWallet.h"
#include "didkit.h"

using namespace std;

int main()
{
    //create wallet
	DIDWallet didWallet(new FileSystemStore("./Wallet"));

    //create key(verification method)
    string keyID = "keys-1";
    string privateKeyHex = "a889f4da49ff8dd6b03d4334723fe3e5ff55ae6a2483de1627bec873b0b73e1e86eabd6abce2f96553251de61def0265784688ff712ce583621a5b181ef21639";
    string publicKeyHex = "86eabd6abce2f96553251de61def0265784688ff712ce583621a5b181ef21639";
    Key key(keyID, KeyType::Ed25519, privateKeyHex, publicKeyHex);

    //create did
    //const char* edKey = didkit_vc_generate_ed25519_key(); 
    string did = "did:example:3dda540891d14a1baec2c7485c273c00";

    //create credential with did and key
    TestDID testDID(did, key);

    //add credential to wallet
    didWallet.put("User1", &testDID);

    //print wallet data
    vector<string> list = didWallet.list();
    for (string label : list)
    {
        Identity* identity = didWallet.get(label);
        if (identity != nullptr && dynamic_cast<TestDID*>(identity) != nullptr)
        {
            TestDID* tdid = (TestDID*)identity;
            cout << "did id: " + tdid->getId() << endl;
            cout << "did type: " << tdid->getType() << endl;

            Key k = tdid->getKey();
            cout << "key id: " + k.getId() << endl;
            cout << "key type: " << k.getType() << endl;
            cout << "key pri: " + k.getPrivateKeyHex() << endl;
            cout << "key pub: " + k.getPublicKeyHex() << endl;
        }
        cout << endl;
    }
}