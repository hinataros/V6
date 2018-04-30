/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::setDat(ofstream& stream, string dataName, int i)
{
  // model
  if(dataName=="t-rB")
    stream << data.t[i] << " " << data.tm[i].rB.transpose() << endl;
  else if(dataName=="t-vB")
    stream << data.t[i] << " " << data.tm[i].vB.transpose() << endl;
  else if(dataName=="t-xiB")
    stream << data.t[i] << " " << data.tm[i].xiB.transpose() << endl;
  else if(dataName=="t-wB")
    stream << data.t[i] << " " << data.tm[i].wB.transpose() << endl;

  else if(dataName=="t-th")
    stream << data.t[i] << " " << data.tm[i].th.transpose() << endl;
  else if(dataName=="t-dth")
    stream << data.t[i] << " " << data.tm[i].dth.transpose() << endl;

  else if(dataName=="t-rC")
    stream << data.t[i] << " " << data.tm[i].rC.transpose() << endl;
  else if(dataName=="t-vC")
    stream << data.t[i] << " " << data.tm[i].vC.transpose() << endl;

  else if(dataName=="t-r")
    stream << data.t[i] << " " << data.tm[i].r.transpose() << endl;
  else if(dataName=="t-v")
    stream << data.t[i] << " " << data.tm[i].v.transpose() << endl;

  else if(dataName=="t-xi")
    stream << data.t[i] << " " << data.tm[i].xi.transpose() << endl;
  else if(dataName=="t-w")
    stream << data.t[i] << " " << data.tm[i].w.transpose() << endl;

  else if(dataName=="t-f")
    stream << data.t[i] << " " << data.tm[i].f.transpose() << endl;
  else if(dataName=="t-n")
    stream << data.t[i] << " " << data.tm[i].n.transpose() << endl;

  else if(dataName=="t-p")
    stream << data.t[i] << " " << data.tm[i].p.transpose() << endl;
  else if(dataName=="t-lC")
    stream << data.t[i] << " " << data.tm[i].lC.transpose() << endl;


  // controller
  else if(dataName=="t-rBDes")
    stream << data.t[i] << " " << data.dc[i].rBDes.transpose() << endl;
  else if(dataName=="t-vBDes")
    stream << data.t[i] << " " << data.dc[i].vBDes.transpose() << endl;
  else if(dataName=="t-dvBDes")
    stream << data.t[i] << " " << data.dc[i].dvBDes.transpose() << endl;

  else if(dataName=="t-xiBDes")
    stream << data.t[i] << " " << data.dc[i].xiBDes.transpose()<< endl;
  else if(dataName=="t-wBDes")
    stream << data.t[i] << " " << data.dc[i].wBDes.transpose() << endl;
  else if(dataName=="t-dwBDes")
    stream << data.t[i] << " " << data.dc[i].dwBDes.transpose() << endl;

  else if(dataName=="t-rXDes")
    stream << data.t[i] << " " << data.dc[i].rXDes.transpose() << endl;
  else if(dataName=="t-drXDes")
    stream << data.t[i] << " " << data.dc[i].drXDes.transpose() << endl;

  else if(dataName=="t-rDes")
    stream << data.t[i] << " " << data.dc[i].rDes.transpose() << endl;
  else if(dataName=="t-vDes")
    stream << data.t[i] << " " << data.dc[i].vDes.transpose() << endl;
  else if(dataName=="t-dvDes")
    stream << data.t[i] << " " << data.dc[i].dvDes.transpose() << endl;

  else if(dataName=="t-xiDes")
    stream << data.t[i] << " " << data.dc[i].xiDes.transpose() << endl;
  else if(dataName=="t-wDes")
    stream << data.t[i] << " " << data.dc[i].wDes.transpose() << endl;
  else if(dataName=="t-dwDes")
    stream << data.t[i] << " " << data.dc[i].dwDes.transpose() << endl;

  else if(dataName=="t-erB")
    stream << data.t[i] << " " << data.dc[i].erB.transpose() << endl;
  else if(dataName=="t-evB")
    stream << data.t[i] << " " << data.dc[i].evB.transpose() << endl;
  else if(dataName=="t-eoB")
    stream << data.t[i] << " " << data.dc[i].eoB.transpose() << endl;
  else if(dataName=="t-ewB")
    stream << data.t[i] << " " << data.dc[i].ewB.transpose() << endl;
  else if(dataName=="t-erC")
    stream << data.t[i] << " " << data.dc[i].erC.transpose() << endl;
  else if(dataName=="t-evC")
    stream << data.t[i] << " " << data.dc[i].evC.transpose() << endl;
  else if(dataName=="t-eX")
    stream << data.t[i] << " " << data.dc[i].eX.transpose() << endl;

  else if(dataName=="t-er")
    stream << data.t[i] << " " << data.dc[i].er.transpose() << endl;
  else if(dataName=="t-ev")
    stream << data.t[i] << " " << data.dc[i].ev.transpose() << endl;

  else if(dataName=="t-eo")
    stream << data.t[i] << " " << data.dc[i].eo.transpose() << endl;
  else if(dataName=="t-ew")
    stream << data.t[i] << " " << data.dc[i].ew.transpose() << endl;

  else if(dataName=="t-ef")
    stream << data.t[i] << " " << data.dc[i].ef.transpose() << endl;
  else if(dataName=="t-en")
    stream << data.t[i] << " " << data.dc[i].en.transpose() << endl;

  else if(dataName=="t-dpRef")
    stream << data.t[i] << " " << data.dc[i].dpRef.transpose() << endl;
  else if(dataName=="t-dlRef")
    stream << data.t[i] << " " << data.dc[i].dlRef.transpose() << endl;

  else if(dataName=="t-fRef")
    stream << data.t[i] << " " << data.dc[i].fRef.transpose() << endl;
  else if(dataName=="t-nRef")
    stream << data.t[i] << " " << data.dc[i].nRef.transpose() << endl;

  else if(dataName=="t-fextRef")
    stream << data.t[i] << " " << data.dc[i].cal_FextRef.head(3).transpose() << endl;
  else if(dataName=="t-nextRef")
    stream << data.t[i] << " " << data.dc[i].cal_FextRef.tail(3).transpose() << endl;

  else if(dataName=="t-tau")
    stream << data.t[i] << " " << data.dc[i].tau.transpose() << endl;

  else if(dataName=="t-rpkx")
    stream << data.t[i] << " " << data.dc[i].rpkx.transpose() << endl;
  else if(dataName=="t-rpky")
    stream << data.t[i] << " " << data.dc[i].rpky.transpose() << endl;

  else if(dataName=="rpky-rpkx")
    stream << data.dc[i].rpk.transpose() << endl;

  else if(dataName=="t-rpx")
    stream << data.t[i] << " " << data.dc[i].rp(0) << endl;
  else if(dataName=="t-rpy")
    stream << data.t[i] << " " << data.dc[i].rp(1) << endl;

  else if(dataName=="t-xStabilityIndex")
    stream << data.t[i] << " " <<
      data.tm[i].rC(0) << " " << data.dc[i].rp(0) << " " << data.dc[i].rX(0) << endl;
  else if(dataName=="t-yStabilityIndex")
    stream << data.t[i] << " " <<
      data.tm[i].rC(1) << " " << data.dc[i].rp(1) << " " << data.dc[i].rX(1) << endl;

  else if(dataName=="yStabilityIndex-xStabilityIndex")
    stream <<
      data.tm[i].rC(1) << " " << data.tm[i].rC(0) << " " <<
      data.dc[i].rp(1) << " " << data.dc[i].rp(0) << " " <<
      data.dc[i].rX(1) << " " << data.dc[i].rX(0) << endl;


  else
    cout << "not found: " << "'" << dataName << "'" << endl;
}
