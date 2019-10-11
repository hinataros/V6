/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::constraintCheck(RlsDynamics *io)
{
  if(debug) DEBUG;


  if(io->constraintModel.info.constraint.c.all == 12){

    Vector2d rDelta = io->model->r[1].head(2) - io->model->r[0].head(2);
    Vector2d rCross = Vector2d::Zero();
    rCross <<
      -1000*rDelta(1), 1000*rDelta(0);

    polygon DSregion;
    bg::exterior_ring(DSregion) = boost::assign::list_of<point>
      (io->model->r[0](0), io->model->r[0](1))
      ((io->model->r[0].head(2)+rCross)(0), (io->model->r[0].head(2)+rCross)(1))
      ((io->model->r[0].head(2)+rCross+rDelta)(0), (io->model->r[0].head(2)+rCross+rDelta)(1))
      (io->model->r[1](0), io->model->r[1](1))
      ((io->model->r[1].head(2)-rCross)(0), (io->model->r[1].head(2)-rCross)(1))
      ((io->model->r[1].head(2)-rCross-rDelta)(0), (io->model->r[1].head(2)-rCross-rDelta)(1))
      (io->model->r[0](0), io->model->r[0](1))
      ;

    Vector3d rvrpRef = io->model->rX - io->fb.drXfb/io->model->wX;
    // Vector3d rvrpRef = io->model->rC - io->fb.dvCfb/pow(io->model->wX,2);
    Vector2d rcmpRef = rvrpRef.head(2);
    point CMPRef(rcmpRef(0), rcmpRef(1));

    bool DSdistribution = bg::within(CMPRef, DSregion);

    if(!DSdistribution && bg::intersects(CMPRef, BoS)){
      if((io->model->r[0].head(2) - rcmpRef).norm() < (io->model->r[1].head(2) - rcmpRef).norm()){
        io->constraintModel.Bc_kDiag.block(6,6,6,6) = MatrixXi::Zero(6,6); 
      }
      else{
        io->constraintModel.Bc_kDiag.block(0,0,6,6) = MatrixXi::Zero(6,6); 
      }

      io->constraintModel.reconfigure();
      io->reconfigure();
      reconfigure(io);

      io->constraintModel.update();
    }
  }

}
