#include <vector>
#include "treeModelList.hpp"
#include "rlsVelocityList.hpp"
#include "rlsAccelerationList.hpp"
#include "rlsDynamicsList.hpp"
#include "common.hpp"

namespace RLS{
  class Output:
    virtual public Common{
  private:
    string path;
    FILE *gp;

    struct Data{
      vector<double> t;
      vector<TreeModelList> tm;
      vector<RlsVelocityList> vc;
      vector<RlsAccelerationList> ac;
      vector<RlsDynamicsList> dc;
    } data;

    void makeGpLibrary(Config&);
    void makeGpTime3D(Config&, string, string, string, string, int);
    void makeGpTimeLimb(Config&, Info&, string, string, string, string, int);

    // smiyahara: どうにかしたい
    void makeGifDat(Config&, Info&);

    void makeModelDat(Config&, Info&);
    void makeTreeModelDat(Config&, Info&);

    void makeControllerDat(Config&, Info&);
    // make dat file of controller data
    void makeRlsVelocityDat(Config&, Info&);
    void makeRlsAccelerationDat(Config&, Info&);
    void makeRlsDynamicsDat(Config&, Info&);

    void makeGraph(Config&);

    void makeMotionYaml(Config&, Info&);
    void makeTreeModelMotionYaml(Config&, Info&);

    // int setPlane(string);
    // void makeGif2D(Config&, Info&, string, string, string);
    // void makeGif3D(Config&, Info&, string);
    // void makeGif(Config&, Info&);

  public:
    // smiyahara: 要検討
    TreeModelList tm_temp;
    RlsVelocityList vc_temp;
    RlsAccelerationList ac_temp;
    RlsDynamicsList dc_temp;

    void finalize(Config&);

    void pushBack(Config&, double&);
    void output(Config&, Info&);
  };
}
