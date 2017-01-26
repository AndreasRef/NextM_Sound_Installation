#include "Note.h"
Note::Note(){
}

void Note::setup(float _startTime, float _duration, int _volume, int _id, int _brand_id){
    
    startTime = _startTime;
    duration = _duration;
    volume = _volume;
    started = false;
    killAble = false;
    id = _id;
    percent = 0;
    
    brand_id = _brand_id;
    
   
    x = ofRandom(100, ofGetWidth()-100);      // give some random positioning
    y = ofRandom(100, ofGetHeight()-100);
    
    color.set(ofRandom(255),ofRandom(255),ofRandom(255)); //Random color
    
}

void Note::update(){

}

void Note::draw(){
    float p = 1 - percent;
    
    ofSetColor(color);
    ofDrawEllipse(x,y, 2*volume*p, 2*volume*p);
}

