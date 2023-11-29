#include<iostream>
#include<string>
#include<cmath>

int main() {
    double x, y;
    std::cout << "Input your x: ";
    std::cin >> x;
    std::cout << "Input your y: ";
    std::cin >> y;
    std::cout << "The magnitude is " << std::sqrt(x*x+y*y) << std::endl;
    return 0;
}
