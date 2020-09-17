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

typedef std::complex<double>Complex;
int main (int argc, char * * argv) {

 
//Solution for N=0
        double v0=1;
	double v=v0*exp(-8.0);
        double k=0.2;
        
        Complex I(0,1.0);
  Complex nk=k*sqrt(Complex(1-v));
  
  Eigen::VectorXcd Y(4);
  Y(0)= -exp(-I*k);
  Y(1)= 0;
  Y(2)= -I*k*exp(-I*k);
  Y(3)= 0;

  Eigen::MatrixXcd A(4,4);
  // First row:
  A(0,0)= exp(I*k)      ;
  A(0,1)=-exp(-I*nk)    ; 
  A(0,2)= -exp(I*nk)    ; 
  A(0,3)=0              ;

  // Second row:
  A(1,0)= 0             ;
  A(1,1)= exp(I*nk)     ; 
  A(1,2)= exp(-I*nk)    ; 
  A(1,3)=-exp(I*k)      ;
  
  // Third row:
  A(2,0)= -I*k*exp(I*k)  ;
  A(2,1)=-I*nk*exp(-I*nk); 
  A(2,2)= I*nk*exp(I*nk) ; 
  A(2,3)=0                 ;

  // Fourth row:
  A(3,0)= 0                ;
  A(3,1)=I*nk*exp(I*nk)  ; 
  A(3,2)=-I*nk*exp(-I*nk); 
  A(3,3)=-I*k*exp(I*k)   ;

  Eigen::MatrixXcd AInv= A.inverse();
  Eigen::VectorXcd BCDF=AInv*Y;


//Solution for N=1


  Complex nk_2=v0*exp(-2);
  
  
  Eigen::VectorXcd y(8);
  y(0)= -exp(-I*k*Complex(2.0001,0.0));
  y(1)= 0;
  y(2)= 0;
  y(3)= 0;
  y(4)= Complex(2.0001,0.0)*I*k*exp(-I*k*Complex(2.0001,0.0));
  y(5)= 0;
  y(6)= 0;
  y(7)= 0;
  

  Eigen::MatrixXcd a(8,8);
  // First row:
  a(0,0)= exp(Complex(2.0001,0.0)*I*k)      ;
  a(0,1)=-exp(-I*nk*Complex(2.0001,0.0))    ; 
  a(0,2)= -exp(I*nk*Complex(2.0001,0.0))    ; 
  a(0,3)=0              ;
  a(0,4)=0              ;
  a(0,5)=0              ;
  a(0,6)=0              ;
  a(0,7)=0              ;

  // Second row:
  a(1,0)= 0             ;
  a(1,1)= exp(-I*nk)     ; 
  a(1,2)= exp(I*nk)    ; 
  a(1,3)=-exp(-I*nk_2)      ;
  a(1,4)=-exp(I*nk_2)      ;
  a(1,5)= 0;
  a(1,6)= 0;
  a(1,7)= 0;
  
  // Third row:
  a(2,0)= 0  ;
  a(2,1)= 0; 
  a(2,2)= 0 ; 
  a(2,3)=exp(I*nk_2);
  a(2,4)=exp(-I*nk_2);
  a(2,5)=-exp(I*nk);
  a(2,6)=-exp(-I*nk);
  a(2,7)= 0 ;      

  // Fourth row:
  a(3,0)= 0                ;
  a(3,1)= 0                ;
  a(3,2)= 0                ;
  a(3,3)= 0                ;
  a(3,4)= 0                ;
  a(3,5)=exp(Complex(2.0001,0.0)*I*nk)  ; 
  a(3,6)=exp(-I*nk*Complex(2.0001,0.0)); 
  a(3,7)=-exp(Complex(2.0001,0.0)*I*k)   ;
  
  // Fifth Row
  a(4,0)=Complex(2.0001,0.0)*I*k* exp(Complex(2.0001,0.0)*I*k)      ;
  a(4,1)=I*nk*Complex(2.0001,0.0)*exp(-I*nk*Complex(2.0001,0.0))    ; 
  a(4,2)= -I*nk*Complex(2.0001,0.0)*exp(I*nk*Complex(2.0001,0.0))    ; 
  a(4,3)=0              ;
  a(4,4)=0              ;
  a(4,5)=0              ;
  a(4,6)=0              ;
  a(4,7)=0              ;

//Sixth Row
  a(5,0)= 0             ;
  a(5,1)=-I*nk* exp(-I*nk)     ; 
  a(5,2)= I*nk*exp(I*nk)    ; 
  a(5,3)=I*nk_2*exp(-I*nk_2)      ;
  a(5,4)=-I*nk_2*exp(I*nk_2)      ;
  a(5,5)= 0;
  a(5,6)= 0;
  a(5,7)= 0;
  
  //Seventh Row
  a(6,0)= 0  ;
  a(6,1)= 0; 
  a(6,2)= 0 ; 
  a(6,3)=I*nk_2*exp(I*nk_2);
  a(6,4)=-I*nk_2*exp(-I*nk_2);
  a(6,5)=-I*nk*exp(I*nk);
  a(6,6)=I*nk*exp(-I*nk);
  a(6,7)= 0 ;      

//Eighth Row
  a(7,0)= 0                ;
  a(7,1)= 0                ;
  a(7,2)= 0                ;
  a(7,3)= 0                ;
  a(7,4)= 0                ;
  a(7,5)=Complex(2.0001,0.0)*I*nk*exp(Complex(2.0001,0.0)*I*nk)  ; 
  a(7,6)=-I*Complex(2.0001,0.0)*nk*exp(-I*nk*Complex(2.0001,0.0)); 
  a(7,7)=-exp(Complex(2.0001,0.0)*I*k)*Complex(2.0001,0.0)*k*I   ;

  Eigen::MatrixXcd aInv= a.inverse();
  Eigen::VectorXcd BCDEFGHI=aInv*y;
   
  std::cout<<"Complex Coefficients :"<<std::endl;
  std::cout<<BCDEFGHI<<std::endl; 
  std::cout<<norm(BCDEFGHI(0))+norm(BCDEFGHI(7)); 

  













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

