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
    void makeGifDat(Config&, TreeModel::Info&);

    // tree model output
    // ********************************************
    void joint(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void baseTrans(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRot(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTrans(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRot(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrench(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void com(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void mix(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void spatialMom(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    // gif
    // ****************
    void allJointPos(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    // ********************************************

    // ********************************************
    // des
    void baseTransDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRotDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void comDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void dcmDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTransDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRotDes(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // err
    void baseTransErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRotErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void comErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void dcmErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTransErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRotErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrenchErr(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // ref
    void mixedQuasiAccRef(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void mixedQuasiAccOptRef(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void rcMomRef(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrenchRef(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void extWrenchRef(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void jointTorque(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void sysMom(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // cop
    void localCop(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void netCop(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void stabilityIndex(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // dcm
    void dcm(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // walking
    void localCop4walking(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void netCop4walking(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void cmp4walking(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void stabilityIndex4walking(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void vrpDes4walking(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    void footPrint(Config&, TreeModel::Info&, GpMaker&, TexMaker&);
    // ********************************************

    // gif
    void indexPrint(Config&, TreeModel::Info&, GpMaker&, TexMaker&);

    // velocity
    void velocityGraphConfig(Config&, TreeModel::Info&);

    // acceleration
    void accelerationGraphConfig(Config&, TreeModel::Info&);

    //torque
    void masterGraphConfig(Config&, TreeModel::Info&);
    void torqueGraphConfig(Config&, TreeModel::Info&);

    void runGnuplot(Config&);

    void makeMotionYaml(Config&, TreeModel::Info&);
    void makeTreeModelMotionYaml(Config&, TreeModel::Info&);

    // int setPlane(string);
    // void makeGif2D(Config&, TreeModel::Info&, string, string, string);
    // void makeGif3D(Config&, TreeModel::Info&, string);
    // void makeGif(Config&, TreeModel::Info&);

  public:
    // smiyahara: 要検討
    TreeModelList tm_temp;
    RlsDynamicsList dc_temp;

    void finalize(Config&);

    void pushBack(Config&, double&);
    void output(Config&, TreeModel::Info&);
  };
}
