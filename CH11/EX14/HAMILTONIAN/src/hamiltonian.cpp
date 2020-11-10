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
  
  rect.setXmin(2.5);
  rect.setXmax(4.5);
  rect.setYmin(1.5);
  rect.setYmax(3.5);
 
  using namespace Genfun;
  using namespace std;
  RKIntegrator integrator;
  
  
  float l2=1.0; 
  float l1=1.0;
  float m2=1.0;
  float m1=1.0;
  float g=1.0;
  Variable theta1(0,4),theta2(1,4),P1(2,4),P2(3,4);  //Variables for the hamiltonian problem
  
  struct PPoint{
  double x;
  double y;
  };
  
  Sin sin;
  Cos cos;
  
  GENFUNCTION Hamiltonian=((l2*l2*P1*m2+l1*l1*(m1+m2)*P2*P2-2*m2*l1*l2*P1*P2*cos(theta1-theta2))/2*m2*l1*l1*l2*l2*(m1+m2*sin(theta1-theta2)*sin(theta1-theta2)))-((m1+m2)*g*l1*cos(theta1)-m2*g*l2*l2*cos(theta2));
  
  GENFUNCTION dtheta1dt=Hamiltonian.partial(P1);
  GENFUNCTION dtheta2dt=Hamiltonian.partial(P2);
  GENFUNCTION dP1dt=-Hamiltonian.partial(theta1);
  GENFUNCTION dP2dt=-Hamiltonian.partial(theta2);
  
  integrator.addDiffEquation(&dtheta1dt,"theta1",M_PI/12);
  integrator.addDiffEquation(&dtheta2dt,"theta2",M_PI/12);
  integrator.addDiffEquation(&dP1dt,"P1",1.0);
  integrator.addDiffEquation(&dP2dt,"P2",1.0);
  
  
  GENFUNCTION angle1= *integrator.getFunction(theta1);
  GENFUNCTION angle2= *integrator.getFunction(theta2);
 
  vector<PPoint> pointColl;
  
  for (double t=0; t<5; t++)
  {
     
   pointColl.push_back({angle1(t),angle2(t)}); 
   
   
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

