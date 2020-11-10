#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/ButcherTableau.h"
#include "QatGenericFunctions/SimpleRKStepper.h"
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/AdaptiveRKStepper.h"
#include "QatGenericFunctions/StepDoublingRKStepper.h"
using namespace Genfun;
using namespace std;

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
  rect.setXmin(0.0);
  rect.setXmax(1.0);
  rect.setYmin(0.0);
  rect.setYmax(1.0);
  
  float zee=10;
  float omega0=1;
  
  Variable ETA(0,3),X(1,3),TAU(2,3);
  FixedConstant I(1.0);
  
  GENFUNCTION DXDTAU=ETA;
  GENFUNCTION DETADTAU=-2*zee*ETA-X;
  GENFUNCTION DTDTAU  = I%I%I;
  
  ClassicalRungeKuttaTableau t;
  //SimpleRKStepper stepper(t,0.1); //Fixed size control 
  StepDoublingRKStepper stepper0(t); //Adaptive
  
  AdaptiveRKStepper stepper(&stepper0);
  RKIntegrator integrator(&stepper);
  
  integrator.addDiffEquation(&DXDTAU, "X",0);
  integrator.addDiffEquation(&DETADTAU,"ETA",0);
  integrator.addDiffEquation(&DTDTAU,"TAU",0);
  
  GENFUNCTION x=*integrator.getFunction(X)*omega0;
  
  cout<<x(1.0);
  

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

