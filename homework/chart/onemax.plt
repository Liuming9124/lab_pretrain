set terminal png font arial 14 size 800,600
set key bmargin

#set xrange [0:10000]
#set yrange [0:20]

set xlabel 'iteration'
set ylabel 'value'
set output 'onemax.png'

#plot 'temperture_in_iteration.txt' pt 7 lw 2 lc rgb "blue" title 'T-100--CD-0.99'

plot '../result/onemax/exhaustive/onemaxexhaustiveAvg.txt' pt 1 lw 1 ps 1 lc rgb "blue" title 'Exhaustive',\
     '../result/onemax/hill/onemaxhillAvg.txt' pt 1 lw 1 ps 1 lc rgb "red" title 'Hill',\
     '../result/onemax/sa/onemaxsaAvg.txt' with lines lw 2 lc rgb "blue" title 'Sa',\
     '../result/onemax/ga/onemaxgaAvg.txt' with lines lw 2 lc rgb "red" title 'Ga',\
     '../result/onemax/ts/onemaxtsAvg.txt' with lines lw 2 lc rgb "green" title 'Ts'


set output