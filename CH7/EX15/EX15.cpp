#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include <cmath>
int main (int, char **) {

double const_e= 2.718;

  std::mt19937 e;
  const unsigned int N=10000;
//Code for (a) part of the problem

  {
    std::uniform_real_distribution<double> u(0,1);
    double sum=0,sum2=0;
    for (unsigned int i=0;i<N;i++) {
      double x=exp(u(e))-1;
      double f=x/(const_e-1);
      sum  +=   f;
      sum2 += f*f;
    }
    double fBar=sum/N,f2Bar=sum2/N, sigma=sqrt((f2Bar-fBar*fBar)/N);
    std::cout << "Integral is " << fBar  << "+-" << sigma << std::endl;
  }
  

   //Code for (b) part
   
   /*/
  {
    std::uniform_real_distribution<double> u(0,1);
    double sum=0,sum2=0;
    for (unsigned int i=0;i<N;i++) {
      double x=u(e);
      double f=x;
      sum  +=   f;
      sum2 += f*f;
    }
    double fBar=sum/N,f2Bar=sum2/N, sigma=sqrt((f2Bar-fBar*fBar)/N);
    std::cout << "Integral is " << fBar  << "+-" << sigma << std::endl;
  }
  

  
/*/
  // -------------------------------------------------:
  return 1;

}

