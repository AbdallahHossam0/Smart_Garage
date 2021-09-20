# Smart_Garage
A Smart Garage System aims to help people to park their cars in easy way without need to help from anyone.
Intro.: The system consists of two ways to control:

Automatic Control
User with Bluetooth (on foot) Automatic Control It consists of two microcontrollers communicating with I2C communication protocol. One MC, at the entrance, and the other at the exit gate. The First MC, checks for places, enables cars in, open the entrance gate, calculate time for each car, and turn on/off the LEDs in the hall. The other MC works with the Keypad (maybe not necessary – we could use the Bluetooth app), LCD to display time and Fee, checks for smoke sensor, and surely communicates with the other microcontroller. User Control It deals with users on foot who come for their cars. They use an application on the phone to open gates, open lights… etc. PS.: we need to know how to detect if it’s a human or a car.
Garage Specs

The garage can take up to 3 cars.
The Door opens for 5 seconds at most and closes automatically
There’s no way to keep the door opened - only though the code
(CODE) each car has the following variables: o State (Occupied or not) o Time it stayed o ID (should be more complicated like : 1FSD) o Maybe we will add other variables if needed MC @ the Entrance If a CAR comes, the MC checks for places, and do the following:
If there’s a place, open the door for 5 seconds
Turn the lights on for 5 seconds
Displays the ID on the LCD
Timer will start calculating time for the car. MC @ the Exit When it detects the car, it asks for the ID. Once it has the ID, communication between the two MCs to get the time from the first MC (then the second MC is the master all the time), and displays the Fee on the LCD.
Safety System

The Smoke sensor is connected to the second MC. If there’s fire, the MC will turn the buzzer on, communicate with the first MC to switch to (Emergency State) and opens all the doors.
The only way to get back to the (NORMAL State) is the click a button connected the second MC. USER Trick
The Bluetooth doesn’t have full control on the system. Maybe the user tries to open the door even if there’s no place inside.
The Bluetooth app, only works with the ID. The MC will give the app the ability to control if and only if it detects that it’s a human and not a car, and that human has a valid ID! (that would be hard to really make sure).
Now, we need to change the ID, to prevent the user from going in ON FOOT first with a memorized ID. That needs the function RAND(), so it should be simple.
