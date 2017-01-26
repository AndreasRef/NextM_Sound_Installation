#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    seconds = 4;
    timeSpan = seconds * 1000;
    running = false;
    startTimer();
}


void ofApp::startTimer() {
    running = true;
    timeElapsed = 0;
    timeStart = ofGetElapsedTimeMillis();
    timeEnd = timeSpan;
    
    numberOfEvents = round(ofRandom(0,10));
    timeEvent = timeSpan / numberOfEvents;
    currentEvent = 0;
    eventStop = timeEvent;

    
    numberOfEvents = 4;
    for (int i = 0; i < numberOfEvents; i++) {
        float _duration = ofRandom(500, 6000);
        float _startTime = timeStart + (timeEvent * i);
        //        ofLog() << ofToString(i) + ": " + ofToString(duration);
        string _id = "id-" + ofToString(idInt);
        Note note;
        
        note.setup(_startTime, _duration, _id);
        notes.push_back(note);
        idInt++;
    }
    
    ofLog() << ofToString("Start timer with " + ofToString(numberOfEvents) + " events");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (running) {
        timeElapsed = ofGetElapsedTimeMillis() - timeStart;
        
        // Notes
        for (int i = 0; i < notes.size(); i++) {
            if (!notes[i].started) {
                if (ofGetElapsedTimeMillis() >= notes[i].startTime) {
                    notes[i].started = true;
                    
                    // Start note
                    ofLog() << "Start note " + ofToString(notes[i].id);
                }
            }else if (notes[i].started) {
                if (ofGetElapsedTimeMillis() >= notes[i].startTime + notes[i].duration) {
                    ofLog() << "Stop note " + ofToString(notes[i].id);
                    notes[i].killAble = true;
                }else{
                    notes[i].percent = (ofGetElapsedTimeMillis() - notes[i].startTime) / notes[i].duration;
                }
            }
        }
        
        for (int i = 0; i < notes.size(); i++) {
            if (notes[i].killAble == true) {
                notes.erase(notes.begin() + i);
            }
        }
        
        
        if (timeElapsed >= timeEnd) {
            if (numberOfEvents > 0) {
                //ofLog() << "Stop: " + ofToString(currentEvent);
            }
            
            currentEvent = -1;
            ofLog() << "ended";
            

            running = false;
            startTimer();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    /*
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
    */
    
    for (int i = 0; i < notes.size(); i++) {
        if (notes[i].started) {
            float p = 1 - notes[i].percent;
            ofDrawRectangle((i * 20) + 2, 100, 18, 100 * p);
        }
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
