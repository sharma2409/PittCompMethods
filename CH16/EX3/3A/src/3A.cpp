#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatDataModeling/HistChi2Functional.h"
#include "QatDataModeling/MinuitMinimizer.h"
#include <cmath>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Parameter.h"
#include "Eigen/Dense"
using namespace std;
using namespace Genfun;


int main (int argc, char * * argv) {



  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0] + "[1|2|3]"; 

  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  Hist1D histogram (1000.0, 90.0, 110.0);
  
  ifstream stream("data00.dat");
  
  double x;
  
  Exp exp;
  Sqrt sqrt;
  
  while (stream>>x) {
    
    histogram.accumulate(x);
  }
  
  Parameter pgamma("Gamma",0.5,0.01,4.0);
  //Parameter psigma("Sigma", 0.5,0.01,10.0);
  
  Variable X;
  
  GENFUNCTION lorenzianDistribution=1/(M_PI*pgamma*(1+(X/pgamma)*(X/pgamma))); //Function for Lorentzian Distribution
    //GENFUNCTION normaldistribution=exp((-X*X)/(2*psigma*psigma))/sqrt(2*M_PI)/psigma; 
 
  HistChi2Functional objectiveFunction(&histogram);
  GENFUNCTION f= histogram.sum()*lorenzianDistribution;
  //GENFUNCTION f= histogram.sum()*normaldistribution;
  
  bool verbose=true;
  MinuitMinimizer minimizer(verbose);
  minimizer.addParameter(&pgamma);
 // minimizer.addParameter(&psigma);
  minimizer.addStatistic(&objectiveFunction, &f);
  minimizer.minimize();
  
  //PlotFunction1D pplot(histogram.sum()*lorenzianDistribution); 
  
  PlotHist1D pH=histogram;
  PlotView view(pH.rectHint());
  view.setGrid(false);
  view.setBox(false);
  view.setXZero(false);
  view.setYZero(false);
  view.add(&pH);
  view.add(&pplot);
  view.yAxisFont().setPointSize(12);
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
	       << "x" 
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  
  view.show();
  window.show();
  app.exec();
  return 1;
}
