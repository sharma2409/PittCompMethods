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
  
  int bin=400; //Number of bins
  
  int min=0; //Minimum value of data (estimate)
  int max=150; //Maximum value of data (estimate)
  
  Hist1D histogram (bin, min, max);
  
  ifstream stream("data04.dat");
  
  double x;
  
  Exp exp;
  Sqrt sqrt;
  
  while (stream>>x) {
    
    histogram.accumulate(x);
  }
  
  Parameter pT1("T1",100.0,0.0,500.0);  //Minimizer cog
  Parameter pA1("A1", 1,0,10); //Minimizer Cog
  Parameter pT2("T2",100.0,0.0,500.0);  //Minimizer cog
  Parameter pA2("A2", 1,0,10); //Minimizer Cog
  Parameter pfrac("frac",0.4,0,1);
  
  Variable X;
  
  
  GENFUNCTION bose_einstein_distribution_1= (pA1*X*X*X)/(exp(X/pT1)-1);  //Bose-Einstein distribution for black-body distribution (non-dimensionalized)
  GENFUNCTION bose_einstein_distribution_2= (pA2*X*X*X)/(exp(X/pT2)-1);
  GENFUNCTION frac=pfrac*bose_einstein_distribution_1+(1-pfrac)*bose_einstein_distribution_2;
  HistChi2Functional objectiveFunction(&histogram);
  GENFUNCTION f= histogram.sum()*frac;
  
  bool verbose=true;
  MinuitMinimizer minimizer(verbose);
  minimizer.addParameter(&pT1);
  minimizer.addParameter(&pA1);
  minimizer.addParameter(&pT2);
  minimizer.addParameter(&pA2);
  minimizer.addParameter(&pfrac);
  minimizer.addStatistic(&objectiveFunction, &f);
  minimizer.minimize(); 
  
  PlotHist1D pH=histogram;
  PlotFunction1D fplot(f*1.0/bin*(max-min));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(150);
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
	      <<"Black-Body"
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
