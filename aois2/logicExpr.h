#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Stack.cpp"
using namespace std;


class LogicExpr
{
public:
	LogicExpr(string expr);
	int get_index_form();
	void show_table();
	void show_expr();
	void show_pdnf();
	void show_pcnf();
	void show_num_pdnf();
	void show_num_pcnf();
	void show_index_form();
private:
	string expr;
	vector<vector<char>> truthTable;
	string pdnf;
	string pcnf;
	vector<int> num_pdnf;
	vector<int> num_pcnf;
	int index_form = 0;
	char disunction(char a, char b);
	char conunction(char a, char b);
	char implication(char a, char b);
	char equivalation(char a, char b);
	char revers(char a);

	void make_table();
	void make_result();
	Stack* make_operation(Stack* begin, char sign, int number, vector<char> value);

	void make_pdnf();
	void make_pcnf();
	void make_num_pdnf();
	void make_num_pcnf();
	void make_index_form();
};