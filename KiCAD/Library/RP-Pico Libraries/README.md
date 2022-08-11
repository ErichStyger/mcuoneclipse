# KiCad-RP-Pico
A simple repository of files needed to add a 3D footprint of the Raspberry Pi Pico board to KiCad.

![Rasperry Pi Pico mechanical specification](Images/Image01.png)

## Schematic and footprint
I've started from the schematics and footprint files available on the [HeadBoffin RP_Silicon_KiCad GitHub project](https://github.com/HeadBoffin/RP_Silicon_KiCad). Because there are some errors in the readme file on how and where we can get those files from the Raspberry Pi web site, I've copied the needed files here, on the `RP-Pico Libraries` folder. Follow the [install instructions](Install%20instructions.md) to add the Raspberry Pi Pico board schema and footprint to a KiCad project:

![schema and footprint screenshot](Images/Image02.png)

## 3D Visual
Elas, with the files found in the [HeadBoffin project](https://github.com/HeadBoffin/RP_Silicon_KiCad) no visual footprint is available, as we can see on the 3D viewer:

![footprint without 3D visual screenshot](Images/Image03.png)

So I decided to create one, using the mechanical specification from the [Raspberry Pi Pico datasheet](https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf):

![Rasperry Pi Pico mechanical specification](Images/Image04.png)

I've used SketchUp to create the 3D model:

![Rasperry Pi Pico mechanical specification](Images/Image05.png)

and I used the native Sketchup export function (no plugin needed) to create the VRLM file `Pico.wrl` that I've also added an the  `RP-Pico Libraries` folder, as the VRLM format is one of the 3D model format that KiCad allow to use for the visual representation of a CPB footprint.

After adding it to the Raspberry Pi Pico KiCad footprint library, we can finally see the visual representation of the Raspberry Pi Pico board:

![Rasperry Pi Pico mechanical specification](Images/Image06.png)

Please note that the castellated pins of the Pico board allow it to be usable as a surface mount module. That's way you see the board simply placed on top of the PCB board.

## Install 3D visual

Please note that adding the visual file to the footprint make the use of KiCad very slow when showing the 3D viewer for the first time. On my old laptop it takes 30s to show, but only 3s to reopen it. The good news are that you can disable it while working at your project and enable it when you want a nice 3D representation of your work.

To install and enable/disable it follow the [install instructions](Install%20instructions.md).

## Test project

I've created a test project where you can find a simple usage example. The first image of this readme shows the result.

## License
Please read the [License](LICENSE) where is stated that this work is free to use.
A tweet with an image of your Raspberry Pi Pico project with a link this project and me (@tpcware) would be greatly appreciated.