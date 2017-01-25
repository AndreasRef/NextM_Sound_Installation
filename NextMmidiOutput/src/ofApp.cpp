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

    
    //TIMER
    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = 1000; // in milliseconds
    
    
    //GUI
    
    //GUI
    gui.setup();
    gui.setPosition(ofGetWidth()-250, 10);
    gui.add(millisPerSecond.setup("millisPerSecond", 1000, 10, 2000));
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(255);
    //ofSetHexColor(0x00FF00);
//
//
    if (currentSecond < totalSeconds) {
        //currentSecond++;
     
        string dateString = timestamps[currentSecond];
        
        ofDrawBitmapString(dateString, 20, 100);
        
        int count = 0;
        
        conversionCount = 0;
        
        
        
        for (int i = 0; i < totalItems; i++) {
            if (jsonData[i]["datetime"].asString() == dateString) {
                count++;
                
                //ofLog() << jsonData[i]["geo_city"];
                //ofLog() << jsonData[i]["site_domain"];
                
                //if (jsonData[i]["site_domain"] == "tv2.dk") {
                if (jsonData[i]["event_type (impression)"] == "pc_conv" || jsonData[i]["event_type (impression)"] == "pv_conv" ) {
                    conversionCount++;
                }
                
                
                ofDrawCircle( (count * 4) + 20, 200, 2);
                if (conversionCount > 0) ofDrawCircle( (conversionCount * 4) + 20, 220, 2);
                
            }
        }
        
        
        ofDrawBitmapString("Total items: " + ofToString(count), 20, 130);
        
        ofDrawBitmapString("Konverteringer: " + ofToString(conversionCount), 20, 150);
        
        
        //ofLog() << tv2Count;
        
        
    }else{
        currentSecond = 0;
    }
//
//    
//    ofSleepMillis(100);
    
    
    //TIMER
    
    float barWidth = 500;
    
    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if(timer >= endTime && !bTimerReached) {
        bTimerReached = true;
        currentSecond++;
    }
    
    // the background to the progress bar
    ofSetColor(100);
    ofDrawRectangle((ofGetWidth()-barWidth)/2, ofGetHeight()/2, barWidth, 30);
    
    // get the percantage of the timer
    float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetHexColor(0xf02589);
    ofDrawRectangle((ofGetWidth()-barWidth)/2, ofGetHeight()/2, barWidth*pct, 30);
    
    // draw the percantage
    ofSetColor(20);
    ofDrawBitmapString(ofToString(pct*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/2)+20);
    
    // the timer was reached :)
    if(bTimerReached) {
        ofSetColor(20);
        ofDrawBitmapString("Timer Reached!", (ofGetWidth()-100)/2, (ofGetHeight()/2)+70);
        
        bTimerReached = false;                     // reset the timer
        startTime = ofGetElapsedTimeMillis();  // get the start time
        endTime = millisPerSecond; // in milliseconds
        
        
//        if (conversionCount >0) {
//        note = 64+conversionCount;
//        velocity = 64;
//        
//        midiOut.sendNoteOn(channel, note,  velocity);
//        midiOut.sendNoteOff(channel, note,  velocity);
//        
//        }
        
        //Chord test
        for (int i = 0; i<conversionCount; i++) {
            
            note = 64+i*4;
            velocity = ofRandom(80,100);
            
            midiOut.sendNoteOn(channel, note,  velocity);
            midiOut.sendNoteOff(channel, note,  velocity);
            
        }
        
    }
    
    // some information about the timer
    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0)+"\n";
    info += "Start Time: "+ofToString(startTime, 1)+"\n";
    info += "End Time:   "+ofToString(endTime/1000.0, 1)+" seconds\n";
    info += "Timer:      "+ofToString(timer/1000.0, 1)+" seconds\n";
    info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
    ofSetColor(0);
    ofDrawBitmapString(info, 20, 20);
    
    
 gui.draw();
}
