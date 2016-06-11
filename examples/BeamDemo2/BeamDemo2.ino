/*
===========================================================================    

  This is an example for Beam. 
  
  Beam is a beautiful LED matrix — features 120 LEDs that displays scrolling text, animations, or custom lighting effects. 
  Beam can be purchased here: http://www.hoverlabs.co
  
  Written by Emran Mahbub and Jonathan Li for Hover Labs.  
  BSD license, all text above must be included in any redistribution

  
#  HISTORY
    v1.0  -  Initial Release

#  INSTALLATION
    The 4 library files (beam.cpp, beam.h and charactermap.h and frames.h) are required to run Beam.
    Run the BeamDemo.ino file.
    
#  SUPPORT
    For questions and comments, email us at support@hoverlabs.co
===========================================================================    
*/ 

#include "application.h"
#include "beam.h"

/* pin definitions for Beam */
#define RSTPIN 2        //use any digital pin
#define IRQPIN 9        //currently not used - leave unconnected
#define BEAMCOUNT 1     //number of beams daisy chained together

/* Iniitialize an instance of Beam */
Beam b = Beam(RSTPIN, IRQPIN, BEAMCOUNT);

void setup() {
    
    Serial.begin(9600);
    Wire.begin();
    
    Serial.println("Starting Beam example");
    
    b.begin();

}



void loop() {

    //  Beam can begin scrolling text with just print() and play()
    b.print("Hello World!");
    b.play();
    
    delay(4000);
    
    //  Beam can print static text using the display() function. 
    //    Change the BEAMCOUNT declaration above depending on the # of Beams you have connected. 
    switch (BEAMCOUNT){
        case 1:
            b.print("Hello");
            b.display();
            break;
        case 2:
            b.print("Hello World!");
            b.display();
            break;
        case 3:
            b.print("Beam has 120 LEDs.");
            b.display();
            break;
        case 4: 
            b.print("Great for looong text!");
            b.display();
            break;
        default:
            break;
    }

    delay(4000);

    b.print("Keep scrolling dude");
    b.play();
    
    // methods like setSpeed(), setScroll() setLoops(), setMode() can be called 
    //on the fly to change the existing default settings
    delay(1500);
    b.setSpeed(2);      //increase speed
    delay(1000);
    b.setSpeed(1);      //increase speed again!
    delay(3000);
    b.setSpeed(15);     //reduce speed to lowest setting
    
    delay(4000);

}