reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'CoM pos. [mm]'

set output MODEL_EPS.'030_comPos.eps'

plot MODEL_DAT.'030_comPos.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*K) t '' w l ls 1,\
MODEL_DAT.'030_comPos.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*K) t '' w l ls 2,\
MODEL_DAT.'030_comPos.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*K) t '' w l ls 3

set terminal TERMINAL 0
if(VIEWMODE) replot

