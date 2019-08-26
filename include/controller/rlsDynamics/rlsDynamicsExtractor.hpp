/**
   @author Sho Miyahara 2017
*/

#ifndef RLSDYNAMICS_EXTRACTOR_HPP_
#define RLSDYNAMICS_EXTRACTOR_HPP_

namespace RLS{
  class RlsDynamicsExtractor{
  public:
    bool readFlag;

    vector<Vector3d> footPrintList;

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
