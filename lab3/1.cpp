#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct HashNode {
    string username;
    string password;
    HashNode *next;
    HashNode(const string &u, const string &p, HashNode *n = nullptr)
        : username(u), password(p), next(n) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 100003;
    vector<HashNode*> table;

    int hashFunction(const string &key) const {
        int hashVal = 0;
        for (size_t i = 0; i < key.length(); i++) {
            hashVal = 37 * hashVal + key[i];
        }
        hashVal %= TABLE_SIZE;
        if (hashVal < 0) {
            hashVal += TABLE_SIZE;
        }
        return hashVal;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE, nullptr);
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode *entry = table[i];
            while (entry != nullptr) {
                HashNode *prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;

    void insert(const string &username, const string &password) {
        int index = hashFunction(username);
        HashNode *entry = table[index];
        while (entry != nullptr) {
            if (entry->username == username) {
                entry->password = password;
                return;
            }
            entry = entry->next;
        }
        table[index] = new HashNode(username, password, table[index]);
    }

    bool authenticate(const string &username, const string &password) const {
        int index = hashFunction(username);
        HashNode *entry = table[index];
        while (entry != nullptr) {
            if (entry->username == username) {
                return entry->password == password;
            }
            entry = entry->next;
        }
        return false;
    }
};

int main() {
    HashTable ht;
    ifstream file("user.txt");
    if (file.is_open()) {
        string u, p;
        while (file >> u >> p) {
            ht.insert(u, p);
        }
        file.close();
    }

    string username, password;
    while (cout << "Username: " && cin >> username) {
        cout << "Password: ";
        if (!(cin >> password)) {
            break;
        }
        if (ht.authenticate(username, password)) {
            cout << "Authentication successful" << endl;
        } else {
            cout << "Authentication failure" << endl;
        }
    }
    return 0;
}
