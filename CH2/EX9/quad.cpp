#include<iostream>
#include<cmath>
#include<complex>

typedef std::complex<double> Complex;

void roots(Complex a, Complex b, Complex c, Complex num1, Complex num2)
{
	Complex d;
	
	d=sqrt(b*b-4.0*a*c); //Square root of discriminant

	num1=(-b+d)/(2.0*a);

	num2=(-b-d)/(2.0*a);
	
	std::cout<<"1st Solution of Equation ="<<num1<<std::endl;
	std::cout<<"2nd Solution of Equation ="<<num2<<std::endl;

				}

int main(int argc, char **argv){

float a1;
float a2;
float b1;
float b2;
float c1;
float c2;

a1=atof(argv[1]);
a2=atof(argv[2]);
b1=atof(argv[3]);
b2=atof(argv[4]);
c1=atof(argv[5]);
c2=atof(argv[6]);

Complex a(a1,a2); //Complex declaration
Complex b(b1,b2);
Complex c(c1,c2);

Complex num1, num2;

roots(a,b,c,num1,num2);

return 0;

}


