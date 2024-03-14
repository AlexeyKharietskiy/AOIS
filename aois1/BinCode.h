#pragma once
#include <vector>
#include <iostream>
using namespace std;

class BinCode
{
public:
	BinCode();
	BinCode(int a);
	BinCode(double a);

	void showStraightCode();
	void showReverseCode();
	void showAddCode();
	void showFloatPointCode();
	void showFixedPointCode();
	void showNumber();
	double getNumber();

	BinCode operator +(BinCode a);
	BinCode operator -(BinCode a);
	BinCode operator *(BinCode a);
	BinCode operator/(BinCode a);
	BinCode operator%(BinCode a);

private:
	vector<int> straightCode;
	vector<int> reverseCode;
	vector<int> addCode;
	vector<int> fixedPointCode;
	vector<int> floatPointCode;
	double number = 0;
	int comma = 0;
	void makeFixedPointCode(double num);
	void makeIntNumber();
	void makeDoubleNumber(int a);
	void makeStraightCode(int a);
	void makeReverseCode();
	void makeAddCode();
	void makeFloatPointCode(int a);
};


