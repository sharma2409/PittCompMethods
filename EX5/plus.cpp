#include <sstream>
#include <iostream>

int main (int argc, char** argv){

float x,y;

std::istringstream stream1(argv[1]);
std::istringstream stream2(argv[2]);

stream1>>x;
stream2>>y;

std::cout<<x<<"+"<<y<<"= "<<x+y<<std::endl;

return 0;

}

