/**
x   @author Sho Miyahara 2017
*/

#include <sys/stat.h>
#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeSequence(const string &work_path, const TreeModel::Info &info)
{
  if(debug) DEBUG;

  multiSequence = false;
  seqNum = 0;

  struct stat statFile;
  if(stat(work_path.c_str(), &statFile)!=0)
    cout << manip_error("RlsDynamics::initializeSequence() error...") << endl
         << manip_error("no such file '"+work_path+"'") << endl;
  else{
    YAML::Node doc = YAML::LoadFile(work_path.c_str());

    if(doc["Sequence"][0].size()){
      if(doc["Sequence"][0][0].size()){
        seqNum = doc["Sequence"].size();
        multiSequence = true;
      }
      else{
        seqNum = 1;
      }
    }
  }

  sequence = new Sequence[seqNum];

  for(int i=0; i<seqNum; i++){
    sequence[i].phase = 0;
    sequence[i].tw0 = 0.;
    sequence[i].twf = 0.;

    sequence[i].rCf = Vector3d::Zero();
    sequence[i].rBf = Vector3d::Zero();
    sequence[i].xiBf = Vector3d::Zero();
    sequence[i].rXf = Vector3d::Zero();
    sequence[i].cal_Xf = VectorXd::Zero(6*info.controlNodeNum);
    sequence[i].cal_Fextf = Vector6d::Zero();

    // previous desired value
    // ******************************
    sequence[i].rCpreDes = Vector3d::Zero();
    sequence[i].rBpreDes = Vector3d::Zero();
    sequence[i].xiBpreDes = Vector3d::Zero();
    sequence[i].rXpreDes = Vector3d::Zero();
    sequence[i].cal_XpreDes = VectorXd::Zero(6*info.controlNodeNum);
    sequence[i].cal_FextpreDes = Vector6d::Zero();

    sequence[i].cal_Xtd = VectorXd::Zero(6*info.controlNodeNum);
  }
}
