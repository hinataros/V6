reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Base pos. [mm]'

set output MODEL_EPS.'000_basePos.eps'

plot MODEL_DAT.'000_basePos.dat' u 1:($2*K) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'000_basePos.dat' u 1:($3*K) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'000_basePos.dat' u 1:($4*K) t '' w l lw LINE_WIDTH

set terminal TERMINAL 0
if(VIEWMODE) replot

