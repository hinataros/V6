/**
   @author Sho Miyahara 2018
*/

#include <unistd.h>

#include "config.hpp"

void RLS::Config::setLink()
{
  if(debug) DEBUG;

  dir.link = "/usr/local/etc/rls/user/"+to_string(getuid())+"/rlsSimulator/sl/";
}
