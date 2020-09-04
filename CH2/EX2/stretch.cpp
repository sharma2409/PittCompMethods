#include<iostream>
#include<cmath>
int main(){

double beta=0.999999999999; //beta value
double stretch_beta=1/sqrt(1-beta*beta); //Stretch factor calculation using the 1st method
std::cout<<"Stretch Factor for 1st Case = "<<stretch_beta<<std::endl;

double eps=0.000000000001; //epsilon value
double stretch_eps=1/sqrt((2-eps)*eps);
std::cout<<"Stretch Factor for 2nd Case = "<<stretch_eps<<std::endl;



return 0;
}
