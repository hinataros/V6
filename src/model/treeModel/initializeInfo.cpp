/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::initializeInfo()
{
  if(debug) DEBUG;

  // for(int i=0; i<info.value.node; i++){
  //   // smiyahara: 初期化の場所考えたほうがいい
  //   info.limb[i].contact = false;
  //   info.limb[i].c = info.limb[i].m = 0;

  info.dof.joint = 0;

  info.eeNum = 0;

  info.contact.num = 0;
  info.contact.c.all = info.contact.m.all = 0;

  for(int i=0; i<6; i++)
    info.contact.c.axis[i] = info.contact.m.axis[i] = 0;
}
