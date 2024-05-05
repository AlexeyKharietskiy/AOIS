
#include "logicExpr.h"



inline Stack* change_form(LogicExpr a, bool flag)
{
	Stack* begin = NULL;
	vector<char> el_expr;
	string new_form;
	if (flag == true)
		new_form = a.get_pdnf();
	else
		new_form = a.get_pcnf();
	new_form.erase(std::remove_if(new_form.begin(), new_form.end(), [](char c) {
		return c == '(' || c == ')' || c == '&' || c == '|';
		}), new_form.end());
	for (int i = 0, j; i < new_form.size() - 1; )
	{
		for (j = 0; el_expr.size() != a.get_vars().size(); j++)
		{
			if (isalpha(new_form[i + j]))
			{
				el_expr.push_back('1');
			}
			else
			{
				el_expr.push_back('0');
				j++;
			}

		}
		i += j;
		begin = inStack(begin, el_expr, '-');
		el_expr.clear();
	}
	return begin;
}
inline Stack* glue_stage(Stack* begin,LogicExpr a, bool& operation) {
	Stack* newbegin = NULL;
	vector<char> el_expr;
	while (begin != NULL)
	{
		Stack* t = begin->next;
		while (t != NULL)
		{
			int mistake = 0;
			for (int i = 0; i < a.get_vars().size(); i++)
			{
				if (begin->vec[i] == t->vec[i])
					el_expr.push_back(begin->vec[i]);
				else
				{
					mistake++;
					if (mistake == 1) {
						el_expr.push_back('x');
					}
					else
					{
						el_expr.clear();
						break;
					}
				}
			}

			if (el_expr.size() != 0 && mistake != 0)
			{
				operation = true;
				begin->oper = '+';
				t->oper = '+';
				newbegin = inStack(newbegin, el_expr, '-');
			}
			if (mistake == 0)
				begin->oper = '+';
			t = t->next;
			el_expr.clear();
			mistake = 0;
		}
		if (begin->oper == '+')
		{
			del_last(&begin);
		}
		else
		{
			newbegin = inStack(newbegin, begin->vec, '-');
			del_last(&begin);
		}
	}
	return newbegin;
}
inline string make_pdnf_form(Stack* begin, LogicExpr a)
{
	string pdnf;
	Stack* t = begin;
	while (t != NULL)
	{
		pdnf += '(';
		for (int i = 0; i < t->vec.size(); i++) {
			switch (t->vec[i])
			{
			case '0':
				pdnf += '!';
				pdnf += a.get_vars()[i];
				break;
			case '1':
				pdnf += a.get_vars()[i];
				break;
			default:
				break;
			}
			if (isalpha(pdnf.back()))
				pdnf += '&';
		}
		if (pdnf.back() == '&')
			pdnf.pop_back();
		pdnf += ")|";
		t = t->next;
	}
	pdnf.pop_back();

	return pdnf;
}
inline string make_pcnf_form(Stack* begin, LogicExpr a)
{
	string pcnf;
	Stack* t = begin;
	while (t != NULL)
	{
		pcnf += '(';
		for (int i = 0; i < t->vec.size(); i++) {
			switch (t->vec[i])
			{
			case '0':
				pcnf += '!';
				pcnf += a.get_vars()[i];
				break;
			case '1':
				pcnf += a.get_vars()[i];
				break;
			default:
				break;
			}
			if (isalpha(pcnf.back()))
				pcnf += '|';
		}
		if (pcnf.back() == '|')
			pcnf.pop_back();
		pcnf += ")&";
		t = t->next;
	}
	if(!pcnf.empty())
	pcnf.pop_back();

	return pcnf;
}
inline string make_min_form(Stack** begin, LogicExpr a, bool flag)
{
	LogicExpr b;
	b.truthTable = a.truthTable;
	Stack* t = NULL, * lt = NULL;
	while (*begin != NULL) {
		t = *begin;
		*begin = t->next;
		if (flag == true)
			b.set_expr(make_pdnf_form(*begin, a));
		else
			b.set_expr(make_pcnf_form(*begin, a));
		if (b.get_index_form() != a.get_index_form())
		{
			*begin = t;
			break;
		}
		else {
			t->next = NULL;
			delete t;
		}

	}
	while (t->next != NULL)
	{
		lt = t;
		t = t->next;
		lt->next = t->next;
		if (flag == true)
			b.set_expr(make_pdnf_form(*begin, a));
		else
			b.set_expr(make_pcnf_form(*begin, a));
		if (b.get_index_form() != a.get_index_form()) {
			lt->next = t;
		}
		else
		{
			t->next = NULL;
			delete t;
			t = lt;
		}
	}
	if (flag == true)
		return make_pdnf_form(*begin, a);
	else
		return make_pcnf_form(*begin, a);

}
inline void calculation_method(LogicExpr a) {
	bool operation = true;
	Stack* begin = NULL;
	begin = change_form(a, true);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, a, operation);
	}
	operation = true;
	cout << "Calculation method:\n";
	cout << "DNF before verification:" << make_pcnf_form(begin, a) << endl;
	cout << "DNF after verification:" << make_min_form(&begin, a, true) << endl;
	begin = change_form( a, false);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, a, operation);
	}
	cout << "CNF before verification:" << make_pdnf_form(begin, a) << endl;
	cout << "CNF after verification:" << make_min_form(&begin, a, false) << endl;
	del_all(&begin);
}
inline void show_calc_table(vector<vector<string>> table, string expr, string not_vertix_form, bool type) {
	if (type)
		cout << "DNF before verification:";
	else
		cout << "CNF before verification:";
	cout << not_vertix_form << endl;;
	cout << "Table:" << endl;
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[0].size(); j++)
		{
			cout << setw(15) << table[i][j] << "|";
		}
		cout << endl;
	}
	if (type)
		cout << "DNF after verification:";
	else
		cout << "CNF after verification:";
	cout << expr << endl;
}
inline string make_table_form(LogicExpr a, Stack* begin, bool type) {
	vector<vector<string>> table;
	table.push_back({ " " });
	string expr;
	bool flag;
	string not_verif_form;
	if (type == true) {
		not_verif_form = make_pdnf_form(begin, a);
		for (int j = 0; j < a.get_pdnf().size(); j++)
		{
			if (a.get_pdnf()[j] != ')')
				expr += a.get_pdnf()[j];
			else {
				expr += ')';
				j++;
				table[0].push_back(expr);
				expr.clear();
			}

		}
	}
	else {
		not_verif_form = make_pcnf_form(begin, a);

		for (int j = 0; j < a.get_pcnf().size(); j++)
		{
			if (a.get_pcnf()[j] != ')')
				expr += a.get_pcnf()[j];
			else {
				expr += ')';
				j++;
				table[0].push_back(expr);
				expr.clear();
			}

		}
	}
	for (int j = 0; j < not_verif_form.size(); j++)
	{
		if (not_verif_form[j] != ')')
			expr += not_verif_form[j];
		else {
			expr += ')';
			j++;
			table.push_back({ expr });
			expr.clear();
		}

	}
	for (int i = 1; i < table.size(); i++)
	{
		vector<string> vars;
		vars.push_back("");
		for (int k = 1; k < table[i][0].size(); k++)
		{
			if (isalpha(table[i][0][k])) {
				if (table[i][0][k - 1] == '(' && a.get_vars()[0] != table[i][0][k])
				{
					vars[vars.size() - 1] += (type) ? '&' : '|';
					vars[vars.size() - 1] += table[i][0][k];
				}
				else {
					vars[vars.size() - 1] += table[i][0][k - 1];
					vars[vars.size() - 1] += table[i][0][k];
				}
				vars.push_back("");
			}

		}
		if (!vars.empty())
		vars.pop_back();
		for (int j = 1; j < table[0].size(); j++)
		{
			table[i].push_back("");
			flag = true;
			for (int k = 0; k < vars.size(); k++)
				if (table[0][j].find(vars[k]) == std::string::npos)
					flag = false;
			if (flag == true)
				table[i][j] = "X";
			else
				table[i][j] = "O";

		}
		if (!vars.empty())
		vars.clear();
	}
	for (int i = 1, coord = 0, j; i < table[0].size(); i++)
	{
		j = 1;
		for (int k = 0; j < table.size(); j++)
		{
			if (k <= 1) {
				if (table[j][i] == "X")
				{
					k++;
					coord = j;
				}
			}
			else
				break;
		}
		if (j = table.size() && expr.find(table[coord][0]) == std::string::npos) {
			expr += table[coord][0];
			if (type)
				expr += '|';
			else
				expr += '&';
		}
	};
	if(!expr.empty())
	expr.pop_back();
	show_calc_table(table, expr, not_verif_form, type);
	return expr;
}
inline void calculation_table_method(LogicExpr a) {
	bool operation = true;
	Stack* begin = NULL;
	begin = change_form(a, true);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, a, operation);
	}
	operation = true;
	make_table_form(a, begin, true);
	begin = change_form(a, false);
	while (operation == true)
	{
		operation = false;
		begin = glue_stage(begin, a, operation);
	}
	make_table_form(a, begin, false);
	del_all(&begin);
}