https://learn.adafruit.com/adafruit-ultimate-gps-logger-shield/direct-connect



Look for the line that says $GPRMC,194509.000,A,4042.6142,N,07400.4168,W,2.03,221.11,160412,,,A*77
This line is called the RMC (Recommended Minimum) sentence and has pretty much all of the most useful data. Each chunk of data is separated by a comma.

The first part 194509.000 is the current time GMT (Greenwich Mean Time). The first two numbers 19 indicate the hour (1900h, otherwise known as 7pm) the next two are the minute, the next two are the seconds and finally the milliseconds. So the time when this screenshot was taken is 7:45 pm and 9 seconds. The GPS does not know what time zone you are in, or about "daylight savings" so you will have to do the calculation to turn GMT into your timezone

The second part is the 'status code', if it is a V that means the data is Void (invalid). If it is an A that means its Active (the GPS could get a lock/fix)

The next 4 pieces of data are the geolocation data. According to the GPS, my location is 4042.6142,N (Latitude 40 degrees, 42.6142 decimal minutes North) & 07400.4168,W. (Longitude 74 degrees, 0.4168 decimal minutes West) To look at this location in Google maps, type +40° 42.6142', -74° 00.4168' into the google maps search box . Unfortunately gmaps requires you to use +/- instead of NSWE notation. N and E are positive, S and W are negative.

#if 0
This is the raw GPS "NMEA sentence" output from the module. There are a few different kinds of NMEA sentences, the most common ones people use are the $GPRMC (Global Positioning RecommendedMinimum Coordinates or something like that) and the $GPGGA sentences. These two provide the time, date, latitude, longitude, altitude, estimated land speed, and fix type. Fix type indicates whether the GPS has locked onto the satellite data and received enough data to determine the location (2D fix) or location+altitude (3D fix).
#endif

#if 0
$GPGSV,2,1,08,25,79,359,,29,57,216,,12,49,079,,02,35,072,*79
$GPGSV,2,2,08,31,30,311,,14,29,242,,24,15,148,,04,11,036,*77
$GPRMC,154537.254,V,,,,,0.00,0.00,200514,,,N*4D
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154538.254,,,,,0,0,,,M,,M,,*45
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154538.254,V,,,,,0.00,0.00,200514,,,N*42
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154539.254,,,,,0,0,,,M,,M,,*44
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154539.254,V,,,,,0.00,0.00,200514,,,N*43
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154540.254,,,,,0,0,,,M,,M,,*4A
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154540.254,V,,,,,0.00,0.00,200514,,,N*4D
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154557.821,,,,,0,0,,,M,,M,,*44
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154557.821,V,,,,,0.00,0.00,200514,,,N*43
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154558.821,,,,,0,0,,,M,,M,,*4B
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154558.821,V,,,,,0.00,0.00,200514,,,N*4C
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
$GPGGA,154559.821,,,,,0,0,,,M,,M,,*4A
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPRMC,154559.821,V,,,,,0.00,0.00,200514,,,N*4D
$GPVTG,0.00,T,,M,0.00,N,0.00,K,N*32
#endif
