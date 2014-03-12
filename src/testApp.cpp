#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableDepthTest();

    box.set(42);
    objs.push_back(new ofSpherePrimitive());
    objs.push_back(new ofBoxPrimitive());
//    objs.push_back(new Object<ofBoxPrimitive>());
    //set some sketch parameters
    //Background Color
    backgroundColor = ofColor(233, 52, 27);

    gui = new ofxUICanvas(20, 20, 200, 200);
    gui->addLabel("Background", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addSlider("BG Red", 0, 255, backgroundColor.r);
    gui->addSlider("BG Green", 0, 255, backgroundColor.g);
    gui->addSlider("BG Blue", 0, 255, backgroundColor.b);
    gui->addSpacer();
    // Object controls
    gui->addLabel("Object color", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
//    gui->addLabel("CIRCLE CONTROL");
//    gui->addSlider("RED", 0.0, 255.0, red);
//	gui->addSlider("GREEN", 0.0, 255.0, green);
//    gui->addSlider("BLUE", 0.0, 255.0, blue);
//    gui->addSlider("ALPHA", 0.0, 255.0, alpha);
//    gui->addSlider("RADIUS", 0.0, 600.0, radius);
//	gui->addSlider("RESOLUTION", 3, 60, resolution);
//    gui->addLabelToggle("DRAW FILL", drawFill);

    gui->addSpacer();
    gui->addTextArea("TEXT AREA", "HIDE & SHOW GUI BY PRESSING 'g'. MOUSE OVER A SLIDER AND PRESS UP, DOWN, LEFT, RIGHT", OFX_UI_FONT_SMALL);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    target = 0;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(backgroundColor);
	cam.begin();
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(ofColor::blue);
    box.draw();
	ofPopStyle();
	cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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


void testApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui;
}

void testApp::guiEvent(ofxUIEventArgs &e)
{

    	string name = e.widget->getName();
	int kind = e.widget->getKind();

	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
//		red = slider->getScaledValue();
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	//	green = slider->getScaledValue();
	}
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	//	blue = slider->getScaledValue();
	}
	else if(name == "BG Red")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.r = rslider->getScaledValue();
	}
	else if(name == "BG Green")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.g = rslider->getScaledValue();
	}
	else if(name == "BG Blue")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.b = rslider->getScaledValue();
	}
	else if(name == "ALPHA")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
//		alpha = slider->getScaledValue();
	}
	else if(name == "RADIUS")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		//radius = slider->getScaledValue();
	}
	else if(name == "RESOLUTION")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	//	resolution = slider->getScaledValue();          //gets the value from the specified range, otherwise you can get a normalized value (0.0 -> 1.0);
     //   ofSetCircleResolution(resolution);
//        slider->setValue(resolution);                   //shows the int value on the slider
	}
    else if(name == "POSITION")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget;
	//	position.x = pad->getPercentValue().x*ofGetWidth();
	//	position.y = pad->getPercentValue().y*ofGetHeight();
	}
    else if (name == "THEME") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        gui->setTheme(slider->getScaledValue());
    }
}



