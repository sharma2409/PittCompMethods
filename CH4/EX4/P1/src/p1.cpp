#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotOrbit.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/InterpolatingPolynomial.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <cstdlib>
#include <iostream>
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

//std::vector<PPoint> pointColl={{130,227},{230,300},{360,285},{395,300},{480,270},{520,233},{530,190}};
std::vector<PPoint> pointColl={{-545.18,-23.26},{230,300},{360,285},{395,300},{480,270},{520,233},{530,190}};
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-770);
  rect.setXmax(0);
  rect.setYmin(-80);
  rect.setYmax(0);

 

  PlotView view(rect);
  view.setXZero(false);
  view.setYZero(false);
  view.setGrid(false);
  view.setFixedWidth(900);
  view.setFixedHeight(700);
  window.setCentralWidget(&view);

  char *wd=dirname(argv[0]);
  std::string imageName=std::string(wd)+"/../../src/p1.png";
  QPixmap imagePix(imageName.c_str());
  QGraphicsPixmapItem imagePixItem;
  imagePixItem.setPixmap(imagePix);
  //imagePixItem.setFlags(QGraphicsItem::ItemIsMovable);
  view.scene()->addItem(&imagePixItem);
  imagePixItem.setScale(1.0);
  imagePixItem.setPos(130,130);

	PlotProfile prof;
	{
		PlotProfile::Properties prop;
		prop.symbolSize=10;
		prop.pen.setColor("blue");
		prop.brush.setStyle(Qt::SolidPattern);
		prof.setProperties(prop);
		
		}

/*/	PlotOrbit prof2;
	{ PlotOrbit::Properties prop
		prop.pen.setColor("blue");
		prof2.setProperties(prop);
	}
	
/*/		
	using namespace Genfun;
	Genfun::InterpolatingPolynomial ip;
	
	for (unsigned int i=0; i<pointColl.size();i++) {
	ip.addPoint(pointColl[i].x, pointColl[i].y);
	prof.addPoint(pointColl[i].x, pointColl[i].y);
	}	
		
	PlotFunction1D plotIP=ip;	
	
	//view.add(&plotIP);
	view.add(&prof);
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      << "P1 Bus interpolated position"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "r position, pixel units"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "theta position, pixel units"
	       << PlotStream::EndP();


  
  view.show();
  window.show();
  app.exec();
  return 1;
}

