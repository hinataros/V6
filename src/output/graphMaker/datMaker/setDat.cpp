/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::setDat(ofstream& stream, int id, string dataName, int i)
{
  if(dataName=="time")
    stream << data.time[i];

  // tree model
  else if(dataName=="tree model rB")
    stream << data.treeModel[id].vec[i].rB.transpose();
  else if(dataName=="tree model vB")
    stream << data.treeModel[id].vec[i].vB.transpose();

  else if(dataName=="tree model xiB")
    stream << data.treeModel[id].vec[i].xiB.transpose();
  else if(dataName=="tree model wB")
    stream << data.treeModel[id].vec[i].wB.transpose();

  else if(dataName=="tree model th")
    stream << data.treeModel[id].vec[i].th.transpose();
  else if(dataName=="tree model dth")
    stream << data.treeModel[id].vec[i].dth.transpose();

  else if(dataName=="tree model r")
    stream << data.treeModel[id].vec[i].r.transpose();
  else if(dataName=="tree model v")
    stream << data.treeModel[id].vec[i].v.transpose();
  else if(dataName=="tree model xi")
    stream << data.treeModel[id].vec[i].xi.transpose();
  else if(dataName=="tree model w")
    stream << data.treeModel[id].vec[i].w.transpose();

  else if(dataName=="tree model rC")
    stream << data.treeModel[id].vec[i].rC.transpose();
  else if(dataName=="tree model vC")
    stream << data.treeModel[id].vec[i].vC.transpose();

  else if(dataName=="tree model f")
    stream << data.treeModel[id].vec[i].f.transpose();
  else if(dataName=="tree model n")
    stream << data.treeModel[id].vec[i].n.transpose();

  else if(dataName=="tree model p")
    stream << data.treeModel[id].vec[i].p.transpose();
  else if(dataName=="tree model lC")
    stream << data.treeModel[id].vec[i].lC.transpose();

  // controller
  // desired value
  else if(dataName=="rBDes")
    stream << data.rlsDynamics[id].vec[i].rBDes.transpose();
  else if(dataName=="vBDes")
    stream << data.rlsDynamics[id].vec[i].vBDes.transpose();
  else if(dataName=="dvBDes")
    stream << data.rlsDynamics[id].vec[i].dvBDes.transpose();

  else if(dataName=="xiBDes")
    stream << data.rlsDynamics[id].vec[i].xiBDes.transpose();
  else if(dataName=="wBDes")
    stream << data.rlsDynamics[id].vec[i].wBDes.transpose();
  else if(dataName=="dwBDes")
    stream << data.rlsDynamics[id].vec[i].dwBDes.transpose();

  else if(dataName=="rCDes")
    stream << data.rlsDynamics[id].vec[i].rCDes.transpose();
  else if(dataName=="vCDes")
    stream << data.rlsDynamics[id].vec[i].vCDes.transpose();
  else if(dataName=="dvCDes")
    stream << data.rlsDynamics[id].vec[i].dvCDes.transpose();
  else if(dataName=="dvCRef")
    stream << data.rlsDynamics[id].vec[i].dvCfb.transpose();

  else if(dataName=="rXDes")
    stream << data.rlsDynamics[id].vec[i].rXDes.transpose();
  else if(dataName=="drXDes")
    stream << data.rlsDynamics[id].vec[i].drXDes.transpose();

  else if(dataName=="rXDesx")
    stream << data.rlsDynamics[id].vec[i].rXDes(0);
  else if(dataName=="rXDesy")
    stream << data.rlsDynamics[id].vec[i].rXDes(1);
  else if(dataName=="rexDes")
    stream << data.rlsDynamics[id].vec[i].rXDes.head(2).transpose();
  else if(dataName=="drexDes")
    stream << data.rlsDynamics[id].vec[i].drXDes.head(2).transpose();

  // desired VRP
  else if(dataName=="rvrpDes")
    stream << data.rlsDynamics[id].vec[i].rvrpDes.transpose();

  else if(dataName=="rvrpDesx")
    stream << data.rlsDynamics[id].vec[i].rvrpDes(0);
  else if(dataName=="rvrpDesy")
    stream << data.rlsDynamics[id].vec[i].rvrpDes(1);
  else if(dataName=="recmpDes")
    stream << data.rlsDynamics[id].vec[i].rvrpDes.head(2).transpose();

  // desired N-DVRP
  else if(dataName=="rndvrpDes")
    stream << data.rlsDynamics[id].vec[i].rndvrpDes.transpose();

  else if(dataName=="rndvrpDesx")
    stream << data.rlsDynamics[id].vec[i].rndvrpDes(0);
  else if(dataName=="rndvrpDesy")
    stream << data.rlsDynamics[id].vec[i].rndvrpDes(1);
  else if(dataName=="rndecmpDes")
    stream << data.rlsDynamics[id].vec[i].rndvrpDes.head(2).transpose();

  else if(dataName=="rDes")
    stream << data.rlsDynamics[id].vec[i].rDes.transpose();
  else if(dataName=="vDes")
    stream << data.rlsDynamics[id].vec[i].vDes.transpose();
  else if(dataName=="dvDes")
    stream << data.rlsDynamics[id].vec[i].dvDes.transpose();

  else if(dataName=="xiDes")
    stream << data.rlsDynamics[id].vec[i].xiDes.transpose();
  else if(dataName=="wDes")
    stream << data.rlsDynamics[id].vec[i].wDes.transpose();
  else if(dataName=="dwDes")
    stream << data.rlsDynamics[id].vec[i].dwDes.transpose();

  // error
  else if(dataName=="erB")
    stream << data.rlsDynamics[id].vec[i].erB.transpose();
  else if(dataName=="evB")
    stream << data.rlsDynamics[id].vec[i].evB.transpose();
  else if(dataName=="eoB")
    stream << data.rlsDynamics[id].vec[i].eoB.transpose();
  else if(dataName=="ewB")
    stream << data.rlsDynamics[id].vec[i].ewB.transpose();

  else if(dataName=="erC")
    stream << data.rlsDynamics[id].vec[i].erC.transpose();
  else if(dataName=="evC")
    stream << data.rlsDynamics[id].vec[i].evC.transpose();

  else if(dataName=="eX")
    stream << data.rlsDynamics[id].vec[i].eX.transpose();

  else if(dataName=="er")
    stream << data.rlsDynamics[id].vec[i].er.transpose();
  else if(dataName=="ev")
    stream << data.rlsDynamics[id].vec[i].ev.transpose();

  else if(dataName=="eo")
    stream << data.rlsDynamics[id].vec[i].eo.transpose();
  else if(dataName=="ew")
    stream << data.rlsDynamics[id].vec[i].ew.transpose();

  else if(dataName=="ef")
    stream << data.rlsDynamics[id].vec[i].ef.transpose();
  else if(dataName=="en")
    stream << data.rlsDynamics[id].vec[i].en.transpose();

  // reference
  // else if(dataName=="dvBRef")
  //   stream << data.rlsDynamics[id].vec[i].dvBRef.transpose();
  // else if(dataName=="dwBRef")
  //   stream << data.rlsDynamics[id].vec[i].dwBRef.transpose();
  // else if(dataName=="ddthRef")
  //   stream << data.rlsDynamics[id].vec[i].dthRef.transpose();

  // else if(dataName=="dvCRef")
  //   stream << data.rlsDynamics[id].vec[i].dvCRef.transpose();

  else if(dataName=="dvBoptRef")
    stream << data.rlsDynamics[id].vec[i].dvBoptRef.transpose();
  else if(dataName=="dwBoptRef")
    stream << data.rlsDynamics[id].vec[i].dwBoptRef.transpose();
  else if(dataName=="ddthoptRef")
    stream << data.rlsDynamics[id].vec[i].ddthoptRef.transpose();

  else if(dataName=="dvCoptRef")
    stream << data.rlsDynamics[id].vec[i].dvCoptRef.transpose();

  else if(dataName=="dpRef")
    stream << data.rlsDynamics[id].vec[i].dpRef.transpose();
  else if(dataName=="dlCRef")
    stream << data.rlsDynamics[id].vec[i].dlCRef.transpose();
  // amiyata
  else if(dataName=="dlCRBRef")
    stream << data.rlsDynamics[id].vec[i].dlCRBRef.transpose();
  else if(dataName=="dlThRef")
    stream << data.rlsDynamics[id].vec[i].dlThRef.transpose();

  else if(dataName=="dlBRef")
    stream << data.rlsDynamics[id].vec[i].dlBRef.transpose();

  else if(dataName=="fRef")
    stream << data.rlsDynamics[id].vec[i].fRef.transpose();
  else if(dataName=="nRef")
    stream << data.rlsDynamics[id].vec[i].nRef.transpose();

  // else if(dataName=="fextRef")
  //   stream << data.rlsDynamics[id].vec[i].cal_FextRef.head(3).transpose();
  // else if(dataName=="nextRef")
  //   stream << data.rlsDynamics[id].vec[i].cal_FextRef.tail(3).transpose();

  else if(dataName=="tau")
    stream << data.rlsDynamics[id].vec[i].tau.transpose();
  // amiyata limbs torque 4DoF only
  else if(dataName=="tauRLAnk")
    stream << data.rlsDynamics[id].vec[i].tau(5) << " " << // ankle only
    data.rlsDynamics[id].vec[i].tau(4);
  else if(dataName=="tauLLAnk")
    stream << data.rlsDynamics[id].vec[i].tau(11) << " " <<
    data.rlsDynamics[id].vec[i].tau(10);
  else if(dataName=="tauAnk1")
    stream << data.rlsDynamics[id].vec[i].tau(5) << " " <<
    data.rlsDynamics[id].vec[i].tau(11);
  else if(dataName=="tauAnk2")
    stream << data.rlsDynamics[id].vec[i].tau(4) << " " <<
    data.rlsDynamics[id].vec[i].tau(10);
  else if(dataName=="tauRA")
    stream << data.rlsDynamics[id].vec[i].tau.segment(12,4).transpose();
  else if(dataName=="tauLA")
    stream << data.rlsDynamics[id].vec[i].tau.segment(16,4).transpose();

  else if(dataName=="quatB")
    stream << data.rlsDynamics[id].vec[i].quatB.transpose();
  else if(dataName=="quatBDes")
    stream << data.rlsDynamics[id].vec[i].quatBDes.transpose();
  else if(dataName=="quat")
    stream << data.rlsDynamics[id].vec[i].quat.transpose();
  else if(dataName=="quatDes")
    stream << data.rlsDynamics[id].vec[i].quatDes.transpose();

  else if(dataName=="pCRB")
    stream << data.rlsDynamics[id].vec[i].pCRB.transpose();
  else if(dataName=="lCRB")
    stream << data.rlsDynamics[id].vec[i].lCRB.transpose();
  else if(dataName=="pCth")
    stream << data.rlsDynamics[id].vec[i].pCth.transpose();
  else if(dataName=="lTh")
    stream << data.rlsDynamics[id].vec[i].lTh.transpose();
  else if(dataName=="psys")
    stream << data.rlsDynamics[id].vec[i].p.transpose();
  else if(dataName=="lCsys")
    stream << data.rlsDynamics[id].vec[i].lC.transpose();
  else if(dataName=="wC")
    stream << data.rlsDynamics[id].vec[i].wC.transpose();
  else if(dataName=="wth")
    stream << data.rlsDynamics[id].vec[i].wth.transpose();
  else if(dataName=="wthF")
    stream << data.rlsDynamics[id].vec[i].wthF.transpose();
  else if(dataName=="lThH")
    stream << data.rlsDynamics[id].vec[i].lThH.transpose();
  else if(dataName=="lThF")
    stream << data.rlsDynamics[id].vec[i].lThF.transpose();

  else if(dataName=="rX")
    stream << data.rlsDynamics[id].vec[i].rX.transpose();

  else if(dataName=="rpkx")
    stream << data.rlsDynamics[id].vec[i].rpkx.transpose();
  else if(dataName=="rpky")
    stream << data.rlsDynamics[id].vec[i].rpky.transpose();

  else if(dataName=="rpx")
    stream << data.rlsDynamics[id].vec[i].rp(0);
  else if(dataName=="rpy")
    stream << data.rlsDynamics[id].vec[i].rp(1);

  else if(dataName=="rpw2k")
    stream << data.rlsDynamics[id].vec[i].rpw2k.transpose();
  else if(dataName=="rp")
    stream << data.rlsDynamics[id].vec[i].rp.transpose();

  // else if(dataName=="rcmpx")
  //   stream << data.rlsDynamics[id].vec[i].rcmp(0);
  // else if(dataName=="rcmpy")
  //   stream << data.rlsDynamics[id].vec[i].rcmp(1);

  else if(dataName=="xStabilityIndex")
    stream <<
      data.treeModel[id].vec[i].rC(0) << " " <<
      data.rlsDynamics[id].vec[i].rp(0) << " " <<
      data.rlsDynamics[id].vec[i].rX(0) << " " <<
      data.rlsDynamics[id].vec[i].rvrpRef(0) << " " <<
      data.rlsDynamics[id].vec[i].rndvrpDes(0);
  else if(dataName=="yStabilityIndex")
    stream <<
      data.treeModel[id].vec[i].rC(1) << " " <<
      data.rlsDynamics[id].vec[i].rp(1) << " " <<
      data.rlsDynamics[id].vec[i].rX(1) << " " <<
      data.rlsDynamics[id].vec[i].rvrpRef(1) << " " <<
      data.rlsDynamics[id].vec[i].rndvrpDes(1);
  else if(dataName=="xStabilityIndexNC")
    stream <<
      data.rlsDynamics[id].vec[i].rp(0) << " " <<
      data.rlsDynamics[id].vec[i].rX(0) << " " <<
      data.rlsDynamics[id].vec[i].rvrpRef(0);
  else if(dataName=="yStabilityIndexNC")
    stream <<
      data.rlsDynamics[id].vec[i].rp(1) << " " <<
      data.rlsDynamics[id].vec[i].rX(1) << " " <<
      data.rlsDynamics[id].vec[i].rvrpRef(1);

  else if(dataName=="gCoM")
    stream << data.treeModel[id].vec[i].rC.head(2).transpose();
  else if(dataName=="gCoMDes")
    stream << data.rlsDynamics[id].vec[i].rCDes.head(2).transpose();
  else if(dataName=="xCoM")
    stream << data.rlsDynamics[id].vec[i].rX.head(2).transpose();
  else if(dataName=="xCoMDes")
    stream << data.rlsDynamics[id].vec[i].rXDes.head(2).transpose();
  else if(dataName=="eCMPRef")
    stream << data.rlsDynamics[id].vec[i].rvrpRef.head(2).transpose();
  else if(dataName=="eCMPDes")
    stream << data.rlsDynamics[id].vec[i].rvrpDes.head(2).transpose();
  else if(dataName=="thArmR")
    stream << data.rlsDynamics[id].vec[i].th.segment(12, 4).transpose();
  else if(dataName=="thArmL")
    stream << data.rlsDynamics[id].vec[i].th.segment(12+4, 4).transpose();
  else if(dataName=="thArmVelR")
    stream << data.rlsDynamics[id].vec[i].dth.segment(12, 4).transpose();
  else if(dataName=="thArmVelL")
    stream << data.rlsDynamics[id].vec[i].dth.segment(12+4, 4).transpose();

  // // foot print
  // else if(dataName=="foot print")
  //   stream << data.rlsDynamics[id].vec[i].rXDes.head(2).transpose();

  // // gif
  // else if(dataName=="index print")
  //   stream <<
  //     data.rlsDynamics[id].vec[i].indexPrintMatrix.transpose().row(0) <<
  //     data.rlsDynamics[id].vec[i].indexPrintMatrix.transpose().row(1) <<
  //     data.rlsDynamics[id].vec[i].indexPrintMatrix.transpose().row(2) <<
  //     data.rlsDynamics[id].vec[i].indexPrintMatrix.transpose().row(3) <<
  //     data.rlsDynamics[id].vec[i].indexPrintMatrix.transpose().row(4);

  else{
    if(!setDat(stream, dataName, i))
      cout << manip_error("not found: '" + dataName + "'") << endl;
  }
}
