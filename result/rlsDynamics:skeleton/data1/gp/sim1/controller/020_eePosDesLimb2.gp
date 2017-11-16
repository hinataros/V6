reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 desired EE pos. [mm]'

set output CONTROLLER_EPS.'020_eePosDesLimb2.eps'

plot CONTROLLER_DAT.'020_eePosDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*K) t '' w l ls 1,\
CONTROLLER_DAT.'020_eePosDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*K) t '' w l ls 2,\
CONTROLLER_DAT.'020_eePosDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*K) t '' w l ls 3

set terminal TERMINAL 20
if(VIEWMODE) replot

