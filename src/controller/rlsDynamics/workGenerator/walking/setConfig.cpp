void RLS::Walking::setConfig()
{
  tstab = 2.;

  // dtstep = 1.;
  // dtDSstep = .5;
  // alphDSstep = .5;

  dtstep = .5;
  dtDSstep = .1;
  alphDSstep = .5;

  // steplength = 0.01;
  // steplength = 0.055;
  steplength = 0.08;

  offset = 0.;
  offset = 0.015;
  // offset = 0.01;
  // offset = 0.011;

  height = 0.;

  // HT
  // setting
  alphaHTstep = 0.5;

  toe = 0.025;
  heel = -0.015;
}

