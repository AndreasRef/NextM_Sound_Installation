#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxJSON.h"
#include "ofxGUI.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed (int key);
	void keyReleased (int key);
	
    
    void mousePressed (int x, int y, int button);
    void mouseReleased (int x, int y, int button);
    
	
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
    
    
    //DEBUG
    int tv2Count = 0;
};
