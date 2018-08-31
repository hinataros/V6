/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readSequence(YAML::Node &doc, bool multi, string node, int num, int phase, int eeNum)
{
  sequence[num].twf = updateValue<double>(doc, multi, node, num, phase, "twf", sequence[num].twf);

  sequence[num].rCf = updateVector<Vector3d>(doc, multi, node, num, phase, "rCf", sequence[num].rCf);

  sequence[num].rBf = updateVector<Vector3d>(doc, multi, node, num, phase, "rBf", sequence[num].rBf);
  sequence[num].xiBf = updateVector<Vector3d>(doc, multi, node, num, phase, "xiBf", sequence[num].xiBf);

  sequence[num].rXf = updateVector<Vector3d>(doc, multi, node, num, phase, "rXf", sequence[num].rXf);
  sequence[num].cal_Fextf = updateVector<Vector6d>(doc, multi, node, num, phase, "cal_Fextf", sequence[num].cal_Fextf);

  sequence[num].cal_Xf = updateVector<VectorXd>(doc, multi, node, num, phase, "cal_Xf", eeNum, sequence[num].cal_Xf);

  // info.sim.trecf = checkValue<double>(doc, node, seq, "trecf", info.sim.trecf);
}

