#include<iostream>
#include<cmath>
#include<complex>

typedef std::complex<double> Complex;


int main(int argc,char **argv) {

float m1,v1,e1,x1;  //x is position of particle


m1=atof(argv[1]);
v1=atof(argv[2]);
e1=atof(argv[3]);
x1=atof(argv[4]);

float h1=1; //h

Complex m,e,v,k,k_prime,reflect,transmit,h,two,val,x;
val=Complex(1.0,0);
two=Complex(2.0,0);
h=Complex(h1,0);
m=Complex(m1,0.0);
v=Complex(e1,0.0);
e=Complex(v1,0.0);
x=Complex(x1,0.0);

k=sqrt(two*m*e/(h*h));

k_prime=sqrt(two*m*(e-v)/(h*h));

reflect=(k-k_prime)/(k+k_prime);

transmit=val+reflect;

std::cout<<"Reflection and transmission coefficient are "<<reflect<<" and "<<transmit<<" respectively "<<std::endl;

if (real(x)<=0){

std::cout<<"Wave Function= e^(i"<<k<<"*"<<real(x)<<") +"<<reflect<<"e^(-i"<<k<<"*"<<real(x)<<")"; }

else {std::cout<<"Wave Function= "<<transmit<<"e^(i"<<k_prime<<"*"<<real(x)<<")";
};



return 0;
}

