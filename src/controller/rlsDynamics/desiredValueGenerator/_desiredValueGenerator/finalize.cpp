/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::finalize()
{
  if(debug) DEBUG;

  walking.finalize();

  delete[] rDes;
  delete[] qDes;
  delete[] dqDes;
  delete[] ddqDes;
  delete[] RDes;

  delete[] tw0;
  delete[] twf;

  delete[] r0;
  delete[] q0;

  delete[] rpreDes;
  delete[] rpreDesabs;
  delete[] qpreDes;
  delete[] qpreDesabs;
  delete[] fpreDes;
  delete[] npreDes;

  delete[] rf;
  delete[] rfabs;
  delete[] xif;
  delete[] xifabs;
  delete[] qf;
  delete[] qfabs;
  delete[] ff;
  delete[] nf;

  delete[] rtd;

  delete[] controlNodeTranslationNum;
  delete[] controlNodeTranslationName;
  delete[] controlNodeRotationNum;
  delete[] controlNodeRotationName;
  delete[] controlNodeForceNum;
  delete[] controlNodeForceName;
  delete[] controlNodeMomentNum;
  delete[] controlNodeMomentName;
  delete[] controlNodeTranslation_map;
  delete[] controlNodeRotation_map;
  delete[] controlNodeForce_map;
  delete[] controlNodeMoment_map;
  free(controlNodeTranslation_ptr);
  free(controlNodeRotation_ptr);
  free(controlNodeForce_ptr);
  free(controlNodeMoment_ptr);
}
