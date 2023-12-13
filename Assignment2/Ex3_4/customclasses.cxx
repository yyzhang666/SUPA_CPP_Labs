#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#include "FiniteFunctions.h"
#include "customclasses.h"
#include <filesystem> //To check extensions in a nice way
#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;
//using namespace std;

// parameter setters
void normalDistribution::setSigma(double user_sigma){
    sigma=user_sigma;
};
void normalDistribution::setMu(double user_mu){
    mu=user_mu;
};

void CauchyLorentz::setGamma(double user_gamma){
    if (user_gamma > 0) { 
            gamma = user_gamma;
        } else {
            std::cout << "gamma must be positive." << std::endl;
        };
};
void CauchyLorentz::setX0(double user_x0){
    x0=user_x0;
};

void negativeCrystallBall::setSigmaCry(double user_sigmaCry){
    sigmaCry=user_sigmaCry;
};
void negativeCrystallBall::setXbar(double user_xbar){
    xbar=user_xbar;
};
void negativeCrystallBall::setAlpha(double user_alpha){
    if (user_alpha > 0) { 
            alpha = user_alpha;
        } else {
            std::cout << "alpha must be positive." << std::endl;
        };
};
void negativeCrystallBall::setN(double user_n){
    if (user_n > 1) { 
            n = user_n;
        } else {
            std::cout << "n must bigger than 1." << std::endl;
        };
};

/*
###################
//Function eval, overrided
###################
*/ 
double normalDistribution::gaussian(double x) {return (1.0 / (sigma * std::sqrt(2.0 * M_PI))) * std::exp(-0.5 * std::pow((x - mu) / sigma, 2));
};
double normalDistribution::callFunction(double x) {return this->gaussian(x);}; //(overrided)

double CauchyLorentz::cauchy(double x){return 1 / (M_PI * gamma * (1 + std::pow((x - x0) / gamma, 2)));}
double CauchyLorentz::callFunction(double x){return this->cauchy(x);};

double negativeCrystallBall::crystall(double x){
    A=std::pow(n / std::abs(alpha), n) * std::exp(-std::pow(std::abs(alpha), 2) / 2);
    B=n / std::abs(alpha) - std::abs(alpha);
    C=(n / std::abs(alpha)) * (1 / (n - 1)) * std::exp(-std::pow(std::abs(alpha), 2) / 2);
    D=std::sqrt(M_PI / 2) * (1 + std::erf(std::abs(alpha) / std::sqrt(2)));
    N=1 / (sigmaCry * (C + D));
    double z = (x - xbar) / sigmaCry;//Define the segment
    if (z > alpha) {
        return N * std::exp(-std::pow(z, 2) / 2);
    } else {
        return N * std::pow(A * (B - std::pow(z, n)), n);
    }
}
double negativeCrystallBall::callFunction(double x){return this->crystall(x);};


//Function info
void normalDistribution::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout<<"the parameters 'sigma, mu' are: "<<sigma<<" and "<<mu<<std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}
void CauchyLorentz::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout<<"the parameters 'gamma, x0' are: "<<gamma<<" and "<<x0<<std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}
void negativeCrystallBall::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout<<"the parameters 'alpha,n,sigma ' are: "<<alpha<<" , "<<n<<" and "<<sigmaCry<<std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

//Sampling
double  normalDistribution::sampledistribution(double x){
    return (1.0 / (1.5 * std::sqrt(2.0 * M_PI))) * std::exp(-0.5 * std::pow((x - 2) / 1.5, 2));
}
void normalDistribution::metropolis(std::vector<double> &sample){
    int n_random=10000;

    int i=0;
    double y;
    double x_i;
    double f_y;
    double f_x;
    double A;
    double T;
    
    std::random_device rd;
    std::mt19937 mtEngine{rd()};
    std::uniform_real_distribution<double> dicPDF(-10.0,10.0);
    std::uniform_real_distribution<double> disT(0,1);


    double x_0=dicPDF(mtEngine);
    x_i=x_0;

    while(i<n_random){
        double sig=dicPDF(mtEngine);
        std::normal_distribution<double> norm(x_i,sig);
        y=norm(mtEngine);
        f_y=this->sampledistribution(y);
        f_x=this->sampledistribution(x_i);
        A=std::min(f_y/f_x,1.0);
        T=disT(mtEngine);
        if(T<A){sample.push_back(y);x_i=y;i++;}

        }
    }

    