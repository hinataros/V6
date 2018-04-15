/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeDynamicsDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string dir = config.dir.dat.ind + "controller/";

  string name;
  string load;
  string minipage;

  string input_dir = "\\input{\\result/"+config.controller.name+":"+config.body.name+"/"+config.result.name.cmp+"/"+"pdf/src/"+config.result.name.ind+"/";
  string input;

  name = "100_baseTransDes";
  minipage = baseAccDes(config, info, dir, load);

  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
		  "Desired base translation values."
		  );
    input += input_dir+name+"}\n";
  }

  name = "101_baseRotDes";
  minipage = baseAngAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired base rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "101_dcmDes";
  minipage = dcmVelDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired DCM values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "110_eeTransDes";
  minipage = eeAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector translation values."
  		  );
    input += input_dir+name+"}\n";
  }


  name = "111_eeRotDes";
  minipage = eeAngAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "120_baseTransErr";
  minipage = baseVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base translation errorvalues."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "121_baseRotErr";
  minipage = baseAngVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base rotation error values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "122_comErr";
  minipage = comVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "CoM error values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "122_dcmErr";
  minipage = dcmErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "DCM error values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "123_eeTransErr";
  minipage = eeVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector translation error values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "123_eeForceErr";
  minipage = eeForceErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector force error values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "130_rcMomRef";
  minipage = rcMomRef(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Rate of change of momentum reference values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "131_eeWrenchRef";
  minipage = eeWrenchRef(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector wrench reference values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "131_externalWrenchRef";
  minipage = extWrenchRef(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "External wrench reference values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "132_jointTorque";
  minipage = jointTorque(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Joint torque."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "140_formulatedMom";
  minipage = formulatedMom(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Formulated momentum values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "150_localCoP";
  minipage = localCop(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Local CoP values."
  		  );
    input += input_dir+name+"}\n";
  }

  // name = "150_CoP";
  // minipage = cop(config, info, dir, load);
  // if(config.graph.tex){
  //   makeFigureTex(config, name, minipage,
  // 		  "net CoP values."
  // 		  );
  //   input += input_dir+name+"}\n";
  // }

  name = "150_stabilityIndex";
  minipage = stabilityIndex(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Stability index values."
  		  );
    input += input_dir+name+"}\n";
  }

  // name = "160_footPrint";
  // minipage = footPrint(config, info, dir, load);
  // if(config.graph.tex){
  //   makeFigureTex(config, name, minipage,
  // 		  "Foot print."
  // 		  );
  //   input += input_dir+name+"}\n";
  // }

  ofstream rlsDynamicsGp((config.dir.gp.ind+"controller.gp").c_str());
  if(!rlsDynamicsGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    rlsDynamicsGp << load << endl;
    rlsDynamicsGp.close();
  }
  ofstream tex((config.dir.pdf.ind+config.result.name.ind+".tex").c_str(), ios::app);
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex << input << endl;
    tex.close();
  }
}
