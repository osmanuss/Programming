#include <iostream>

double bmi(double weight, double height) 
{
    height /= 100;
    return weight / (height * height);
}

void printBMI(double BMI) 
{
    if (BMI < 18.5)
        std::cout << "Underweight";
    else 
        if (BMI >= 18.5 && BMI < 25.0)
        std::cout << "Normal";
    else 
        if (BMI >= 25.0 && BMI < 30.0)
        std::cout << "Overweight";
    else 
        if (30.0 <= BMI)
        std::cout << "Obesity";
}
int main()
{
    double weight, height;
    std::cin >> weight >> height;
    printBMI(bmi(weight, height));
}