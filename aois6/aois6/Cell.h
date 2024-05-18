#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class Cell {
public:

    Cell(string key, string data);
    friend class HashTable;
private:
    string key;
    string data;
    int id;
};