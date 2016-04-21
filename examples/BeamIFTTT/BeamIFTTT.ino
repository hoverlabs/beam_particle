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
#define IRQPIN 9        //currently not used
#define BEAMCOUNT 1     //number of beams daisy chained together

/* Iniitialize an instance of Beam */
Beam b = Beam(RSTPIN, IRQPIN, BEAMCOUNT);

/* Timer used by the demo loop */
unsigned long updateTimer = 0;
int demo = 0;

void setup() {
    
    Serial.begin(9600);
    Wire.begin();
    
    Serial.println("Starting Beam example");
    
    Particle.subscribe("Fitbit_Steps", fitbitHandler);

}

    void fitbitHandler(const char *event, const char *data)
    {
       
       const char* stats = data;
       b.begin();
       b.print(stats);
       b.setLoops(7);
       b.setSpeed(4);
       b.setMode(SCROLL);
       b.play();    
       
    }

void loop() {

    


    // do something else here

}
