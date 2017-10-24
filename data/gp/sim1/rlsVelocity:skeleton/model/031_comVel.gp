reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'CoM vel. [m/s]'

set output MODEL_EPS.'031_comVel.eps'

plot MODEL_DAT.'031_comVel.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'031_comVel.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'031_comVel.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 2
if(VIEWMODE) replot

