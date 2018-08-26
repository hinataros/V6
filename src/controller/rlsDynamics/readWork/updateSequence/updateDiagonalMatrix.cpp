/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  // template<>
  // MatrixXd RlsDynamics::checkMatrix(YAML::Node &doc, string node, int seq, string name, MatrixXd A)
  // {
  //   if(doc[node][seq][name].size())
  //     A = readVector<VectorXd>(doc, node, seq, name, A.diagonal().size()).asDiagonal();

  //   else{
  //     try{
  //       checkNode(doc, node, seq, name);
  //     }
  //     catch(...){return A;}

  //     for(int i=0; i<A.diagonal().size(); i++)
  //       A(i,i) = readValue<double>(doc, node, seq, name);
  //   }

  //   return A;
  // }

  template<>
  MatrixXi RlsDynamics::updateDiagonalMatrix(YAML::Node &doc, string node, int num, int phase, string name, int eeNum, MatrixXi mat)
  {
    MatrixXi temp_mat = MatrixXi::Zero(mat.rows(),mat.cols());

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][num][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][num][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<int>(doc, node, num, phase, name, i, j);
        }

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<int>(doc, node, phase, name, i, j);
        }

        return temp_mat;
      }
    }

    return mat;
  }
  template<>
  Matrix2d RlsDynamics::updateDiagonalMatrix(YAML::Node &doc, string node, int num, int phase, string name, Matrix2d mat)
  {
    Matrix2d temp_mat = Matrix2d::Zero();

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix2d::Identity();
      }
      else if(doc[node][num][phase][name].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix2d::Identity();
      }
      else if(doc[node][phase][name].size()==2){
        for(int i=0; i<2; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix3d RlsDynamics::updateDiagonalMatrix(YAML::Node &doc, string node, int num, int phase, string name, Matrix3d mat)
  {
    Matrix3d temp_mat = Matrix3d::Zero();

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix3d::Identity();
      }
      else if(doc[node][num][phase][name].size()==3){
        for(int i=0; i<3; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix3d::Identity();
      }
      else if(doc[node][phase][name].size()==3){
        for(int i=0; i<3; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  Matrix6d RlsDynamics::updateDiagonalMatrix(YAML::Node &doc, string node, int num, int phase, string name, Matrix6d mat)
  {
    Matrix6d temp_mat = Matrix6d::Zero();

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*Matrix6d::Identity();
      }
      else if(doc[node][num][phase][name].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, num, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*Matrix6d::Identity();
      }
      else if(doc[node][phase][name].size()==6){
        for(int i=0; i<6; i++)
          temp_mat(i,i) = readValue<double>(doc, node, phase, name, i);

        return temp_mat;
      }
      else
        return mat;
    }

    return mat;
  }
  template<>
  MatrixXd RlsDynamics::updateDiagonalMatrix(YAML::Node &doc, string node, int num, int phase, string name, int eeNum, MatrixXd mat)
  {
    MatrixXd temp_mat = MatrixXd::Zero(mat.rows(),mat.cols());

    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return mat;

      if(doc[node][num][phase][name].size()==0){
        return readValue<double>(doc, node, num, phase, name)*MatrixXd::Identity(mat.rows(),mat.cols());
      }
      else if(doc[node][num][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][num][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][num][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<double>(doc, node, num, phase, name, i, j);
        }

        return temp_mat;
      }
      else
        return mat;
    }
    else{
      if(!checkNode(doc, node, phase, name))
        return mat;

      if(doc[node][phase][name].size()==0){
        return readValue<double>(doc, node, phase, name)*MatrixXd::Identity(mat.rows(),mat.cols());
      }
      else if(doc[node][phase][name].size()==eeNum){
        int size = 0;
        for(int i=0; i<eeNum; i++)
          size += doc[node][phase][name][i].size();
        if(mat.diagonal().size() != size)
          return mat;

        for(int i=0, k=0; i<eeNum; i++){
          size = doc[node][phase][name][i].size();
          for(int j=0; j<size; j++, k++)
            temp_mat(k,k) = readValue<double>(doc, node, phase, name, i, j);
        }

        return temp_mat;
      }
    }

    return mat;
  }

  // template<> MatrixXd RlsDynamics::checkMatrix(YAML::Node &doc, string node, int seq, string name, int limb, MatrixXd A)
  // {
  //   if(doc[node][seq][name].size())
  //     for(int i=0, temp=0, size=0; i<limb; i++){
  //       if(size = doc[node][seq][name][i].size()){
  //         A.block(temp, temp, size, size) = readVector<VectorXd>(doc, node, seq, name, i, size).asDiagonal();
  //         temp += size;

  //       }else{
  //         try{
  //           temp += doc[node][seq][name][i].as<int>();
  //         }
  //         catch(...){cout << "checkMatrix() error..." << endl;return A;}
  //       }
  //     }

  //   else{
  //     try{
  //       checkNode(doc, node, seq, name);
  //     }
  //     catch(...){return A;}

  //     for(int i=0; i<A.diagonal().size(); i++)
  //       A(i,i) = readValue<double>(doc, node, seq, name);
  //   }
  //   return A;
  // }
}
