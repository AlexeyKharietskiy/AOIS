
#include "minimalize.cpp"

LogicExpr::LogicExpr(string expr) {
	this->expr = expr;
	this->make_table();
	this->make_result();
	this->make_pdnf();
	this->make_pcnf();
	this->make_num_pdnf();
	this->make_num_pcnf();
	this->make_index_form();
	this->make_vars();
	this->show_table();
	this->show_pdnf();
	this->show_num_pdnf();
	this->show_pcnf();
	this->show_num_pcnf();
	show_index_form();
	make_carno_table();
	show_carno_table();
}

int LogicExpr::get_index_form() {
	return this->index_form;
}
string LogicExpr::get_pdnf() {
	return this->pdnf;

}
string LogicExpr::get_pcnf() {
	return this->pcnf;
}
string LogicExpr::get_vars() {
	return this->vars;

}

void LogicExpr::show_table() {
	for (int i = 0; i < truthTable[0].size(); i++)
	{
		for (int j = 0; j < truthTable.size(); j++)
		{
			std::cout << truthTable[j][i] << " ";
		}
		cout << endl;
	}
}
void LogicExpr::show_carno_table() {
	cout << "Carno table:" << endl;
	for (int j,i = 0; i < carno_table.size(); i++)
	{
		for (j = 0; j < carno_table[i].size(); j++)
		{
			cout << setw(6) << carno_table[i][j] << "| ";
		}
		cout << endl;
	}
	bool operation = true;
	Stack* begin = NULL;
	begin = change_form(*this, false);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, *this, operation);
	}
	operation = true;
	cout << "DNF after verification:" << make_min_form(&begin, *this, false) << endl;
	begin = change_form(*this, true);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, *this, operation);
	}
	cout << "CNF after verification:" << make_min_form(&begin, *this, true) << endl;
	del_all(&begin);
}

void LogicExpr::show_expr() {
	cout << expr << endl;
}
void LogicExpr::show_pdnf() {
	cout << "PDNF: " << pdnf << endl;
}
void LogicExpr::show_pcnf() {
	cout << "PCNF: " << pcnf << endl;
}
void LogicExpr::show_num_pdnf() {
	cout << "(";
	for (int num : num_pdnf) {
		cout << num << " ";
	}

	cout << ")|" << endl;
}
void LogicExpr::show_num_pcnf() {
	cout << "(";
	for (int num : num_pcnf) {
		cout << num << " ";
	}

	cout << ")&" << endl;
}
void LogicExpr::show_index_form() {

	cout << "Index form: " << index_form << endl;
}
char LogicExpr::disunction(char a, char b)
{
	return (a == '1' || b == '1') ? '1' : '0';
}
char LogicExpr::conunction(char a, char b)
{
	return (a == '1' && b == '1') ? '1' : '0';
}
char LogicExpr::implication(char a, char b)
{
	return (a <= b) ? '1' : '0';
}
char LogicExpr::equivalation(char a, char b)
{
	return (a == b) ? '1' : '0';
}
char LogicExpr::revers(char a)
{
	return (a == '1') ? '0' : '1';
}

void LogicExpr::make_carno_table() {
	string vars_set, vars_before, vars_after;
	vars_set = vars;
	vars_set.insert(vars.length() / 2, "/");
	int i = 0;
	while (i < vars_set.size())
		if (vars_set[i] == '/')
			break;
		else
		{
			vars_before.push_back(vars_set[i]);
			i++;
		}
	i++;
	while (i < vars_set.size()) {
		vars_after.push_back(vars_set[i]);
		i++;
	}
	carno_table.push_back({ vars_set });
	switch (vars_before.size())
	{
	case 1:
		carno_table.push_back({ "0" });
		carno_table.push_back({ "1" });

		break;

	case 2:
		carno_table.push_back({ "00" });
		carno_table.push_back({ "01" });
		carno_table.push_back({ "11" });
		carno_table.push_back({ "10" });

		break;

	default:
		break;
	}
	switch (vars_after.size())
	{
	case 1:
		carno_table[0].push_back("0");
		carno_table[0].push_back("1");
		break;

	case 2:
		carno_table[0].push_back("00");
		carno_table[0].push_back("01");
		carno_table[0].push_back("11");
		carno_table[0].push_back("10");

		break;
	case 3:
		carno_table[0].push_back("000");
		carno_table[0].push_back("001");
		carno_table[0].push_back("011");
		carno_table[0].push_back("010");
		carno_table[0].push_back("100");
		carno_table[0].push_back("101");
		carno_table[0].push_back("111");
		carno_table[0].push_back("110");
		break;

	default:
		break;
	}
	string bin_val;
	for (int i = 1; i < carno_table.size(); i++)
	{
		for (int j = 1; j < carno_table[0].size(); j++)
		{
			carno_table[i].push_back(" ");
		}
	}
	for (int i = 1; i < truthTable[0].size(); i++)
	{
		for (int j = 0; j < truthTable.size(); j++)
		{
			bin_val += truthTable[j][i];
		}
		for (int k = 1; k < carno_table.size(); k++)
		{
			if (bin_val.substr(0, vars_before.size()) == carno_table[k][0]) {
				for (int m = 1; m < carno_table[0].size(); m++)
				{
					if (bin_val.substr(vars_before.size(), vars_after.size()) == carno_table[0][m])
					{
						carno_table[k][m] = bin_val[bin_val.size() - 1];
						break;
					}
				}
				break;
			}
		}
		bin_val.clear();
	}
}
void LogicExpr::make_table()
{
	bool repeat = false;
	for (int i = 0; i < expr.length(); i++)
	{
		if (isalpha(expr[i])) {
			for (int j = 0; j < truthTable.size(); j++)
			{
				if (expr[i] == truthTable[j][0])
					repeat = true;
			}
			if (repeat == false)
				truthTable.push_back({ expr[i] });

		}
	}
	for (auto& vec : truthTable)
		vec.resize(pow(2, truthTable.size()) + 1);
	for (int a, i = 1; i < truthTable[0].size(); i++)
	{
		a = i - 1;
		for (int j = truthTable.size() - 1; j >= 0; j--)
		{
			if (a != 0) {
				truthTable[j][i] = (a % 2 == 0) ? '0' : '1';
				a /= 2;
			}
			else
				truthTable[j][i] = '0';
		}
	}

}
void LogicExpr::make_result() {
	if (truthTable[truthTable.size() - 1][0] == '=')
		truthTable.pop_back();
	int size = truthTable.size();
	int number;
	vector<char> value(truthTable[0].size());
	Stack* begin = NULL;
	for (char sign : expr)
	{
		if (isalpha(sign)) {
			for (number = 0; number < truthTable.size() && truthTable[number][0] != sign; number++) {}
			if (begin == NULL || begin->oper == '(') {
				begin = inStack(begin, truthTable[number]);
			}
			else
				begin = make_operation(begin, sign, number, value);
		}
		else {
			if (sign != ')' && (begin != NULL || sign != '('))
				begin = inStack(begin, sign);
			else if (begin != NULL && begin->next != NULL && begin->next->oper == '(')
			{
				del_sec_last(&begin);
				truthTable.push_back(begin->vec);
				del_last(&begin);
				number = truthTable.size() - 1;
				begin = make_operation(begin, sign, number, value);
			}
		}
	}
	if (begin != NULL) {
		while (truthTable.size() != size)
			truthTable.erase(truthTable.end() - 1);
		truthTable.push_back(begin->vec);
		truthTable[truthTable.size() - 1][0] = '=';
		del_all(&begin);
	}
}
Stack* LogicExpr::make_operation(Stack* begin, char sign, int number, vector<char> value)
{
	switch (begin->oper)
	{
	case '!':
		for (int i = 1; i < truthTable[0].size(); i++)
		{
			value[i] = revers(truthTable[number][i]);
		}
		del_last(&begin);
		if (begin != NULL && begin->oper != '(')
		{
			truthTable.push_back(value);
			number = truthTable.size() - 1;
			begin = make_operation(begin, sign, number, value);
			truthTable.erase(truthTable.end() - 1);
		}
		else
			begin = inStack(begin, value);

		break;
	case '&':
		for (int i = 1; i < truthTable[0].size(); i++)
		{
			value[i] = conunction(begin->next->vec[i], truthTable[number][i]);
		}
		del_last(&begin);
		del_last(&begin);
		begin = inStack(begin, value);
		break;

	case '|':
		for (int i = 1; i < truthTable[0].size(); i++)
		{
			value[i] = disunction(begin->next->vec[i], truthTable[number][i]);
		}
		del_last(&begin);
		del_last(&begin);
		begin = inStack(begin, value);
		break;
	case '-':
		for (int i = 1; i < truthTable[0].size(); i++)
		{
			value[i] = implication(begin->next->vec[i], truthTable[number][i]);
		}
		del_last(&begin);
		del_last(&begin);
		begin = inStack(begin, value);
		break;
	case '~':
		for (int i = 1; i < truthTable[0].size(); i++)
		{
			value[i] = equivalation(begin->next->vec[i], truthTable[number][i]);
		}
		del_last(&begin);
		del_last(&begin);
		begin = inStack(begin, value);
		break;
	case '(':
		begin = inStack(begin, truthTable[number]);
		break;
	default:
		break;
	}
	return begin;
}

void LogicExpr::make_pdnf()
{
	pdnf += '(';
	for (int i = 1; i < truthTable[0].size(); i++)
		if (truthTable[truthTable.size() - 1][i] == '1')
		{
			if (pdnf != "(")
				pdnf += "|(";
			for (int j = 0; j < truthTable.size() - 1; j++) {
				if (j != truthTable.size() - 2)
					if (truthTable[j][i] == '0') {
						pdnf += '!';
						pdnf += truthTable[j][0];
						pdnf += '&';
					}
					else {
						pdnf += truthTable[j][0];
						pdnf += '&';
					}
				else if (truthTable[j][i] == '0') {
					pdnf += '!';
					pdnf += truthTable[j][0];
				}
				else
					pdnf += truthTable[j][0];
			}
			if (i != truthTable[0].size() - 1)
				pdnf += ")";
			else
				pdnf += ')';
		}
}
void LogicExpr::make_pcnf()
{
	pcnf += '(';
	for (int i = 1; i < truthTable[0].size(); i++)
		if (truthTable[truthTable.size() - 1][i] == '0')
		{
			if (pcnf != "(")
				pcnf += "&(";
			for (int j = 0; j < truthTable.size() - 1; j++) {
				if (j != truthTable.size() - 2)
					if (truthTable[j][i] == '1') {
						pcnf += '!';
						pcnf += truthTable[j][0];
						pcnf += '|';
					}
					else {
						pcnf += truthTable[j][0];
						pcnf += '|';
					}
				else if (truthTable[j][i] == '1') {
					pcnf += '!';
					pcnf += truthTable[j][0];
				}
				else
					pcnf += truthTable[j][0];
			}
			pcnf += ')';
		}
}
void LogicExpr::make_num_pdnf() {
	int num = 0;
	for (int i = 1; i < truthTable[0].size(); i++)
		if (truthTable[truthTable.size() - 1][i] == '1')
		{
			num = 0;
			for (int deg = 0, j = truthTable.size() - 2; j >= 0; j--, deg++) {

				if (truthTable[j][i] == '1') {
					num += pow(2, deg);
				}
			}
			num_pdnf.push_back(num);

		}
}
void LogicExpr::make_num_pcnf() {
	int num = 0;
	for (int i = 1; i < truthTable[0].size(); i++)
		if (truthTable[truthTable.size() - 1][i] == '0')
		{
			num = 0;
			for (int deg = 0, j = truthTable.size() - 2; j >= 0; j--, deg++) {

				if (truthTable[j][i] == '1') {
					num += pow(2, deg);
				}
			}
			num_pcnf.push_back(num);

		}
}
void LogicExpr::make_index_form() {
	index_form = 0;
	for (int deg = 0, i = truthTable[0].size() - 1; i > 0; i--, deg++)
		if (truthTable[truthTable.size() - 1][i] == '1')
			index_form += pow(2, deg);
}
void LogicExpr::make_vars() {
		for (int j = 0; j < truthTable.size()-1; j++)
		{
			this->vars += truthTable[j][0];
		}
}


