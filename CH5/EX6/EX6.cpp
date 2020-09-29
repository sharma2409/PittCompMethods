#include "QatGenericFunctions/NormalDistribution.h"
#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"

int main(int argc, char**argv){

using namespace Genfun;
NormalDistribution f;

GaussLegendreRule rule(argc==2 ? std::stoi(argv[1]):4);
GaussIntegrator integrator(rule);

double approx=integrator(f);
std::cout<<approx;

return 0;
}
