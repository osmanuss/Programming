#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

const double PI = 3.141592653589793;
const double precision = 1e-10;

enum type
{
    Cartesian,
    Polar
};

class Point
{
private:
    double x, y;

public:
    Point(double a1 = 0, double a2 = 0, type coord_system = Cartesian)
    {
        if (coord_system == Cartesian)
        {
            x = a1;
            y = a2;
            return;
        }
        else
        {
            x = a1 * cos(a2);
            y = a1 * sin(a2);
        }
    }

    bool operator ==(const Point& second) const
    {
        return abs(x - second.x) < precision && abs(y - second.y) < precision;
    }

    bool operator !=(const Point& second) const
    {
        return !(*this == second);
    }

    double get_x() const
    {
        return x;
    }

    double get_y() const
    {
        return y;
    }

    double get_r() const
    {
        return sqrt(x * x + y * y);
    }

    double get_phi() const
    {
        return atan(y / x) + (x < 0 ? PI : 0);
    }

    void set_x(double x)
    {
        this->x = x;
    }

    void set_y(double y)
    {
        this->y = y;
    }

    void set_r(double r)
    {
        double phi = get_phi();
        this->x = cos(phi) * r;
        this->y = sin(phi) * r;
    }

    void set_phi(double phi)
    {
        double r = get_r();
        this->x = cos(phi) * r;
        this->y = sin(phi) * r;
    }
};

std::ostream& operator <<(std::ostream& out, const Point& point)
{
    return out << '(' << point.get_x() << ',' << point.get_y() << ')';
}

std::istream& operator >>(std::istream& in, Point& point)
{
    double num;
    in.ignore(1);
    in >> num;
    point.set_x(num);
    in.ignore(1);
    in >> num;
    point.set_y(num);
    in.ignore(1);
    return in;
}

class Vector
{
private:
    Point line;

public:
    Vector()
        : line(1, 0)
    {
    }

    Vector(const Point& end)
        : line(end.get_x(), end.get_y())
    {
    }

    Vector(const Point& begin, const Point& end)
        : line(end.get_x() - begin.get_x(), end.get_y() - begin.get_y())
    {
    }

    bool operator ==(const Vector& second) const
    {
        return line == second.line;
    }

    Vector operator -() const
    {
        Point vec = line;
        vec.set_x(-vec.get_x());
        vec.set_y(-vec.get_y());
        return Vector(vec);
    }

    Vector operator +(const Vector& second) const
    {
        Point vec;
        vec.set_x(line.get_x() + second.line.get_x());
        vec.set_y(line.get_y() + second.line.get_y());
        return Vector(vec);
    }

    Vector operator -(const Vector& second) const
    {
        Point vec;
        vec.set_x(line.get_x() - second.line.get_x());
        vec.set_y(line.get_y() - second.line.get_y());
        return Vector(vec);
    }

    Vector operator *(double mul) const
    {
        Point vec = line;
        vec.set_x(vec.get_x() * mul);
        vec.set_y(vec.get_y() * mul);
        return Vector(vec);
    }

    double length() const
    {
        return line.get_r();
    }

    double operator *(const Vector& second) const
    {
        return length() * second.length() * cos(line.get_phi() - second.line.get_phi());
    }
};

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox * ox, sqr(ox.length())) &&
        equal(oy * oy, sqr(oy.length())) &&
        equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), sqr((ox * 3 + oy * 4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}