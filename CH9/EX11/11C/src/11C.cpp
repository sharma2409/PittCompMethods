#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "QatGenericFunctions/Theta.h"
#include "QatDataAnalysis/Hist1D.h"
#include "QatPlotting/PlotHist1D.h"
#include "QatGenericFunctions/ASin.h"
#include "QatGenericFunctions/CubicSplinePolynomial.h"
#include <cmath>
#include "QatPlotting/PlotProfile.h"
#include <thread>
#include <memory>
#include "omp.h"

using namespace std;
using namespace Genfun;

typedef mt19937 Enginetype;

int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }

struct PPoint {
	double x;
	double y;
	};
	
vector<PPoint> data={{400.0,1.339},{450.0,1.337},{500.0,1.335},{550.0,1.333},{600.0,1.332},{650.0,1.331},{700.0,1.331}}; //Refraction data from 400-700 nm	

Enginetype e;

  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-0.5);
  rect.setXmax(0.5);
  rect.setYmin(0.5);
  rect.setYmax(0.8);
  
  PlotView view(rect);
  window.setCentralWidget(&view);

uniform_real_distribution<double>red(620,700);
uniform_real_distribution<double>violet(400,450);
uniform_real_distribution<double>yellow(560,590);
uniform_real_distribution<double>green(520,559);
uniform_real_distribution<double>blue(400,500);	//Distributions for various colors

uniform_real_distribution<double>u(0.5,0.6);
uniform_real_distribution<double>theta(-0.5,0.5);

CubicSplinePolynomial p;
for(unsigned int i =0;i<data.size();i++){
    p.addPoint(data[i].x,data[i].y);
  }
  
  PlotProfile prof_red;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("red");
    prof_red.setProperties(prop);
  }
  
  PlotProfile prof_violet;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("violet");
    prof_violet.setProperties(prop);
  }
  
  PlotProfile prof_yellow;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("yellow");
    prof_yellow.setProperties(prop);
  }
  
  PlotProfile prof_green;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("green");
    prof_green.setProperties(prop);
  }
  
  PlotProfile prof_blue;
  {
    PlotProfile::Properties prop;
    prop.symbolSize=1;
    prop.pen.setColor("blue");
    prof_blue.setProperties(prop);
  }
  
  
  int N=10000000; //Number of points
  
  //#pragma omp parallel for
  #pragma omp simd
  for (int i=0; i<N+1; i++){
   double i1=asin(u(e));
   double i2=theta(e);
   double i3=theta(e);
   double i4=theta(e);
   double i5=theta(e);
   double i6=theta(e);
   double color_red=red(e);
   double color_violet=violet(e);
   double color_yellow=yellow(e);
   double color_green=green(e);
   double color_blue=blue(e);
   
   double p_red=tan(4*asin(sin(i1)/p(color_red))-2*i1);
   double p_violet=tan(4*asin(sin(i1)/p(color_violet))-2*i1);
   double p_yellow=tan(4*asin(sin(i1)/p(color_yellow))-2*i1);
   double p_green=tan(4*asin(sin(i1)/p(color_green))-2*i1);
   double p_blue=tan(4*asin(sin(i1)/p(color_blue))-2*i1);
   
   prof_red.addPoint(p_red*sin(i2),p_red*cos(i2));
   prof_violet.addPoint(p_violet*sin(i3),p_violet*cos(i3));
   prof_yellow.addPoint(p_yellow*sin(i4),p_yellow*cos(i4));
   prof_green.addPoint(p_green*sin(i5),p_green*cos(i5));
   prof_blue.addPoint(p_blue*sin(i6),p_blue*cos(i6));
   
   
   }
   
   
   view.add(&prof_red);
   view.add(&prof_violet);
   view.add(&prof_yellow);
   view.add(&prof_green);
   view.add(&prof_blue);
  
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      <<"Rainbow"
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

