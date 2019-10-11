/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::rootLinkManipulability(RlsDynamics *io, Vector6d CRBfull, string mode)
{
  if(debug) DEBUG;

  for(int i=0; i<io->info.model.dof.joint; i++){
    if(io->model->th(i) > io->model->thMid(i)){
      pMinus(i) = 1;
      pPlus(i) = 1/sqrt(1 + abs(h2(i)));
    }
    else{
      pMinus(i) = 1/sqrt(1 + abs(h2(i)));
      pPlus(i) = 1;
    }
    
  }

  VectorXd Gamma = Vector6d::Zero();
  VectorXd vec = Vector6d::Zero();

  int i,j;

  double sum;

  ///////////////////////////////////// CRB weight //////////////////////////////////
  
  if(io->constraintModel.info.constraint.c.all == 0){
    w_CRB = Vector6d::Zero();
  }

  else{
    if(io->constraintModel.info.constraint.c.all == 6){

      MatrixXd JcM = MatrixXd::Zero(6,6);
      MatrixXd L = MatrixXd::Zero(6,6);

      vec = - io->constraintModel.mbb_CcM.block(0,0,6,6).transpose()*CRBfull;
      for(int i=0; i<6; i++){
        Gamma(i) =  (vec(i)>0) - (vec(i)<0);
      }

      if(io->constraintModel.info.constraint.c.controlNode[0] == 6){
        JcM = io->constraintModel.cal_JcM.block(0,0,6,6);
        
        for(i=0; i<6; i++){
          for(j=0; j<6; j++){
            if( ((JcM(i,j)>0) - (JcM(i,j)<0)) * Gamma(i) < 0)
              L(i,j) = pMinus(j);
            else
              L(i,j) = pPlus(j);
          }
        }
      }

      if(io->constraintModel.info.constraint.c.controlNode[1] == 6){
        JcM = io->constraintModel.cal_JcM.block(0,6,6,6);

        for(i=0; i<6; i++){
          for(j=0; j<6; j++){
            if( ((JcM(i,j)>0) - (JcM(i,j)<0)) * Gamma(i) < 0)
              L(i,j) = pMinus(6+j);
            else
              L(i,j) = pPlus(6+j);
          }
        }
      }

      for(i=0; i<6; i++){
        sum = 1;
        for(j=0; j<6; j++){
          sum *= pow(L(i,j), abs(((JcM.row(i)).normalized())(j)) );
        }
        w_CRB(i) = sum;
      }

    }
      
    if(io->constraintModel.info.constraint.c.all == 12){
      MatrixXd JcMRL = io->constraintModel.cal_JcM.block(0,0,6,6);
      MatrixXd L_RL = MatrixXd::Zero(6,6);

      vec = - io->constraintModel.mbb_CcM.block(0,0,6,6).transpose()*CRBfull;
      for(int i=0; i<6; i++){
        Gamma(i) =  (vec(i)>0) - (vec(i)<0); 
      }

      for(i=0; i<6; i++){
        for(j=0; j<6; j++){
          if( ((JcMRL(i,j)>0) - (JcMRL(i,j)<0)) * Gamma(i) < 0)
            L_RL(i,j) = pMinus(j);
          else
            L_RL(i,j) = pPlus(j);
        }
      }

      Vector6d w_RL;

      for(i=0; i<6; i++){
        sum = 1;
        for(j=0; j<6; j++){
          sum *= pow(L_RL(i,j), abs(((JcMRL.row(i)).normalized())(j)) );
        }
        w_RL(i) = sum;
      }

      
      MatrixXd JcMLL = io->constraintModel.cal_JcM.block(0,0,6,6);
      MatrixXd L_LL = MatrixXd::Zero(6,6);

      vec = - io->constraintModel.mbb_CcM.block(0,0,6,6).transpose()*CRBfull;
      for(int i=0; i<6; i++){
        Gamma(i) =  (vec(i)>0) - (vec(i)<0); 
      }

      for(i=0; i<6; i++){
        for(j=0; j<6; j++){
          if( ((JcMLL(i,j)>0) - (JcMLL(i,j)<0)) * Gamma(i) < 0)
            L_LL(i,j) = pMinus(j);
          else
            L_LL(i,j) = pPlus(j);
        }
      }

      Vector6d w_LL;

      for(i=0; i<6; i++){
        sum = 1;
        for(j=0; j<6; j++){
          sum *= pow(L_LL(i,j), abs(((JcMLL.row(i)).normalized())(j)) );
        }
        w_LL(i) = sum;
      }

      
      for(i=0; i<6; i++){
          if(w_RL(i) <= w_LL(i))
          w_CRB(i) = w_RL(i);
        else
          w_CRB(i) = w_LL(i);
      }
    }
  }

  for(i=0; i<6; i++){
    W(i,i) = w_CRB(i);
  }

  static MatrixXd Wpre = W;
  double damp = 2;
  if(mode == "acc"){
    for(i=0; i<6; i++){
      dW(i,i) = (W(i,i) - Wpre(i,i))/io->worldModel->dt;
      if(abs(dW(i,i)) >= damp)
        // dW(i,i) = 0;
        dW(i,i) = damp*dW(i,i)/abs(dW(i,i));
    }
    Wpre = W;
  }

}
