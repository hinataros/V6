reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Base ang. vel. [rad/s]'

set output MODEL_EPS.'003_baseAngVel.eps'

plot MODEL_DAT.'003_baseAngVel.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'003_baseAngVel.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'003_baseAngVel.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 3
if(VIEWMODE) replot

