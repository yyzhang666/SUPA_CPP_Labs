#include <string>
#include <vector>
#include "gnuplot-iostream.h"
#include "FiniteFunctions.h"

#pragma once //Replacement for IFNDEF

class normalDistribution: public FiniteFunction{

public:
    normalDistribution():FiniteFunction(){};
    normalDistribution(double range_min, double range_max, std::string outfile):FiniteFunction(range_min,range_max, outfile){};

    void printInfo(); //Dump parameter info about the current function (Overridable)
    double callFunction(double x); //Call the function with value x (Overridable)
    void setSigma(double user_sigma);//user set function parameters
    void setMu(double user_mu);
    void metropolis(std::vector<double> &sample);//my sample comes from this class
    

private:
    double x,sigma,mu;
    double gaussian(double x);
    double sampledistribution(double x);//The function which I will sample from.
};

class CauchyLorentz: public FiniteFunction{

public:
    CauchyLorentz():FiniteFunction(){};
    CauchyLorentz(double range_min, double range_max, std::string outfile):FiniteFunction(range_min,range_max, outfile){};

    void printInfo(); //Dump parameter info about the current function (Overridable)
    double callFunction(double x);
    void setGamma(double user_gamma);//user set function parameters
    void setX0(double user_x0);

private:
    double gamma,x0;
    double cauchy(double x);
    
};

class negativeCrystallBall: public FiniteFunction{

public:
    negativeCrystallBall():FiniteFunction(){};
    negativeCrystallBall(double range_min, double range_max, std::string outfile):FiniteFunction(range_min,range_max, outfile){};
    
    void printInfo(); //Dump parameter info about the current function (Overridable)
    double callFunction(double x);
    void setSigmaCry(double user_sigmaCry);//user set function parameters
    void setXbar(double user_xbar);
    void setAlpha(double user_alpha);
    void setN(double user_n);

private:
    double crystall(double x);
    double sigmaCry,xbar,alpha,n;
    double A,B,N,C,D;
    
};