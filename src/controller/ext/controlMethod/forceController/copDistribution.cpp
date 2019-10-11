/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::copDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  double g = 9.81;

  MatrixXd S2X = MatrixXd::Zero(2,2);
  S2X <<
    0, 1,
    -1, 0;

  Vector2d rcop =
    (io->model->rX - io->fb.drXfb/io->model->wX).head(2)
    - 1 / (io->model->M * g) * S2X * io->dlCRef.head(2);

  MatrixXd Wcopc = io->h_weight(rcop);
  // MatrixXd Wecmpc = h_weight(recmp, model->r[0].head(2)+distOffset, model->r[1].head(2)-distOffset);

  io->cal_FcBarRef =
    pInv(io->constraintModel.mbb_CcM, Wcopc)*(io->cal_dLCRef + io->model->cal_GC);

}
