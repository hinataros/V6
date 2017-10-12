#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeGif(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(config.gif.terminal){
    if(config.gif.all.flag)
      makeGif3D(config, model, "terminal");
    if(config.gif.yz.flag)
      makeGif2D(config, model, "terminal", "y","z");
    if(config.gif.xz.flag)
      makeGif2D(config, model, "terminal", "x","z");
    if(config.gif.xy.flag)
      makeGif2D(config, model, "terminal", "x","y");
  }

  if(config.gif.dir){
    if(config.gif.all.flag)
      makeGif3D(config, model, "dir");
    if(config.gif.yz.flag)
      makeGif2D(config, model, "dir", "y","z");
    if(config.gif.xz.flag)
      makeGif2D(config, model, "dir", "x","z");
    if(config.gif.xy.flag)
    makeGif2D(config, model, "dir", "x","y");
  }
}
