#include <iostream>
#include <string>
#include "polinom.h"
#include "list.h"
using namespace std;

int main()
{
  setlocale(0, "");
  string pol1, pol2;
  cout << "Введите первый полином: ";
  cin >> pol1;
  cout << "Введите второй полином: ";
  cin >> pol2;
  Polinom polinom1(pol1);
  Polinom polinom2(pol2);
  int k=1;
  while (k)
  {
	  cout << " Выберете действие:                    " << endl
		  << "1.Сложение                              " << endl
		  << "2.Вычитание                             " << endl
		  << "3.Сравнение                             " << endl
		  << "4.Первый полином в заданной точке       " << endl
		  << "5.Второй полином в заданной точке       " << endl
		  << "6.Умножение                             " << endl
		  << "0.Выход                                 " << endl;

	  int n;
	  do
	  {
		  cin >> n;
	  } while ((n < 0) || (n > 6));
	  switch (n)
	  {
	  case 1:
	  {
		  cout << polinom1 + polinom2 << endl;
		  break;
	  }
	  case 2:
	  {
		  cout << polinom1 - polinom2 << endl;
		  break;
	  }
	  case 3:
	  {
		  if (polinom1 == polinom2)
			  cout << "Полиномы равны." << endl;
		  else
			  cout << "Полиномы не равны." << endl;
		  break;
	  }
	  case 4:
	  {
		  int x, y, z;
		  cout << "Введите занчения x,y,z:" << endl;
		  cin >> x;
		  cin >> y;
		  cin >> z;
		  cout << "Полином в точке равен: " << polinom1.Result(x, y, z) << endl;
		  break;
	  }
	  case 5:
	  {
		  int x, y, z;
		  cout << "Введите занчения x,y,z:" << endl;
		  cin >> x;
		  cin >> y;
		  cin >> z;
		  cout << "Полином в точке равен: " << polinom2.Result(x, y, z) << endl;
		  break;
	  }
	  case 6:
	  {
		  cout << polinom1 * polinom2 << endl;
		  break;
	  }
	  case 0:
	  {
		  k = 0;
		  cout << "Работа с полиномами завершена!" << endl;
		  break;
	  }
	  }
  }
  return 0;
}