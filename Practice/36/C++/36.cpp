#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}