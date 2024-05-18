#include "HashTable.h"
#include <iomanip>

const int ALPHABET_SIZE = 33;

inline int get_char_index(char c) {
    if (c >= 'À' && c <= 'ß') {
        return c - 'À';
    }
    if (c >= 'à' && c <= 'ÿ') {
        return c - 'à';
    }
    throw std::invalid_argument("Invalid character");
}

inline int make_v(const string& key) {
    return get_char_index(key[0]) * ALPHABET_SIZE + get_char_index(key[1]);
}

inline int HashTable::hash_func_1(int v) {
    return v % capacity + baseAddress;
}

inline int HashTable::hash_func_2(int v) {
    return 7 - (v % 7);
}

inline HashTable::HashTable(int capacity, int baseAddress) {
    this->capacity = capacity;
    this->baseAddress = baseAddress;
    size = id = 0;
    table.resize(capacity, nullptr);
}

inline HashTable::~HashTable() {
    for (Cell* cell : table) {
        delete cell;
    }
}

inline void HashTable::insert_cell(string key, string data) {
    int v = make_v(key);
    int index = hash_func_1(v);
    int step = hash_func_2(v);

    while (table[index] != nullptr && table[index]->key != key) {
        index = (index + step) % capacity;
    }

    if (table[index] != nullptr && table[index]->key == key) {
        table[index]->data = data;
    }
    else {
        table[index] = new Cell(key, data);
        ++size;
        table[index]->id = ++id;
    }
}

inline string HashTable::get_cell_data(string key) {
    int v = make_v(key);
    int index = hash_func_1(v);
    int step = hash_func_2(v);

    while (table[index] != nullptr) {
        if (table[index]->key == key) {
            return table[index]->data;
        }
        index = (index + step) % capacity;
    }

    return "";
}

inline void HashTable::delete_cell(string key) {
    int v = make_v(key);
    int index = hash_func_1(v);
    int step = hash_func_2(v);

    while (table[index] != nullptr) {
        if (table[index]->key == key) {
            delete table[index];
            table[index] = nullptr;
            --size;
            return;
        }
        index = (index + step) % capacity;
    }
}

inline void HashTable::print_table() {
    cout << setw(10) << " ID" << setw(25) << "Key" << setw(30) << "Data" << endl;
    for (int i = 0; i < capacity; ++i) {
        if (table[i] != nullptr) {
            cout<< setw(10) << " ID" << table[i]->id << setw(25) << table[i]->key << setw(30) << table[i]->data << endl;
        }
        else {
            cout << endl;
        }
    }
}