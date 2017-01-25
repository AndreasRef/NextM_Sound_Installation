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
    void update();
    void startTimer();
    
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
    
    
    //NEW TIMER
    float seconds;
    float timeSpan;
    float timeStart;
    float timeEnd;
    float timeElapsed = 0;
    int numberOfEvents = 0;
    int currentEvent = 0;
    float eventStop = 0;
    float timeEvent;
    bool running;
    
    vector<float> durations;
    vector<float> noteStartTimes;
    vector<float> noteStopTimes;
    
    
    //GUI
    ofxIntSlider millisPerSecond;
    ofxPanel gui;
    
    
    int conversionCount;
    string dateString;
    
};
