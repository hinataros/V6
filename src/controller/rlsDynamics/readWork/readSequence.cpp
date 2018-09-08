/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readSequence(YAML::Node &doc, bool multi, string node, int num, int phase, int controlNodeNum)
{
  sequence[num].twf = updateValue<double>(doc, multi, node, num, phase, "twf", sequence[num].twf);

  sequence[num].rCf = updateValue<Vector3d>(doc, multi, node, num, phase, "rCf", sequence[num].rCf);

  sequence[num].rBf = updateValue<Vector3d>(doc, multi, node, num, phase, "rBf", sequence[num].rBf);
  sequence[num].xiBf = updateValue<Vector3d>(doc, multi, node, num, phase, "xiBf", sequence[num].xiBf);

  sequence[num].rXf = updateValue<Vector3d>(doc, multi, node, num, phase, "rXf", sequence[num].rXf);
  sequence[num].cal_Fextf = updateValue<Vector6d>(doc, multi, node, num, phase, "cal_Fextf", sequence[num].cal_Fextf);
}

