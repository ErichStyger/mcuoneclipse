readme.txt
----------

Install Mosuquitto on Win:
https://sivatechworld.wordpress.com/2015/06/11/step-by-step-installing-and-configuring-mosquitto-with-windows-7/


MQTT Spy: (http://www.hivemq.com/blog/seven-best-mqtt-client-tools)
http://kamilfb.github.io/mqtt-spy/
https://github.com/eclipse/paho.mqtt-spy/wiki/Downloads
MQTT FX



MQTT test server:
https://test.mosquitto.org/
    1883 : MQTT, unencrypted
    8883 : MQTT, encrypted
    8884 : MQTT, encrypted, client certificate required
    8080 : MQTT over WebSockets, unencrypted
    8081 : MQTT over WebSockets, encrypted

    
    
    http://www.nongnu.org/lwip/2_0_x/group__mqtt.html
    
 "c:\Program Files (x86)\mosquitto\mosquitto_sub.exe" -h localhost -t "$SYS/broker/clients/total"