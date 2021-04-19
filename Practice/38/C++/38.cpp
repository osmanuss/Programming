#include <iostream>
#include <cmath>

bool equal(double a, double b, double e = 1E-10);

int signOf(int a) {
    if (a < 0) {
        return -1;
    }
    else {
        return 1;
    }
}

class Rational
{
private:
    int num, den, sign;
public:
    static int gcd(int a, int b)
    {
        if (a == 0)
        {
            return b;
        }
        if (b == 0)
        {
            return a;
        }
        if (b > a)
        {
            std::swap(a, b);
        }
        for (int i = b; i > 1; --i)
        {
            if (a % i == 0 and b % i == 0)
            {
                return i;
            }
        }
        return 1;
    }
    Rational() : num(0), den(1), sign(1)
    {}

    Rational(int a, int b) : num(abs(a)), den(abs(b)), sign(signOf(a) == signOf(b) ? 1 : -1)
    {
        if (a != 0 and b != 0)
        {
            int NOD = Rational::gcd(num, den);
            num /= NOD;
            den /= NOD;
        }
    }

    bool isNaN() const
    {
        return num == 0 and den == 0;
    }

    bool operator ==(const Rational& second) const
    {
        if (isNaN() or second.isNaN())
        {
            return false;
        }
        if (num == 0 and second.num == 0)
        {
            return true;
        }
        if (sign != second.sign)
        {
            return false;
        }
        if (den == 0 and second.den == 0)
        {
            return true;
        }
        return num == second.num and den == second.den;
    }

    Rational operator +(const Rational& second) const
    {
        if (isNaN() or second.isNaN())
        {
            return Rational(0, 0);
        }
        if (den == 0 and second.den == 0)
        {
            if (sign == second.sign)
            {
                return second;
            }
            else
            {
                return Rational(0, 0);
            }
        }
        return Rational((sign * num * second.den) + (second.sign * second.num * den), den * second.den);
    }

    Rational operator -(const Rational& second) const
    {
        Rational reserv = second;
        reserv.sign = -reserv.sign;
        return *this + reserv;
    }

    Rational operator *(const Rational& second) const
    {
        Rational out(num * second.num, den * second.den);
        out.sign = sign * second.sign;
        return out;
    }

    Rational operator /(const Rational& second) const
    {
        auto out = Rational(num * second.den, den * second.numerator());
        out.sign = sign * second.sign;
        return out;
    }

    operator double() const
    {
        return sign * num / double(den);
    }

    operator bool() const
    {
        return num != 0 or den == 0;
    }

    int numerator() const
    {
        return num;
    }

    int denominator() const
    {
        return den;
    }
};





















int main()
{
    if (Rational::gcd(91, 65) == 13 &&
        Rational::gcd(10, 3) == 1 &&
        Rational::gcd(-10, 3) == 1 &&
        Rational::gcd(10, -3) == 1 &&
        Rational::gcd(-10, -3) == 1 &&
        Rational::gcd(30, 10) == 10 &&
        Rational::gcd(10, 30) == 10 &&
        Rational::gcd(0, 10) == 10 &&
        Rational::gcd(10, 0) == 10) std::cout << "gcd test passed\n";
    else std::cout << "gcd test failed\n";

    if (!Rational(22, 0).isNaN() &&
        !Rational(22, 9).isNaN() &&
        !Rational(0, 9).isNaN() &&
        !Rational(-22, 9).isNaN() &&
        !Rational(-22, 0).isNaN() &&
        Rational(0, 0).isNaN()
        ) std::cout << "isNaN test passed\n";
    else std::cout << "isNaN test failed\n";

    if (Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 0) == Rational(9, 0) &&
        !(Rational(22, 0) == Rational(22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 0)) &&
        !(Rational(22, 0) == Rational(0, 9)) &&
        !(Rational(22, 0) == Rational(0, 0)) &&

        Rational(22, 9) == Rational(22, 9) &&
        Rational(22, 9) == Rational(-22, -9) &&
        Rational(22, 9) == Rational(110, 45) &&
        Rational(22, 9) == Rational(-110, -45) &&
        !(Rational(22, 9) == Rational(-22, 9)) &&
        !(Rational(22, 9) == Rational(22, -9)) &&
        !(Rational(22, 9) == Rational(9, 22)) &&
        !(Rational(22, 9) == Rational(22, 0)) &&
        !(Rational(22, 9) == Rational(-22, 0)) &&
        !(Rational(22, 9) == Rational(0, 9)) &&
        !(Rational(22, 9) == Rational(0, 0)) &&

        Rational(0, 1) == Rational(0, 1) &&
        Rational(0, 1) == Rational(0, 9) &&
        Rational(0, 1) == Rational(0, -9) &&
        !(Rational(0, 1) == Rational(22, 9)) &&
        !(Rational(0, 1) == Rational(-22, 9)) &&
        !(Rational(0, 1) == Rational(22, 0)) &&
        !(Rational(0, 1) == Rational(-22, 0)) &&
        !(Rational(0, 1) == Rational(0, 0)) &&

        Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) == Rational(22, -9) &&
        Rational(-22, 9) == Rational(-110, 45) &&
        Rational(-22, 9) == Rational(110, -45) &&
        !(Rational(-22, 9) == Rational(-22, -9)) &&
        !(Rational(-22, 9) == Rational(22, 9)) &&
        !(Rational(-22, 9) == Rational(9, -22)) &&
        !(Rational(-22, 9) == Rational(22, 0)) &&
        !(Rational(-22, 9) == Rational(-22, 0)) &&
        !(Rational(-22, 9) == Rational(0, 9)) &&
        !(Rational(-22, 9) == Rational(0, 0)) &&

        Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) == Rational(-9, 0) &&
        !(Rational(-22, 0) == Rational(22, 9)) &&
        !(Rational(-22, 0) == Rational(-22, 9)) &&
        !(Rational(-22, 0) == Rational(22, 0)) &&
        !(Rational(-22, 0) == Rational(0, 9)) &&
        !(Rational(-22, 0) == Rational(0, 0)) &&

        !(Rational(0, 0) == Rational(0, 0))
        ) std::cout << "Equality test passed\n";
    else std::cout << "Equality test failed\n";

    if (Rational(22, 0) + Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(0, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(-22, 9) + Rational(22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) + Rational(22, 0)).isNaN() &&

        Rational(22, 0) + Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 9) == Rational(44, 9) &&
        Rational(0, 9) + Rational(22, 9) == Rational(22, 9) &&
        Rational(-22, 9) + Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 0) + Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) + Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) + Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) + Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) + Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(-22, 9) == Rational(0, 9) &&
        Rational(0, 9) + Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) + Rational(-22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) + Rational(-22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(-22, 0)).isNaN() &&
        Rational(22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(0, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) + Rational(-22, 0) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(0, 0)).isNaN() &&
        (Rational(22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(0, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) + Rational(0, 0)).isNaN()
        ) std::cout << "Summation test passed\n";
    else std::cout << "Summation test failed\n";

    if ((Rational(22, 0) - Rational(22, 0)).isNaN() &&
        Rational(22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(0, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) - Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(22, 9) == Rational(0, 9) &&
        Rational(0, 9) - Rational(22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) - Rational(22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) - Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) - Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) - Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) - Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) - Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 9) == Rational(44, 9) &&
        Rational(0, 9) - Rational(-22, 9) == Rational(22, 9) &&
        Rational(-22, 9) - Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 0) - Rational(-22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(0, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) - Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) - Rational(0, 0)).isNaN() &&
        (Rational(22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(0, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) - Rational(0, 0)).isNaN()
        ) std::cout << "Subtraction test passed\n";
    else std::cout << "Subtraction test failed\n";

    if (Rational(22, 0) * Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 0) == Rational(22, 0) &&
        (Rational(0, 9) * Rational(22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) * Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) * Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 9) == Rational(22 * 22, 9 * 9) &&
        Rational(0, 9) * Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(22, 9) == Rational(-22 * 22, 9 * 9) &&
        Rational(-22, 0) * Rational(22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) * Rational(0, 1)).isNaN() &&
        Rational(22, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(0, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(0, 1) == Rational(0, 9) &&
        (Rational(-22, 0) * Rational(0, 1)).isNaN() &&

        Rational(22, 0) * Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 9) == Rational(-22 * 22, 9 * 9) &&
        Rational(0, 9) * Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(-22, 9) == Rational(22 * 22, 9 * 9) &&
        Rational(-22, 0) * Rational(-22, 9) == Rational(22, 0) &&

        Rational(22, 0) * Rational(-22, 0) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 0) == Rational(-22, 0) &&
        (Rational(0, 9) * Rational(-22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 0) * Rational(-22, 0) == Rational(22, 0) &&

        (Rational(22, 0) * Rational(0, 0)).isNaN() &&
        (Rational(22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(0, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) * Rational(0, 0)).isNaN()
        ) std::cout << "Multiplication test passed\n";
    else std::cout << "Multiplication test failed\n";

    if ((Rational(22, 0) / Rational(22, 0)).isNaN() &&
        Rational(22, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(22, 0)).isNaN() &&

        Rational(22, 0) / Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) / Rational(22, 9) == Rational(9, 9) &&
        Rational(0, 9) / Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 9) == Rational(-9, 9) &&
        Rational(-22, 0) / Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) / Rational(0, 1) == Rational(22, 0) &&
        (Rational(0, 9) / Rational(0, 1)).isNaN() &&
        Rational(-22, 9) / Rational(0, 1) == Rational(-22, 0) &&
        Rational(-22, 0) / Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) / Rational(-22, 9) == Rational(-9, 9) &&
        Rational(0, 9) / Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 9) == Rational(9, 9) &&
        Rational(-22, 0) / Rational(-22, 9) == Rational(22, 0) &&

        (Rational(22, 0) / Rational(-22, 0)).isNaN() &&
        Rational(22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) / Rational(0, 0)).isNaN() &&
        (Rational(22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(0, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) / Rational(0, 0)).isNaN()
        ) std::cout << "Division test passed\n";
    else std::cout << "Division test failed\n";

    if (equal(Rational(-22, -9), 22 / 9.0) &&
        equal(Rational(-9, -9), 1) &&
        equal(Rational(-6, -9), 6 / 9.0) &&
        equal(Rational(0, -9), 0) &&
        equal(Rational(6, -9), -6 / 9.0) &&
        equal(Rational(9, -9), -1) &&
        equal(Rational(22, -9), -22 / 9.0) &&
        std::isinf((double)Rational(-9, 0)) &&
        std::isnan((double)Rational(0, 0)) &&
        std::isinf((double)Rational(9, 0)) &&
        equal(Rational(-22, 9), -22 / 9.0) &&
        equal(Rational(-9, 9), -1) &&
        equal(Rational(-6, 9), -6 / 9.0) &&
        equal(Rational(0, 9), 0) &&
        equal(Rational(6, 9), 6 / 9.0) &&
        equal(Rational(9, 9), 1) &&
        equal(Rational(22, 9), 22 / 9.0)) std::cout << "Conversion to double test passed\n";
    else std::cout << "Conversion to double test failed\n";

    if (Rational(-22, -9) &&
        Rational(-9, -9) &&
        Rational(-6, -9) &&
        !Rational(0, -9) &&
        Rational(6, -9) &&
        Rational(9, -9) &&
        Rational(22, -9) &&
        Rational(-9, 0) &&
        Rational(0, 0) &&
        Rational(9, 0) &&
        Rational(-22, 9) &&
        Rational(-9, 9) &&
        Rational(-6, 9) &&
        !Rational(0, 9) &&
        Rational(6, 9) &&
        Rational(9, 9) &&
        Rational(22, 9)) std::cout << "Conversion to bool test passed\n";
    else std::cout << "Conversion to bool test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}