#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeTreeModelMotionYaml(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string path = config.dir.link + "share/motion/" + config.body.name + "Motion.yaml";

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
      << " frameRate: " << 1/(info.sim.dt*config.cho.st) << endl
      << " numParts: " << info.dof.joint << endl
      << " frames:" << endl << endl;

    for(int i=0; i<info.sim.n+1; i+=config.cho.st){
      motionYaml << "  - [";

      for (int j=0; j<info.dof.joint-1; j++)
	motionYaml <<
	  setprecision(6) << scientific <<
	  data.tm[i].th(j) << ", ";

      motionYaml << data.tm[i].th(info.dof.joint-1) << "]" << endl;
    }

    Quaterniond quat;
    Matrix3d R;
    double alpha;
    Vector3d k = Vector3d::Zero();

    motionYaml
      << "-" << endl
      << " type: 'MultiSE3Seq'" << endl
      << " content: 'LinkPosition'" << endl
      << " frameRate: " << 1/(info.sim.dt*config.cho.st) << endl
      << " numParts: " << "1" << endl
      << " format: " << "XYZQWQXQYQZ" << endl
      << " frames:" << endl << endl;

    for(int i=0; i<info.sim.n+1; i+=config.cho.st){
      motionYaml << "  - [ [";

      for(int j=0; j<3; j++)
	motionYaml <<
	  setprecision(6) << scientific <<
	  data.tm[i].rB(j) << ", ";

      // **** calc Quaternion ****
      R = data.tm[i].RB;
      alpha = acos((R(0,0)+R(1,1)+R(2,2)-1)/2);

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
