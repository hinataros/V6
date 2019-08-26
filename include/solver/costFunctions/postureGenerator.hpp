#define CFSQP_DEBUG 0

namespace RLS{
  class postureGenerator:
  virtual public Common{
  private:

  public:
    int nparam, ni, ne;

    int fixed; // 0=B
    MatrixXd REE[5];
    VectorXd rEE[5];

    int limbs, dofs[5]; //info
    double mk[5][8], mall;
    string jTk[5][8];
    VectorXd lk[5][8];
    MatrixXd r2Ck[5][8]; //model

    postureGenerator();
    ~postureGenerator();

    void configuration(TreeModelInfo&, TreeModel&);
    void initialSearcher(double*);

    void makeFuncCoef(double*, double*, double*);
    bool inTriangle(double*, double*, double*, double*);
    void convexFull(double*, int);

    static VectorXd calcCoM(double*);
    VectorXd calcdCoM(double*);

    static void objection(int, int, double*, double*, void*);
    static void gradientObjection(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
    static void constraint(int, int, double*, double*, void*);
    static void gradientConstraint(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
  };
}
