reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 EE ang. vel. [rad/s]'

set output MODEL_EPS.'023_eeAngVelLimb4.eps'

plot MODEL_DAT.'023_eeAngVelLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '' w l ls 1,\
MODEL_DAT.'023_eeAngVelLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '' w l ls 2,\
MODEL_DAT.'023_eeAngVelLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '' w l ls 3

set terminal TERMINAL 23
if(VIEWMODE) replot

