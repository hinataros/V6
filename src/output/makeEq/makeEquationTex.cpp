/**
   @author AKinori Miyata 2019
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeEquationTex()
{
  string controllerName = "controller.tex";
  string inputEqs = "";

  if(eq.controlMethod){
    inputEqs += "\\input{\\srces/sectionCM}\n";

    for(int i=0; i<(int)extractor.controllers.controlMethod.size(); i++)
      inputEqs += ("\\input{\\srces/controlMethod/"+extractor.controllers.controlMethod[i]+"}\n");
    // inputEqs += "\\input{\\srces/controlMethod/test}\n";
  }

  if(eq.desiredValueGenerator){
    inputEqs += "\\input{\\srces/sectionDVG}\n";

    inputEqs += "\\input{\\srces/desiredValueGenerator/test}\n";
  }
  if(eq.feedbackController){
    inputEqs += "\\input{\\srces/sectionFC}\n";

    inputEqs += "\\input{\\srces/feedbackController/test}\n";
  }

  ofstream eqTex((dir.eq.ind+controllerName).c_str(), ios::out);
  if(!eqTex)
    cout << dir.eq.ind+controllerName << ": " << endl << "file open error..." << endl;
  else{
    eqTex << inputEqs << endl;
    eqTex.close();
  }
}
