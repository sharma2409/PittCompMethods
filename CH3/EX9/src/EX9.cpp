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
	
	
	if (n==1)
	{	nk[1]=V0*exp(-8); 
	}
	else if (n==2)
	{ 	
	  nk[1]=V0*exp(-4.5);
	  nk[2]=V0*exp(-2);
	  nk[3]=V0*exp(-0.5);
	}
	
	int no_of_eq=bin*4;
	
	Eigen::VectorXcd Y(no_of_eq);
	
	for (int i=0; i<no_of_eq; i++) //Initialization of Y vector
	{	Y(i)=0;
	
	}
	
	Y(0)=-exp(I*k*Complex(4.0,0.0));
	Y(no_of_eq/2)=exp(I*k*Complex(4.0,0.0))*Complex(4.0,0.0)*I*k;
	
	Eigen::MatrixXcd A(no_of_eq,no_of_eq);
	
	for (int j=0; j<no_of_eq; j++)
	{
		for (int k=0; k<no+of_eq; k++)
		{	A(j,k)=1
		
		} 
	
	} 
	
	
	
	
	
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

