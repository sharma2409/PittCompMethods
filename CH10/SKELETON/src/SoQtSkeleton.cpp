// SoQt includes
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
// Coin includes
#include <Inventor/nodes/SoSeparator.h>
#include "Inventor/sensors/SoTimerSensor.h"
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoMaterial.h>
// Inventor includes:
#include <QApplication>
#include <QWidget>
#include <iostream>
#include <Inventor/nodes/SoTexture2.h>
//std namespace std;
SoSphere *myVersion=nullptr;
int timeCounter;

void callback(void *,SoSensor *){
//std::cout<<"Hello Again"<<std::endl;
}
//Forward Decleration

int main(int argc, char **argv)
{


  // Initialize the Qt system:
  QApplication app(argc, argv);
  
  // Make a main window:
  QWidget mainwin;
  mainwin.resize(400,400);

  // Initialize SoQt 
  SoQt::init(&mainwin);

SoTimerSensor * timerSensor = new SoTimerSensor;
timerSensor->setFunction(callback);
timerSensor->setInterval(0.01);
//timerSensor->schedule();
  
  
  // The root of a scene graph
  SoSeparator *root = new SoSeparator;
//  root->ref();

SoTexture2 *texture_sphere= new SoTexture2;

texture_sphere->filename= "gogh";

root->addChild(texture_sphere);

SoSphere * Sphere1 = new SoSphere;
//SoMaterial * red = new SoMaterial;
//red->diffuseColor.setValue(1,0,0);
Sphere1->radius.setValue(2.0);
root->addChild(texture_sphere);
root->addChild(Sphere1);
myVersion=Sphere1;

  
  // Initialize an examiner viewer:
  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(&mainwin);
  eviewer->setSceneGraph(root);
  eviewer->show();
  
  // Pop up the main window.
  SoQt::show(&mainwin);

  // Loop until exit.
  SoQt::mainLoop();




  // Clean up resources.
  delete eviewer;
  root->unref();
}
