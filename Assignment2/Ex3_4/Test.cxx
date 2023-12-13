#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include "customclasses.h"

//read data from file
int readvalue(std::vector<double>& datas) {
    std::fstream myInput;
    myInput.open("MysteryData04123.txt");
    if (myInput.fail()) {
        std::cout << "Sorry, couldn't open file" << std::endl;
        exit(1);
    }
    double x;
    while (myInput >> x) {
        datas.push_back(x);
    }
    myInput.close();
}

// main function
int main() {
     //read data
    std::vector<double> datas;
    readvalue(datas);

    //plot default function
    FiniteFunction Default;
    Default.printInfo();
    Default.plotFunction();
    Default.plotData(datas, 1000, true);

    //Normal distribution
    normalDistribution my_normal(-10.0,10.0,"NormalDistribution");
    my_normal.setSigma(1.5);
    my_normal.setMu(2);
    my_normal.printInfo();
    my_normal.plotFunction();
    my_normal.plotData(datas, 1000, true);

    //Make and plot samples
    std::vector<double> sample;
     my_normal.metropolis(sample);
     my_normal.plotData(sample,1000,false);

    //Cauchy-Lorentz distribution
    CauchyLorentz my_cauchy(-10.0,12.0,"CauchyLorentzDistribution");
    my_cauchy.setGamma(1.5);
    my_cauchy.setX0(2);
    my_cauchy.printInfo();
    my_cauchy.plotFunction();
    my_cauchy.plotData(datas, 1000, true);

    //Negative Crystall Ball distribution
    negativeCrystallBall my_crystall(-10.0,12.0,"NegativeCrystallBallDistribution");
    my_crystall.setAlpha(5);
    my_crystall.setN(3);
    my_crystall.setXbar(2.5);
    my_crystall.setSigmaCry(1);
    my_crystall.printInfo();
    my_crystall.plotFunction();
    my_crystall.plotData(datas, 1000, true);

    return 0;
}
