#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <libgen.h>

int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }

struct PPoint{
 double x;
 double y;
 };

std::vector<PPoint> pointColl={{2007,346},{2008,654},{2009,724},{2010,873},{2011,1410}};




  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(2006.0);
  rect.setXmax(2022.0);
  rect.setYmin(0.0);
  rect.setYmax(100000.0);
  
  
  PlotProfile prof;
  
    {
		PlotProfile::Properties prop;
		prop.symbolSize=10;
		prop.pen.setColor("blue");
		prop.brush.setStyle(Qt::SolidPattern);
		prof.setProperties(prop);
		prof.addPoint(2020,71000);
		}
		
	using namespace Genfun;
	Genfun::InterpolatingPolynomial ip;
	
	for (unsigned int i=0; i<pointColl.size();i++) {
	ip.addPoint(pointColl[i].x, pointColl[i].y);
	prof.addPoint(pointColl[i].x, pointColl[i].y);
	}	
		
	PlotFunction1D plotIP=ip;	
	
	
  PlotView view(rect);
  window.setCentralWidget(&view);
  
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

