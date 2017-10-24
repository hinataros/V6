reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 EE ang. vel. [rad/s]'

set output MODEL_EPS.'023_eeAngVelLimb2.eps'

plot MODEL_DAT.'023_eeAngVelLimb2.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'023_eeAngVelLimb2.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'023_eeAngVelLimb2.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 23
if(VIEWMODE) replot

