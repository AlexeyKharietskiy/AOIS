#include "BinCode.h"

BinCode::BinCode() {
	straightCode = { 0,0,0,0,0,0,0,0 };
	reverseCode = { 0,0,0,0,0,0,0,0 };
	addCode = { 0,0,0,0,0,0,0,0 };
}
BinCode::BinCode(int a)
{
	makeStraightCode(a);
	makeReverseCode();
	makeAddCode();
	makeIntNumber();
}
BinCode::BinCode(double a) {
	makeFixedPointCode(a);
}

double BinCode::getNumber() {
	return number;
}
void BinCode::showStraightCode(){
	for (int i = 0; i < 8; i++)
	{
		cout << straightCode[i] << " ";
	}
	cout << endl;
}
void BinCode::showReverseCode() {
	for (int i = 0; i < 8; i++)
	{
		cout << reverseCode[i] << " ";
	}
	cout << endl;
}
void BinCode::showAddCode() {
	for (int i = 0; i < 8; i++)
	{
		cout << addCode[i] << " ";
	}
	cout << endl;
}
void BinCode::showFixedPointCode() {
	for (int i = 0; i < fixedPointCode.size(); i++)
	{
		cout << fixedPointCode[i] << " ";
		if (i == comma)
			cout << ". ";
	}
	cout << endl;
}
void BinCode::showFloatPointCode() {
	for (int i = 0; i < 32; i++)
	{
		cout << floatPointCode[i] << " ";
		if (i == 0 || i == 8)
			cout << "| ";
	}
	cout << endl;
}
void BinCode::showNumber() {

	cout << number << endl;
}

void BinCode::makeStraightCode(int a) {
	straightCode = { 0,0,0,0,0,0,0,0 };
	if (a < 0)
	{
		straightCode[0] = 1;
		a = abs(a);
	}
	else
		straightCode[0] = 0;
	for (int i = 7; i > 0; i--)
	{
		if (a != 0) {
			straightCode[i] = a % 2;
			a /= 2;
		}
		else
			straightCode[i] = 0;
	}
}
void BinCode::makeReverseCode() {
	reverseCode = { 0,0,0,0,0,0,0,0 };
	if (straightCode[0] == 1)
	{
		reverseCode[0] = 1;
		for (int i = 1; i < 8; i++)
		{
			if (straightCode[i] == 0)
				reverseCode[i] = 1;
			else
				reverseCode[i] = 0;
		}
	}
	else
		reverseCode = straightCode;
}
void BinCode::makeAddCode() {
	addCode = {0,0,0,0,0,0,0,0};
	if (straightCode[0] == 0)
		addCode = straightCode;
	else
	{
		addCode[0] = 1;
		int carry = 1;
		for (int i = 7; i > 0; i--)
		{
			switch (reverseCode[i] + carry)
			{
			case 0:
				addCode[i] = 0;
				break;
			case 1:
				addCode[i] = 1;
				carry = 0;
				break;
			case 2:
				addCode[i] = 0;
				carry = 1;
				break;
			default:
				break;
			}
		}
	}
}
void BinCode::makeFloatPointCode(int sign) {
	vector<int> result(32,0);
	int point = comma;
	point += 127;
	result.insert(result.begin(), sign);
	for (int i = 8; i > 0; i--)
	{
		if (point != 0) {
			result[i] = point% 2;
			point /= 2;
		}
		else
			result[i] = 0;
	}
	for (int i = 9, j = 1; i < 32; i++, j++)
	{
		if (j < fixedPointCode.size())
			result[i] = fixedPointCode[j];
		else
			result[i] = 0;
	}
	floatPointCode = result;
}
void BinCode::makeFixedPointCode(double num) {

	vector<int> result;
	int pointIndex = 0;
	int sign;
	sign = ((num < 0) ? 1 : 0);
	if (num < 0)
		num = abs(num);
	int integerPart = static_cast<int>(num);

	while (integerPart > 0) {
		result.insert(result.begin(), integerPart % 2);
		integerPart /= 2;
		pointIndex++;
	}
	pointIndex--;
	double fractionPart = num - static_cast<int>(num);
	while (fractionPart != 0 && result.size() < 24) {
		fractionPart *= 2;
		if (fractionPart >= 1) {
			result.push_back(1);
			fractionPart -= 1;
		}
		else {
			result.push_back(0);
		}
	}
	if (result[0] == 0)
		for (int i = 0; result[i] != 1; i++) {
			pointIndex--;
		}
	while (result.size() < 24)
		result.push_back(0);
	fixedPointCode = result;
	comma = pointIndex;
	makeFloatPointCode(sign);
	makeDoubleNumber(sign);
};
void BinCode::makeIntNumber() {
	number = 0;
	for (int i = 7; i > 0; i--)
	{
		if (straightCode[i] != 0) {	
			number += pow(2, 7 - i);
		}
	}
	if (straightCode[0] == 1)
		number *= -1;
}
void BinCode::makeDoubleNumber(int a) {
	number = 0;
	for (int i = 23; i > comma; i--)
	{
		if (fixedPointCode[i] != 0) {
			number += pow(2, comma+(i*(-1)));
		}
	}
	for (int i = comma; i >= 0; i--)
	{
		if (fixedPointCode[i] != 0) {
			number += pow(2, comma-i);
		}
	}
	if (a == 1)
		number *= -1;
}

BinCode  BinCode::operator +(BinCode a) {
	BinCode result;
	int sum, carry = 0;
	for (int i = 7; i >= 0; i--)
	{
		sum = addCode[i] + a.addCode[i];
		switch (sum + carry)
		{
		case 0:
			result.straightCode[i] = 0;
			break;
		case 1:
			result.straightCode[i] = 1;
			carry = 0;
			break;
		case 2:
			result.straightCode[i] = 0;
			carry = 1;
			break;
		case 3:
			result.straightCode[i] = 1;
			carry = 1;
		default:
			break;
		}
	}
	result.makeReverseCode();
	result.makeAddCode();
	if (result.straightCode[0] == 1) {
		result.straightCode = result.addCode;
		result.makeReverseCode();
		result.makeAddCode();
	}
		result.makeIntNumber();
	return result;
}
BinCode  BinCode::operator -(BinCode a) {
	if (a.straightCode[0] == 0) {
		a.straightCode[0] = 1;
		a.makeReverseCode();
		a.makeAddCode();
	}
	else {
		a.straightCode[0] = 0;
		a.makeReverseCode();
		a.makeAddCode();
	}
	BinCode result = *this + a;
	return result;	
}
BinCode BinCode:: operator *(BinCode a) {
	BinCode result;
	BinCode buff;
	for (int i = 7; i > 0; i--) {
		for (int j = 7, k = j; k > 0;) {
			if (i < k)
			{
				buff.addCode[k] = 0;
				k--;
			}
			else
			{
				buff.addCode[k] = a.straightCode[i] * straightCode[j];
				k--; j--;
			}
		}
		result = result + buff;
	}
	if (straightCode[0] == a.straightCode[0])
		result.addCode[0] = 0;
	else
	{
		result.addCode[0] = 1;
		result.straightCode = result.addCode;
		result.makeReverseCode();
		result.makeAddCode();
	}
	result.makeIntNumber();
	return result;
}
BinCode BinCode:: operator /(BinCode a) {
	BinCode result;
	double decimal1 = 0, decimal2 = 0;
	for (int i = 1; i < 8; i++)
	{
		decimal1 += straightCode[i] * pow(2, 7 - i);
		decimal2 += a.straightCode[i] * pow(2, 7 - i);
	}
	if (decimal2 != 0) {
		double quotient = decimal1 / decimal2;
		result.makeFixedPointCode(quotient);
	}
	else {
		cout << "Error: Division by zero" << endl;
	}
	result.makeDoubleNumber((straightCode[0] == a.straightCode[0]) ? 0 : 1);
	return result;
}
BinCode BinCode:: operator%(BinCode a) {
	BinCode result;
	int sum, carry = 0;
	if (a.comma != comma)
		if (a.comma > comma)
		{
			result.comma = a.comma;
			for (int i = 0; i < a.comma - comma; i++)
			{
				fixedPointCode.insert(fixedPointCode.begin(), 0);
			}
		}
		else {
			result.comma = comma;
			for (int i = 0; i < comma - a.comma; i++)
			{
				a.fixedPointCode.insert(a.fixedPointCode.begin(), 0);
			}
		}
	else result.comma = comma;
	vector<int> fixCode(24);
	for (int i = 23; i >= 0; i--)
	{
		sum = fixedPointCode[i] + a.fixedPointCode[i];
		switch (sum + carry)
		{
		case 0:
			fixCode[i] = 0;
			break;
		case 1:
			fixCode[i] = 1;
			carry = 0;
			break;
		case 2:
			fixCode[i] = 0;
			carry = 1;
			break;
		case 3:
			fixCode[i] = 1;
			carry = 1;
		default:
			break;
		}
	}
	if (carry == 1) {
		fixCode.insert(fixCode.begin(), 1);
		result.comma++;
	}
	while (fixCode.size() != 24)
		fixCode.pop_back();
	result.fixedPointCode = fixCode;
	result.makeFloatPointCode(0);
	result.makeDoubleNumber(0);
	return result;
}