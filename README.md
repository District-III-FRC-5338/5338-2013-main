Team 5338 District III Robot Code
=================================

The C++ source for the robot code which implements a safe teleop with an override. 

Autonomus
=========
Autonomous Code is omitted since public demos will not use an autonomous. 

Teleop Controls
===============

### Drive Joysticks
A left and right joystick are used for driving the robot.
The left joystick trigger can be used for making the robot drive straight. 
The robot uses an override joystick in case the public user does something bad (like running into a wall). 

### Functionality
The right joystick also controls functionality. 
The functionality is as follows 
<table> 
<tr> 
<td> Button </td> <td> Action </td> 
</tr> 
<tr> 
<td> 1 </td> <td> Launch ball </td> 
</tr>
<tr>  
<td> 2 </td> <td> Spin BallMotor @ 50% </td> 
</tr>
<tr> 
<td> 3 </td> <td> Retract the Arm  </td> 
</tr> 
<tr> 
<td> 4 </td> <td>Prime the Catapult </td> 
</tr> 

<tr> 
<td> 5 </td> <td>Extend the Arm </td> 
</tr> 
 
<tr> 
<td> 8 </td> <td> Spin BallMotor @ 80% </td> 
</tr> 
</table> 
The same buttons apply for the functionality/override joystick, as long as button 12 is pressed on the override joystick. 
Button 12 allows the override joystick to have complete control of the robot. 
