#include<iostream>
#include<vector>
#include <cmath>
int main(){
    double x,y;
    x=2.3;
    y=4.5;
    std::vector<double> vec2D = {x, y};
    std::cout<<"The magnitude is "<<sqrt(x*x+y*y)<<std::endl;
}
