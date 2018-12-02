/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::reset()
{
  datNum = 1;
  vector<int>().swap(dat.id);
  dat.id.push_back(0);
  vector<string>().swap(dat.dataName);
  dat.dataName.push_back("default");

  file_name = "";
}

void RLS::Output::setFileName(string arg)
{
  file_name = lzero3format(nameNum)+"_" + arg;
  nameNum++;
}

void RLS::Output::setDatPath(string arg)
{
  path_dat = arg;
}

void RLS::Output::setDataNum(int arg)
{
  dataNum = arg;
}

void RLS::Output::setST(int arg)
{
  st = arg;
}

// ********************************
void RLS::Output::setDatNum(int arg)
{
  datNum = arg;

  dat.id.resize(arg, 0);
  dat.dataName.resize(arg, "default");
}
void RLS::Output::setDatID(int arg0, int arg1)
{
  dat.id[arg0-1] = arg1;
}
void RLS::Output::setDatName(int arg0, string arg1)
{
  dat.dataName[arg0-1] = arg1;
}
void RLS::Output::setDat(string arg)
{
  setDatName(1, arg);
}

// ********************************
void RLS::Output::setTimeDependentDatNum(int arg)
{
  datNum = arg + 1;

  dat.id.resize(arg+1, 0);
  dat.dataName.resize(arg+1, "default");
}
void RLS::Output::setTimeDependentDatID(int arg0, int arg1)
{
  dat.id[arg0] = arg1;
}
void RLS::Output::setTimeDependentDatName(int arg0, string arg1)
{
  dat.dataName[arg0] = arg1;
}
void RLS::Output::setTimeDependentDat(string arg)
{
  setTimeDependentDatNum(1);
  setTimeDependentDatName(0, "time");

  setTimeDependentDatName(1, arg);
}

void RLS::Output::makeDat()
{
  ofstream stream((path_dat+file_name+".dat").c_str());
  if(!stream){
    cout << manip_error(path_dat+file_name+".dat"+": ") << endl << "file open error..." << endl;
  }
  else{
    stream << setprecision(9) << scientific;

    for(int i=0; i<dataNum; i+=st){
      for(int j=0; j<datNum; j++){
        setDat(stream, dat.id[j], dat.dataName[j], i);
        stream << " ";
      }

      stream << endl;
    }

    stream.close();
  }

  vector<int>().swap(dat.id);
  vector<string>().swap(dat.dataName);
}
