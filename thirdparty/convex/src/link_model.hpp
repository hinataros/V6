#ifndef LINK_MODEL_HPP
#define LINK_MODEL_HPP

#include <string>

class LinkModel {
public:
  double length_x[4];
  double length_y[4];
public:
  LinkModel(std::string str) {
    //   y
    // 3 -- 0
    // |    | x
    // |    |
    // 2 -- 1
    //

    if (str == "Foot_R"){
      length_x[0] = 0.0315;
      length_y[0] = 0.058;

      length_x[1] = 0.0315;
      length_y[1] = -0.040;

      length_x[2] = -0.0315;
      length_y[2] = -0.040;

      length_x[3] = -0.0315;
      length_y[3] = 0.058;
    }
    if (str == "Foot_L"){
      length_x[0] = 0.0315;
      length_y[0] = 0.058;

      length_x[1] = 0.0315;
      length_y[1] = -0.040;

      length_x[2] = -0.0315;
      length_y[2] = -0.040;

      length_x[3] = -0.0315;
      length_y[3] = 0.058;
    }
    if (str == "Hand_R"){
      length_x[0] = 0.0125;
      length_y[0] = 0.0125;

      length_x[1] = 0.0125;
      length_y[1] = -0.0125;

      length_x[2] = -0.0125;
      length_y[2] = -0.0125;

      length_x[3] = -0.0125;
      length_y[3] = 0.0125;
    }
    if (str == "Hand_L"){
      length_x[0] = 0.0125;
      length_y[0] = 0.0125;

      length_x[1] = 0.0125;
      length_y[1] = -0.0125;

      length_x[2] = -0.0125;
      length_y[2] = -0.0125;

      length_x[3] = -0.0125;
      length_y[3] = 0.0125;
    }
  }
};


#endif
