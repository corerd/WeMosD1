BluetoothSerial Library
=======================
The BluetoothSerial library has been developed to allow the communication
with an HC-05 Bluetooth module on the digital pins of the WeMos D1 Mini.

HC-05 Bluetooth module (ZS-040 breakout board)
==============================================
![user input clear](https://corerd.github.io/WeMosD1/img/HC-05_ZS-040.jpg)

**PINOUT**

 Pin  |  Mode  | Function
----- | ------ | ----------------------------
  EN  | Input  | Module Enable / Disable
 VCC  |   -    | Power input (3.3v - 6v)
 GND  |   -    | Ground
 TXD  | Output | Serial Data Output
 RXD  | Input  | Serial Data Input
STATE | Output | Monitor Bluetooth connection

The zs-040 breakout board includes a 3.3v voltage regulator and this allows
the board to accept from 3.6v to 6v on the main `VCC Pin`.
However, all the other digital pins run at 3.3v.

The zs-040 boards differ from some of the other modules in that
they have a `EN Pin` rather than a `KEY Pin`.

The lack of the `KEY Pin` implies that it isn't possible to enter
**AT Command mode** programmatically, but only manually pressing
the small button switch just above the `EN Pin`.

Instead it will be possibile to force programmatically the exit
from **AT Command mode** by means of a LOW-HIGH transition on `EN Pin`.

**`EN Pin`**

Pull the `EN Pin` HIGH or left unconnected to enable the module.
Pull the pin LOW to disable.

**`STATE Pin`**

The `STATE Pin` returns HIGH if the module has an active Bluetooth connection,
LOW otherwise.

See [HC-05 and HC-06 zs-040 Bluetooth modules. First Look](http://www.martyncurrey.com/hc-05-and-hc-06-zs-040-bluetooth-modules-first-look/)
for more informations.


Connecting the HC-05 to the WeMos D1 Mini
-----------------------------------------
![user input clear](https://corerd.github.io/WeMosD1/img/hc05-D1mini_bb.jpg)

HC-05             ||       WeMos D1 Mini
------------------||-----------------------------------------------------
**Pin** | **Mode** | **GPIO** | **Mode** | **Function**
  EN    |  Input   |    D0    |  Output  | Set Module Enable / Disable
  VCC   |    -     |    5V    |    -     | Power supply
  GND   |    -     |    G     |    -     | Ground
  TXD   |  Output  |    D5    |  Input   | RX Serial Data
  RXD   |  Input   |    D6    |  Output  | TX Serial Data
 STATE  |  Output  |    D7    |  Input   | Get Bluetooth connection state

Software serial is used on WeMos D1 Mini GPIOs D5 and D6 to talk to the HC-05.
This means that the hardware serial can still be used to talk to
the serial monitor on a host computer.

HC-05 `STATE Pin` is connected to the WeMos D1 Mini GPIO D7 to monitor
the Bluetooth connection.

HC-05 `EN Pin` is connected to the WeMos D1 Mini GPIO D0 to programmatically
enable / disable the module.
If a connection is in progress, the LOW-HIGH transition on `EN Pin` forces
the disconnection. The same applies also to exit from **AT Command mode**.