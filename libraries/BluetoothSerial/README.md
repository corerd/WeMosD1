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

<table>
  <tr>
    <th colspan="2">HC-05</th>
    <th colspan="3">WeMos D1 Mini</th>
  </tr>
  <tr><b>
    <td>PIN</td> <td>**Mode**</td> <td>**GPIO**</td> <td>**Mode**</td>  <td>**Function**</td>
  </b></tr>
  <tr>
    <td>EN</td> <td>Input</td> <td>D0</td> <td>Output</td> <td>Set Module Enable / Disable</td>
  </tr>
  <tr>
    <td>VCC</td> <td>-</td> <td>5V</td> <td>-</td> <td>Power supply</td>
  </tr>
  <tr>
    <td>GND</td> <td>-</td> <td>G</td> <td>-</td> <td>Ground</td>
  </tr>
  <tr>
    <td>TXD</td> <td>Output</td> <td>D5</td> <td>Input</td> <td>RX Serial Data</td>
  </tr>
  <tr>
    <td>RXD</td> <td>Input</td> <td>D6</td> <td>Output</td> <td>TX Serial Data</td>
  </tr>
  <tr>
    <td>STATE</td> <td>Output</td> <td>D7</td> <td>Input</td> <td>Get Bluetooth connection state</td>
  </tr>
</table>

Software serial is used on WeMos D1 Mini GPIOs D5 and D6 to talk to the HC-05.
This means that the hardware serial can still be used to talk to
the serial monitor on a host computer.

HC-05 `STATE Pin` is connected to the WeMos D1 Mini GPIO D7 to monitor
the Bluetooth connection.

HC-05 `EN Pin` is connected to the WeMos D1 Mini GPIO D0 to programmatically
enable / disable the module.
If a connection is in progress, the LOW-HIGH transition on `EN Pin` forces
the disconnection. The same applies also to exit from **AT Command mode**.
