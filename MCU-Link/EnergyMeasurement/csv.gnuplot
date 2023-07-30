set datafile separator ','			# CSV with comma as separator

set key autotitle columnhead 			# use the first line as title
set ylabel "Current (mA)" 			# label for the Y axis
set xlabel 'Time (us)' 				# label for the X axis

set style line 100 lt 1 lc rgb "grey" lw 0.5 	# linestyle for the grid
set grid ls 100 				# enable grid with specific linestyle

plot "data.csv" using 1:2 with lines
