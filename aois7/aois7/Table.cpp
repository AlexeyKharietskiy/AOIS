#include "Table.h"

inline bool disunction(bool a, bool b)
{
	return (a == 1 || b == 1) ? 1 : 0;
}
inline bool conunction(bool a, bool b)
{
	return (a == 1 && b == 1) ? 1 : 0;
}
inline bool revers(bool a)
{
	return (a == 1) ? 0 : 1;
}

inline bool Table::function_6(bool a, bool b) { //(!a/\b)\/(a/\!b)
	return disunction(conunction(revers(a), b), conunction(a, revers(b)));
}
inline bool Table::function_9(bool a, bool b) { //(a/\b)\/(!a/\!b)
	return disunction(conunction(a, b), conunction(revers(a), revers(b)));
}
inline bool Table::function_4(bool a, bool b) { //!a/\b
	return conunction(revers(a), b);
}
inline bool Table::function_11(bool a, bool b) { //a\/!b
	return disunction(a, revers(b));
}

inline Table::Table(vector<vector<bool>> matrix)
{
	this->table = matrix;
	this->size = this->table.size();
}
inline Table::Table()
{
	this->table = {
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
	this->size = this->table.size();
}

inline void Table::do_function_6(int a,int b, int c) {
	vector<bool> foo_a = this->get_word(a);
	vector<bool> foo_b = this->get_word(b);
	vector<bool> result;
	for (int i = 0; i < this->size; i++)
		result.push_back(function_6(foo_a[i], foo_b[i]));
	this->update_word(result, c);
}
inline void Table::do_function_9(int a, int b, int c) {
	vector<bool> foo_a = this->get_word(a);
	vector<bool> foo_b = this->get_word(b);
	vector<bool> result;
	for (int i = 0; i < this->size; i++)
		result.push_back(function_9(foo_a[i], foo_b[i]));
	this->update_word(result, c);

}
inline void Table::do_function_4(int a, int b, int c) {
	vector<bool> foo_a = this->get_word(a);
	vector<bool> foo_b = this->get_word(b);
	vector<bool> result(this->size);
	for (int i = 0; i < this->size; i++)
		result[i] = function_4(foo_a[i], foo_b[i]);
	this->update_word(result, c);

}
inline void Table::do_function_11(int a, int b, int c) {
	vector<bool> foo_a = this->get_word(a);
	vector<bool> foo_b = this->get_word(b);
	vector<bool> result;
	for (int i = 0; i < this->size; i++)
		result.push_back(function_11(foo_a[i], foo_b[i]));
	this->update_word(result, c);

}

inline vector<bool> Table::get_word(int number) {
	vector <bool> word;
	for (int i = number; word.size() < this->size; i++)
	{
		word.push_back(table[i][number]);
		i = (i == this->size - 1) ? -1 : i;
	}
	return word;
}
inline vector<bool> Table::get_address_column(int number)
{
	vector <bool> address_column;
	for (int i = number,j = 0; address_column.size() < this->size; i++, j++)
	{
		address_column.push_back(table[i][j]);
		i = (i == this->size - 1) ? -1 : i;
	}
	return address_column;
}

inline void Table::show_table()
{
	cout << "Table:" << endl;
	for (const auto& row : this->table) {
		for (bool value : row) {
			cout << value << " ";
		}
		cout << endl;
	}
}
inline void Table::show_vec(vector<bool> vec) {
	cout << "Result:" << endl;
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i];
	cout << endl;
}

inline void Table::update_word(vector<bool> word, int number) {
	for (int i = number, j = 0; j < word.size(); j++, i++)
	{
		this->table[i][number] = word[j];
		i = (i == this->size - 1) ? -1 : i;
	}
}
inline void Table::update_address_column(vector<bool> address_column, int number) {
	for (int i = number, j = 0;j < this->size; i++, j++)
	{
		table[i][j] = address_column[j];
		i = (i == this->size - 1) ? -1 : i;
	}
}
inline vector<bool> Table::sum(vector<bool> a, vector<bool> b){
	vector<bool> result(5,0);
	for (int i = 3; i >= 0; i--)
	{
		if (a[i] == 1 && b[i] == 1 && result[i + 1] == 1) {
			result[i] = 1;
			continue;
		}
		if (a[i] == 1 && b[i] == 1 && result[i + 1] == 0) {
			result[i+1] = 0;
			result[i] = 1;
			continue;
		}
		if ((a[i] == 0 && b[i] == 0 )&& (result[i + 1] == 0||result[i+1]==1))
			continue;
		if (result[i + 1] == 0) {
			result[i + 1] = 1;
			continue;
		}
		result[i + 1] = 0;
		result[i] = 1;
	}
	return result;
}

inline int Table::find_word(vector<bool> V) {
	vector<bool> vec_word;
	for (int i = 0,flag = 1; i < this->size; i++,flag = 1)
	{
		vec_word = this->get_word(i);
		for (size_t j = 0; j < V.size(); j++) {
			if (V[j] != vec_word[j]) {
				flag = 0;
			}
		}
		if (flag == 1)
			return i;
	}
	return -1;
}

inline void Table::sum_words(vector<bool> V) {
	int number = this->find_word(V);
	vector<bool> A(4), B(4), S(5);
	int i = 3;
	if (number == -1)
		return;
	vector<bool> word = this->get_word(number);
	while (i<7)
	{
		A[i-3] = word[i];
		i++;
	}
	while (i < 11)
	{
		B[i-7] = word[i];
		i++;
	}
	S = this->sum(A, B);
	while (i < this->size)
	{
		word[i] = S[i-11];
		i++;
	}
	this->update_word(word, number);
}

inline int Table::decimal_view(vector<bool> word) {
	int value = 0;
	for (int i = 0; i < word.size(); ++i) {
		if (word[i]) {
			value += pow(2, word.size() - 1 - i);
		}
	}
	return value;
}

inline void Table::sort_table() {
	vector<pair<int, vector<bool>>> sort_helper_list;

	for (int i = 0; i < table.size(); ++i) {
		vector<bool> word = this->get_word(i);
		int value = this->decimal_view(word);
		sort_helper_list.push_back(std::make_pair(value, word));
	}

	sort(sort_helper_list.begin(), sort_helper_list.end(),
		[](const std::pair<int, std::vector<bool>>& a, const std::pair<int, std::vector<bool>>& b) {
			return a.first < b.first;
		});

	for (int i = 0; i < sort_helper_list.size(); ++i) {
		update_word(sort_helper_list[i].second, i);
	}
}