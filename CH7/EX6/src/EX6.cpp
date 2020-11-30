#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include "QatGenericFunctions/Variable.h"
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include <random>
#include "QatGenericFunctions/AssociatedLegendre.h"
#include "QatPlotting/PlotFunction1D.h"

typedef std::mt19937 EngineType;

using namespace std;
using namespace Genfun;
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
  
  EngineType e(100);
  
  std::uniform_real_distribution<double> rx(-1,1),ry(0,5.82843);
  
  Hist1D hx("X", 100,-2,2);
  
  Variable X;
  
  GENFUNCTION P1=AssociatedLegendre(1,0);
  GENFUNCTION P3=AssociatedLegendre(3,0);
  GENFUNCTION P5=AssociatedLegendre(5,0);
  GENFUNCTION P7=AssociatedLegendre(7,0);
  
  GENFUNCTION F=(sqrt(3/8)*P1(X)-sqrt(7/6)*P3(X)+sqrt(11/24)*P5(X)-sqrt(15/6)*P7(X))*(sqrt(3/8)*P1(X)-sqrt(7/6)*P3(X)+sqrt(11/24)*P5(X)-sqrt(15/6)*P7(X));
  
  for (int i=0; i<=100000; i++){
  double x=rx(e);
  double y= ry(e);
  if (y<F(x)) {
  hx.accumulate(x);
  }
  }
  
  
  
  PlotHist1D px=hx;
  
  PlotView view;
  view.add(&px);
  view.setRect(px.rectHint());
  
  PlotFunction1D pF=F;
  
  view.add(&pF);
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);
  

  //PlotView view(rect);
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

