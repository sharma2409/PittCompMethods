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
#include "QatGenericFunctions/F2D.h"
#include "QatGenericFunctions/AbsFunction.h"
#include "QatPlotting/PlotWave1D.h"
#include <cmath>
using namespace Genfun;

typedef std::complex<double>Complex;

int input=1;

double f(double x, double t){
	
	double sol;
	double v=1.50001;
        double k=0.5;
        
        Complex I(0,1.0);
  Complex nk=k*sqrt(Complex(1-v));
  Complex nk_2=k*sqrt(Complex(1-(2*v)));
  
  
  Eigen::VectorXcd Y(8);
  Y(0)= -exp(-I*k*Complex(2.0001,0.0));
  Y(1)= 0;
  Y(2)= 0;
  Y(3)= 0;
  Y(4)= Complex(2.0001,0.0)*I*k*exp(-I*k*Complex(2.0001,0.0));
  Y(5)= 0;
  Y(6)= 0;
  Y(7)= 0;
  

  Eigen::MatrixXcd A(8,8);
  // First row:
  A(0,0)= exp(Complex(2.0001,0.0)*I*k)      ;
  A(0,1)=-exp(-I*nk*Complex(2.0001,0.0))    ; 
  A(0,2)= -exp(I*nk*Complex(2.0001,0.0))    ; 
  A(0,3)=0              ;
  A(0,4)=0              ;
  A(0,5)=0              ;
  A(0,6)=0              ;
  A(0,7)=0              ;

  // Second row:
  A(1,0)= 0             ;
  A(1,1)= exp(-I*nk)     ; 
  A(1,2)= exp(I*nk)    ; 
  A(1,3)=-exp(-I*nk_2)      ;
  A(1,4)=-exp(I*nk_2)      ;
  A(1,5)= 0;
  A(1,6)= 0;
  A(1,7)= 0;
  
  // Third row:
  A(2,0)= 0  ;
  A(2,1)= 0; 
  A(2,2)= 0 ; 
  A(2,3)=exp(I*nk_2);
  A(2,4)=exp(-I*nk_2);
  A(2,5)=-exp(I*nk);
  A(2,6)=-exp(-I*nk);
  A(2,7)= 0 ;      

  // Fourth row:
  A(3,0)= 0                ;
  A(3,1)= 0                ;
  A(3,2)= 0                ;
  A(3,3)= 0                ;
  A(3,4)= 0                ;
  A(3,5)=exp(Complex(2.0001,0.0)*I*nk)  ; 
  A(3,6)=exp(-I*nk*Complex(2.0001,0.0)); 
  A(3,7)=-exp(Complex(2.0001,0.0)*I*k)   ;
  
  // Fifth Row
  A(4,0)=Complex(2.0001,0.0)*I*k* exp(Complex(2.0001,0.0)*I*k)      ;
  A(4,1)=I*nk*Complex(2.0001,0.0)*exp(-I*nk*Complex(2.0001,0.0))    ; 
  A(4,2)= -I*nk*Complex(2.0001,0.0)*exp(I*nk*Complex(2.0001,0.0))    ; 
  A(4,3)=0              ;
  A(4,4)=0              ;
  A(4,5)=0              ;
  A(4,6)=0              ;
  A(4,7)=0              ;

//Sixth Row
  A(5,0)= 0             ;
  A(5,1)=-I*nk* exp(-I*nk)     ; 
  A(5,2)= I*nk*exp(I*nk)    ; 
  A(5,3)=I*nk_2*exp(-I*nk_2)      ;
  A(5,4)=-I*nk_2*exp(I*nk_2)      ;
  A(5,5)= 0;
  A(5,6)= 0;
  A(5,7)= 0;
  
  //Seventh Row
  A(6,0)= 0  ;
  A(6,1)= 0; 
  A(6,2)= 0 ; 
  A(6,3)=I*nk_2*exp(I*nk_2);
  A(6,4)=-I*nk_2*exp(-I*nk_2);
  A(6,5)=-I*nk*exp(I*nk);
  A(6,6)=I*nk*exp(-I*nk);
  A(6,7)= 0 ;      

//Eighth Row
  A(7,0)= 0                ;
  A(7,1)= 0                ;
  A(7,2)= 0                ;
  A(7,3)= 0                ;
  A(7,4)= 0                ;
  A(7,5)=Complex(2.0001,0.0)*I*nk*exp(Complex(2.0001,0.0)*I*nk)  ; 
  A(7,6)=-I*Complex(2.0001,0.0)*nk*exp(-I*nk*Complex(2.0001,0.0)); 
  A(7,7)=-exp(Complex(2.0001,0.0)*I*k)*Complex(2.0001,0.0)*k*I   ;

  Eigen::MatrixXcd AInv= A.inverse();
  Eigen::VectorXcd BCDEFGHI=AInv*Y;
   
  if (x<-2){
	
	if (input==1){
	sol=real(exp(-I*t)*(exp(I*k*x)+BCDEFGHI(0)*exp(-I*k*x)));}
	
	else if (input==2){
	sol=imag(exp(-I*t)*(exp(I*k*x)+BCDEFGHI(0)*exp(-I*k*x)));}
	
	else if (input==3){
	sol=abs(exp(-I*t)*(exp(I*k*x)+BCDEFGHI(0)*exp(-I*k*x)))*abs(exp(-I*t)*(exp(I*k*x)+BCDEFGHI(0)*exp(-I*k*x)));
	}
	
	
	return sol;

	}
	else if (x>=-2 && x<-1){
	
	if (input==1){
	sol=real(exp(-I*t)*(BCDEFGHI(1)*exp(I*nk*x)+BCDEFGHI(2)*exp(-I*nk*x)));}
	
	else if (input==2){
	sol=imag(exp(-I*t)*(BCDEFGHI(1)*exp(I*nk*x)+BCDEFGHI(2)*exp(-I*nk*x)));}
	
	else if (input==3){
	sol=abs(exp(-I*t)*(BCDEFGHI(1)*exp(I*nk*x)+BCDEFGHI(2)*exp(-I*nk*x)))*abs(exp(-I*t)*(BCDEFGHI(1)*exp(I*nk*x)+BCDEFGHI(2)*exp(-I*nk*x)));
	}
	
	return sol;
	
	}
	
	else if (x>=-1 && x<1){
	
	if (input==1){
	sol=real(exp(-I*t)*(BCDEFGHI(3)*exp(I*nk_2*x)+BCDEFGHI(4)*exp(-I*nk_2*x)));}
	
	else if (input==2){
	sol=imag(exp(-I*t)*(BCDEFGHI(3)*exp(I*nk_2*x)+BCDEFGHI(4)*exp(-I*nk_2*x)));}
	
	else if (input==3){
	sol=abs(exp(-I*t)*(BCDEFGHI(3)*exp(I*nk_2*x)+BCDEFGHI(4)*exp(-I*nk_2*x)))*abs(exp(-I*t)*(BCDEFGHI(3)*exp(I*nk_2*x)+BCDEFGHI(4)*exp(-I*nk_2*x)));
	}
	return sol;
	
	}
	
	else if (x>=1 && x<2){
	
	if (input==1){
	sol=real(exp(-I*t)*(BCDEFGHI(5)*exp(I*nk*x)+BCDEFGHI(6)*exp(-I*nk*x)));}
	
	else if (input==2){
	sol=imag(exp(-I*t)*(BCDEFGHI(5)*exp(I*nk*x)+BCDEFGHI(6)*exp(-I*nk*x)));}
	
	else if (input==3){
	sol=abs(exp(-I*t)*(BCDEFGHI(5)*exp(I*nk*x)+BCDEFGHI(6)*exp(-I*nk*x)))*abs(exp(-I*t)*(BCDEFGHI(5)*exp(I*nk*x)+BCDEFGHI(6)*exp(-I*nk*x)));
	}
	return sol;
	
	}
	
	else {
	
	if (input==1){
	sol=real(exp(-I*t)*(BCDEFGHI(7)*exp(I*k*x)));}
	
	else if (input==2){
	sol=imag(exp(-I*t)*(BCDEFGHI(7)*exp(I*k*x)));}
	
	else if (input==3){
	sol=abs(exp(-I*t)*(BCDEFGHI(7)*exp(I*k*x)))*abs(exp(-I*t)*(BCDEFGHI(7)*exp(I*k*x)));
	}
	
	
	return sol;
	
	}


}


int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  input=atoi(argv[1]);

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  
  
  PRectF rect;
  rect.setXmin(-20);
  rect.setXmax(20);
  rect.setYmin(-2);
  rect.setYmax(2);
  

  PlotView view(rect);
  PlotWave1D p=F2D(f);
  
  view.add(&p);
  
  window.setCentralWidget(&view);
  
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

