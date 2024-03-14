#include <iostream>
#include <vector>

using namespace std;

 struct Stack {
	vector<char> vec;
	char oper = NULL;
	Stack* next = NULL;
};

 inline Stack* inStack(Stack* p, vector<char> in) {
	Stack* t = new Stack;
	t->vec = in;
	t->next = p;
	return t;
}

 inline Stack* inStack(Stack* p, char in) {
	Stack* t = new Stack;
	t->oper = in;
	t->next = p;
	return t;
}

 inline void del_all(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

 inline void del_sec_last(Stack** p)
{
	Stack* t = (*p)->next;
	(*p)->next = (*p)->next->next;
	delete t;
}

 inline void del_last(Stack** p) {
	Stack* t;
	t = *p;
	*p = (*p)->next;
	delete t;

}