/**
   @author Sho Miyahara 2018
*/

#include "yamlInfo.hpp"

#include "interpolation.hpp"
#include "walkingFunction.hpp"

#include "controllerTreeModel.hpp"

namespace RLS{
  class Walking:
    public Interpolation,
    public WalkingFunction{
  private:
    const ControllerTreeModel *model;

    YamlInfo *yamlInfo;

    double g;

    double wX;
    double wX_; // amiyata osc

    Vector3d rX0;
    Vector3d rCw0;

    VectorXd rxw0; // amiyata for EE

    Vector3d des;

    double tw0;
    double twf;
    double tInitial; // amiyata
    Vector3d rXpreDes;
    Vector3d rXf;
    Vector3d rXfabs;

    int phaseDS;
    bool flagDS;

    struct HT_config{
      int convergenceNum;
      double dtstep;
      double dtDSstep;
      double alphaDSstep;
      double alphaHTstep;
      double offset;
      double toe;
      double heel;
      double tstab;
      double zOsc; // amiyata CoM up-down oscillation
      int ipDim; // amiyata for VRP interpolative dimension
    } ht_config;

    int convergencePhaseNum;
    int vwpNum;

    int stepPhase;
    double tstep0;
    double tstep;
    double tDS0;

    // Vector3d *vwp; // amiyata
    vector<Vector6d> vwp;

    VectorXd dT;
    MatrixXd rf;
    MatrixXd rvrpd;

    MatrixXd rXeos;

    // double sopport
    VectorXd dtDS;
    VectorXd alphaDS;
    VectorXd dtDSini;
    VectorXd dtDSend;

    MatrixXd rXiniDS;
    MatrixXd rXeoDS;
    MatrixXd drXiniDS;
    MatrixXd drXeoDS;
    MatrixXd ddrXiniDS;
    MatrixXd ddrXeoDS;

    // HT
    VectorXd alphaHT;
    VectorXd dtHT;
    VectorXd dtTH;

    MatrixXd rfT;
    MatrixXd rfH;

    MatrixXd rXHT;
    MatrixXd rXTH;

    MatrixXd rvrpTd;
    MatrixXd rvrpHd;

    // ext HT
    Vector3d rext;

    MatrixXd rndvrpTd;
    MatrixXd rndvrpHd;

    // amiyata VRP interpolation walking ***
    VectorXd dtD;
    VectorXd dtS;

    MatrixXd rXDS;
    MatrixXd rXSS;

    MatrixXd rCDS;
    MatrixXd rCSS;

    MatrixXd Cp, Cm;
    double convT; // 重心の収束目安時間
    // *************************************

    // polynomial
    bool initial_walking;
    int support;
    double tphasef;

    // void resize(); // amiya
    void readController();
    void resetMat(); // amiyata

  public:
    Vector3d rXDes;
    Vector3d drXDes;
    Vector3d rXBarDes;
    Vector3d drXBarDes;

    // amiyata for htVRP
    Vector3d rCDes;
    Vector3d drCDes;
    Vector3d ddrCDes;

    bool oscF;

    void setModel(const ControllerTreeModel&);
    void setYamlInfo(YamlInfo&);

    void setInitialDcmPosition(const Vector3d&);
    void setComPosition(const Vector3d&);
    void setEEPosition(const int, Vector3d*, Matrix3d*);
    void setNaturalFrequency(const double&);

    void setStartTime(const double&);
    void setFinishTime(const double&);
    void setInitialTime(const double&); // amiyata
    void setStartValue(const Vector3d&);
    void setFinishValue(const Vector3d&);

    void setExt(const Vector3d&);

    void setWayPoint(); // amiyata 足位置とVRP軌道計算を別関数化
    void createHTTrajectory();

    // amiyata
    void createVRPTrajectory();

    void ht(const double&);
    void htVRP(const double&); // amiyata
    void eht(const double&);
    void htOscillate(const double&); // amiyata

    void resize(); // amiyata
    void initialize();
    void finalize();

    // ~DesiredValueGenerator(){
    //   finalize();
    // }
  };
}
