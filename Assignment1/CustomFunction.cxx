#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>

#include<vector>
#include<cmath>

#include "CustomFunction.h"


int readfile(){
    std::fstream myInput;
    myInput.open("input2D_float.txt");
    if (myInput.fail()){
        std::cout<<"Sorry, couldn't open file"<<std::endl;
        exit(1);
    }
    
    std::string x;
    int line=0;
    while(myInput>>x){
        line++;
        std::cout<<x<<std::endl;
    }
    std::cout<<line<<"lines read from file"<<std::endl;

    myInput.close();

    return 0;
}

int readvalue(std::vector<double>& datas){
    std::fstream myInput;
    myInput.open("input2D_float.txt");
    
    std::string line;
    std::string t;

    if (myInput.fail()){
        std::cout<<"Sorry, couldn't open file"<<std::endl;
        exit(1);
    }
    
    double x,y;

    int nline=0;
    std::getline(myInput,line);
    while(std::getline(myInput,line)){
        std::istringstream iss(line);
        if(std::getline(iss,t,',')&&(iss>>y)){
            x=std::stod(line);
            datas.push_back (x);
            datas.push_back(y);
            //std::cout<<x<<","<<y<<std::endl;
            nline++;
        }
    }


    myInput.close();
    //std::cout<<"data size is "<<datas.size()<<" nline is "<<nline<<std::endl;

    return 0;

}

int readerror(std::vector<double>& errors){
    std::fstream myInput;
    myInput.open("error2D_float.txt");
    
    std::string line;
    std::string t;

    if (myInput.fail()){
        std::cout<<"Sorry, couldn't open file"<<std::endl;
        exit(1);
    }
    
    double x,y;

    int nline=0;
    std::getline(myInput,line);
    while(std::getline(myInput,line)){
        std::istringstream iss(line);
        if(std::getline(iss,t,',')&&(iss>>y)){
            x=std::stod(line);
            errors.push_back (x);
            errors.push_back(y);
            nline++;
        }
    }

    myInput.close();

    return 0;

}


double magnitude(double x,double y){
    double m= std::sqrt(x*x+y*y);
    return m;
}


double fit(std::vector<double>& datas,std::vector<double> errors,double& p, double& q){
    int N=datas.size();
    double sum_test=0;
    double sum_x=0,sum_y=0,sum_xy=0,sum_x2=0;
    for (int i=0;i<N/2;i++)
    {
        sum_x=sum_x+datas[2*i];
        sum_y=sum_y+datas[2*i+1];
        sum_xy=sum_xy+datas[2*i]*datas[2*i+1];
        sum_x2=sum_x2+datas[2*i]*datas[2*i];
    }
    p=(N*sum_xy-sum_x*sum_y)/(N*sum_x2-sum_x*sum_x);
    q=(sum_x2*sum_y-sum_xy*sum_x)/(N*sum_x2-sum_x*sum_x);

    for (int i=0;i<N/2;i++){
        double y=p*datas[i]+q;
        double merror=magnitude(errors[2*i],errors[2*i+1]);
    sum_test=sum_test+std::pow((datas[2*i+1]-y)/merror,2);
    }
    sum_test=sum_test/N;

    return sum_test;
}


double power(double x,double y){
    int k=round(y);
    if(k==0){
        return 1;
    }
    return x*power(x,y-1);
    }

    void printing(int n,std::vector<double> datas){
    int line=datas.size()/2;
    if (n>line){std::cout<<"Warning: the n is lager than the total number of data points";
    n=5;}
    for (int i=0;i<n;i++){
        double x=datas[2*i];
        double y=datas[2*i+1];
        std::cout<<"("<<x<<","<<y<<")"<<std::endl;
    }
}

void printing(std::vector<double> datas){
    std::ofstream mag("magnitude.txt");
    int n=datas.size();
    for (int i=0;i<n/2;i++){
        double x=datas[2*i];
        double y=datas[2*i+1];
        std::cout << "The magnitude of ("<<x<<","<<y<<") is " << magnitude(x,y) << std::endl;
        mag<<"("<<x<<","<<y<<") "<<magnitude(x,y)<<"\n";
    }
    mag.close();
}

void printing(std::vector<double> datas,std::vector<double> errors,double& p, double& q){
     std::ofstream fit_function("fit_funciton.txt");
    double chi_NDF=fit(datas,errors,p,q);
    std::cout<<"the fit function is: y="<<p<<"*x+"<<q<<std::endl;
    std::cout<<"chi^2/NDF="<<chi_NDF<<std::endl;
    fit_function<<"the fit function is: y="<<p<<"*x+"<<q<<"\n";
    fit_function<<"chi^2/NDF="<<chi_NDF;
    fit_function.close();
}

void printing(std::vector<double> datas,double p){
    std::ofstream powe("power.txt");
    int n=datas.size();
    for (int i=0;i<n/2;i++){
        double x=datas[2*i];
        double y=datas[2*i+1];
        std::cout << "x^y of ("<<x<<","<<y<<") is " << power(x,y) << std::endl;
        powe<<"("<<x<<","<<y<<") "<<power(x,y)<<"\n";
    }
    powe.close();
}