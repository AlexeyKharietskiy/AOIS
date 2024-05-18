#include "Cell.h"

inline Cell::Cell(string key, string data) {
    this->key = key;
    this->data = data;
    this->id = 0;
}