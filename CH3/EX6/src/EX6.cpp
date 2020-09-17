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
#include "QatPlotting/PlotFunction1D.h"
#include <cmath>
using namespace Genfun;
 
typedef std::complex<double>Complex;

double f (double x) {
//default values
	double v=0.5;
        double k=0.2;
        double psi_square;
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


	if (x<0){
	psi_square=norm(exp(I*k*x)+BCDF(0)*exp(-I*k*x))*norm(exp(I*k*x)+BCDF(0)*exp(-I*k*x));
	return psi_square;
	
	}
	
	else if (x>0){
	psi_square=norm(BCDF(3)*exp(I*k*x))*norm(BCDF(3)*exp(I*k*x));
	return psi_square;
	}
	
	else { psi_square=norm(BCDF(1)*exp(I*nk*x)+BCDF(2)*exp(I*nk*x))+norm(BCDF(1)*exp(I*nk*x)+BCDF(2)*exp(I*nk*x));
	
	return psi_square;}
	
	

}


int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }

  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-1.0);
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(4.0);
  

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

