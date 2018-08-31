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

    // // smiyahara: どうにかしたい
    // void makeGifDat(Config&, TreeModel::Info&);

    // tree model output
    // ********************************************
    void joint(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void baseTrans(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRot(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTrans(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRot(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrench(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void com(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void mix(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void spatialMom(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    // gif
    // ****************
    void allJointPos(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    // ********************************************

    // ********************************************
    // des
    void baseTransDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRotDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void comDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void dcmDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTransDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRotDes(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // err
    void baseTransErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void baseRotErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void comErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void dcmErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeTransErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeRotErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrenchErr(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // ref
    void mixedQuasiAccRef(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void mixedQuasiAccOptRef(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void rcMomRef(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void eeWrenchRef(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void extWrenchRef(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void jointTorque(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void sysMom(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // cop
    void localCop(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void netCop(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void stabilityIndex(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // dcm
    void dcm(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // walking
    void localCop4walking(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void netCop4walking(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void cmp4walking(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void stabilityIndex4walking(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void vrpDes4walking(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    void footPrint(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);
    // ********************************************

    // gif
    void indexPrint(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    // velocity
    void velocityGraphConfig(const Config&, const TreeModel::Info&);

    // acceleration
    void accelerationGraphConfig(const Config&, const TreeModel::Info&);

    //torque
    void masterGraphConfig(const Config&, const TreeModel::Info&);
    void torqueGraphConfig(const Config&, const TreeModel::Info&);

    void runGnuplot(const Config&);

    void makeMotionYaml(const Config&, const TreeModel::Info&);
    void makeTreeModelMotionYaml(const Config&, const TreeModel::Info&);

    // int setPlane(string);
    // void makeGif2D(const Config&, const TreeModel::Info&, string, string, string);
    // void makeGif3D(const Config&, const TreeModel::Info&, string);
    // void makeGif(const Config&, const TreeModel::Info&);

  public:
    // smiyahara: 要検討
    TreeModelList tm_temp;
    RlsDynamicsList dc_temp;

    void finalize();

    void pushBack(const double&);
    void output(const Config&, const TreeModel::Info&);
  };
}
