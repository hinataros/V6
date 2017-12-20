#include <vector>
#include "treeModelList.hpp"
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
      vector<RlsDynamicsList> dc;
    } data;

    void makeGpLibrary(Config&, Info&);
    void makeGpTime3D(Config&, string, string, int, string, string, int);
    void makeGpTime3D(Config&, string, string, string, string, int);
    void makeGpTimeLimb(Config&, Info&, string, string, string, string, int);

    // smiyahara: どうにかしたい
    void makeGifDat(Config&, Info&);

    // tree model output
    // ********************************************
    string baseTrans(Config&, Info&, string, string&);
    string baseRot(Config&, Info&, string, string&);
    string joint(Config&, Info&, string, string&);
    string eeTrans(Config&, Info&, string, string&);
    string eeRot(Config&, Info&, string, string&);
    string eeWrench(Config&, Info&, string, string&);
    string com(Config&, Info&, string, string&);
    string mom(Config&, Info&, string, string&);
    void makeTreeModelDat(Config&, Info&);
    // ********************************************

    void makeModelDat(Config&, Info&);

    // dynamics output
    // ********************************************
    // desired base translation
    string basePosDes(Config&, Info&, string, string&);
    string baseVelDes(Config&, Info&, string, string&);
    string baseAccDes(Config&, Info&, string, string&);
    // desired base rotation
    string baseOrientDes(Config&, Info&, string, string&);
    string baseAngVelDes(Config&, Info&, string, string&);
    string baseAngAccDes(Config&, Info&, string, string&);

    // desired EE translation
    string eePosDes(Config&, Info&, string, string&);
    string eeVelDes(Config&, Info&, string, string&);
    string eeAccDes(Config&, Info&, string, string&);
    // desired EE translation
    string eeOrientDes(Config&, Info&, string, string&);
    string eeAngVelDes(Config&, Info&, string, string&);
    string eeAngAccDes(Config&, Info&, string, string&);

    // base translation error
    string basePosErr(Config&, Info&, string, string&);
    string baseVelErr(Config&, Info&, string, string&);
    // base rotation error
    string baseOrientErr(Config&, Info&, string, string&);
    string baseAngVelErr(Config&, Info&, string, string&);

    // EE translation error
    string eePosErr(Config&, Info&, string, string&);
    string eeVelErr(Config&, Info&, string, string&);

    // EE wrench error
    string eeForceErr(Config&, Info&, string, string&);
    string eeMomentErr(Config&, Info&, string, string&);

    // com error
    string comPosErr(Config&, Info&, string, string&);
    string comVelErr(Config&, Info&, string, string&);

    // rate of chage of spatial momentum reference
    string rcMomRef(Config&, Info&, string, string&);

    // EE wrench reference
    string eeForceRef(Config&, Info&, string, string&);
    string eeMomentRef(Config&, Info&, string, string&);
    string eeWrenchRef(Config&, Info&, string, string&);

    // joint torque
    string jointTorque(Config&, Info&, string, string&);

    // formulated spatial momentum
    string formulatedMom(Config&, Info&, string, string&);

    void makeDynamicsDat(Config&, Info&);
    // ********************************************

   // make dat file of controller data
    void makeVelocityDat(Config&, Info&);
    void makeAccelerationDat(Config&, Info&);
    void makeRlsDynamicsDat(Config&, Info&);

    void makeControllerDat(Config&, Info&);

    void makeGraph(Config&);

    string makeMinipage(Config&, string, string, string);
    string makeMinipageLimb(Config&, Info&, string, string, string);
    void makeFigureTex(Config&, string, string, string);
    void makeSimInfo(Config&);

    void makeMotionYaml(Config&, Info&);
    void makeTreeModelMotionYaml(Config&, Info&);

    // int setPlane(string);
    // void makeGif2D(Config&, Info&, string, string, string);
    // void makeGif3D(Config&, Info&, string);
    // void makeGif(Config&, Info&);

    template<typename TYPE, std::size_t SIZE>
    std::size_t array_length(const TYPE (&)[SIZE]){return SIZE;}

    // string limbName[1] = {"default"};
    string limbName[4] = {
      "R. leg",
      "L. leg",
      "R. arm",
      "L. arm"
    };

  public:
    // smiyahara: 要検討
    TreeModelList tm_temp;
    RlsDynamicsList dc_temp;

    void finalize(Config&);

    void pushBack(Config&, double&);
    void output(Config&, Info&);
  };
}
