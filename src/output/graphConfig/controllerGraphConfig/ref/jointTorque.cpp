/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::jointTorque(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  texMaker.reset();
  texMaker.setLimb(info.value.joint);

  reset();
  setFileName("jointTorque");
  makeDat("t-tau");

  gpMaker.reset();
  gpMaker.setName(file_name);
  gpMaker.setLimb(info.value.joint);
  for(int i=1; i<info.value.joint+1; i++)
    gpMaker.setDimention(i, info.limb[i].dof);
  gpMaker.setYLabel("j. torque [Nm]");
  gpMaker.makeGp();

  texMaker.setName(file_name);
  texMaker.addMinipage();

  texMaker.setTexName("jointTorque");
  texMaker.setCaption("Joint torque.");
  texMaker.makeTex();
}
