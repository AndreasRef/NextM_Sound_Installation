#pragma once

#include "ofMain.h"
#include "Note.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
        void startTimer();
    
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
    
        int idInt = 0;
        vector<Note> notes;
    
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
    
    
};
