#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
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
#include <cmath>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Parameter.h"
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
  
  Hist1D histogram (1000.0, 80.0, 110.0);
  
  ifstream stream("data00.dat");
  
  double x;
  
  while (stream>>x) {
    
    histogram.accumulate(x);
  }
  
  Parameter pgamma("Gamma",0.5,0.01,4.0);
  
  Variable X;
  
  GENFUNCTION lorenzianDistribution=1/(M_PI*pgamma*(1+(X/pgamma)*(X/pgamma)));
 
  HistChi2Functional objectiveFunction(&histogram);

  PlotHist1D pH=histogram;
  PlotView view(pH.rectHint());
  view.setGrid(false);
  view.setBox(false);
  view.setXZero(false);
  view.setYZero(false);
  view.add(&pH);
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
