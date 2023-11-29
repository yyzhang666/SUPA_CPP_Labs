#include<iostream>
#include<vector>
#include"CustomFunction.h"

int main(){
    int n;
    std::cout<<"intput your n:"<<std::endl;
    std::cin>>n;

    std::vector<double> datas;
    std::vector<double> errors;

    readvalue(datas);
    printing(n,datas);

    double p=0,q=0;
    
    readerror(errors);

    int i;
    bool go=true;

    while(go){
        std::cout<<"Do you want to know: 1.magnitudes? 2.fit function? 3.x^y? Choose the number."<<std::endl;
        std::cin>>i;
        switch(i){
            case 1:{
                printing(datas);
                break;

            }
            case 2:{
                printing(datas,errors,p,q);
                break;
            }
            case 3:{
                printing(datas,p);
                break;
            }
            default:{
                std::cout<<"You didn't choose a valid integer :("<<std::endl;
                std::cout<<"Exiting loop"<<std::endl;
                go=false;
                break;
            }
        }
    }
}
