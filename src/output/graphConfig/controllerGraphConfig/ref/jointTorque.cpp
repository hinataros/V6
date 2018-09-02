/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::jointTorque(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  // texMaker.reset();
  // texMaker.setLimb(info.controlNodeNum);

  // reset();
  // setFileName("jointTorque");
  // makeDat("t-tau");

  // gpMaker.reset();
  // gpMaker.setName(file_name);
  // gpMaker.setLimb(info.controlNodeNum);
  // for(int i=1; i<info.controlNodeNum+1; i++)
  //   gpMaker.setDimention(i, info.limb[i].dof);
  // gpMaker.setYLabel("j. torque [Nm]");
  // gpMaker.makeGp();

  // texMaker.setName(file_name);
  // texMaker.addMinipage();

  // texMaker.setTexName("jointTorque");
  // texMaker.setCaption("Joint torque.");
  // texMaker.makeTex();
}
