#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //MIDI
    midiOut.listPorts(); // via instance
    midiOut.openPort(0); // by number
    
    channel = 1;
    currentPgm = 0;
    midiNote = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
    
    //JSON
    std::string file = "convertcsv-all.json";
    
    bool parsingSuccessful = jsonData.open(file);
    
    if (parsingSuccessful)
    {
        ofLog() << "JSON Loaded";
        totalItems = jsonData.size();
        ofLog() << "Total: " + ofToString(totalItems);
        
        string currentTimestamp = "";
        
        for (int i = 0; i < totalItems; i++) {
            if (jsonData[i]["datetime"].asString() != currentTimestamp) {
                currentTimestamp = jsonData[i]["datetime"].asString();
                timestamps.push_back(currentTimestamp);
                totalSeconds++;
            }
        }
        ofLog() << "Secs: " + ofToString(totalSeconds);
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
    //GUI
    gui.setup();
    gui.setPosition(ofGetWidth()-220, 10);
    gui.add(millisPerSecond.setup("millisPerSecond", 1000, 10, 2000));
    
    //TIMER
    seconds = 1;
    timeSpan = seconds * millisPerSecond;
    running = false;
    startTimer();
    
}

//--------------------------------------------------------------
void ofApp::startTimer() {
    running = true;
    timeElapsed = 0;
    timeStart = ofGetElapsedTimeMillis();
    timeEnd = timeSpan;
    
    numberOfEvents = conversionCount; // round(ofRandom(0,10));
    timeEvent = timeSpan / numberOfEvents;
    currentEvent = 0;
    eventStop = timeEvent;
    
    int n = 0;
    
    dateString = timestamps[currentSecond];
    for (int i = 0; i < totalItems; i++) {
        if (jsonData[i]["datetime"].asString() == dateString) {
            if (jsonData[i]["event_type (impression)"] == "pc_conv" || jsonData[i]["event_type (impression)"] == "pv_conv" ) {
                //conversionCount++;
                        
                cout << "eventJSON: " + ofToString(i) << endl;
                
                float _duration = ofRandom(100,1000);
                float _startTime = timeStart + (timeEvent * n);
                //        ofLog() << ofToString(i) + ": " + ofToString(duration);
                string _id = "id-" + ofToString(idInt);
                Note note;
                
                note.setup(_startTime, _duration, idInt);
                notes.push_back(note);
                idInt++;

//                ofLog() << jsonData[i]["geo_region"];
                
                
                n++;
            }
        }
    }
    
    
    ofLog() << ofToString("Start timer with " + ofToString(numberOfEvents) + " events");
    
    if(ofGetFrameNum()>5) currentSecond++; //Sloppy way to make sure currentSecond is not incremented on startup
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    timeSpan = seconds * millisPerSecond;
    
    //JSON
    if (currentSecond < totalSeconds) {
        dateString = timestamps[currentSecond];
        conversionCount = 0;
        for (int i = 0; i < totalItems; i++) {
            if (jsonData[i]["datetime"].asString() == dateString) {
                if (jsonData[i]["event_type (impression)"] == "pc_conv" || jsonData[i]["event_type (impression)"] == "pv_conv" ) {
                    conversionCount++;
                    
                    //ofLog() << jsonData[i]["geo_region"];
                }
            }
        }
    }else{
        currentSecond = 0;
    }
    
    
    if (running) {
        timeElapsed = ofGetElapsedTimeMillis() - timeStart;
        
        // Notes
        for (int i = 0; i < notes.size(); i++) {
            if (!notes[i].started) {
                if (ofGetElapsedTimeMillis() >= notes[i].startTime) {
                    notes[i].started = true;
                    
                    // Start note
                    ofLog() << "Start note " + ofToString(notes[i].id);
                    
                    //MIDI
                    midiNote =round(ofRandom(12)) + 60;
                    velocity = 64;
                    
                    midiOut.sendNoteOn(channel, midiNote,  velocity);
                    
                }
            }else if (notes[i].started) {
                if (ofGetElapsedTimeMillis() >= notes[i].startTime + notes[i].duration) {
                    ofLog() << "Stop note " + ofToString(notes[i].id);
                    notes[i].killAble = true;
                    
                    
                    //MIDI
                    midiNote = round(ofRandom(12)) + 60;
                    velocity = 64;
                    
                    midiOut.sendNoteOff(channel, midiNote,  velocity);
                    
                }else{
                    notes[i].percent = (ofGetElapsedTimeMillis() - notes[i].startTime) / notes[i].duration;
                }
            }
        }
        
        
        //Erase old notes
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
    ofSetColor(255);
    
    ofDrawBitmapString(dateString, 20, 20);
    ofDrawBitmapString(ofToString(numberOfEvents) + " events", 180, 20);
    
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
            notes[i].draw();
        }
    }
    
    
    gui.draw();
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
