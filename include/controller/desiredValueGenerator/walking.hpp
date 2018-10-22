/**
   @author Sho Miyahara 2018
*/

#include "yamlInfo.hpp"

#include "interpolation.hpp"

#include "controllerTreeModel.hpp"

namespace RLS{
  class Walking:
    public Interpolation{
  private:
    const ControllerTreeModel *model;

    YamlInfo *yamlInfo;

    double g;

    double wX;

    Vector3d rX0;
    Vector3d rCw0;

    Vector3d des;

    double tw0;
    double twf;
    Vector3d rXpreDes;
    Vector3d rXf;

    int phaseDS;
    bool flagDS;

    struct HT_config{
      int stepNum;
      double dtstep;
      double dtDSstep;
      double alphaDSstep;
      double alphaHTstep;
      double offset;
      double toe;
      double heel;
    } ht_config;

    int stepNum;
    int stepPhase;
    double tstep0;
    double tstep;
    double tDS0;

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

    // polynomial
    bool initial_walking;
    int support;
    double tphasef;

    void resize();
    void readController();
    void reset();

  public:
    Vector3d rXDes;
    Vector3d drXDes;

    void setModel(const ControllerTreeModel&);
    void setYamlInfo(YamlInfo&);

    void setComPosition(const Vector3d&);
    void setInitialDcmPosition(const Vector3d&);

    void setStartTime(const double&);
    void setFinishTime(const double&);
    void setStartValue(const Vector3d&);
    void setFinishValue(const Vector3d&);

    void createHTTrajectory();

    void ht(const double&);

    void initialize();
    void finalize();

    // ~DesiredValueGenerator(){
    //   finalize();
    // }
  };
}
