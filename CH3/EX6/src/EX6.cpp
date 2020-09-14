#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include<eigen3/Eigen/Dense>
#include<complex>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/F1D.h"
#include "QatGenericFunctions/AbsFunction.h"
#include <cmath>
using namespace Genfun;


typedef std::complex<double>Complex;
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }

//default values
	double v=0.5;
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
  
  // Till this point the standard problem is solved

Genfun::Variable X;
        
Genfun::GENFUNCTION cos=Genfun::F1D(std::cos);

Genfun::GENFUNCTION f1=4*(cos (k*Genfun::Variable())); //Simplified form of the density function in the 1st region

Genfun::GENFUNCTION f2=BCDF(1)*BCDF(1)+BCDF(2)*BCDF(2)+Complex (2.0,0.0)*BCDF(1)*BCDF(2)*(2*cos*cos (real(nk)*Genfun::Variable())); //Simplified form of the density function in the second region

Genfun::GENFUNCTION f3= BCDF(3); //Simplified form of the density function in 3rd region


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

