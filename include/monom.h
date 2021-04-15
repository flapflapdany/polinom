#ifndef __MONOM_H__
#define __MONOM_H__

#include "list.h"
#include "polinom.h"
#include <stdlib.h>
#include <string>
#include <vector>

class Monom
{
	double coefficient;//коэффициент;
	int pow;
public:
	Monom(double coefficient = 0, int pow = 0, string _monom = "")
	{
		this->coefficient = coefficient;
		this->pow = pow;
	}
	Monom operator+(const Monom &monom);
	Monom operator-(const Monom &monom);
	Monom operator*(const Monom &monom);
	bool   operator==(const Monom &monom);
	bool   operator!=(const Monom &monom);
	bool   IsEqualPow(Monom monom);
	double GetCoeff() { return coefficient; } 
	int    GetPow() { return pow; } 
};

inline Monom Monom::operator+(const Monom & monom)
{
	if (pow != monom.pow)
		throw "Error";
	Monom res;
	res.coefficient = coefficient + monom.coefficient;
	res.pow = pow;
	return res;
}

inline Monom Monom::operator-(const Monom & monom)
{
	if (pow != monom.pow)
		throw "Error";
	Monom res;
	res.coefficient = coefficient - monom.coefficient;
	res.pow = monom.pow;
	return res;
}

inline Monom Monom::operator*(const Monom & monom)
{
	Monom res;
	res.coefficient = coefficient * monom.coefficient;
	res.pow = pow + monom.pow;
	return res;
}

inline bool Monom::operator==(const Monom & monom)
{
	return ((coefficient == monom.coefficient) && (pow == monom.pow));
}

inline bool Monom::operator!=(const Monom & monom)
{
	return ((coefficient != monom.coefficient) && (pow != monom.pow));
}

inline bool Monom::IsEqualPow(Monom monom)
{
	return (GetPow() == monom.GetPow());
}
#endif