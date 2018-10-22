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
    if(doc_layout[i]["use function"])
      (this->*map_use_function[doc_layout[i]["use function"].as<string>()])(gpMaker, texMaker);
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

        if(doc_elements["dat value"]["name"]){
          setDat(doc_elements["dat value"]["name"].as<string>());
        }
        else{
          // ******************************** vertical ********************************
          if(doc_elements["dat value"]["vertical"]){
            YAML::Node doc_vertical = doc_elements["dat value"]["vertical"];

            if(doc_vertical["name"]){
              setVerticalDat(doc_vertical["name"].as<string>());
            }
            else{
              if(doc_vertical[0]){
                setVerticalDatNum(doc_vertical.size());

                for(unsigned k=0; k<doc_vertical.size(); k++){
                  if(doc_vertical[k]["name"])
                    setVerticalDatName(k, doc_vertical[k]["name"].as<string>());
                }
              }
            }
          }
          // ******************************** vertical ********************************

          // ******************************** horizontal ********************************
          if(doc_elements["dat value"]["horizontal"]){
            YAML::Node doc_horizontal = doc_elements["dat value"]["horizontal"];

            if(doc_horizontal["name"]){
              setHorizontalDat(doc_horizontal["name"].as<string>());
            }
            else{
              if(doc_horizontal[0]){
                setHorizontalDatNum(doc_horizontal.size());

                for(unsigned k=0; k<doc_horizontal.size(); k++){
                  if(doc_horizontal[k]["name"])
                    setHorizontalDatName(k, doc_horizontal[k]["name"].as<string>());
                }
              }
            }
          }
          // ******************************** horizontal ********************************
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
