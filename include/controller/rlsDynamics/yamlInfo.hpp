/**
   @author Sho Miyahara 2018
*/

#ifndef YAMLINFO_HPP_
#define YAMLINFO_HPP_

#include <map>

#include "yaml-cpp/yaml.h"

namespace RLS{
  class YamlInfo{
  private:
    map<string, YAML::Node> localKey;

  public:
    int sequenceNum;

    string key;
    int sequence;
    int state;

    struct Doc{
      YAML::Node controllerKey;
      YAML::Node defaultKey;
      YAML::Node *sequenceKey;
      YAML::Node stateKey;
    } doc;

    string controllerKeyName;
    string defaultKeyName;
    string sequenceKeyName;
    string stateKeyName;

    string angleUnit;

    void reset(const string&, const int&, const int&);
    void initialize(const string&, const int&);

    template <class T> bool checkValue(T &value, const string);
    template <class T> bool checkValue(T &value, const string, const string);
    template <class T> bool checkValue(T &value, const string, const string, const string);
    template <class T> bool checkValue(T &value, const string, const string, const string, const string);

    template <class T> bool checkUserValue(T &value, const string);
    template <class T> bool checkUserValue(T &value, const string, const string);
    template <class T> bool checkUserValue(T &value, const string, const string, const string);
  };
}

#endif // YAMLINFO_HPP_
