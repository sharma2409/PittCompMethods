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
#include <random>
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include <cmath>
typedef std::mt19937 EngineType;

using namespace std;
using namespace Genfun;
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }

EngineType e;

//Gamma Distribution scaling

int bin=500; //Number of bins
int count=100000; //Number of points being plotted
int end_val=10;
Hist1D histogram (bin, 0.0, end_val);

std::gamma_distribution<double> u(2.0,1.0);

for (int i=0; i<=count; i++){

	double x=u(e);
	histogram.accumulate(sqrt(x),1./(count*end_val)*bin/(sqrt(x))*1.1238);
	}

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-2.0);
  rect.setXmax(4.0);
  rect.setYmin(0.0);
  rect.setYmax(1.4);
 PlotView view(rect);
  window.setCentralWidget(&view);
  
PlotHist1D ph=histogram;
//PlotView view(ph.rectHint());
//view.add(&ph);// Plot for the Gamma distribution

Variable X;
Exp exp;
Sqrt sqrt;

GENFUNCTION F=0.5641*4*X*X*exp(-X*X);
PlotFunction1D pF=F;
view.add(&ph);
view.add(&pF);
  
 
  
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

