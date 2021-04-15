#include "list.h"
#include "polinom.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void Polinom::ToWriteMonom()
{
	int i = 0;
	monom.DeleteAllNodes();
	vector<string> monoms;//для записи мономов;
	while(i < polinom.size())//разделяем полином на мономы и записываем в вектор;
	{
		string monom1;
		do
		{
			monom1 += polinom[i];
			i++;
		} while (!IsSign(polinom[i]) && i != polinom.size());
		monoms.push_back(monom1);
	}
	for (int i = 0; i < monoms.size(); i++)
	{
		string coefficient;
		int j = 0;
		if (IsVariable(monoms[i][j]))
		{
			coefficient = "1";
		}
		else
		{
			while (!IsVariable(monoms[i][j]) && j != monoms[i].size())
			{
				coefficient += monoms[i][j];
				j++;
			}
		}
		if (j == monoms[i].size())
		{
			double b = atof(coefficient.c_str());
			Monom tmp(b, 0);
			monom.PushBack(tmp);
		}
		else
		{
			int pow1 = 0;
			for (j; j < monoms[i].size(); j++)
			{
				if (monoms[i][j] == 'x')
				{
					if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
					{
						pow1 += 100;
					}
					else
					{
						j = j + 2;
						pow1 += (int)(monoms[i][j] - '0') * 100;
					}
				}
				else
					if (monoms[i][j] == 'y')
					{
						if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
						{
							pow1 += 10;
						}
						else
						{
							j = j + 2;
							pow1+= (int)(monoms[i][j] - '0') * 10;
						}
					}
					else
						if (monoms[i][j] == 'z')
						{
							if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
							{
								pow1 += 1;
							}
							else
							{
								j = j + 2;
								pow1 += (int)(monoms[i][j] - '0');
							}
						}
			}
			Monom tmp(atof(coefficient.c_str()), pow1, "");
			monom.PushBack(tmp);
		}
	}
}

bool Polinom::IsVariable(char c)
{
	return (c == 'x' || c == 'y' || c == 'z');
}

bool Polinom::IsSign(char c)
{
	return (c == '+' || c == '-');
}

bool Polinom::operator==(const Polinom &pol)
{
	if (monom == pol.monom)
		return 1;
	else
		return 0;
}

bool Polinom::operator!=(const Polinom & pol)
{
	return !(*this == pol);
}

Polinom & Polinom::operator=(Polinom & pol)
{
	if (*this == pol) 
		return *this;
	monom = pol.monom;
	polinom = pol.polinom;
	return *this;
}

string Polinom::GetPol(Polinom& p)
{
	string kk;
	for (auto it = p.monom.Begin(); it != p.monom.End(); ++it)
	{
		int deg = it->data.GetPow();
		if (it != p.monom.Begin() && it->data.GetCoeff() > 0)
		{
			kk += "+";
		}
		double coef = round(it->data.GetCoeff()*10.0) / 10.0;
		kk += to_string(coef);
		if ((int)(deg / 100) % 10 != 0)
		{
			if ((int)(deg / 100) % 10 == 1)
			{
				kk += "x";
			}
			else
				kk = kk + "x^" + to_string((int)(deg / 100) % 10);
		}
		if ((int)(deg / 10) % 10 != 0)
		{
			if ((int)(deg / 10) % 10 == 1)
			{
				kk += "y";
			}
			else
				kk = kk + "y^" + to_string((int)(deg / 10) % 10);
		}
		if (deg % 10 != 0)
		{
			if (deg % 10 == 1)
			{
				kk += "z";
			}
			else
				kk += "z^" + to_string(deg % 10);
		}
	}
	return kk;
}

Polinom Polinom::operator+(Polinom& p)
{
	Polinom sum, pol1, pol2;
	List<Monom>::LinkPointer it1, it2, it3 = sum.Begin();

	pol1 = *this;
	pol2 = p;
	it1 = monom.Begin();
	it2 = p.monom.Begin();
	while (it1 != pol1.monom.End())
	{
		if (it2 == pol2.monom.End())
		{
			sum.monom.Insert1(it3.GetIntenge(), &it1);
			++it1;
		}
		else
			if (it1->data.GetPow() == it2->data.GetPow())
			{
				if ((it1->data.GetCoeff() + it2->data.GetCoeff()) != 0)
				{
					sum.monom.Insert1(it3.GetIntenge(),&(it1)+&(it2));
				}
				++it1;
				++it2;
			}
			else if (it1->data.GetPow() > it2->data.GetPow())
			{
				sum.monom.Insert1(it3.GetIntenge(),&it1);
				++it1;
			}
			else
			{
				sum.monom.Insert1(it3.GetIntenge(),&it2);
				++it2;
			}
	}
	while (it2 != pol2.monom.End())
	{
		sum.monom.Insert1(it3.GetIntenge(),&it2);
		++it2;
	}
	return sum;
}

Polinom Polinom::operator-(Polinom & p)
{
	Polinom sub, pol1, pol2;
	List<Monom>::LinkPointer it1, it2, it3;
	pol1 = *this;
	pol2 = p;
	it1 = monom.Begin();
	it2 = p.monom.Begin();
	for (it1; it1 != pol1.monom.End();)
	{
		if (it2 == pol2.monom.End())
		{
			sub.monom.PushBack(&it1);
			++it1;
		}
		else
			if (it1->data.GetPow() == it2->data.GetPow())
			{
				if ((it1->data.GetCoeff() - it2->data.GetCoeff()) != 0)
					sub.monom.PushBack(&(it1)-&(it2));
				++it1; ++it2;
			}
			else
				if (it1->data.GetPow() > it2->data.GetPow())
				{
					sub.monom.PushBack(&it1);
					++it1;
				}
				else
				{
					Monom mn(-it2->data.GetCoeff(), it2->data.GetPow());
					it3.Change(mn);
					sub.monom.PushBack(&(it3));
					++it2;
				}
	}
	while (it2 != pol2.monom.End())
	{
		Monom mn(-it2->data.GetCoeff(), it2->data.GetPow());
		it3.Change(mn);
		sub.monom.PushBack(&(it3));
		++it2;
	}
	return sub;
}

Polinom Polinom::operator*( Polinom & p)
{
	Monom monom1;
	Polinom mul, pol1, pol2;
	List<Monom>::LinkPointer it1, it2, it4=mul.Begin();

	pol1 = *this;
	pol2 = p;
	it1 = monom.Begin();
	for (it1; it1 != pol1.monom.End();)
	{
		it2 = p.monom.Begin();
		while (it2 != pol2.monom.End())
		{
			mul.monom.Insert1(it4.GetIntenge(), &(it1)*&(it2));
			++it2;
		}
		++it1;
	}
	return mul;
}

double Polinom::Result(int _x, int _y, int _z)
{
	monom.DeleteAllNodes();
	double sum = 0;
	vector<string> monoms; 
	int i = 0;
	while (i < polinom.length())
	{
		string Monom;
		do
		{
			Monom += polinom[i];
			i++;
		} while (!IsSign(polinom[i]) && i != polinom.size());
		monoms.push_back(Monom);
	}
	for (int i = 0; i < monoms.size(); i++)
	{
		string coeff;
		int j = 0;
		while (!IsVariable(monoms[i][j]) && j != monoms[i].size())
		{
			coeff += monoms[i][j];
			j++;
		}
		if (j == monoms[i].size())
		{
			sum += atof(coeff.c_str());
		}
		else
		{
			double mult = 1;
			for (j; j < monoms[i].size(); j++)
			{
				if (monoms[i][j] == 'x')
				{
					if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
					{
						mult *= _x;

					}
					else
					{
						int pr = 1;
						for (int t = 0; t < (int)(monoms[i][j + 2] - '0'); t++)
						{
							pr *= _x;
						}
						mult *= pr;
						j = j + 2;
					}
				}
				else
					if (monoms[i][j] == 'y')
					{
						if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
						{
							mult *= _y;

						}
						else
						{
							int pr = 1;
							for (int t = 0; t < (int)(monoms[i][j + 2] - '0'); t++)
							{
								pr *= _y;
							}
							mult *= pr;
							j = j + 2;
						}
					}
					else
						if (monoms[i][j] == 'z')
						{
							if (j + 1 == monoms[i].size() || monoms[i][j + 1] != '^')
							{
								mult *= _z;

							}
							else
							{
								int pr = 1;
								for (int t = 0; t < (int)(monoms[i][j + 2] - '0'); t++)
								{
									pr *= _z;
								}
								mult *= pr;
								j = j + 2;
							}
						}
			}
			double qw = 1;
			qw = (atof(coeff.c_str()))*mult;
			sum += ((atof(coeff.c_str()))*mult);

		}
	}
	return sum;
}
ostream & operator<<(ostream & os, Polinom & p)
{
	for (auto it = p.monom.Begin(); it != p.monom.End(); ++it)
	{
		int deg = it->data.GetPow();
		if (it != p.monom.Begin() && it->data.GetCoeff() > 0.0)
		{
			os << "+";
			os << to_string(it->data.GetCoeff());
		}
		else
		{
			if (it == p.monom.Begin() || it->data.GetCoeff() < 0.0)
				os << to_string(it->data.GetCoeff());
			else
				os << "+";
		}
		if ((int)(deg / 100) % 10 != 0)
		{
			if ((int)(deg / 100) % 10 == 1)
				os << "x";
			else
				os << "x^" << (int)(deg / 100) % 10;
		}
		if ((int)(deg / 10) % 10 != 0)
		{
			if ((int)(deg / 10) % 10 == 1)
				os << "y";
			else
				os << "y^" << (int)(deg / 10) % 10;
		}
		if (deg % 10 != 0)
		{
			if (deg % 10 == 1)
				os << "z";
			else
				os << "z^" << deg % 10;
		}
	}
	return os;
}
istream & operator>>(istream & is, Polinom & pol)
{
	is >> pol.polinom;
	pol.ToWriteMonom();
	return is;
}