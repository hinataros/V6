/**
   @author Sho Miyahara 2018
*/

#include "treeModelList.hpp"
#include "rlsDynamicsList.hpp"
#include "common.hpp"

#include "gpMaker.hpp"
#include "texMaker.hpp"

namespace RLS{
  class Output:
    virtual public Common{
  private:
    FILE *gp;

    struct Data{
      vector<double> t;
      vector<TreeModelList> tm;
      vector<RlsDynamicsList> dc;
    } data;

    string lzero3format(int i){
      ostringstream ss;
      ss << setw(3) << setfill('0') << i;
      string s(ss.str());
      return s;
    }

    // smiyahara: vectorのdataオブジェクトをどうにかすれば別のクラスにできる
    // dat maker
    int nameNum;
    string file_name;
    string datName;
    string path_dat;
    int dataNum;
    int st;

    // dat maker
    void reset();
    void setFileName(string);
    void setDatPath(string);
    void setDataNum(int);
    void setST(int);
    void makeDat(string);
    void setDat(ofstream&, string, int);

    // smiyahara: どうにかしたい
    void makeGifDat(Config&, Info&);

    // // tree model output
    // // ********************************************
    void joint(Config&, Info&, GpMaker&, TexMaker&);
    void baseTrans(Config&, Info&, GpMaker&, TexMaker&);
    void baseRot(Config&, Info&, GpMaker&, TexMaker&);
    void eeTrans(Config&, Info&, GpMaker&, TexMaker&);
    void eeRot(Config&, Info&, GpMaker&, TexMaker&);
    void eeWrench(Config&, Info&, GpMaker&, TexMaker&);
    void com(Config&, Info&, GpMaker&, TexMaker&);
    void mix(Config&, Info&, GpMaker&, TexMaker&);
    void spatialMom(Config&, Info&, GpMaker&, TexMaker&);
    // // ********************************************

    void treeModelGraphConfig(Config&, Info&);

    // // ********************************************
    // desired base translation
    void baseTransDes(Config&, Info&, GpMaker&, TexMaker&);
    // desired base rotation
    void baseRotDes(Config&, Info&, GpMaker&, TexMaker&);
    // desired DCM
    void dcmDes(Config&, Info&, GpMaker&, TexMaker&);
    // desired EE translation
    void eeTransDes(Config&, Info&, GpMaker&, TexMaker&);
    // desired EE rotation
    void eeRotDes(Config&, Info&, GpMaker&, TexMaker&);
    // base translation error
    void baseTransErr(Config&, Info&, GpMaker&, TexMaker&);
    // base rotation error
    void baseRotErr(Config&, Info&, GpMaker&, TexMaker&);
    // com error
    void comErr(Config&, Info&, GpMaker&, TexMaker&);
    // dcm error
    void dcmErr(Config&, Info&, GpMaker&, TexMaker&);
    // EE translation error
    void eeTransErr(Config&, Info&, GpMaker&, TexMaker&);
    // EE rotation error
    void eeRotErr(Config&, Info&, GpMaker&, TexMaker&);
    // EE wrench error
    void eeWrenchErr(Config&, Info&, GpMaker&, TexMaker&);
    // rate of chage of spatial momentum reference
    void rcMomRef(Config&, Info&, GpMaker&, TexMaker&);
    // EE wrench reference
    void eeWrenchRef(Config&, Info&, GpMaker&, TexMaker&);
    // external wrench reference
    void extWrenchRef(Config&, Info&, GpMaker&, TexMaker&);
    // joint torque
    void jointTorque(Config&, Info&, GpMaker&, TexMaker&);
    // // formulated spatial momentum
    // void formulatedMom(Config&, Info&, GpMaker&, TexMaker&);
    // cop
    void localCop(Config&, Info&, GpMaker&, TexMaker&);
    void netCop(Config&, Info&, GpMaker&, TexMaker&);
    void stabilityIndex(Config&, Info&, GpMaker&, TexMaker&);

    // walking
    void localCop4walking(Config&, Info&, GpMaker&, TexMaker&);
    void netCop4walking(Config&, Info&, GpMaker&, TexMaker&);
    void stabilityIndex4walking(Config&, Info&, GpMaker&, TexMaker&);
    void footPrint(Config&, Info&, GpMaker&, TexMaker&);

    // ********************************************

    void velocityGraphConfig(Config&, Info&);
    void accelerationGraphConfig(Config&, Info&);
    void dynamicsGraphConfig(Config&, Info&);

    void runGnuplot(Config&);

    void makeMotionYaml(Config&, Info&);
    void makeTreeModelMotionYaml(Config&, Info&);

    // int setPlane(string);
    // void makeGif2D(Config&, Info&, string, string, string);
    // void makeGif3D(Config&, Info&, string);
    // void makeGif(Config&, Info&);

  public:
    // smiyahara: 要検討
    TreeModelList tm_temp;
    RlsDynamicsList dc_temp;

    void finalize(Config&);

    void pushBack(Config&, double&);
    void output(Config&, Info&);
  };
}
