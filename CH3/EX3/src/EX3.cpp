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
#include "QatGenericFunctions/Sin.h"
#include "QatGenericFunctions/Cos.h"
#include "QatGenericFunctions/Exp.h"
#include <sstream>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/AssociatedLegendre.h"
#include "QatGenericFunctions/F1D.h"
#include "QatGenericFunctions/AbsFunction.h"
#include <cmath>
using namespace Genfun;

int main (int argc, char * * argv) {

int i;

std::istringstream stream1(argv[1]);

stream1>>i;

  // Automatically generated:-------------------------:

/*/  std::string usage= std::string("usage: ") + argv[0]; 
  if (argc!=1) {
    std::cout << usage << std::endl;
  }
/*/
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  rect.setXmin(-1.0);
  rect.setXmax(1.0);
  rect.setYmin(-1.0);
  rect.setYmax(1.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  unsigned int l=3; 
  int m=2; //Legendre Polynomial Coefficients
  
  
  //Direct Plot Function declerations
  PlotFunction1D psin=Genfun::Sin();
  PlotFunction1D plegend=Genfun::AssociatedLegendre(l, m, STD);
    
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  psin.setProperties(prop);
  }
  
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  plegend.setProperties(prop);
  }
  
  //General Function Declerations
  Genfun::Variable X;
  Genfun::Exp exp;
  Genfun::Sin sin;
  
  
  Genfun::GENFUNCTION cos=Genfun::F1D(std::cos);  //F1D function
  Genfun::GENFUNCTION f_6=cos*cos;
  PlotFunction1D pf=f_6;
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  pf.setProperties(prop);
  }
  
  //Genfun::GENFUNCTION fd=f_6.prime()(1);
  PlotFunction1D pfd=f_6.prime()(X);
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  pfd.setProperties(prop);
  }
  
  
  Genfun::GENFUNCTION sin_5= sin(5*X);
  PlotFunction1D psin5=sin_5;
    
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  psin5.setProperties(prop);
  }
  
  Genfun::GENFUNCTION sin_sqr= sin(X*X);
  PlotFunction1D psinsqr=sin_sqr;
    
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  psinsqr.setProperties(prop);
  }
  
  Genfun::GENFUNCTION exp_sin=exp(-1*X)*sin(X);
  PlotFunction1D pexpsin=exp_sin;
  
  {PlotFunction1D::Properties prop;
  prop.pen.setWidth(3);
  pexpsin.setProperties(prop);}
  
  if (i==1){
  view.add (&psin); //Sin function 
  };
  
  if (i==2){
  view.add (&psin5);};
  
  if (i==3){
  view.add (&psinsqr);};
  
  if (i==4){
  view.add (&pexpsin);};
  
  if (i==5){
  view.add (&plegend);};
  
  if (i==6){
  view.add (&pf);};
  
  if (i==7){
  view.add (&pfd);};
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center()
	      <<"Function " 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(12)
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       <<"X"
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(4)
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(4)
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

