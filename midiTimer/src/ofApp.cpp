#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    seconds = 1;
    timeSpan = seconds * 1000;
    running = false;
    startTimer();
    
    //MIDI
    
    midiOut.listPorts(); // via instance
    midiOut.openPort(0); // by number
    
    channel = 1;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
}

//--------------------------------------------------------------
void ofApp::startTimer() {
    running = true;
    timeElapsed = 0;
    timeStart = ofGetElapsedTimeMillis();
    timeEnd = timeSpan;
    
    numberOfEvents = round(ofRandom(0,10)); //Replace this with number of conversions
    timeEvent = timeSpan / numberOfEvents;
    currentEvent = 0;
    eventStop = timeEvent;
    
    durations.clear();
    noteStartTimes.clear();
    noteStopTimes.clear();
    for (int i = 0; i < numberOfEvents; i++) {
        float duration = ofRandom(500, 6000);
        durations.push_back(duration);
        
        ofLog() << ofToString(i) + ": " + ofToString(duration);
    }
    ofLog() << ofToString("Start timer with " + ofToString(numberOfEvents) + " events");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (noteStopTimes.size() > 0) {
        for (int i = 0; i < noteStopTimes.size(); i++) {
            float noteTimeElapsed = ofGetElapsedTimeMillis() - noteStartTimes[i];
            if (noteStopTimes[i] != -1 && noteTimeElapsed >= noteStopTimes[i]) {
                ofLog() << "Stop note: " + ofToString(i);
                noteStopTimes[i] = -1;
            }
        }
    }
    
    if (running) {
        timeElapsed = ofGetElapsedTimeMillis() - timeStart;
        if (timeElapsed >= timeEnd) {
            if (numberOfEvents > 0) {
                //ofLog() << "Stop: " + ofToString(currentEvent);
            }
            
            currentEvent = -1;
            ofLog() << "ended";
            

            running = false;
            startTimer();
        }else{
            
            if (timeElapsed >= (eventStop * currentEvent)) {
                if (currentEvent > 0) {
//                    ofLog() << "Stop: " + ofToString(currentEvent);
                }
                float duration = durations[currentEvent];
                float eventStartTime = ofGetElapsedTimeMillis();
                float eventStopTime = eventStartTime + duration;
                noteStartTimes.push_back(eventStartTime);
                noteStopTimes.push_back(eventStopTime);
                currentEvent++;
                ofLog() << "Start: " + ofToString(currentEvent);
                ofLog() << "Stop after " + ofToString(duration);
                
                //MIDI
                
                note =64;
                velocity = 64;
                midiOut.sendNoteOn(channel, note,  velocity);
                midiOut.sendNoteOff(channel, note,  velocity);
                
            }
        
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Timespan: " + ofToString(seconds) + " seconds", 100, 40);
    ofDrawBitmapString(ofToString(numberOfEvents) + " events", 100, 80);
    ofDrawBitmapString("Countdown: " + ofToString(timeSpan - timeElapsed) + " milliseconds", 100, 120);
    
    for (int i = 0; i < numberOfEvents; i++) {
        ofSetColor(255, 255, 255);
        if (currentEvent - 1 == i) {
            ofSetColor(255, 0, 0);
        }
        ofDrawRectangle((i * 62) + 100, 300, 60, 20);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
