#include<iostream>
#include<vector>


int readfile();
int readvalue(std::vector<double>& datas);
int readerror(std::vector<double>& errors);
double magnitude(double x,double y);


double fit(std::vector<double>& datas,std::vector<double> errors,double& p, double& q);

double power(double x,double y);

void printing(int n,std::vector<double> datas);

void printing(std::vector<double> datas);

void printing(std::vector<double> datas,std::vector<double> errors,double& p, double& q);
void printing(std::vector<double> datas,double p);