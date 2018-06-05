/**
   @author Sho Miyahara 2017
*/

#include <unistd.h>

#include "config.hpp"

void RLS::Config::setLink()
{
  if(flag.debug) DEBUG;

  dir.link = "/usr/local/etc/rls/user/"+to_string(getuid())+"/rlsSimulator/sl/";
}
