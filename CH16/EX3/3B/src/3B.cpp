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
  
  int bin=200; //Number of bins
  
  int min=60; //Minimum value of data (estimate)
  int max=110; //Maximum value of data (estimate)
  
  Hist1D histogram (bin, min, max);
  
  ifstream stream("data01.dat");
  
  double x;
  
  Exp exp;
  Sqrt sqrt;
  
  while (stream>>x) {
    
    histogram.accumulate(x);
  }
  
  Parameter psigma_1("sigma_1", histogram.variance(),0.01,1.0);
  Parameter pmu_1("mu_1", 102,histogram.min(),histogram.max());
  
  Parameter psigma_2("sigma_2", histogram.variance(),0.01,1.0);
  Parameter pmu_2("mu_2", 105,histogram.min(),histogram.max());
  Parameter pfraction("fraction",0.5,0,1);
  
  Variable X;
  
  GENFUNCTION lorenzianDistribution_1= 1.0/(M_PI*psigma_1*(1+((X-pmu_1)/psigma_1)*((X-pmu_1)/psigma_1))); //Function for Lorentzian Distribution
  GENFUNCTION lorenzianDistribution_2= 1.0/(M_PI*psigma_2*(1+((X-pmu_2)/psigma_2)*((X-pmu_2)/psigma_2)));
  
  GENFUNCTION frac=pfraction*lorenzianDistribution_1+(1-pfraction)*lorenzianDistribution_2;
 
  HistChi2Functional objectiveFunction(&histogram);
  //GENFUNCTION f= histogram.sum()*lorenzianDistribution;
  GENFUNCTION f= histogram.sum()*frac;
  
  bool verbose=true;
  MinuitMinimizer minimizer(verbose);
  minimizer.addParameter(&psigma_1);
  minimizer.addParameter(&pmu_1);
  minimizer.addParameter(&psigma_2);
  minimizer.addParameter(&pmu_2);
  minimizer.addParameter(&pfraction);
  minimizer.addStatistic(&objectiveFunction, &f);
  minimizer.minimize(); 
  
  PlotHist1D pH=histogram;
  PlotFunction1D fplot(f*1.0/bin*(max-min));
  
  PRectF rect;
  rect.setXmin(95);
  rect.setXmax(110);
  rect.setYmin(0);
  rect.setYmax(300);
  PlotView view(rect);
  window.setCentralWidget(&view);

 view.add(&pH);
 view.add(&fplot);
 
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      <<"Spectral Over-Lap"
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
