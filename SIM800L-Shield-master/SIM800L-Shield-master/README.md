# SIM800L-Shield
## Supporting Documents (Technical Manual, Sample codes,Libraries)

- Github account: www.github.com/e-Gizmo/
- Visit our Website at www.e-gizmo.com - [e-Gizmo Mechatronix Central](www.e-gizmo.com)
- Facebook Page: www.facebook.com/eGizmoMechatronix/
- YouTube Channel: www.youtube.com/channel/UCPTmP3ql3_D302-zh5sZqAw

## Sample connections: gizDuino PLUS
![Imgur](http://i.imgur.com/4wc1kd8.png)
### If you are using a SoftwarSerial library, you need to select the SUART to connect on the pin 2 and 3.

## Arduino MEGA 2560
![Imgur](http://i.imgur.com/1msoLWR.png)
### You can use Serial1 on your codes, instead of using library.

## Sample Code
Using SoftwareSerial library
<https://github.com/e-Gizmo/SIM800L-Shield/blob/master/SIM800_900_Sample_sketch/SIM800_900_Sample_sketch.ino>

Note: If you are using gizDuino PLUS, X and Arduino MEGA) use Serial1.
<https://gist.github.com/e-Gizmo/dc55f1426d70c404abf01dd302a1cca4>

## The library
###### Add the GPRS_Shield_Arduino.h <https://drive.google.com/open?id=0BxdLxDCD6HidNDJrdHdYNmstRWs>
###### Go to My Documents>Arduino>libraries> GPRS_Shield_Arduino folder

## The Sample Code with GPRS_Shield_Arduino library
```ruby
//SERIAL PIN ASSIGNMENT
#define PIN_TX    2
#define PIN_RX    3
```

## without library
Sample code Serial Only <https://gist.github.com/e-Gizmo/7866465>

- For Technical Support, Kindly email us at <egizmo.technical@gmail.com>
