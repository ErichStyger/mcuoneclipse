readme.txt
----------

This folder contains 'eye' images from Adafruit, see
- https://github.com/adafruit/Adafruit-1.5inch-Color-OLED-PCB
- https://learn.adafruit.com/animated-electronic-eyes-using-teensy-3-1

run the Python program to convert images, e.g.
(copy files to the same directory as the script)

c:\Python27\python.exe tablegen.py DEFAULT_ defaultEye/sclera.png defaultEye/iris.png defaultEye/lid-upper-symmetrical.png defaultEye/lid-lower-symmetrical.png defaultEye/lid-upper.png defaultEye/lid-lower.png 80 > defaultEye.h

python tablegen.py dragonEye/sclera.png dragonEye/iris.png dragonEye/lid-upper-symmetrical.png dragonEye/lid-lower-symmetrical.png dragonEye/lid-lower.png dragonEye/lid-upper.png 160 dragonEye/pupilMap.png > dragonEye.h

Links:
- https://github.com/adafruit/Adafruit-1.5inch-Color-OLED-PCB
- https://learn.adafruit.com/animated-electronic-eyes-using-teensy-3-1
