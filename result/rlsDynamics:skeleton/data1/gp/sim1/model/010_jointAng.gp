reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 joint ang. [deg]'
set output MODEL_EPS.'010_jointAngLimb1.eps'

plot MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*RAD2DEG) t '1' w l ls 1,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*RAD2DEG) t '2' w l ls 2,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*RAD2DEG) t '3' w l ls 3,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($5*RAD2DEG) t '4' w l ls 4,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($6*RAD2DEG) t '5' w l ls 5,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($7*RAD2DEG) t '6' w l ls 6

set terminal TERMINAL 11
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 joint ang. [deg]'
set output MODEL_EPS.'010_jointAngLimb2.eps'

plot MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($8*RAD2DEG) t '1' w l ls 1,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($9*RAD2DEG) t '2' w l ls 2,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($10*RAD2DEG) t '3' w l ls 3,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($11*RAD2DEG) t '4' w l ls 4,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($12*RAD2DEG) t '5' w l ls 5,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($13*RAD2DEG) t '6' w l ls 6

set terminal TERMINAL 12
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 joint ang. [deg]'
set output MODEL_EPS.'010_jointAngLimb3.eps'

plot MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($14*RAD2DEG) t '1' w l ls 1,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($15*RAD2DEG) t '2' w l ls 2,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($16*RAD2DEG) t '3' w l ls 3,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($17*RAD2DEG) t '4' w l ls 4

set terminal TERMINAL 13
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 joint ang. [deg]'
set output MODEL_EPS.'010_jointAngLimb4.eps'

plot MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($18*RAD2DEG) t '1' w l ls 1,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($19*RAD2DEG) t '2' w l ls 2,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($20*RAD2DEG) t '3' w l ls 3,\
MODEL_DAT.'010_jointAng.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($21*RAD2DEG) t '4' w l ls 4

set terminal TERMINAL 14
if(VIEWMODE) replot


