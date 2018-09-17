/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialValue(const string &work_dir, Model &model)
{
  if(debug) DEBUG;

  th0 = model.hoap2.readJointStateVector("joint angle");

  rC0 = model.hoap2.all.rC;
  rB0 = model.hoap2.link[model.hoap2.info.rootNode].r;
  xiB0 = R2xi(model.hoap2.link[model.hoap2.info.rootNode].R);

  rX0 = model.hoap2.all.rC + sqrt(model.hoap2.all.rC(2)/abs(model.hoap2.ag(2)))*model.hoap2.all.vC;

  cal_X0 = model.hoap2.readControlNodeValueVector("6D position");

  cal_Fext0 <<
    model.hoap2.link[model.hoap2.info.rootNode].f,
    model.hoap2.link[model.hoap2.info.rootNode].n;

  // high gain control
  thDes = model.hoap2.readJointStateVector("joint angle");

  readWork(work_dir, model.hoap2.info, false, "Default", 0, 0);

  initialValueFlag = false;
}
