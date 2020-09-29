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
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/QuadratureRule.h"
#include "QatGenericFunctions/SimpleIntegrator.h"
#include <cmath>
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/F1D.h"
#include "QatPlotting/PlotProfile.h"

int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }
  

using namespace Genfun;

Sqrt sqrt;
GENFUNCTION cos=Genfun::F1D(std::cos);
double theta0=(11.0*M_PI)/12.0;

GENFUNCTION f=1.0/sqrt((cos-(std::cos(theta0))));

MidpointRule rule;

SimpleIntegrator integrator(0,theta0,rule,4096*4);

double integral=integrator(f);
std::cout<<integral;
//PlotFunction1D pf=integrator


//Plotting the function
struct PPoint{
double x;
double y;
};  

std::vector<PPoint> pointColl={{M_PI/12.0,2.21758},{M_PI/6.0,2.25327},{M_PI/3.0,2.37666},{M_PI/2.0,2.61368},{2.0*M_PI/3.0,3.03938},{5.0*M_PI/6.0,0.00501846},{11.0*M_PI/12.0,4.83907}};




  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(3.0);
  rect.setYmin(2.0);
  rect.setYmax(5.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  PlotProfile prof;
	{
		PlotProfile::Properties prop;
		prop.symbolSize=10;
		prop.pen.setColor("blue");
		prop.brush.setStyle(Qt::SolidPattern);
		prof.setProperties(prop);
		
		}
		
	for (unsigned int i=0; i<pointColl.size();i++){
	prof.addPoint(pointColl[i].x,pointColl[i].y);
	}
	
	view.add(&prof);	

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
	       <<"f(theta)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       <<"theta_max"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

