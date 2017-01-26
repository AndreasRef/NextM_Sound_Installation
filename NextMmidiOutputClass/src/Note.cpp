#include "Note.h"
Note::Note(){
}

void Note::setup(float _startTime, float _duration, int _id){
    
    startTime = _startTime;
    duration = _duration;
    started = false;
    killAble = false;
    id = _id;
    percent = 0;
    
   
    x = ofRandom(100, ofGetWidth()-100);      // give some random positioning
    y = ofRandom(100, ofGetHeight()-100);
    
    color.set(ofRandom(255),ofRandom(255),ofRandom(255));
    
     /*
     speedX = ofRandom(-1, 1);           // and random speed and direction
     speedY = ofRandom(-1, 1);
     
     dim = 20;
     
     color.set(ofRandom(255),ofRandom(255),ofRandom(255));
     */
}

void Note::update(){

}

void Note::draw(){
    float p = 1 - percent;
    
    ofSetColor(color);
    ofDrawEllipse(x,y, 100*p, 100*p);
}

