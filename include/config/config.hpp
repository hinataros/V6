/**
   @author Sho Miyahara 2018
*/

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <iomanip>

#include <limits>
// setprecision(numeric_limits<double>::max_digits10)

#include "manipulator.hpp"
#include "define.hpp"

extern bool debug;

using namespace std;

using namespace Eigen;
typedef Eigen::Matrix<int, 6, 1> Vector6i;
typedef Eigen::Matrix<double, 6, 1> Vector6d;
typedef Eigen::Matrix<int, 6, 6> Matrix6i;
typedef Eigen::Matrix<double, 6, 6> Matrix6d;

namespace RLS{
  class Config{
  private:
    string _init_config;

    void initialize();
    void readArgument(int, char**);
    void setLink();
    void readInitYaml();
    void setPath();

  public:
    string option;

    struct Dir{
      string link;
      string share;
    } dir;

    struct SharedMemory{
      bool flag;
    } shm;

    // smiyahara: コマンドライン引数の処理は未実装
    struct Read{
      string model;
      string controller;
      string output;
      string rlsSimulator;
    } read;

    struct Path{
      string config;
      string model;
      string controller;
      string output;
      string rlsSimulator;
    } path_yaml;

    void readConfig();

    // smiyahara: コンストラクタをここでだけ分けるのはビミョー
    Config();
    Config(int, char *[]);
  };
}
