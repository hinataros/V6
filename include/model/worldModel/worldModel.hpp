/**
   @author Sho Miyahara 2018
*/

#ifndef WORLDMODEL_HPP_
#define WORLDMODEL_HPP_

namespace RLS{
  class WorldModel{
  private:
    void setPath();
    void readCnoid();

  public:
    string dir_share;

    struct Include{
      string type;
      string search;
      string read;
      string path;
    } include;

    double t0;
    double tf;
    double dt;
    int n;
    Vector3d ag;

    void initialize(const string&);
    void readModel(const string&);
  };
}

#endif // WORLDMODEL_HPP_
