#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/PlotProfile.h"
#include "QatPlotting/PlotPoint.h"
#include "QatPlotting/PlotOrbit.h"
#include "QatGenericFunctions/Theta.h"
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Sin.h"
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
std::vector<PPoint> pointColl={{130,227},{230,300},{360,285},{395,300},{480,270},{520,233},{530,190},{525,110},{557,80}};
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *nextAction=toolBar->addAction("Next");
  
  nextAction->setShortcut(QKeySequence("n"));
  
  QObject::connect(nextAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(0);
  rect.setXmax(642);
  rect.setYmin(0);
  rect.setYmax(422);

 

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

	PlotPoint A(400,100); //New Origin

	using namespace Genfun;
	
	Genfun::InterpolatingPolynomial I;
	
	double r,phi;
	
	for (unsigned int i=0; i<pointColl.size();i++) {
	r=sqrt(pow((pointColl[i].x-400),2.0)+pow((pointColl[i].y-100),2.0));
	phi=atan2(pointColl[i].y-100.0,pointColl[i].x-400.0);
	I.addPoint(phi,r);
	}	
		
	Genfun::GENFUNCTION X=I*Cos();
	Genfun::GENFUNCTION Y=I*Sin();	
		
	PlotOrbit prof2(X+400,Y+100,0,2.5);	
	{       PlotOrbit::Properties prop;
		prop.pen.setColor("blue");
		prof2.setProperties(prop);
	}
	
		

	view.add(&prof2);
	view.add(&A);
	
  
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
	       << "X position, pixel units"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << "Y position, pixel units"
	       << PlotStream::EndP();


  
  view.show();
  window.show();
  app.exec();
  return 1;
}

