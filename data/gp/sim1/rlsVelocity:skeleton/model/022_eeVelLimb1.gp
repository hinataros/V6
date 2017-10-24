reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 EE vel. [m/s]'

set output MODEL_EPS.'022_eeVelLimb1.eps'

plot MODEL_DAT.'022_eeVelLimb1.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'022_eeVelLimb1.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'022_eeVelLimb1.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 22
if(VIEWMODE) replot

