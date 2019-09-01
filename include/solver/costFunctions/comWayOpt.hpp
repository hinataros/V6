
#define CWO_DEBUG 0


namespace RLS{
  class comWayOpt{
  // virtual public Common,
  // virtual public WalkingFunction{
  private:
    static int Tnum, rCnum, ipDim;
    static double wX;
    static VectorXd comDes;
    static MatrixXd vwp,  Cp, Cm;

    static MatrixXd WT, WC, WV;


    static MatrixXd calcDwp(VectorXd);
    static MatrixXd calcCwp(VectorXd, MatrixXd);
    static MatrixXd calcdTnDwp(int, VectorXd, MatrixXd);
    static MatrixXd calcdTnCwp(int, VectorXd, MatrixXd, MatrixXd, MatrixXd);

    static WalkingFunction wf;

  public:
    // int nparam, ni, ne;

    comWayOpt(MatrixXd, MatrixXd, int, double);
    comWayOpt();
    ~comWayOpt();

    // void configuration();
    void initialSearcher(int, double*, double);
    void initialSearcher(int, double*);

    static void objection(int, int, double*, double*, void*);
    static void gradientObjection(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
    static void constraint(int, int, double*, double*, void*);
    static void gradientConstraint(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
  };
}
