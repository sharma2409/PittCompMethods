#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatGenericFunctions/Abs.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>

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

struct PPoint
{
	double x;
	double y;
	};
	
	vector<PPoint> ns;
	vector<PPoint> na;   //Vectors to record Ns and Na values for plotting  

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(1.0);
  rect.setXmax(10.0);
  rect.setYmin(0.0);
  rect.setYmax(5.0);

	Exp exp;
	Sqrt sqrt;
	Abs abs;
	
	Variable X(0,4),Y(1,4),Z(2,4),D(3,4);
	
	int N=500000;
	
	GENFUNCTION phi1=0.5641*exp(-sqrt(abs(X*X+Y*Y+(Z-D/2)*(Z-D/2))));
	GENFUNCTION phi2=0.5641*exp(-sqrt(abs(X*X+Y*Y+(Z+D/2)*(Z+D/2))));
  
  	GENFUNCTION f1=(phi1+phi2)*(phi1+phi2)*exp(X+Y+Z);
  	GENFUNCTION f2=(phi1-phi2)*(phi1-phi2)*exp(X+Y+Z);
  	GENFUNCTION f3=phi1*phi1*exp(X+Y+Z);
  	
  	exponential_distribution<double>c(1.0);
  	
  	for (double j=1; j<=10; j=j+0.5) {
  	
  	double a=0;
  	double b=0;
  	
  	for (int i=0; i<=N; i++){  //Points for Monte-Carlo Integration
  	
  	double x1= c(e);
  	double y1= c(e);
  	double z1= c(e);
  	
  	//a=a+f3({x1,y1,z1,j});
  	a=a+f1({x1,y1,z1,j});
  	b=b+f2({x1,y1,z1,j});
  	}
  	
  	//na.push_back({j,sqrt(N/(8*b))}); //Normalization
  	//ns.push_back({j,sqrt(N/(8*a))});
  	
  	na.push_back({j,((8*b)/N)}); //Energy
  	ns.push_back({j,((8*a)/N)});
  	
  	
  	}
  
	

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  PlotProfile p1;  //For Na
  
  {
    PlotProfile::Properties prop;
    prop.symbolSize=30;
    prop.pen.setColor("blue");
    p1.setProperties(prop);
  }
  
  PlotProfile p2;  //For Ns
  
  {
    PlotProfile::Properties prop;
    prop.symbolSize=30;
    prop.pen.setColor("black");
    p2.setProperties(prop);
  }
  
  for (unsigned int i=0; i<=na.size();i++) {
 	p1.addPoint(na[i].x,na[i].y);
  	p2.addPoint(ns[i].x,ns[i].y);
  	}

  view.add(&p1);
  view.add(&p2);

  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      <<"Energy v/s Distance"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       <<"Radial Distance"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       <<"Energy"
	       << PlotStream::EndP();
  
  

  window.show();
  app.exec();
  return 1;
}

