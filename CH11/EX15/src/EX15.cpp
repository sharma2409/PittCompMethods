#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
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
  
  setLogX(true);
  setLogY(true);
  rect.setXmin(0.0);
  rect.setXmax(10);
  rect.setYmin(0.0);
  rect.setYmax(1e-6);
  
  
  
  
  using namespace Genfun;
  using namespace std;
  RKIntegrator integrator;
  
  Variable S(0,4),I(1,4),E(2,4),R(3,4);  //Variables for SIER model
  
  float beta=0.2; 
  float gamma=0.1;
  float b=0.0001;
  float d=0.0001;
  float alpha=0.1;
  float nu=0.001;
  float n=1.0;
  
  struct PPoint{
  double x;
  double y;
  };
  
  GENFUNCTION DSDT=b-beta*I*S/n-d*S+nu*R;
  GENFUNCTION DEDT=beta*I*S/n-alpha*E;
  GENFUNCTION DIDT=alpha*E-gamma*I-d*I;
  GENFUNCTION DRDT= gamma*I-d*R;
  
  integrator.addDiffEquation(&DSDT, "S",1);
  integrator.addDiffEquation(&DIDT, "I",1e-6);
  integrator.addDiffEquation(&DEDT, "E",0);
  integrator.addDiffEquation(&DRDT, "R",0);
  
  GENFUNCTION i= *integrator.getFunction(I);
  
  vector<PPoint> pointColl;
  
  for (int t=0; t<10; t++)
  {
     
   pointColl.push_back({t,i(t)}); 
   
  }
  

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
  
  
  InterpolatingPolynomial ip;
  
  for (unsigned int i=0; i<pointColl.size();i++) {
	ip.addPoint(pointColl[i].x, pointColl[i].y);
	prof.addPoint(pointColl[i].x, pointColl[i].y);
	}	
		
	PlotFunction1D plotIP=ip;	
	
	view.add(&plotIP);
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

