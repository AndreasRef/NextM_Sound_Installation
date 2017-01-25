#pragma once


#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxMidi.h"
#include "ofxGUI.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    
    //MIDI
    ofxMidiOut midiOut;
    int channel;
    
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    
    //JSON
    ofxJSONElement jsonData;
    int totalItems;
    vector <string> timestamps;
    int totalSeconds = 0;
    int currentSecond = 0;
    

    //TIMER
    float startTime; // store when we start time timer
    float endTime; // when do want to stop the timer
    bool  bTimerReached; // used as a trigger when we hit the timer
    
    
    //GUI
    ofxIntSlider millisPerSecond;
    ofxPanel gui;
    
    
    int conversionCount;
    
};
