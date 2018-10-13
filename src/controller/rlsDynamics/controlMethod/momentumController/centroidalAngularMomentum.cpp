/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalAngularMomentum()
{
  if(debug) DEBUG;

  // dlCRef = cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef + model->IC*fb.dwBfb;
  // dlCRef = cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef;
  // dlCRef += model->IC*fb.dwBfb + dmodel->IC*model->wB;

  // dlCRef =
  //   cross((Vector3d() << rp, 0.).finished() - model->rC)*dpRef
  //   - KDlC*(model->HC*model->dth);
  // dlCRef = model->IC*fb.dwBfb + dmodel->IC*model->wB - KDlC*(model->IC*model->wB + model->HC*model->dth);
  dlCRef = model->IC*fb.dwBfb + model->IC*model->wB - KDlC*model->HC*model->dth;
  // dlCRef = model->IC*fb.dwBfb + dmodel->IC*model->wB + model->HC*ddthRef + dmodel->HC*model->dth;
  // dlCRef = model->IC*fb.dwBfb + dmodel->IC*model->wB;
  // dlCRef = -KDlC*model->lC;
}
