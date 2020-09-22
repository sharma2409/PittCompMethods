#include "QatPlotWidgets/PlotView.h"
#include "QatPlotting/PlotStream.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <cstdlib>
#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <complex>
#include "QatGenericFunctions/F1D.h"
#include "QatGenericFunctions/AbsFunction.h"
#include "QatPlotting/PlotFunction1D.h"
#include <cmath>
#include "QatGenericFunctions/Variable.h"
#include "QatGenericFunctions/Cos.h"

using namespace Genfun;

typedef std::complex<double>Complex;


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

double m=1.0;

Eigen::MatrixXd M(5,5);

double k=1.0; //spring constant value
double k1=k;
double k2=2*k;
double k3=2*k;
double k4=k;

for (int l=0; l<5; l++)
{    for (int k=0; k<5; k++)
    {  M(l,k)=0.0;} //Initialzing K Matrix with zeroes
}

M(0,0)=sqrt(m);
M(1,1)=sqrt(3*m);
M(2,2)=sqrt(2*m);
M(3,3)=sqrt(m);
M(4,4)=sqrt(2*m);


Eigen::MatrixXd K(5,5);
//First Row
for (int i=0; i<5; i++)
{    for (int j=0; j<5; j++)
    {  K(i,j)=0.0;} //Initialzing K Matrix with zeroes
}

//First Row
K(0,0)=k1;
K(0,1)=-k1;

//Second Row
K(1,0)=-k1;
K(1,1)=k1+k2;
K(1,2)=-k2;

//Third Row
K(2,1)=-k2;
K(2,2)=k2+k3;
K(2,3)=-k3;

//Fourth Row
K(3,2)=-k3;
K(3,3)=k3+k4;
K(3,4)=-k4;

//Fifth Row
K(4,3)=-k4;
K(4,4)=k4;

Eigen::MatrixXd M2(5,5);
M2=M.inverse(); //Inverse of square root M

Eigen::MatrixXd delta(5,5);
delta=M2*K*M2; //Delta square matrix

Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> s(delta);

Eigen::VectorXd val=s.eigenvalues();
Eigen::MatrixXd vec=s.eigenvectors();

Eigen::VectorXd x0(5); //Initial Position Vector

x0(0)=-2;
x0(1)=3;
x0(2)=0;
x0(3)=-3;
x0(4)=2;

//Eigen::VectorXd eta(5);
//eta=vec.transpose()*M2*x0;

//Eigen::VectorXd a(5,5);
//a=M2*vec;

Variable t;
Cos cos;
GENFUNCTION f0=vec.col(0).transpose()*M2*x0(0)*M2*vec.col(0)*cos(sqrt(val(0))*t);
GENFUNCTION f1=vec.col(1).transpose()*M2*x0(1)*M2*vec.col(1)*cos(sqrt(val(1))*t);
GENFUNCTION f2=vec.col(2).transpose()*M2*x0(2)*M2*vec.col(2)*cos(sqrt(val(2))*t);
GENFUNCTION f3=vec.col(3).transpose()*M2*x0(3)*M2*vec.col(3)*cos(sqrt(val(3))*t);
GENFUNCTION f4=vec.col(4).transpose()*M2*x0(4)*M2*vec.col(4)*cos(sqrt(val(4))*t);

GENFUNCTION fcom=f0+f1+f2+f3+f4;


PlotFunction1D p0=f0;
PlotFunction1D p1=f1;
PlotFunction1D p2=f2;
PlotFunction1D p3=f3;
PlotFunction1D p4=f4;
PlotFunction1D pcom=fcom;
  
  PRectF rect;
  rect.setXmin(0.0);
  rect.setXmax(10.0);
  rect.setYmin(-6.0);
  rect.setYmax(2.5);
  
  PlotView view(rect);
  window.setCentralWidget(&view);
  
//view.add(&p0);
//view.add(&p1);
//view.add(&p2);
//view.add(&p3);
//view.add(&p4);
view.add(&pcom);

  
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

