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

    // tree model output
    // ********************************************
    void joint(Config&, Info&, GpMaker&, TexMaker&);
    void baseTrans(Config&, Info&, GpMaker&, TexMaker&);
    void baseRot(Config&, Info&, GpMaker&, TexMaker&);
    void eeTrans(Config&, Info&, GpMaker&, TexMaker&);
    void eeRot(Config&, Info&, GpMaker&, TexMaker&);
    void eeWrench(Config&, Info&, GpMaker&, TexMaker&);
    void com(Config&, Info&, GpMaker&, TexMaker&);
    void mix(Config&, Info&, GpMaker&, TexMaker&);
    void spatialMom(Config&, Info&, GpMaker&, TexMaker&);
    // gif
    // ****************
    void allJointPos(Config&, Info&, GpMaker&, TexMaker&);
    // ********************************************

    // ********************************************
    // des
    void baseTransDes(Config&, Info&, GpMaker&, TexMaker&);
    void baseRotDes(Config&, Info&, GpMaker&, TexMaker&);
    void comDes(Config&, Info&, GpMaker&, TexMaker&);
    void dcmDes(Config&, Info&, GpMaker&, TexMaker&);
    void eeTransDes(Config&, Info&, GpMaker&, TexMaker&);
    void eeRotDes(Config&, Info&, GpMaker&, TexMaker&);

    // err
    void baseTransErr(Config&, Info&, GpMaker&, TexMaker&);
    void baseRotErr(Config&, Info&, GpMaker&, TexMaker&);
    void comErr(Config&, Info&, GpMaker&, TexMaker&);
    void dcmErr(Config&, Info&, GpMaker&, TexMaker&);
    void eeTransErr(Config&, Info&, GpMaker&, TexMaker&);
    void eeRotErr(Config&, Info&, GpMaker&, TexMaker&);
    void eeWrenchErr(Config&, Info&, GpMaker&, TexMaker&);

    // ref
    void mixedQuasiAccRef(Config&, Info&, GpMaker&, TexMaker&);
    void mixedQuasiAccOptRef(Config&, Info&, GpMaker&, TexMaker&);
    void rcMomRef(Config&, Info&, GpMaker&, TexMaker&);
    void eeWrenchRef(Config&, Info&, GpMaker&, TexMaker&);
    void extWrenchRef(Config&, Info&, GpMaker&, TexMaker&);
    void jointTorque(Config&, Info&, GpMaker&, TexMaker&);
    void sysMom(Config&, Info&, GpMaker&, TexMaker&);

    // cop
    void localCop(Config&, Info&, GpMaker&, TexMaker&);
    void netCop(Config&, Info&, GpMaker&, TexMaker&);
    void stabilityIndex(Config&, Info&, GpMaker&, TexMaker&);

    // dcm
    void dcm(Config&, Info&, GpMaker&, TexMaker&);

    // walking
    void localCop4walking(Config&, Info&, GpMaker&, TexMaker&);
    void netCop4walking(Config&, Info&, GpMaker&, TexMaker&);
    void cmp4walking(Config&, Info&, GpMaker&, TexMaker&);
    void stabilityIndex4walking(Config&, Info&, GpMaker&, TexMaker&);
    void vrpDes4walking(Config&, Info&, GpMaker&, TexMaker&);
    void footPrint(Config&, Info&, GpMaker&, TexMaker&);
    // ********************************************

    // gif
    void indexPrint(Config&, Info&, GpMaker&, TexMaker&);

    // velocity
    void velocityGraphConfig(Config&, Info&);

    // acceleration
    void accelerationGraphConfig(Config&, Info&);

    //torque
    void masterGraphConfig(Config&, Info&);
    void torqueGraphConfig(Config&, Info&);

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
