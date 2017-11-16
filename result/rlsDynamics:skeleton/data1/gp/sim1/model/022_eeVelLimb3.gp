reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 EE vel. [m/s]'

set output MODEL_EPS.'022_eeVelLimb3.eps'

plot MODEL_DAT.'022_eeVelLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '' w l ls 1,\
MODEL_DAT.'022_eeVelLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '' w l ls 2,\
MODEL_DAT.'022_eeVelLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '' w l ls 3

set terminal TERMINAL 22
if(VIEWMODE) replot

