#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


class Table
{
public:
	Table(vector<vector<bool>>);
	Table();
	vector<bool> get_word(int);
	vector<bool> get_address_column(int);
	void do_function_4(int, int, int);
	void do_function_6(int, int, int);
	void do_function_9(int, int, int);
	void do_function_11(int, int, int);
	void show_table();
	void show_vec(vector<bool>);
	void sum_words(vector<bool>);
	void sort_table();
	void update_word(vector<bool>, int);
	void update_address_column(vector<bool>, int);
private:
	vector<vector<bool>> table;
	int size;
	bool function_6(bool, bool);
	bool function_9(bool, bool);
	bool function_4(bool, bool);
	bool function_11(bool, bool);
	vector<bool> sum(vector<bool>, vector<bool>);
	int find_word(vector<bool>);
	int decimal_view(vector<bool>);
};

