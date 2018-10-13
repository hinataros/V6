/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::reset()
{
  planeFlag = false;
  planeNum = 1;
  vector<int>().swap(plane.id);
  plane.id.push_back(0);
  vector<string>().swap(plane.dataName);
  plane.dataName.push_back("default");

  verticalNum = 1;
  vector<int>().swap(vertical.id);
  vertical.id.push_back(0);
  vector<string>().swap(vertical.dataName);
  vertical.dataName.push_back("default");

  horizontalNum = 1;
  vector<int>().swap(horizontal.id);
  horizontal.id.push_back(0);
  vector<string>().swap(horizontal.dataName);
  horizontal.dataName.push_back("default");

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

void RLS::Output::setDatNum(int arg)
{
  planeNum = arg;

  plane.id.resize(arg, 0);
  plane.dataName.resize(arg, "default");
}
void RLS::Output::setDatID(int arg0, int arg1)
{
  plane.id[arg0-1] = arg1;
}
void RLS::Output::setDatName(int arg0, string arg1)
{
  planeFlag = true;

  plane.dataName[arg0-1] = arg1;
}
void RLS::Output::setDat(string arg)
{
  setDatName(1, arg);
}

void RLS::Output::setVerticalDatNum(int arg)
{
  verticalNum = arg;

  vertical.id.resize(arg, 0);
  vertical.dataName.resize(arg, "default");
}
void RLS::Output::setVerticalDatID(int arg0, int arg1)
{
  vertical.id[arg0-1] = arg1;
}
void RLS::Output::setVerticalDatName(int arg0, string arg1)
{
  vertical.dataName[arg0-1] = arg1;
}
void RLS::Output::setVerticalDat(string arg)
{
  setVerticalDatName(1, arg);
}

void RLS::Output::setHorizontalDatNum(int arg)
{
  horizontalNum = arg;

  horizontal.id.resize(arg, 0);
  horizontal.dataName.resize(arg, "default");
}
void RLS::Output::setHorizontalDatID(int arg0, int arg1)
{
  horizontal.id[arg0-1] = arg1;
}
void RLS::Output::setHorizontalDatName(int arg0, string arg1)
{
  horizontal.dataName[arg0-1] = arg1;
}
void RLS::Output::setHorizontalDat(string arg)
{
  setHorizontalDatName(1, arg);
}

void RLS::Output::makeDat()
{
  ofstream stream((path_dat+file_name+".dat").c_str());
  if(!stream){
    cout << manip_error(path_dat+file_name+".dat"+": ") << endl << "file open error..." << endl;
  }
  else{
    stream << setprecision(9) << scientific;

    if(planeFlag){
      for(int i=0; i<dataNum; i+=st){
        for(int j=0; j<planeNum; j++){
          setDat(stream, plane.id[j], plane.dataName[j], i);stream << " ";
        }

        stream << endl;
      }
    }
    else{
      for(int i=0; i<dataNum; i+=st){
        for(int j=0; j<verticalNum; j++){
          setDat(stream, vertical.id[j], vertical.dataName[j], i);stream << " ";
        }
        for(int j=0; j<horizontalNum; j++){
          setDat(stream, horizontal.id[j], horizontal.dataName[j], i);stream << " ";
        }

        stream << endl;
      }
    }

    stream.close();
  }

  vector<int>().swap(plane.id);
  vector<string>().swap(plane.dataName);
  vector<int>().swap(vertical.id);
  vector<string>().swap(vertical.dataName);
  vector<int>().swap(horizontal.id);
  vector<string>().swap(horizontal.dataName);
}
