#include <iostream>
#include <cmath>
int main()
{
	float x[20];
	int j=-10;
	float k;
	float taylor[20];
	std::cout<<"x  "<<"exp(x)"<<std::endl;
	for (int i=0;i<=10;i++)
	{ 
		x[i]=j;
		taylor[i]=1+x[i]+((x[i]*x[i])/2)+((x[i]*x[i]*x[i])/6);
		std::cout<<x[i]<<"  "<<taylor[i]<<std::endl;
		
		j=j+2;
			};
		k=exp(2);	

	return 0;
	}
