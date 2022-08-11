# Install instructions

## 1. Copy the files locally

Copy the `RP-Pico Libraries` folder wherever you like on your computer.

## 2. Install the Raspberry Pi Pico board schema symbol

Use the `KiCad | Preferences | Manage Symbol Libraries...` command to manage the symbol library:

![symbol library manager](Images/Image07.png)

then select the global tab and click on the folder button:

![symbol library manager](Images/Image08.png)

navigate to the `RP-Pico Libraries` folder, select the `MCU_RaspberryPi_and_Boards.kicad_sym` file and open it:

![symbol library manager](Images/Image09.png)

et voilà, the first step is completed:

![symbol library manager](Images/Image10.png)

You can now close the symbol libraries manager window.

## 3. Install the Raspberry Pi Pico board footprint

You can use a similar approach to add the footprint to the footprint libraries manager, but I've found some issues that I've solved using the footprint editor, so here are the steps I suggest you to follow:

Open the footprint editor

![symbol library manager](Images/Image11.png)

wait for the footprints to load... then use the `File | Add Library` command:

![symbol library manager](Images/Image12.png)

confirm the `Global` choice:

![symbol library manager](Images/Image13.png)

and select the `MCU_RaspberriPi_and_Boards.pretty` folder (yes, the folder represent a footprint library on KiCad):

![symbol library manager](Images/Image14.png)

Now the library is installed on KiCad with the Raspberry Pi Pico footprint (double click on it to see it on the editor pane):

![symbol library manager](Images/Image15.png)

Don't close the windows as the next step start from here.

## 4. Install the Raspberry Pi Pico board footprint 3D visual

If not already open, open the the footprint editor

![symbol library manager](Images/Image11.png)

double click on the `RPi_Pico_SMD_TH` footprint from the `MCU_RaspberriPi_and_Boards` library and then click on the `Footprint properties` icon:

![symbol library manager](Images/Image16.png)

In the footprint properties window, first select the `3D Settings` tab. Please note that the preview shows only the PCB board with the footprint added on step 3, without any 3D representation of the Raspberry Pi Pico board. Now click on the folder icon to add the 3D model:

![symbol library manager](Images/Image17.png)

Navigate to the `RP-Pico Libraries` folder, select the `Pico.wrl` file and wait until the model is shown in the right panel, then confirm with OK:

![symbol library manager](Images/Image18.png)

The model is already scaled and translated to match the footprint:

![symbol library manager](Images/Image19.png)

now close the `Footprint Properties` window, and the `Footprint Editor`, obviously saving the changes.

## Conclusion

Now that you've installed the schema and footprint and added the 3D model to the footprint, you can use the Raspberry Pi Pico board on your KiCad projects.

I've also added a test KiCad Project on the `Test` folder, that you can use to see an example of it.

Have fun!
