#ifndef __POLINOM_H__
#define __POLINOM_H__

#include <string>
#include <vector>
#include "list.h"
#include "monom.h"
using namespace std;

class Polinom : public List<Monom>
{
	string polinom;
	List<Monom> monom;
public:
	Polinom(string polinom = "")
	{
		this->polinom = polinom;
		if (polinom != "")
			ToWriteMonom();
	}
	void ToWriteMonom();
	bool IsVariable(char c);
	bool IsSign(char c);
	string GetPol(Polinom& pol);
	double Result(int _x, int _y, int _z);
	bool operator==(const Polinom &p);
	bool operator!=(const Polinom &p);
	Polinom& operator=(Polinom& p);
	Polinom  operator+(Polinom& p);
	Polinom  operator-(Polinom& p);
	Polinom  operator*(Polinom& p);
	friend ostream & operator<<(ostream &os, Polinom &pol);
	friend istream & operator>>(istream &is, Polinom &pol);
};
#endif