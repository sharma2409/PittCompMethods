#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include "QatPlotting/PlotProfile.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/FixedConstant.h"
#include "QatGenericFunctions/RombergIntegrator.h"
#include "QatGenericFunctions/Sqrt.h"
#include "QatPlotting/PlotFunction1D.h"
#include "QatPlotting/RealArg.h"
using namespace Genfun;

/*/double newtonRaphson(GENFUNCTION f,double x){
double xold=x;
while (1){
x-=f(x)/f.prime()(x);
if (fabs(x-xold) < 1.0E-5) return x;
xold=x;

}
}
/*/
int main (int argc, char * * argv) {

  // Automatically generated:-------------------------:

 // std::string usage= std::string("usage: ") + argv[0]; 
 // if (argc!=1) {
   // std::cout << usage << std::endl;
  //}

struct PPoint{
 double x;
 double y;
 };

std::vector<PPoint> pointColl={{0,3281.7},{1,3620},{2,3767}}; //Plotting code

  //double E=-atof(argv[1]);
  
  QApplication     app(argc,argv);
  
  QMainWindow window;
  QToolBar *toolBar=window.addToolBar("Tools");
  QAction  *quitAction=toolBar->addAction("Quit");
  
  quitAction->setShortcut(QKeySequence("q"));
  
  QObject::connect(quitAction, SIGNAL(triggered()), &app, SLOT(quit()));
  
  PRectF rect;
  /*/rect.setXmin(0.0);
  rect.setXmax(4.0);
  rect.setYmin(-1500.0);
  rect.setYmax(400.0);
  /*/
  rect.setXmin(0.0);
  rect.setXmax(3.0);
  rect.setYmin(3000.0);
  rect.setYmax(4000.0);
  
  float alpha=0.38;
  float a=0.00243;
  float mass_quark=1370.0; 
  float mu=mass_quark/2;
  float hc= 197.3; //in Mev.fm
  
  
  PlotProfile prof;
	{
		PlotProfile::Properties prop;
		prop.symbolSize=10;
		prop.pen.setColor("blue");
		prop.brush.setStyle(Qt::SolidPattern);
		prof.setProperties(prop);
		
		}

  
  for (unsigned int i=0; i<pointColl.size();i++) {
	
	prof.addPoint(pointColl[i].x, pointColl[i].y);
	}	
  
  //Variable R;
  
  //GENFUNCTION V =-alpha*4*hc/(3*R)+(R/hc/a/a); //Potential for s-states
  //GENFUNCTION V =-alpha*4*hc/(3*R)+(R/hc/a/a)+((hc*hc)/mu/R/R); //Potential for p-states
  //PlotFunction1D pV(V,RealArg::Gt(0.0));
  
  //FixedConstant fE(E);
  //PlotFunction1D pE=fE;
  
  PlotView view(rect);
  window.setCentralWidget(&view);
  
  //GENFUNCTION T=fE-V;
  //double x0=newtonRaphson(T,0.2);
  //double x1=newtonRaphson(T,1); 
  //std::cout<<x0<<" , "<<x1<<std::endl;
  //std::cout<<x0<<std::endl;
  //view.add(&pV);
  //view.add(&pE);
  view.add(&prof);
  
  //GENFUNCTION integrand=Sqrt()(mass_quark*(T))/hc;
  //RombergIntegrator integrator(0,x0, RombergIntegrator::OPEN); //Romberg Integrator for s-state
  //RombergIntegrator integrator(x0,x1, RombergIntegrator::OPEN); //Romberg Integrator for p-state
  //float N=integrator(integrand)-0.75; //N for s-state
  //float N=integrator(integrand)-0.5; //N for p-state 
  //std::cout<<N<<std::endl;
  
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	     // <<"Charmonium Energy levels(s-states)"
	     <<"Charmonium Energy levels(p-states)"
//	      <<"N= "<<N<< "[MeV]"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       //<<"r[fm]"
	       <<"N"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       <<"E[MeV]"
	       << PlotStream::EndP();
  
  
  
  window.show();
  app.exec();
  return 1;
}

