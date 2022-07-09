readme
------
Creating expansion board definition file for Arduino Multifunction shield
https://community.nxp.com/t5/MCUXpresso-Config-Tools/Creating-expansion-board-definition-file-for-Arduino/ta-p/1331509

Adding Expansion Headers to a custom board:
https://community.nxp.com/t5/MCUXpresso-Config-Tools/Adding-Expansion-Headers-to-a-custom-board/ta-p/1415559

Discussion
https://community.nxp.com/t5/MCUXpresso-Config-Tools/Help-Needed-with-Pins-Tool-Expansion-Board-amp-Expansion-Board/m-p/1408539/highlight/true#M1316

Note: the file lpc845-brk.xml needs to be placed into
c:\ProgramData\NXP\mcu_data_{config_tools_version}\expansion_headers
e.g.:
C:\ProgramData\NXP\mcu_data_v11\expansion_headers
(Caution: check the version!)
