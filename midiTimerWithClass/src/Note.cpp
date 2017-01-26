#include "Note.h"
Note::Note(){
}

void Note::setup(float _startTime, float _duration, string _id){
    
    startTime = _startTime;
    duration = _duration;
    started = false;
    killAble = false;
    id = _id;
    percent = 0;
    
    /*
    x = ofRandom(0, ofGetWidth());      // give some random positioning
    y = ofRandom(0, ofGetHeight());
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
    dim = 20;
    
    color.set(ofRandom(255),ofRandom(255),ofRandom(255));
     */
}

void Note::update(){
    /*
     if(x < 0 ){
        x = 0;
        speedX *= -1;
    } else if(x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= -1;
    }
    
    if(y < 0 ){
        y = 0;
        speedY *= -1;
    } else if(y > ofGetHeight()){
        y = ofGetHeight();
        speedY *= -1;
    }
    
    x+=speedX;
    y+=speedY;
     
     */
}

void Note::draw(){
    
    /*
    ofSetColor(color);
    ofDrawCircle(x, y, dim);
     */
}


