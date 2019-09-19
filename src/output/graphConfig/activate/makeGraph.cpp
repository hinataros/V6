/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeGraph()
{
  if(debug) DEBUG;

  // initialize
  // ************************************************
  nameNum = 1;
  setDatPath(dir.dat.ind);
  setDataNum(worldModel->n);
  setST(gp.st);

  GpMaker gpMaker;

  gpMaker.setMainGpName();
  gpMaker.setGpPath(dir.gp.ind);

  TexMaker texMaker;
  texMaker.setMainTexName(result.ind);
  texMaker.setResultPath(dir.result);
  texMaker.setEpsPath(dir.eps.ind);
  texMaker.setPdfPath(dir.pdf.ind);

  // ************************************************

  for(unsigned i=0; i<doc_layout.size(); i++){
    if(doc_layout[i]["use function"]){
      gpMaker.reset(); // amiyata add使用に伴いここで宣言

      if(doc_layout[i]["add"]){ // functionでもaddは使いたい
        if(doc_layout[i]["add"].size()){
          for(unsigned k=0; k<doc_layout[i]["add"].size(); k++){
            if(doc_layout[i]["add"][k]){
              if(doc_layout[i]["add"][k].size()){
                for(unsigned l=0; l<doc_layout[i]["add"][k].size(); l++)
                  gpMaker.add(k+1, doc_layout[i]["add"][k][l].as<string>());
              }
              else{
                gpMaker.add(doc_layout[i]["add"][k].as<string>());
              }
            }
            else{
              gpMaker.add(k+1, doc_layout[i]["add"][k].as<string>());
            }
          }
        }
        else{
          gpMaker.add(doc_layout[i]["add"].as<string>());
        }
      }

      (this->*map_use_function[doc_layout[i]["use function"].as<string>()])(gpMaker, texMaker);
    }
    else{
      texMaker.reset();

      texMaker.setTexName(doc_layout[i]["file name"].as<string>());
      texMaker.setCaption(doc_layout[i]["caption"].as<string>());

      if(doc_layout[i]["control node"])
        texMaker.setLimb(info->treeModel[doc_layout[i]["control node"].as<int>()].controlNodeNum);
      if(doc_layout[i]["activate"])
        if(doc_layout[i]["activate"].size())
          for(unsigned j=0; j<doc_layout[i]["activate"].size(); j++)
            texMaker.setLimbNum(j+1, doc_layout[i]["activate"][j].as<bool>());

      // ******************************** ********************************
      for(unsigned j=0; j<doc_layout[i]["elements"].size(); j++){
        YAML::Node doc_elements = doc_layout[i]["elements"][j];

        reset();

        setFileName(doc_elements["file name"].as<string>());

        if(doc_elements["time-dependent dat"]){
          YAML::Node doc_dat = doc_elements["time-dependent dat"];

          if(doc_dat["name"])
            setTimeDependentDat(doc_dat["name"].as<string>());
          else{
            if(doc_dat[0]){
              setTimeDependentDatNum(doc_dat.size());
              for(unsigned k=0; k<doc_dat.size(); k++){
                if(doc_dat[k]["name"])
                  setTimeDependentDatName(k+1, doc_dat[k]["name"].as<string>());
              }
            }
          }
        }
        else if(doc_elements["dat"]){
          YAML::Node doc_dat = doc_elements["dat"];

          if(doc_dat["name"])
            setDat(doc_dat["name"].as<string>());
          else{
            if(doc_dat[0]){
              setDatNum(doc_dat.size());
              for(unsigned k=0; k<doc_dat.size(); k++){
                if(doc_dat[k]["name"])
                  setDatName(k+1, doc_dat[k]["name"].as<string>());
              }
            }
          }
        }

        makeDat();

        gpMaker.reset();
        gpMaker.setName(file_name);

        if(doc_elements["control node"])
          gpMaker.setLimb(info->treeModel[doc_elements["control node"].as<int>()].controlNodeNum);
        if(doc_elements["activate"])
          if(doc_elements["activate"].size())
            for(unsigned k=0; k<doc_elements["activate"].size(); k++)
              gpMaker.setLimbNum(k+1, doc_elements["activate"][k].as<bool>());

        if(doc_elements["x label"])
          gpMaker.setXLabel(doc_elements["x label"].as<string>());
        if(doc_elements["y label"])
          gpMaker.setYLabel(doc_elements["y label"].as<string>());

        if(doc_elements["unit"])
          gpMaker.setUnit(doc_elements["unit"].as<string>());

        if(doc_elements["dimention"])
          gpMaker.setDimention(doc_elements["dimention"].as<int>());

        if(doc_elements["scale"]){
          if(doc_elements["scale"].size()){
            for(unsigned k=0; k<doc_elements["scale"].size(); k++)
              gpMaker.setScale(k+1, doc_elements["scale"][k].as<int>());
          }
          else{
            gpMaker.setScale(doc_elements["scale"].as<int>());
          }
        }

        if(doc_elements["redef"]){
          if(doc_elements["redef"].size()){
            for(unsigned k=0; k<doc_elements["redef"].size(); k++){
              gpMaker.redef(doc_elements["redef"][k].as<string>());
            }
          }
          else{
            gpMaker.redef(doc_elements["redef"].as<string>());
          }
        }

        if(doc_elements["add"]){
          if(doc_elements["add"].size()){
            for(unsigned k=0; k<doc_elements["add"].size(); k++){
              if(doc_elements["add"][k]){
                if(doc_elements["add"][k].size()){
                  for(unsigned l=0; l<doc_elements["add"][k].size(); l++)
                    gpMaker.add(k+1, doc_elements["add"][k][l].as<string>());
                }
                else{
                  gpMaker.add(doc_elements["add"][k].as<string>());
                }
              }
              else{
                gpMaker.add(k+1, doc_elements["add"][k].as<string>());
              }
            }
          }
          else{
            gpMaker.add(doc_elements["add"].as<string>());
          }
        }

        gpMaker.makeGp();

        texMaker.setName(file_name);
        texMaker.addMinipage();
      }

      texMaker.makeTex();
    }
  }

  // main
  gpMaker.makeMainGp();
  texMaker.makeMainTex();
}
