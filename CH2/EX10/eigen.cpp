#include<iostream>
#include<cmath>
#include<complex>

typedef std::complex<double> Complex;

Complex M[5][5];

void newton (Complex a, Complex b, Complex c, Complex trace_M, Complex minor, Complex det, Complex M[5][5]) //Function to calculate Eigen Values

{
	Complex x, f, f_prime,error, x1;
	
	x=Complex(0.0,0.0);
	
	error=Complex(1.0,0.0);
	
	float iter=0;
	
	f=x*x*x-trace_M*x*x+minor*x-det;
	
	f_prime=Complex(3.0,0.0)*x*x-Complex(2.0,0.0)*trace_M*x+minor;
	
	float tol=1e-3;
	
	//std::cout<<x<<" "<<error;
	
	while (abs(error)>tol && iter<20) //Newton Loop for 1st eigen value
	
	{ x1=x-(f/f_prime);
	
	  
	  error=x1-x;
	  
	  x=x1;
	  
		
	f=x*x*x-trace_M*x*x+minor*x-det;
	
	f_prime=Complex(3.0,0.0)*x*x-Complex(2.0,0.0)*trace_M*x+minor;
	
	iter++;
	
	}
	
	a=x;	//1st Eigen Value
	
	
	x=Complex(1.0,1.0);
	
	f=x*x+(a-trace_M)*x+((a-trace_M)*a)+minor; //Determined via Synthetic Division
	
	f_prime=Complex(2.0,0.0)*x+a-trace_M;
	
	error=Complex(1.0,0.0);
	
	iter=0;
	
	while (abs(error)>tol && iter<40) //Newton Loop for 2nd eigen value
	
	{ x1=x-(f/f_prime);
	
	
	  error=x1-x;
	  
	  x=x1;
	  
		
	f=x*x+(a-trace_M)*x+((a-trace_M)*a)+minor; //Determined via synthetic division
	
	f_prime=Complex(2.0,0.0)*x+a-trace_M;
	
	iter++;
	
	}
	
	b=x;
	
	x=Complex(1.0,1.0);
	
	f=x+(a-trace_M)+b;
	
	f_prime=1;
	
	error=Complex(1.0,0.0);
	
	iter=0;
	
	while (abs(error)>tol && iter<40) //Newton Loop for 3rd eigen value
	
	{ x1=x-(f/f_prime);
	
	
	  error=x1-x;
	  
	  x=x1;
	  
		
	f=x+(a-trace_M)+b;
	
	f_prime=1;
	
	iter++;
	
	}
	
	c=x;
	
	std::cout<<"The Eigen values are " <<a<<" ,"<<b<<" ,"<<c<<std::endl;
	
	Complex lambda,vector_abs,vector[4];
	
	vector[1]=Complex(1.0,0.0);
	
	
	for (int i=1;i<=3;i++)
	{
		if (i==1)
		lambda=a;
		
		 else if (i==2)
		lambda=b;
		
		else lambda=c;
		
		vector[2]=(M[1][2]-(M[2][2]-lambda)*(M[1][2]-lambda))/((M[2][2]-lambda)*M[1][3]-M[1][2]*M[2][3]);	
	       vector[3]=(lambda-M[1][1]-M[1][3]*vector[2])/M[2][1];
	       
	       vector_abs=sqrt(vector[1]*vector[1]+vector[2]*vector[2]+vector[3]*vector[3]);
	        vector[1]=vector[1]/vector_abs;
		vector[2]=vector[2]/vector_abs;
		vector[3]=vector[3]/vector_abs;	
		
		std::cout<<"Eigen Vector is ["<<vector[1]<<std::endl<<"                      "<<vector[2]<<std::endl<<"                      "<<vector[3]<<std::endl<<std::endl;
	
		
	}
	

	
		}
		


void eigen(Complex M[5][5], Complex a, Complex b, Complex c) //Loop to calculate various parameters
{
 	Complex trace_M, minor, det, det1,det2,det3;
 	
	trace_M=M[1][1]+M[2][2]+M[3][3]; //Trace of the Matrix
	
	minor=(M[2][2]*M[3][3]-M[2][3]*M[3][2])+(M[1][1]*M[3][3]-M[1][3]*M[3][1])+(M[1][1]*M[2][2]-M[1][2]*M[2][1]); //Minor along Diagnol
	
	det=M[1][1]*(M[2][2]*M[3][3]-M[2][3]*M[3][2])-M[1][2]*(M[2][1]*M[3][3]-M[2][3]*M[3][1])+M[1][3]*(M[2][1]*M[3][2]-M[2][2]*M[3][1]); //Det of Matrix
	
	newton(a,b,c,trace_M,minor,det,M);
	     
	}
	

int main() {

Complex a,b,c;

a=Complex(0,0);
b=Complex(0,0);
c=Complex(0,0);

M[1][1]=Complex(0.333333,0.0);  //Matrix Initialization
M[1][2]=Complex(-0.244017,0.0);
M[1][3]=Complex(0.910684,0.0);
M[2][1]=Complex(0.910684,0.0);
M[2][2]=Complex(0.333333,0.0);
M[2][3]=Complex(-0.244017,0.0);
M[3][1]=Complex(-0.244017,0.0);
M[3][2]=Complex(0.910684,0.0);
M[3][3]=Complex(0.333333,0.0);


eigen(M,a,b,c);

return 0;
}

