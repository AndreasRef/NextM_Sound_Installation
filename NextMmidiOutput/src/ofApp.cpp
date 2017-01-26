#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
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
    gui.setPosition(ofGetWidth()-250, 10);
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
    
    numberOfEvents = conversionCount;
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
    
    if(ofGetFrameNum()>5) currentSecond++; //Sloppy way to make sure currentSecond is not incremented on startup
}

//--------------------------------------------------------------
void ofApp::update(){
    timeSpan = seconds * millisPerSecond;
    
    if (currentSecond < totalSeconds) {
        dateString = timestamps[currentSecond];
        conversionCount = 0;
        for (int i = 0; i < totalItems; i++) {
            if (jsonData[i]["datetime"].asString() == dateString) {
                if (jsonData[i]["event_type (impression)"] == "pc_conv" || jsonData[i]["event_type (impression)"] == "pv_conv" ) {
                    conversionCount++;
                }
            }
        }
    }else{
        currentSecond = 0;
    }
    
    if (noteStopTimes.size() > 0) {
        for (int i = 0; i < noteStopTimes.size(); i++) {
            float noteTimeElapsed = ofGetElapsedTimeMillis() - noteStartTimes[i];
            if (noteStopTimes[i] != -1 && noteTimeElapsed >= noteStopTimes[i]) {
                
                //STOP MIDI HERE?
                //midiOut.sendNoteOff(channel, note,  velocity);
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
                    //ofLog() << "Stop: " + ofToString(currentEvent);
                }
                float duration = durations[currentEvent];
                float eventStartTime = ofGetElapsedTimeMillis();
                float eventStopTime = eventStartTime + duration;
                noteStartTimes.push_back(eventStartTime);
                noteStopTimes.push_back(eventStopTime);
                currentEvent++;
                ofLog() << "Start: " + ofToString(currentEvent);
                
                //START MIDI HERE?
                //midiOut.sendNoteOn(channel, note,  velocity);
                ofLog() << "Stop after " + ofToString(duration);
                
                //MIDI
                note =60;
                velocity = 64;
                
                midiOut.sendNoteOn(channel, note,  velocity);
                midiOut.sendNoteOff(channel, note,  velocity);
                
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ofDrawBitmapString(dateString, 20, 20);
    //ofDrawBitmapString("Timespan: " + ofToString(millisPerSecond) + " ms", 100, 40);
    ofDrawBitmapString(ofToString(numberOfEvents) + " events", 180, 20);
    //ofDrawBitmapString("Countdown: " + ofToString(timeSpan - timeElapsed) + " milliseconds", 100, 120);
    
    for (int i = 0; i < numberOfEvents; i++) {
        ofSetColor(255, 255, 255);
        if (currentEvent - 1 == i) {
            ofSetColor(255, 0, 0);
        }
        ofDrawRectangle((i * 62) + 20, 300, 60, 20);
    }
    gui.draw();
}
