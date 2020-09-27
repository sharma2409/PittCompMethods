#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }
  
  //Points
  struct PPoint{
 double x;
 double y;
 };

std::vector<PPoint> pointColl={{200,1.396},{250,1.362},{300,1.349},{350,1.343},{400,1.339},{450,1.337},{500,1.335},{550,1.333},{600,1.332},{650,1.331},{700,1.331},{750,1.330},{800,1.329},{850,1.329},{900,1.328},{950,1.327},{1000,1.327}};


  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(199.0);
  rect.setXmax(1002.0);
  rect.setYmin(1.200);
  rect.setYmax(1.397);
  

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
	
		
	using namespace Genfun;
	Genfun::InterpolatingPolynomial ip;
	
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
	       <<"Wavelength (nm)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       <<"Index of Refraction"
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

