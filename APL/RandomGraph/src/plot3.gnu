#! /usr/bin/env gnuplot

set term x11 persist
set title "P(n) = 1/(n^2)";
FILE='< cat plot_3.out | sort -n';

set xlabel "c"
set ylabel "Probability"
#set key off

set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5   # --- red

plot FILE using 1:2  with linespoints ls 2 title 'connected', \
	FILE using 1:3  with linespoints ls 1 title 'cyclic'
