#include <iostream>
#include "variables.h"
using namespace std;
int main (int argc, char** argv){
	float x, y,sum;
	parse(argc, argv, x, y);
	add(x, y, sum);

	print(x,y,sum);

	return 0;
}
