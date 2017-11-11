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

    void makeGpLibrary(Config&, Info&);
    void makeGpTime3D(Config&, string, string, string, string, int);
    void makeGpTimeLimb(Config&, Info&, string, string, string, string, int);

    // smiyahara: どうにかしたい
    void makeGifDat(Config&, Info&);

    // tree model output
    // ********************************************
    string baseTrans(Config&, Info&, string&);
    string baseRot(Config&, Info&, string&);
    string joint(Config&, Info&, string&);
    string eeTrans(Config&, Info&, string&);
    string eeRot(Config&, Info&, string&);
    string com(Config&, Info&, string&);
    string mom(Config&, Info&, string&);
    void makeTreeModelDat(Config&, Info&);
    // ********************************************

    void makeModelDat(Config&, Info&);

    // make dat file of controller data
    void makeVelocityDat(Config&, Info&);
    void makeAccelerationDat(Config&, Info&);

    // dynamics output
    // ********************************************
    string baseTransDes(Config&, Info&, string&);
    string baseRotDes(Config&, Info&, string&);
    string eeTransDes(Config&, Info&, string&);
    string eeRotDes(Config&, Info&, string&);
    string baseTransErr(Config&, Info&, string&);
    string baseRotErr(Config&, Info&, string&);
    string comErr(Config&, Info&, string&);
    string rcMomRef(Config&, Info&, string&);
    string eeWrenchRef(Config&, Info&, string&);
    string formulatedMom(Config&, Info&, string&);
    void makeDynamicsDat(Config&, Info&);
    // ********************************************

    void makeRlsDynamicsDat(Config&, Info&);

    void makeControllerDat(Config&, Info&);

    void makeGraph(Config&);

    string makeMinipage(Config&, string, string, string);
    string makeMinipageLimb(Config&, Info&, string, string, string);
    void makeFigureTex(Config&, string, string, string);
    void makeInterface(Config&);

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
