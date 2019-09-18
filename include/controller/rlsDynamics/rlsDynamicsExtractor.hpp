
#ifndef RLSDYNAMICS_EXTRACTOR_HPP_
#define RLSDYNAMICS_EXTRACTOR_HPP_


namespace RLS{
  struct FootPrint{
    Vector3d pos;
    Matrix3d att;
    short ee;
  };

  class RlsDynamicsExtractor{
  public:
    bool readFlag;

    vector<struct FootPrint> footPrintList;

    vector<Vector2d> *soleConvex;

    // amiyata for eqtex
    struct Controllers{
      vector<string> controlMethod;
      vector<string> desiredValueGenerator;
      vector<string> feedbackController;
    } controllers;

    void resize();

    RlsDynamicsExtractor(){
      readFlag = false;
    }
  };
}

#endif // RLSDYNAMICSLIST_HPP_
