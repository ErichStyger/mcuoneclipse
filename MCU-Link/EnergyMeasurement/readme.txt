readme.txt
----------
Project in C to read in and export energy measurement data exported from the MCUXpresso IDE.
See
https://mcuoneclipse.com/2023/07/30/data-converter-for-mcuxpresso-energy-measurement-data/
https://mcuoneclipse.com/2021/10/17/new-mcu-link-pro-debug-probe-with-energy-measurement/

run
  make
to build the executable. It has been tested on Windows and on Linux (Raspberry Pi)

For testing, an example measurement data is provided as exported from the MCUXpresso (zip file).
Extract the zip file and run the executable.
  converter -h
provides a list of help.

Run the gnuplot with:
gnuplot -p csv.gnulot

Open Points:
- This is work in progress
- UnitMul and UnitDiv are hard coded as #define in the source. Change it to match your data.
- Verbose settings to print more information is done with #defines in the source code
- It is unclear how the timestamps need to be used. Currently the sum of the timestamps is less than what the IDE shows.
 
