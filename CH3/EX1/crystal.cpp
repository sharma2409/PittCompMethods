#include<iostream>

#include<eigen3/Eigen/Dense>

 

using namespace Eigen;

using namespace std;

 

int main(){

 

Vector3d X(3,0,0);

 

Vector3d Y(0.5,2.0,0.0);

 

Vector3d Z(0.3,0.2,1.5);

 

Vector3d XY=X.cross(Y);  //Cross-Product

 

cout<<"The area of the crystal using scalar triple product (Vectors) is "<<XY.dot(Z)<<" units"<<endl; //Scalar Triple Product

 

 

MatrixXd A(3,3); //Volume using Matrix

A(0,0)=3.0; A(0,1)=0.0; A(0,2)=0.0;

A(1,0)=0.5; A(1,1)=2.0; A(1,2)=0.0;

A(2,0)=0.3; A(2,1)=0.2; A(2,2)=1.5;

 

cout<<"The area of the crystal using determinants (Matrix) is "<<A.determinant()<<" units";

 

// (axb).c

 

return 0;

}
