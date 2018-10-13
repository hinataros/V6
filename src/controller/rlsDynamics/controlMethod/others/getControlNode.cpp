/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::getControlNodeVector(const VectorXd a, const string type, const string node)
{
  if(debug) DEBUG;

  VectorXd returnVector;
  int id = info.model.controlNodeID[node];

  int num = 0, nodeNum = 0;
  if(type=="all"){
    for(int i=0; i<id; i++)
      num += 6;

    nodeNum = 6;
  }
  else if(type=="c"){
    if(!info.constraint.c.controlNode[id])
      return VectorXd::Zero(a.size());

    for(int i=0; i<id; i++)
      num += info.constraint.c.controlNode[i];

    nodeNum = info.constraint.c.controlNode[id];
  }
  else if(type=="m"){
    if(!info.constraint.m.controlNode[id])
      return VectorXd::Zero(a.size());

    for(int i=0; i<id; i++)
      num += info.constraint.m.controlNode[i];

    nodeNum = info.constraint.m.controlNode[id];
  }

  returnVector = a.segment(num, nodeNum);

  return returnVector;
}

VectorXd RLS::RlsDynamics::getControlNodeVector(const VectorXd a, const string type, const int argNum, ...)
{
  if(debug) DEBUG;

  VectorXd returnVector;
  string node[argNum];

  va_list ptr;
  va_start(ptr, argNum);

  for(int i=0; i<argNum; i++)
    node[i] = string(va_arg(ptr, char*));

  int nodeNum = 0;
  int tempNum[argNum];
  if(type=="all")
    for(int i=0; i<argNum; i++){
      tempNum[i] = 6;
      nodeNum += 6;
    }
  else if(type=="c")
    for(int i=0; i<argNum; i++){
      int id = info.model.controlNodeID[node[i]];
      tempNum[i] = info.constraint.c.controlNode[id];
      nodeNum += tempNum[i];
    }
  else if(type=="m")
    for(int i=0; i<argNum; i++){
      int id = info.model.controlNodeID[node[i]];
      tempNum[i] = info.constraint.m.controlNode[id];
      nodeNum += tempNum[i];
    }

  returnVector = VectorXd::Zero(nodeNum);

  for(int i=0, temp=0; i<argNum; temp+=tempNum[i], i++)
    if(tempNum[i])
      returnVector.segment(temp, tempNum[i]) = getControlNodeVector(a, type, node[i]);

  return returnVector;
}

MatrixXd RLS::RlsDynamics::getControlNodeMatrix(const MatrixXd A, const bool row, const bool col, const string type, const string node)
{
  if(debug) DEBUG;

  MatrixXd returnMatrix;
  int id = info.model.controlNodeID[node];

  int num = 0, nodeNum = 0;
  if(type=="all"){
    for(int i=0; i<id; i++)
      num += 6;

    nodeNum = 6;
  }
  else if(type=="c"){
    if(!info.constraint.c.controlNode[id])
      return MatrixXd::Zero(A.rows(), A.cols());

    for(int i=0; i<id; i++)
      num += info.constraint.c.controlNode[i];

    nodeNum = info.constraint.c.controlNode[id];
  }
  else if(type=="m"){
    if(!info.constraint.m.controlNode[id])
      return MatrixXd::Zero(A.rows(), A.cols());

    for(int i=0; i<id; i++)
      num += info.constraint.m.controlNode[i];

    nodeNum = info.constraint.m.controlNode[id];
  }

  if(row&&col)
    returnMatrix = A.block(num, num, nodeNum, nodeNum);
  else if(col)
    returnMatrix = A.block(0, num, A.rows(), nodeNum);
  else if(row)
    returnMatrix = A.block(num, 0, nodeNum, A.cols());
  else
    cout << manip_error("RlsDynamics::getControlNode(): error:")
         << manip_error("Please select 'true'");

  return returnMatrix;
}

MatrixXd RLS::RlsDynamics::getControlNodeMatrix(const MatrixXd A, const bool row, const bool col, const string type, const int argNum, ...)
{
  if(debug) DEBUG;

  MatrixXd returnMatrix;
  string node[argNum];

  va_list ptr;
  va_start(ptr, argNum);

  for(int i=0; i<argNum; i++)
    node[i] = string(va_arg(ptr, char*));

  va_end(ptr);

  int nodeNum = 0;
  int tempNum[argNum];
  if(type=="all")
    for(int i=0; i<argNum; i++){
      tempNum[i] = 6;
      nodeNum += 6;
    }
  else if(type=="c")
    for(int i=0; i<argNum; i++){
      int id = info.model.controlNodeID[node[i]];
      tempNum[i] = info.constraint.c.controlNode[id];
      nodeNum += tempNum[i];
    }
  else if(type=="m")
    for(int i=0; i<argNum; i++){
      int id = info.model.controlNodeID[node[i]];
      tempNum[i] = info.constraint.m.controlNode[id];
      nodeNum += tempNum[i];
    }

  if(row&&col){
    returnMatrix = MatrixXd::Zero(nodeNum, nodeNum);

    for(int i=0, temp=0; i<argNum; temp+=tempNum[i], i++)
      if(tempNum[i])
        returnMatrix.block(temp, temp, tempNum[i], tempNum[i]) = getControlNodeMatrix(A, row, col, type, node[i]);
  }
  else if(col){
    returnMatrix = MatrixXd::Zero(A.rows(), nodeNum);

    for(int i=0, temp=0; i<argNum; temp+=tempNum[i], i++)
      if(tempNum[i])
        returnMatrix.block(0, temp, A.rows(), tempNum[i]) = getControlNodeMatrix(A, row, col, type, node[i]);
  }
  else if(row){
    returnMatrix = MatrixXd::Zero(nodeNum, A.cols());

    for(int i=0, temp=0; i<argNum; temp+=tempNum[i], i++)
      if(tempNum[i])
        returnMatrix.block(temp, 0, tempNum[i], A.cols()) = getControlNodeMatrix(A, row, col, type, node[i]);
  }
  else{
    cout << manip_error("RlsDynamics::getControlNode(): error:")
         << manip_error("Please select 'true'");
  }

  return returnMatrix;
}
