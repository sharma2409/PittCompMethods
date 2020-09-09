#include <cmath>
#include <iostream>
#include <sstream>
int main (int argc, char **argv)
{
	double i,j;
	std::istringstream stream(argv[1]);
	stream>>i;
	j=exp(i);
	std::cout<<j<<std::endl;
	return 0;
	}
