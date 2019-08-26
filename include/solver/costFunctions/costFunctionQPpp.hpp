#define CFSQP_DEBUG 0

namespace RLS{
  class costFunctionQPpp:
  virtual public Common{
  private:
    static MatrixXd Go, CEo, CIo;
    static VectorXd go, ceo, cio;

  public:
    VectorXd preX;

    costFunctionQPpp(MatrixXd, VectorXd, MatrixXd, VectorXd, MatrixXd, VectorXd);
    costFunctionQPpp();
    ~costFunctionQPpp();

    void configuration(MatrixXd, VectorXd, MatrixXd, VectorXd, MatrixXd, VectorXd);
    void initialSearcher(double*);

    static void objection(int, int, double*, double*, void*);
    static void gradientObjection(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
    static void constraint(int, int, double*, double*, void*);
    static void gradientConstraint(int, int, double*, double*, void (*dummy)(int, int, double*, double*, void*), void*);
  };
}
