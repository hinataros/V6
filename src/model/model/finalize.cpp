/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"

void RLS::Model::finalize()
{
  if(debug) DEBUG;

  for(int i=0; i<info.treeModelNum; i++)
    treeModel[i].finalize();

  delete[] treeModel;
  delete[] rigidBodyModel;

  for(int i=0; i<info.treeModelNum; i++){
    delete[] info.treeModel[i].controlNode;
    delete[] info.treeModel[i].sensorNode;
  }

  delete[] info.treeModel;
  delete[] info.rigidBodyModel;
}
