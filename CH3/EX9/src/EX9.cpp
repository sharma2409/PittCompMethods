#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>
#include "QatGenericFunctions/F1D.h"
#include "QatGenericFunctions/AbsFunction.h"
#include "QatPlotting/PlotFunction1D.h"

using namespace Genfun;
typedef std::complex<double>Complex;
double n=0;

double f(double x){

	double sol;
	Complex k(0.5,0);
	Complex I(0,1.0);
	Complex nk[10]; //Array of different n values depending on number of bins
	Complex V0=1; //V0 value
	
	int bin=pow(2,n);
	nk[0]=k;
	
	
	if (n==0)
	{	nk[1]=V0*exp(-8); 
	}
	
	else if (n==1)
	{ 	
	  nk[1]=V0*exp(-8);
	  nk[2]=V0*exp(-2);
	  
	}
	
/*/	else if (n==2)
	{ 	
	  nk[1]=V0*exp(-4.5);
	  nk[2]=V0*exp(-2);
	  nk[3]=V0*exp(-0.5);
	}
/*/	
	int no_of_eq=bin*4;
	
	Eigen::VectorXcd Y(no_of_eq);
	
	for (int i=0; i<no_of_eq; i++) //Initialization of Y vector
	{	Y(i)=0;
	
	}
	
	Y(0)=-exp(I*k*Complex(4.0,0.0));
	Y(no_of_eq/2)=exp(I*k*Complex(4.0,0.0))*Complex(4.0,0.0)*I*k;
	
	Eigen::MatrixXcd A(no_of_eq,no_of_eq);
	
	for (int j=0; j<no_of_eq; j++)  //Initializing the Matrix with zeroes
	{
		for (int k=0; k<no_of_eq; k++)
		{	A(j,k)=0;
		
		} 
	
	} 
	
	if (n==0)
	{
	A(0,0)= exp(I*nk[0]*Complex(4.0,0.0))      ;
  	A(0,1)=-exp(-I*nk[1]*Complex(4.0,0.0))    ; 
  	A(0,2)= -exp(I*nk[1]*Complex(4.0,0.0))    ; 
  	A(0,3)=0              ;

  // Second row:
  	A(1,0)= 0             ;
  	A(1,1)= exp(I*nk[1]*Complex(4.0,0.0))     ; 
  	A(1,2)= exp(-I*nk[1]*Complex(4.0,0.0))    ; 
  	A(1,3)=-exp(I*nk[0]*Complex(4.0,0.0))      ;
  
  // Third row:
  	A(2,0)= -I*nk[0]*exp(I*nk[0]*Complex(4.0,0.0))*Complex(4.0,0.0)  ;
  	A(2,1)=-I*nk[0]*exp(-I*nk[1]*Complex(4.0,0.0))*Complex(4.0,0.0); 
  	A(2,2)= I*nk[0]*exp(I*nk[1]*Complex(4.0,0.0))*Complex(4.0,0.0) ; 
  	A(2,3)=0                 ;

  // Fourth row:
  	A(3,0)= 0                ;
  	A(3,1)=I*nk[1]*exp(I*nk[1]*Complex(4.0,0.0))*Complex(4.0,0.0)  ; 
  	A(3,2)=-I*nk[1]*exp(-I*nk[1]*Complex(4.0,0.0))*Complex(4.0,0.0); 
  	A(3,3)=-I*nk[0]*exp(I*nk[0]*Complex(4.0,0.0))*Complex(4.0,0.0)   ;

	
	}
	
	else if (n==1) {
		 // First row:
  	A(0,0)= exp(Complex(4.0001,0.0)*I*nk[0])      ;
  	A(0,1)=-exp(-I*nk[1]*Complex(4.0001,0.0))    ; 
  	A(0,2)= -exp(I*nk[1]*Complex(4.0001,0.0))    ; 
  	A(0,3)=0              ;
  	A(0,4)=0              ;
  	A(0,5)=0              ;
  	A(0,6)=0              ;
  	A(0,7)=0              ;

  // Second row:
  	A(1,0)= 0             ;
  	A(1,1)= exp(-I*nk[1]*Complex(2.0,0.0))     ; 
  	A(1,2)= exp(I*nk[1]*Complex(2.0,0.0))    ; 
  	A(1,3)=-exp(-I*nk[2]*Complex(2.0,0.0))      ;
  	A(1,4)=-exp(I*nk[2]*Complex(2.0,0.0))      ;
  	A(1,5)= 0;
  	A(1,6)= 0;
  	A(1,7)= 0;
  
  // Third row:
 	A(2,0)= 0  ;
  	A(2,1)= 0; 
  	A(2,2)= 0 ; 
  	A(2,3)=exp(I*nk[2]*Complex(2.0,0.0));
  	A(2,4)=exp(-I*nk[2]*Complex(2.0,0.0));
  	A(2,5)=-exp(I*nk[1]*Complex(2.0,0.0));
  	A(2,6)=-exp(-I*nk[1]*Complex(2.0,0.0));
  	A(2,7)= 0 ;      

	  // Fourth row:
	  A(3,0)= 0                ;
	  A(3,1)= 0                ;
	  A(3,2)= 0                ;
	  A(3,3)= 0                ;
	  A(3,4)= 0                ;
	  A(3,5)=exp(Complex(4.0001,0.0)*I*nk[1])  ; 
	  A(3,6)=exp(-I*nk[1]*Complex(4.0001,0.0)); 
	  A(3,7)=-exp(Complex(4.0001,0.0)*I*nk[0])   ;
	  
	  // Fifth Row
	  A(4,0)=Complex(4.0001,0.0)*I*nk[0]* exp(Complex(4.0001,0.0)*I*nk[0])      ;
	  A(4,1)=I*nk[1]*Complex(4.0001,0.0)*exp(-I*nk[1]*Complex(4.0001,0.0))    ; 
	  A(4,2)= -I*nk[1]*Complex(4.0001,0.0)*exp(I*nk[1]*Complex(4.0001,0.0))    ; 
	  A(4,3)=0              ;
	  A(4,4)=0              ;
	  A(4,5)=0              ;
	  A(4,6)=0              ;
	  A(4,7)=0              ;

	//Sixth Row
	  A(5,0)= 0             ;
	  A(5,1)=-I*nk[1]* exp(-I*nk[1])*Complex(2.0,0.0)     ; 
	  A(5,2)= I*nk[1]*exp(I*nk[1])*Complex(2.0,0.0)    ; 
	  A(5,3)=I*nk[2]*exp(-I*nk[2])*Complex(2.0,0.0)      ;
	  A(5,4)=-I*nk[2]*exp(I*nk[2])*Complex(2.0,0.0)      ;
	  A(5,5)= 0;
	  A(5,6)= 0;
	  A(5,7)= 0;
	  
  //Seventh Row
	  A(6,0)= 0  ;
	  A(6,1)= 0; 
	  A(6,2)= 0 ; 
	  A(6,3)=I*nk[2]*exp(I*nk[2])*Complex(2.0,0.0);
	  A(6,4)=-I*nk[2]*exp(-I*nk[2])*Complex(2.0,0.0);
	  A(6,5)=-I*nk[1]*exp(I*nk[1])*Complex(2.0,0.0);
	  A(6,6)=I*nk[1]*exp(-I*nk[1])*Complex(2.0,0.0);
	  A(6,7)= 0 ;      

//Eighth Row
  	A(7,0)= 0                ;
 	 A(7,1)= 0                ;
  	A(7,2)= 0                ;
  	A(7,3)= 0                ;
 	 A(7,4)= 0                ;
  	A(7,5)=Complex(4.0001,0.0)*I*nk[1]*exp(Complex(4.0001,0.0)*I*nk[1])  ; 
  	A(7,6)=-I*Complex(4.0001,0.0)*nk[1]*exp(-I*nk[1]*Complex(4.0001,0.0)); 
  	A(7,7)=-exp(Complex(4.0001,0.0)*I*nk[0])*Complex(4.0001,0.0)*nk[0]*I   ;

	
	}
	
	Eigen::MatrixXcd AInv= A.inverse();
  	Eigen::VectorXcd BCDF=AInv*Y;
  	
  	double transmission=real(BCDF(no_of_eq));
  	return transmission;
	
	} 

int main (int argc, char * * argv) {
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);
  PlotFunction1D p=F1D(f);
  
  view.add(&p);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

