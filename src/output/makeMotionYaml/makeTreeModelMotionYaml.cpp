/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeTreeModelMotionYaml(const int id)
{
  if(debug) DEBUG;

  string path = dir.motion + info->treeModel[id].name + "Motion.yaml";

  ofstream motionYaml(path.c_str());
  if(!motionYaml)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    motionYaml
      << "type: BodyMotion" << endl
      << "components:" << endl
      << "-" << endl
      << " type: 'MultiValueSeq'" << endl
      << " content: 'JointPosition'" << endl
      << " frameRate: " << static_cast<int>(1/(worldModel->dt*cho.st)) << endl
      << " numParts: " << info->treeModel[id].dof.joint << endl
      << " frames:" << endl << endl;

    for(int i=0; i<worldModel->n+1; i+=cho.st){
      motionYaml << "  - [";

      for (int j=0; j<info->treeModel[id].dof.joint-1; j++)
        motionYaml <<
          setprecision(6) << scientific <<
          data.treeModel[id].vec[i].th(j) << ", ";

      motionYaml << data.treeModel[id].vec[i].th(info->treeModel[id].dof.joint-1) << "]" << endl;
    }

    Quaterniond quat;
    Matrix3d R;
    double alpha;
    Vector3d k = Vector3d::Zero();

    motionYaml
      << "-" << endl
      << " type: 'MultiSE3Seq'" << endl
      << " content: 'LinkPosition'" << endl
      << " frameRate: " << static_cast<int>(1/(worldModel->dt*cho.st)) << endl
      << " numParts: " << "1" << endl
      << " format: " << "XYZQWQXQYQZ" << endl
      << " frames:" << endl << endl;

    for(int i=0; i<worldModel->n+1; i+=cho.st){
      motionYaml << "  - [ [";

      for(int j=0; j<3; j++)
        motionYaml <<
          setprecision(6) << scientific <<
          data.treeModel[id].vec[i].rB(j) << ", ";

      // **** calc Quaternion ****
      R = data.treeModel[id].vec[i].RB;
      double ang = (R(0,0)+R(1,1)+R(2,2)-1)/2;

      if(ang>1.)
        ang = 1;

      alpha = acos(ang);

      if(alpha!=0.){
        k <<
          R(2,1)-R(1,2),
          R(0,2)-R(2,0),
          R(1,0)-R(0,1);
        k = k/(2*sin(alpha));
      }

      quat = AngleAxisd(alpha, k);
      // **** *************** ****

      motionYaml <<
        setprecision(6) << scientific <<
        quat.w() << ", " << quat.x() << ", " << quat.y() << ", " << quat.z() << "] ]" << endl;
    }

    motionYaml.close();
  }
}
