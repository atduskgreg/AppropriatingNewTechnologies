#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Clone.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofImage		image, maskImage, jack;
		ofxCvHaarFinder jackFinder, vidFinder;	 // object used to detect haar features

        ofVideoGrabber cam;
    
        int w;
        int h;

    bool showLines;
    
        Clone clone;

};
