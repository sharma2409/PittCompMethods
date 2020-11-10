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
#include "QatGenericFunctions/RKIntegrator.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"

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
  
  using namespace Genfun;
  using namespace std;
  RKIntegrator integrator;
  
  float m=1.0;
  float l=1.0;
  float g=1.0;
  
  Variable theta(0,4), phi(1,4), P1(2,4), P2(3,4);
  
  struct PPoint{
  double x;
  double y;
  };
  
  Sin sin;
  Cos cos;
  
  GENFUNCTION Hamiltonian=((0.5/(m*l*l))*(P1*P1+(P2*P2/(sin(theta)*sin(theta)))))-m*g*l*cos(theta);
  
  GENFUNCTION dthetadt= Hamiltonian.partial(P1);//P1/(m*l*l);
  GENFUNCTION dphidt=Hamiltonian.partial(P2); //P2/(m*l*l*sin(theta)*sin(theta));
  GENFUNCTION dP1dt=-Hamiltonian.partial(theta);
  GENFUNCTION dP2dt=-Hamiltonian.partial(phi);
  
  integrator.addDiffEquation(&dthetadt,"theta",0.5);
  integrator.addDiffEquation(&dphidt,"phi",0.0);
  integrator.addDiffEquation(&dP1dt,"P1",0.0);
  integrator.addDiffEquation(&dP2dt,"P2",0.5);
  
  GENFUNCTION angle1= *integrator.getFunction(theta);
  GENFUNCTION angle2= *integrator.getFunction(phi);
  
  //GENFUNCTION x= sin(angle1)*sin(angle2);
  //GENFUNCTION y= sin(angle1)*cos(angle2);
  
  vector<PPoint> pointColl;
  
  float x,y;
  
  for (double t=0; t<5; t+=0.1)
  {
   
   x=sin(angle1(t))*sin(angle2(t));
   y=sin(angle1(t))*cos(angle2(t));
   pointColl.push_back({x,y}); 
   
   cout<<x<<" "<<y<<endl;
   
   
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

