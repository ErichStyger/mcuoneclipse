readme.txt
----------

This project uses the ESP8266 WiFi module with the FRDM-KL25Z board, using Processor Expert and Kinetis Design Studio.

See
http://mcuoneclipse.com/2014/10/15/cheap-and-simple-wifi-with-esp8266-for-the-frdm-board/
http://www.electrodragon.com/w/Wi07c


http://scargill.wordpress.com/category/esp8266/
http://www.instructables.com/id/ESP8266-Wifi-Temperature-Logger/?ALLSTEPS
http://tomeko.net/other/ESP8266/index.php?lang=en
http://www.snip2code.com/Snippet/194415/Webserver-for-Arduino-ESP8266
https://github.com/esp8266/esp8266-webserver
http://thomaspfeifer.net/esp8266_wlan_seriell_modul_at_kommandos.htm
http://nerdclub-uk.blogspot.ch/2014/10/getting-esp8266-wifi-module-to-work.html



------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST failed!
connection to WiFi FAILED!
CMD> [00][00]ŒŒ[1C]€[1C]ŒŒ[1C][10]Œ[1C]Œ[00]Œ[00]Œ[1C]Œ[1C][00]Œ[10]ŒàŒàŒŒ[1C][00][1C][10]ŒàŒ[00]
ready
status

--------------------------------------------------------------
SYSTEM STATUS
--------------------------------------------------------------
Firmware     : Nov 23 2014 10:22:02
ESP8266      : 
  Firmware   : 00160901
  IP         : 192.168.0.111
  AP         : ESP8266
  CIPMUX     : 0
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80


OK
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,436
received<<:
AT+CIPSEND=0,436

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C<p><input type="radio" name="radio" value="0" >Red LED off<br><input type="radio" name="radio" value="1" checked>Red LED on</strong><p><input type="submit"></form></span></body>
</html>
CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C<p><input type="radio" name="radio" value="0" >Red LED off<br><input type="radio" name=</strong><p><input type="submit"></form></span></body>
</ht
SEND OK
Unlink

------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>
CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

SEND OK
Unlink
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
ESP send AT+CIPCLOSE
sending>>:
AT+CIPCLOSE
received<<:
AT+CIPCLOSE

MUX=1
CMD> Unlink

------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy

SEND OK
Unlink
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Unlink
[00][00]ŒŒ[1C]€[1C]Œ[1C]Œ[1C]Œ[00]Œ[1C]Œ[10]Œà[1C]ŒàŒ[1C]ŒàŒ[00]
ready
status

--------------------------------------------------------------
SYSTEM STATUS
--------------------------------------------------------------
Firmware     : Nov 23 2014 15:51:24
ESP8266      : 
  Firmware   : 00160901
  IP         : 192.168.0.111
  AP         : ESP8266
  CIPMUX     : 0
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80


OK
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy

SEND OK
ESP send AT+CIPCLOSE
sending>>:
AT+CIPCLOSE
received<<:
AT+CIPCLOSE

MUX=1
CMD> [00][00]Œ[1C]Œ[1C][10]Œ[1C]ŒŒ[00]Œ[1C]Œ[1C][00][10]Œà[1C]ŒàŒ[1C][00][10]ŒàŒŒ[00]
ready
status

--------------------------------------------------------------
SYSTEM STATUS
--------------------------------------------------------------
Firmware     : Nov 23 2014 15:51:24
ESP8266      : 
  Firmware   : 00160901
  IP         : 192.168.0.111
  AP         : ESP8266
  CIPMUX     : 0
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80


OK
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,248:GET / HTTP/1.1
Accept: text/html, application/xhtml+xml, */*
Accept-Language: de-CH
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko
Accept-Encoding: gzip, deflate
Host: 192.168.0.111
Connection: Keep-Alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy

SEND OK
Unlink
Link

+IPD,0,221:GET /favicon.ico HTTP/1.1
Accept: */*
UA-CPU: AMD64
Accept-Encoding: gzip, deflate
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; Trident/7.0; rv:11.0) like Gecko
Host: 192.168.0.111
Connection: Keep-Alive


OK
Unlink
ESP send AT+CIPCLOSE=0
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

link is not
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


CMD> HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy

SEND OK
ESP send AT+CIPCLOSE=0
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0


OK
Unlink
CMD> 
------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
ESP startWeb
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0
received<<:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

SEND OK
CMD> sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1

link is builded
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,1,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=1,266
received<<:
AT+CIPSEND=1,266
> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0
received<<:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

SEND OK
CMD> ESP send AT+CIPCLOSE=0
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

link is not
ESP send AT+CIPCLOSE=0
ESP send AT+CIPCLOSE=0
CMD> sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

link is not
CMD> sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

link is not
CMD> Unlink
ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0
received<<:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

SEND OK
CMD> Unlink

------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80


OK
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
AccepINFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,1,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=1,266
received<<:
AT+CIPSEND=1,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0
received<<:
HTTP/1.0 200 OKontent-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

SEND OK
ESP send AT+CIPCLOSE=0
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0
received<<:
HTTP/1.0 200 OKontent-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

SEND OK
CMD> 
------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> Unlink
ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0

received<<:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

busy

SEND OK
CMD> Unlink
ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


sending>>:
AT+CIPCLOSE=0

received<<:
HTTP/1.0 200 OKontent-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy
AT+CIPCLOSE=0
busy

busy

SEND OK
CMD> Unlink
ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


CMD> HTTP/1.0 200 OKtent-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>

busy

busy

SEND OK
ESP send AT+CIPCLOSE=0
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0


OK
Unlink
CMD> 
------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP send AT+CIPCLOSE=0
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

link is not
ESP startWeb
CMD> sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK

------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80


OK
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>


busy

busy

SEND OK
sending>>:
AT+CIPCLOSE=0

received<<:
AT+CIPCLOSE=0



busy now ...

OK
Unlink
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>




busy

busy

SEND OK
sending>>:
AT+CIPCLOSE=0

received<<:
AT+CIPCLOSE=0



busy now ...

OK
Unlink
CMD> 
------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,266
received<<:
AT+CIPSEND=0,266

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C</body>
</html>



busy

busy

SEND OK
INFO: Closing connection!
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

sending>>:
AT+CIPCLOSE=0

received<<:
AT+CIPCLOSE=0

busy now ...


busy now ...

OK
Unlink
CMD> 
------------------------------------------
ESP8266 with FRDM-KL25Z
------------------------------------------
TEST ok!
sending>>:
AT+CWJAP="ESP8266","MyESP8266"
received<<:
AT+CWJAP="ESP8266","MyESP8266"


OK
connected to WiFi!
CMD> ESP startWeb
sending>>:
AT+CIPMUX=1
received<<:
AT+CIPMUX=1


OK
sending>>:
AT+CIPSERVER=1,80
received<<:
AT+CIPSERVER=1,80

no change
INFO: Web Server started, waiting for connection on 192.168.0.111:80
Link

+IPD,0,296:GET / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Connection: keep-alive


OK
Connected!
sending>>:
AT+CIPSEND=0,436
received<<:
AT+CIPSEND=0,436

> INFO: Sending http page...
sending>>:
HTTP/1.0 200 OK
Content-Type: text/html
Pragma: no-cache

<html>
<body>
<title>ESP8266 Web Server</title>
<h2>Web Server using ESP8266</h2>
<br /><hr>
<p><form method="POST"><strong>Temp: <input type="text" size=2 value="21"> <sup>O</sup>C<p><input type="radio" name="radio" value="0" >Red LED off<br><input type="radio" name="radio" value="1" checked>Red LED on</strong><p><input type="submit"></form></span></body>
</html>


tml>

busy

busy

SEND OK
INFO: Closing connection!
sending>>:
AT+CIPCLOSE=0
received<<:
AT+CIPCLOSE=0

sending>>:
AT+CIPCLOSE=0

received<<:
AT+CIPCLOSE=0

busy now ...


busy now ...

OK
Unlink
CMD> Link

+IPD,0,404:POST / HTTP/1.1
Host: 192.168.0.111
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:33.0) Gecko/20100101 Firefox/33.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
Referer: http://192.168.0.111/
Connection: keep-alive
Content-Type: application/x-www-form-urlencoded
Content-Length: 7

radio=0
OK
Unlink

