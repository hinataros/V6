reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 EE pos. [mm]'

set output MODEL_EPS.'020_eePosLimb4.eps'

plot MODEL_DAT.'020_eePosLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*K) t '' w l ls 1,\
MODEL_DAT.'020_eePosLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*K) t '' w l ls 2,\
MODEL_DAT.'020_eePosLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*K) t '' w l ls 3

set terminal TERMINAL 20
if(VIEWMODE) replot

