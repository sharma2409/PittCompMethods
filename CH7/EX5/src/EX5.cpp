#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatGenericFunctions/Erf.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include <cmath>
#include "QatPlotting/PlotFunction1D.h"
using namespace Genfun;
using namespace std;

typedef std::mt19937 EngineType;

int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }
  
  //Programming the convolution result analytically

  int N =0;  
  Variable X;
  Erf erf;
  Exp exp;
  GENFUNCTION I= 1.5*exp((-X*X/8)+(X/2)-6)*(1+erf(0.3535*X-4.2426));


//Random Variate Generation

EngineType e;

Hist1D histogram ("Random", 1000, -10.0, 60.0);
Hist1D histogram2 ("Random", 1000, -10.0, 60.0);

std::exponential_distribution<double> u(3.0);
std::normal_distribution<double> v(2.0);
for (int i=0; i<10000; i++){
        double x=0;
	x=u(e)+v(e);
	histogram.accumulate(x);
	}

PlotHist1D ph=histogram;


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-10.0);
  rect.setXmax(10.0);
  rect.setYmin(0.0);
  rect.setYmax(250.0);

//Rejection methods
  uniform_real_distribution<double> gauss1(-10,10);

  uniform_real_distribution<double> gauss2(0,0.4);
 
  
  for (int i=0;i<=10*10000;i++){
    double x1 = gauss1(e);
    double x2 = gauss2(e);
    if (N<10000){
    if (x2<I(x1)){
    histogram2.accumulate(x1);
    N++;
    }
    }
  }




  

PlotView view(rect);

window.setCentralWidget(&view);

PlotFunction1D pI=I;
PlotHist1D ph2=histogram2;

//view.add(&ph);
view.add(&ph2);
//view.add(&pI);




  
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

