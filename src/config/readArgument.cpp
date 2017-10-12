#include "config.hpp"

void RLS::Config::readArgument(int argc, char *argv[])
{
  if(flag.debug) DEBUG;

  // switch (argc) {
  // case 2:
  //   model = argv[1];
  //   break;
  // case 3:
  //   model = argv[1];
  //   option = argv[2];
  //   break;
  // }
  switch (argc) {
  case 2:
    option = argv[1];
    break;
  }

  if(option=="-d")
    flag.debug = true;
}
