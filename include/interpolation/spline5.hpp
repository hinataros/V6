namespace RLS{
  class Spline5{
  private:
    Vector3d par;
    Vector6d a;
  public:
    Vector3d makeSpline5(double, double, double, double);
    Vector3d makeSpline5(double, double, double, double, double, double, double, double);
  };
}
