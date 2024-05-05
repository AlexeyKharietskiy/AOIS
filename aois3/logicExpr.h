
#include <cmath>
#include "Stack.cpp"
#include <string>
#include <algorithm>
#include <iomanip>


using namespace std;

class LogicExpr
{
public:
	vector<vector<char>> truthTable;
	LogicExpr(string expr);
	LogicExpr() {

	}
	void set_expr(string str) {
		this->expr = str;
		make_result();
		make_index_form();
	}
	int get_index_form();
	string get_pcnf();
	string get_pdnf();
	string get_vars();
	void show_table();
	void show_carno_table();
	void show_expr();
	void show_pdnf();
	void show_pcnf();
	void show_num_pdnf();
	void show_num_pcnf();
	void show_index_form();
	string pdnf;

private:
	string vars;

	vector<vector<string>> carno_table;
	int index_form = 0;
	string expr;
	string pcnf;
	vector<int> num_pdnf;
	vector<int> num_pcnf;
	char disunction(char a, char b);
	char conunction(char a, char b);
	char implication(char a, char b);
	char equivalation(char a, char b);
	char revers(char a);

	void make_carno_table();
	void make_table();
	void make_result();
	Stack* make_operation(Stack* begin, char sign, int number, vector<char> value);

	void make_pdnf();
	void make_pcnf();
	void make_num_pdnf();
	void make_num_pcnf();
	void make_index_form();
	void make_vars();

};