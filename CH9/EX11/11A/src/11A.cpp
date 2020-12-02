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
#include <cmath>

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
  
  uniform_real_distribution<double>u(0,1); 
  
  int bin=100;  //Number of bins for histograms
  int N=100000; //Number of points
  double max=0.8; //Maximum value of observation 
  
  Hist1D hist0(bin,0,max);
  Hist1D hist1(bin,0,max);
  Hist1D hist2(bin,0,max);
  Hist1D hist3(bin,0,max);
  Hist1D hist4(bin,0,max);
  Hist1D hist5(bin,0,max);
  Hist1D hist6(bin,0,max);
  
for (int i=0; i<=N; i++){
	double x=asin(u(e));
	hist0.accumulate(4*asin(sin(x)/data[0].y)-2*x,1.0/(N*max)*bin);
	hist1.accumulate(4*asin(sin(x)/data[1].y)-2*x,1.0/(N*max)*bin);
	hist2.accumulate(4*asin(sin(x)/data[2].y)-2*x,1.0/(N*max)*bin);
	hist3.accumulate(4*asin(sin(x)/data[3].y)-2*x,1.0/(N*max)*bin);
	hist4.accumulate(4*asin(sin(x)/data[4].y)-2*x,1.0/(N*max)*bin);
	hist5.accumulate(4*asin(sin(x)/data[5].y)-2*x,1.0/(N*max)*bin);
	hist6.accumulate(4*asin(sin(x)/data[6].y)-2*x,1.0/(N*max)*bin);
	
	} 
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(0.8);
  rect.setYmin(0.0);
  rect.setYmax(10.0);
  

  PlotView view(rect);
  window.setCentralWidget(&view);
  
  PlotHist1D phist0=hist0;
  PlotHist1D phist1=hist1;
  PlotHist1D phist2=hist2;
  PlotHist1D phist3=hist3;
  PlotHist1D phist4=hist4;
  PlotHist1D phist5=hist5;
  PlotHist1D phist6=hist6;
  
  
  view.add(&phist0);
  view.add(&phist1);
  view.add(&phist2);
  view.add(&phist3);
  view.add(&phist4);
  view.add(&phist5);
  view.add(&phist6);
  
  
  PlotStream titleStream(view.titleTextEdit());
  titleStream << PlotStream::Clear()
	      << PlotStream::Center() 
	      << PlotStream::Family("Sans Serif") 
	      << PlotStream::Size(16)
	      <<"PDF"
	      << PlotStream::EndP();
  
  
  PlotStream xLabelStream(view.xLabelTextEdit());
  xLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       <<"Phi (Radians)"
	       << PlotStream::EndP();
  
  PlotStream yLabelStream(view.yLabelTextEdit());
  yLabelStream << PlotStream::Clear()
	       << PlotStream::Center()
	       << PlotStream::Family("Sans Serif")
	       << PlotStream::Size(16)
	       << PlotStream::EndP();
  
  
  view.show();
  window.show();
  app.exec();
  return 1;
}

