reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVelLimb1.eps'

plot MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '1' w l ls 1,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '2' w l ls 2,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '3' w l ls 3,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($5*E) t '4' w l ls 4,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($6*E) t '5' w l ls 5,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($7*E) t '6' w l ls 6

set terminal TERMINAL 16
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVelLimb2.eps'

plot MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($8*E) t '1' w l ls 1,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($9*E) t '2' w l ls 2,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($10*E) t '3' w l ls 3,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($11*E) t '4' w l ls 4,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($12*E) t '5' w l ls 5,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($13*E) t '6' w l ls 6

set terminal TERMINAL 17
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVelLimb3.eps'

plot MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($14*E) t '1' w l ls 1,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($15*E) t '2' w l ls 2,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($16*E) t '3' w l ls 3,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($17*E) t '4' w l ls 4

set terminal TERMINAL 18
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVelLimb4.eps'

plot MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($18*E) t '1' w l ls 1,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($19*E) t '2' w l ls 2,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($20*E) t '3' w l ls 3,\
MODEL_DAT.'011_jointVel.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($21*E) t '4' w l ls 4

set terminal TERMINAL 19
if(VIEWMODE) replot


