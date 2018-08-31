/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::reset()
{
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

void RLS::Output::makeDat(string dataName)
{
  ofstream stream((path_dat+file_name+".dat").c_str());
  if(!stream){
    cout << path_dat+file_name+".dat" << ": " << endl << "file open error..." << endl;
  }
  else{
    cout << "makedat: " << dataName << endl;
    for(int i=0; i<dataNum; i+=st){
      stream << setprecision(9) << scientific;

      setDat(stream, dataName, i);
    }
    stream.close();
  }
}
