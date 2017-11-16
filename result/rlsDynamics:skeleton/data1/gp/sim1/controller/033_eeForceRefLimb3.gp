reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 EE force reference. [N]'

set output CONTROLLER_EPS.'033_eeForceRefLimb3.eps'

plot CONTROLLER_DAT.'033_eeForceRefLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '' w l ls 1,\
CONTROLLER_DAT.'033_eeForceRefLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '' w l ls 2,\
CONTROLLER_DAT.'033_eeForceRefLimb3.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '' w l ls 3

set terminal TERMINAL 0
if(VIEWMODE) replot

