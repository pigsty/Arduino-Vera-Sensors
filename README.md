## Scope ##

This is an Arduino sketch that reports values of connected sensors to the Vera home automation gateway using HTTP.

## Features ##

This supports the following Vera device types:

* Light level sensor
* Security device

The Security device is updated when tripped. The Light level is updated at a configurable interval.

It runs on any Arduino and requires the Ethernet Shield.

Connect your sensors between the ground pin and the chosen input pin. The sketch enables the internal pullup resistor. 

It also provides a status page on port 80, that is useful for debugging.

## Usage & Limitations ##

You will need to manually create devices in Vera, then configure the ids in this sketch. It does not auto create any devices in Vera.

## License ##

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/