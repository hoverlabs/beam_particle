/*
===========================================================================

  This is an example for Beam.

  Beam is a beautiful LED matrix — features 120 LEDs that displays scrolling text, animations, or custom lighting effects.
  Beam can be purchased here: http://www.hoverlabs.co

  Written by Emran Mahbub and Jonathan Li for Hover Labs.
  BSD license, all text above must be included in any redistribution

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

unsigned long updateTimer = 0;      // timer used to call our webhooks after an elapsed time
int runNow = 1;                     // flag used to indicate when timer reaches our elapsed time


void setup() {

    Serial.begin(9600);
    Wire.begin();

    Serial.println("Starting Beam example");

    Particle.subscribe("hook-response/bus_info", gotBusData, MY_DEVICES);

    b.begin();

}

void loop() {

    if (runNow == 1){

        Particle.publish("bus_info");
        runNow = 0;
        updateTimer = millis();
    }

    /*
    wait 45 seconds before calling our publish functions again
    */
    if (millis() - updateTimer > 45000){
        runNow = 1;
    }

    // do something else here

}

void gotBusData(const char *name, const char *data) {

    String str = String(data);
    String leaveStr = tryExtractString(str, "<ExpectedLeaveTime>", "</ExpectedLeaveTime>");
    String destinationStr = tryExtractString(str, "<Destination>", "</Destination>");
    String countdownStr = tryExtractString(str, "<ExpectedCountdown>", "</ExpectedCountdown>");
    String routeStr = tryExtractString(str, "<RouteNo>", "</RouteNo>");

    if (routeStr != NULL) {
        Serial.println("Route No: " + routeStr);
    }

    if (destinationStr != NULL) {
        Serial.println("Going to: " + destinationStr);
    }

    if (countdownStr != NULL) {
        Serial.println("Leaving in: " + countdownStr + String("Mins"));
    }

    if (routeStr !=NULL){

        String beamString =  String(routeStr + "   " + destinationStr + "   " + countdownStr + " MINS");
        beamString.toUpperCase();
        Serial.println(beamString);

        char buf[1024];
        beamString.toCharArray(buf, 1024);

        b.begin();
        b.print(buf);
        b.setSpeed(5);
        b.play();

    }

}

// Returns any text found between a start and end string inside 'str'
// example: startfooend  -> returns foo
String tryExtractString(String str, const char* start, const char* end) {

    if (str == NULL) {
        return NULL;
    }

    int idx = str.indexOf(start);
    if (idx < 0) {
        return NULL;
    }

    int endIdx = str.indexOf(end);
    if (endIdx < 0) {
        return NULL;
    }

    return str.substring(idx + strlen(start), endIdx);
}
