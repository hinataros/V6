/**
   @author Sho Miyahara 2018
*/

#include "yaml-cpp/yaml.h"

#include "treeModelList.hpp"
#include "rlsDynamicsList.hpp"
#include "_extList.hpp"
#include "common.hpp"

#include "gpMaker.hpp"
#include "texMaker.hpp"

namespace RLS{
  class Output:
    virtual public Common{
  private:
    int controllerNum;
    Info *info;

    const WorldModel *worldModel;

    struct Result{
      string cmp;
      string ind;
    } result;

    struct Gp{
      bool flag;
      bool check;
      int st;
      double tstart;
    } gp;

    struct Tex{
      bool flag;
      string title;
    } tex;

    struct Plane{
      bool flag;
      string xMin;
      string xMax;
      string yMin;
      string yMax;
      string zMin;
      string zMax;
    };

    struct Gif{
      bool flag;
      int st;
      string linkColor;
      string jointColor;
      bool terminal;
      bool dir;
      Plane yz;
      Plane xz;
      Plane xy;
      Plane all;
    } gif;

    struct Choreonoid{
      bool flag;
      int st;
    } cho;

    struct Dir{
      string interface;
      string result;
      string motion;
      string cmp;
      Result dat;
      Result eps;
      Result gp;
      Result pdf;
      Result gif;
    } dir;

    struct TreeModelData{
      vector<TreeModelList> vec;
    };
    struct RlsDynamicsData{
      vector<RlsDynamicsList> vec;
    };

    struct Data{
      vector<double> time;
      TreeModelData *treeModel;
      RlsDynamicsData *rlsDynamics;
      vector<ExtList> ext;
    } data;

    string lzero3format(int i){
      ostringstream ss;
      ss << setw(3) << setfill('0') << i;
      string s(ss.str());
      return s;
    }

    void setDefaultValue();
    void readOutput(const string&);
    void setDir(const string&);
    void setModel(const WorldModel&, Info&, const int&);
    void initializeData();
    void setMap();

    // smiyahara: vectorのdataオブジェクトをどうにかすれば別のクラスにできる
    // dat maker
    YAML::Node doc_layout;

    int nameNum;
    string file_name;
    string datName;
    string path_dat;
    int dataNum;
    int st;

    bool planeFlag;

    int planeNum;
    int verticalNum;
    int horizontalNum;

    struct Dat{
      vector<int> id;
      vector<string> dataName;
    } plane, vertical, horizontal;

    // dat maker
    void reset();
    void setFileName(string);
    void setDatPath(string);
    void setDataNum(int);
    void setST(int);

    // plane dat
    void setDatNum(int);
    void setDatID(int, int);
    void setDatName(int, string);
    void setDat(string);
    // vertical dat
    void setVerticalDatNum(int);
    void setVerticalDatID(int, int);
    void setVerticalDatName(int, string);
    void setVerticalDat(string);
    // horizontal dat
    void setHorizontalDatNum(int);
    void setHorizontalDatID(int, int);
    void setHorizontalDatName(int, string);
    void setHorizontalDat(string);

    void makeDat();
    int setDat(ofstream&, string, int);
    void setDat(ofstream&, int, string, int);

    // // // smiyahara: どうにかしたい
    // // void makeGifDat(Config&, TreeModel::Info&);

    // tree model output
    // ********************************************
    void joint(GpMaker&, TexMaker&);
    void baseTrans(GpMaker&, TexMaker&);
    void baseRot(GpMaker&, TexMaker&);
    void eeTrans(GpMaker&, TexMaker&);
    void eeRot(GpMaker&, TexMaker&);
    void eeWrench(GpMaker&, TexMaker&);
    void com(GpMaker&, TexMaker&);
    void mix(GpMaker&, TexMaker&);
    void mom(GpMaker&, TexMaker&);
    // // gif
    // // ****************
    // void allJointPos(GpMaker&, TexMaker&);
    // // ********************************************

    // ********************************************
    // des
    void baseTransDes(GpMaker&, TexMaker&);
    void baseRotDes(GpMaker&, TexMaker&);
    void comDes(GpMaker&, TexMaker&);
    void dcmDes(GpMaker&, TexMaker&);
    void eeTransDes(GpMaker&, TexMaker&);
    void eeRotDes(GpMaker&, TexMaker&);

    // err
    void baseTransErr(GpMaker&, TexMaker&);
    void baseRotErr(GpMaker&, TexMaker&);
    void comErr(GpMaker&, TexMaker&);
    void dcmErr(GpMaker&, TexMaker&);
    void eeTransErr(GpMaker&, TexMaker&);
    void eeRotErr(GpMaker&, TexMaker&);
    void eeWrenchErr(GpMaker&, TexMaker&);

    // ref
    void mixedQuasiAccRef(GpMaker&, TexMaker&);
    void mixedQuasiAccOptRef(GpMaker&, TexMaker&);
    void rcMomRef(GpMaker&, TexMaker&);
    void eeWrenchRef(GpMaker&, TexMaker&);
    void extWrenchRef(GpMaker&, TexMaker&);
    void jointTorque(GpMaker&, TexMaker&);

    // index
    void dcm(GpMaker&, TexMaker&);
    void sysMom(GpMaker&, TexMaker&);
    void localCop(GpMaker&, TexMaker&);
    void netCop(GpMaker&, TexMaker&);
    void stabilityIndex(GpMaker&, TexMaker&);

    // // walking
    // void localCop4walking(GpMaker&, TexMaker&);
    // void netCop4walking(GpMaker&, TexMaker&);
    // void cmp4walking(GpMaker&, TexMaker&);
    void stabilityIndex4walking(GpMaker&, TexMaker&);
    void vrpDes4walking(GpMaker&, TexMaker&);
    void vrpBarDes4walking(GpMaker&, TexMaker&);
    // void footPrint(GpMaker&, TexMaker&);
    // // ********************************************

    map<string, void (RLS::Output::*)(GpMaker&, TexMaker&)>
    map_use_function;

    // // gif
    // void indexPrint(const Config&, const TreeModel::Info&, GpMaker&, TexMaker&);

    void makeGraph();

    void runGnuplot();

    void makeMotionYaml();
    void makeTreeModelMotionYaml(const int);

    // // int setPlane(string);
    // // void makeGif2D(const Config&, const TreeModel::Info&, string, string, string);
    // // void makeGif3D(const Config&, const TreeModel::Info&, string);
    // // void makeGif(const Config&, const TreeModel::Info&);

  public:
    // // smiyahara: 要検討
    TreeModelList *treeModelList_temp;
    RlsDynamicsList *rlsDynamicsList_temp;
    ExtList extList_temp;

    void initialize(const string&, const string&, Info&, const int&, const WorldModel &worldModel);

    void finalize();

    void pushBack(const double&);
    void output();

    Output(){};
    Output(const string &dir_link, const string &path_yaml_output, Info &info, const int &controllerNum, const WorldModel &worldModel){
      initialize(dir_link, path_yaml_output, info, controllerNum, worldModel);
    }

#ifndef RLSDYNAMICSRTC
    ~Output(){
      finalize();
    }
#endif
  };
}
