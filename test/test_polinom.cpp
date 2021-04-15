#include "polinom.h"
#include "monom.h"
#include <gtest.h>

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p("x^4y^5z^2-x^3y^2z^8+7xyz^6+z"));
}

TEST(Polinom, can_compare_equal_polinoms)
{
	Polinom p1("x^7y^3+7x^4y^5z^2-3x^3y^5+8x-1");
	Polinom p2("x^7y^3+7x^4y^5z^2-3x^3y^5+8x-1");
	EXPECT_TRUE(p1 == p2);
}

TEST(Polinom, can_assign_polinoms)
{
	Polinom p1("4x^3y^3+7x^4y^5z^2");
	Polinom p2("-3x^3+8x");
	ASSERT_NO_THROW(p2 = p1);
}

TEST(Polinom, result_polinom_in_point)
{
	Polinom p1("2.1x^4y^2z+7xyz+2z");
	double res = p1.Result(1, 1, 2);
	EXPECT_TRUE(22.2 == res);
}

TEST(Polinom, can_check_operation)
{
	Polinom p1("7x^4y^5z^2-3x^3y^5+8x-14");
	Polinom p2;
	string p = p2.GetPol(p1);
	EXPECT_EQ(1, p1.IsSign(p[17]));
}
TEST(Polinom, can_check_symbol_in_polinom)
{
	Polinom p1("7x^4y^5z^2-3x^3y^5+8x-14");
	Polinom p2;
	string p = p2.GetPol(p1);
	EXPECT_EQ(1, p1.IsVariable(p[8]));
}

TEST(Polinom, addition_different_polinoms)
{
	Polinom p1("10x^5y^3z^2+4x^4y^5z^2-3x^3y^5+5x^2y^5z^6+3xy^5z^6-8xyz+10");
	Polinom p2("-4x^4y^5z^2+3x^3y^5+5x^2y^5z+8xyz-10");
	Polinom p3;
	EXPECT_EQ("10.000000x^5y^3z^2+5.000000x^2y^5z^6+5.000000x^2y^5z+3.000000xy^5z^6", p3.GetPol(p1 + p2));
}

TEST(Polinom, subtraction_different_polinoms)
{
	Polinom p1("10x^5y^3z^2+4x^4y^5z^2-3x^3y^5+5x^2y^5z^6+3xy^5z^6-8xyz+10");
	Polinom p2("-4x^4y^5z^2+3x^3y^5+5x^2y^5z+8xyz-10");
	Polinom p3;
	EXPECT_EQ("10.000000x^5y^3z^2+8.000000x^4y^5z^2-6.000000x^3y^5+5.000000x^2y^5z^6-5.000000x^2y^5z+3.000000xy^5z^6-16.000000xyz+20.000000", p3.GetPol(p1 - p2));
}

TEST(Monom, can_get_coefficient_monom)
{
	Monom m(11.0, 19);
	Monom m1;
	m1 = m;
	EXPECT_TRUE(11.0 == m1.GetCoeff());
}
TEST(Monom, can_get_pow)
{
	Monom mon(1.0, 111);
	EXPECT_TRUE(111 == mon.GetPow());
}

TEST(Monom, can_check_different)
{
	Monom mon(15.0, 54);
	Monom mon1(27.3, 89);
	EXPECT_TRUE(mon1 != mon);
}

TEST(Monom, can_check_equal_monom)
{
	Monom mon(10.0, 54);
	Monom mon1(10.0, 54);
	EXPECT_TRUE(mon1 == mon);
}