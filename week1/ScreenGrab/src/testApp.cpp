#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){

	finder.setup("haarcascade_frontalface_default.xml");
    w = 640;
    h = 480;
    
	image.allocate(w, h, OF_IMAGE_COLOR);
    
    maskImage.loadImage("face_mask.png");
	maskImage.setImageType(OF_IMAGE_COLOR);
    

	ofSetFrameRate(30);
    clone.setup(w,h);

    
    showLines = true;
}

//--------------------------------------------------------------
void testApp::update(){
	
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		
		unsigned char a = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = a; 
	}
	
	
	if (data!= NULL) {
		image.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		finder.findHaarObjects(image.getPixelsRef());
	}

}

//--------------------------------------------------------------
void testApp::draw(){
    ofFbo src, mask;

    
	//image.draw(0,0, ofGetWidth(), ofGetHeight());
	
	ofNoFill();
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	
    
    if(finder.blobs.size() >= 2){
        src.allocate(w,h);
        mask.allocate(w,h);
        
        
        cout << "0 w: " << finder.blobs[0].boundingRect.width << " h: " << finder.blobs[0].boundingRect.height << endl;
        cout << "1 w: " << finder.blobs[1].boundingRect.width << " h: " << finder.blobs[1].boundingRect.height << endl;
        
        
        int finalWidth = finder.blobs[1].boundingRect.width;
        int finalHeight = finder.blobs[1].boundingRect.height;
        
        if(finder.blobs[1].boundingRect.width > finder.blobs[0].boundingRect.width){
            finalWidth = finder.blobs[0].boundingRect.width;
        }
        
        if(finder.blobs[1].boundingRect.height > finder.blobs[0].boundingRect.height){
            finalHeight = finder.blobs[0].boundingRect.height;
        }
        
        
        //float xProportion = finder.blobs[1].boundingRect.width / finder.blobs[0].boundingRect.width;
        //float yProportion = finder.blobs[1].boundingRect.height / finder.blobs[0].boundingRect.height;

        

        
        src.begin();
           ofClear(0,255);        
           image.draw(finder.blobs[1].boundingRect.x - finder.blobs[0].boundingRect.x, finder.blobs[1].boundingRect.y - finder.blobs[0].boundingRect.y);
        src.end();
        
        mask.begin();
            ofClear(0, 255);
            maskImage.draw(finder.blobs[1].boundingRect.x, finder.blobs[1].boundingRect.y, finalWidth, finalHeight);
		mask.end();
        
        ofSetColor(255);
        ofNoFill();

         

        clone.setStrength(30);        
		clone.update(src.getTextureReference(), image.getTextureReference(), mask.getTextureReference());
        ofBackground(0);
        clone.draw(0,0);
        
        //src.draw(0,0);
        //mask.draw(0,0);

        
        cout << "cloned yo!" << endl; 
        
        if(showLines){
        
            ofSetColor(0,255,0);
            ofDrawBitmapString("0", finder.blobs[0].boundingRect.x, finder.blobs[0].boundingRect.y);
            ofDrawBitmapString("1", finder.blobs[1].boundingRect.x, finder.blobs[1].boundingRect.y);
            ofRect(finder.blobs[0].boundingRect);
            ofRect(finder.blobs[1].boundingRect);
            ofSetColor(255);

        }


    } else {
        image.draw(0,0);
        maskImage.draw(0,0, 100,100);
    }
    


	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    showLines = !showLines;
    cout << showLines << endl;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}