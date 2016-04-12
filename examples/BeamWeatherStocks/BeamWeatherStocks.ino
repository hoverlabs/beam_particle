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
    
    Particle.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);
    Particle.subscribe("hook-response/get_stocks", gotStocksData, MY_DEVICES);
    
    b.begin();

}

void loop() {

    if (runNow == 1){
        
        Particle.publish("get_weather");
        /* 
        delay 30 seconds so that weather data gets scrolled 
        for a few seconds before being overwritten by stocks data      
        */
        delay(30000);       
        Particle.publish("get_stocks");

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

// function to call for the get_weather webhook
void gotWeatherData(const char *name, const char *data) {

    String str = String(data);
    String weatherStr = tryExtractString(str, "<weather>", "</weather>");
    String tempStr = tryExtractString(str, "<temp_f>", "</temp_f>");

    if (tempStr != NULL && weatherStr != NULL) {

      String beamWeather = weatherStr + ", " + tempStr + String("'F ");
      beamWeather.toUpperCase();
      
      Serial.println("Publishing Weather:");
      Serial.println(beamWeather);

      char buf[1024];
      beamWeather.toCharArray(buf, 1024);

      b.print(buf);
      b.play();

    }

}

// function to call for the get_stocks webhook
void gotStocksData(const char *name, const char *data) {

    String str = String(data);
    String PriceStr = tryExtractStock(str);

    if (PriceStr != NULL) {

      String beamStock = PriceStr;
      beamStock.toUpperCase();
      
      Serial.println("Publishing Stock:");      
      Serial.println(beamStock);                //output "AAPL","+1.49%","GOOG","+0.53%","MSFT","+0.35%"

      char buf[1024];
      beamStock.toCharArray(buf, 1024);
      
      b.print(buf);
      b.play();      
        
    }
}

// Formats our stock string by removing unwanted characters
String tryExtractStock(String str) {

    str.replace("\",\"", " ");  //remove ","
    str.replace("\"", " ");     //remove remaining "
    str.replace("\n","");       //remove the new lines

    return str;
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
