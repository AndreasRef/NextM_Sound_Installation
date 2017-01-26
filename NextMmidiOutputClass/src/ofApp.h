#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxMidi.h"
#include "ofxGUI.h"
#include "Note.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void startTimer();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //NOTES
    int idInt = 0;
    vector<Note> notes;
    
    //TIMER
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
    
    //MIDI
    ofxMidiOut midiOut;
    int channel;
    
    unsigned int currentPgm;
    int midiNote, velocity;
    int pan, bend, touch, polytouch;
    
    //JSON
    ofxJSONElement jsonData;
    int totalItems;
    vector <string> timestamps;
    int totalSeconds = 0;
    int currentSecond = 0;
    
    int conversionCount;
    string dateString;
    
    //GUI
    ofxIntSlider millisPerSecond;
    ofxPanel gui;
    
};
