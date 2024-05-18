#pragma once
#include "Cell.cpp"

class HashTable {
private:
    vector<Cell*> table;
    int capacity;
    int size;
    int baseAddress;
    int id;
    int hash_func_1(int v);

    int hash_func_2(int v);

public:
    HashTable(int capacity, int baseAddress);

    ~HashTable();

    void insert_cell(string key, string data);

    string get_cell_data(string key);

    void delete_cell(string key);

    void print_table();
};