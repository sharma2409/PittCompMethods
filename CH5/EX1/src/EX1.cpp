#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include "QatGenericFunctions/Tanh.h"
#include "QatGenericFunctions/Cosh.h"
#include "QatGenericFunctions/Sinh.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Sqrt.h"
#include <cmath>
#include "QatGenericFunctions/F1D.h"
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }


  using namespace Genfun;
 //GENFUNCTION f=Tanh();
 //SimpsonsRule rule; //Which rule is being followed
 //MidpointRule rule;
  //TrapezoidRule rule;
  //SimpleIntegrator integrator(0,1,rule,8);
  
  //double integral=integrator(f);
  //double trueval=0.4388;
  
  //std::cout<<abs(integral-trueval);

//for second part

//Genfun::Variable U;

Genfun::Sqrt sqrt;

GENFUNCTION sinh=Genfun::F1D(std::sinh);
GENFUNCTION cosh=Genfun::F1D(std::cosh);

GENFUNCTION f2=sqrt(cosh/sinh);

SimpsonsRule rule;
SimpleIntegrator integrator(0,1,rule,4);
  
 double integral2=integrator(f2);
 double trueval2=2.068;
 
 std::cout<<abs(integral2-trueval2);

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

