#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
//           guiTabBar = new ofxUITabBar();
//
//    for(int i = 0; i < 10; i++)
//    {
//        string index = ofToString(i);
//        ofxUICanvas* gui = new ofxUICanvas();
//        gui->setName("GUI" + index);
//        gui->addLabel("GUI" + index);
//        gui->addSpacer();
//        gui->addSlider("SLIDER " + index, 0, 1.0, i/10.0);
//        gui->add2DPad("PAD " + index, ofVec2f(-1, 1), ofVec2f(-1, 1), ofVec2f(0.0, 0.0));
//        gui->autoSizeToFitWidgets();
//        ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
//        guiTabBar->addCanvas(gui);
//        guis.push_back(gui);
//    }
    ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableDepthTest();

    objs.push_back(new ofBoxPrimitive());
    objInfos.push_back(new ObjInfo(BOX, "Box1"));
    lights.push_back(ofLight());
    lights[0].setPointLight();
    lights[0].setPosition(100, 100, 0);
    //set some sketch parameters
    //Background Color
    backgroundColor = ofColor(233, 52, 27);

    gui = new ofxUICanvas();


    //guiBackground();
  //  guiMain();
    change = false;
//    gui->addLabel("Background", OFX_UI_FONT_MEDIUM);
//    gui->addSpacer();
//    gui->addSlider("BG Red", 0, 255, backgroundColor.r);
//    gui->addSlider("BG Green", 0, 255, backgroundColor.g);
//    gui->addSlider("BG Blue", 0, 255, backgroundColor.b);
//    gui->addSpacer();
//    // Object controls
//    gui->addLabel("Object Color", OFX_UI_FONT_MEDIUM);
//    gui->addSpacer();
//    gui->addSlider("RED", 0.0, 255.0, objInfos[0]->color()[0]);
//	gui->addSlider("GREEN", 0.0, 255.0, objInfos[0]->color()[1]);
//    gui->addSlider("BLUE", 0.0, 255.0, objInfos[0]->color()[2]);
//    gui->addSlider("ALPHA", 0.0, 255.0, objInfos[0]->color()[3]);
//    gui->addLabel("Object Position", OFX_UI_FONT_MEDIUM);
//    gui->addSpacer();
//    gui->addSlider("X", -2000.0, 2000.0, objs[0]->getPosition()[0]);
//	gui->addSlider("Y", -2000.0, 2000.0, objs[0]->getPosition()[1]);
//    gui->addSlider("Z", -2000.0, 2000.0, objs[0]->getPosition()[2]);
//    gui->addSlider("RADIUS", 0.0, 600.0, radius);
//	gui->addSlider("RESOLUTION", 3, 60, resolution);
//    gui->addLabelToggle("DRAW FILL", drawFill);




    contexts.first = NULL;
    contexts.second = &testApp::guiMain;
    cur_event_listener = NULL;
    target = 0;
}

//--------------------------------------------------------------
void testApp::update() {
    if (contexts.first != contexts.second) {
        cout << "yap" << endl;
        (this->*contexts.second)();
        contexts.first = contexts.second;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(backgroundColor);
	cam.begin();
	ofEnableLighting();
	ofSetSmoothLighting(true);
	lights[0].enable();
	ofPushStyle();
	ofPushMatrix();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(objInfos[target]->color());
	ofScale(objInfos[target]->scale()[0], objInfos[target]->scale()[1], objInfos[target]->scale()[2]);
	if (objInfos[target]->fill()) {
        objs[target]->draw();
	}
	if (objInfos[target]->fill()) {
        objs[target]->draw();
	}
	if (objInfos[target]->drawAxes()) {
        objs[target]->drawAxes(100);
	}
	if (objInfos[target]->drawFaces()) {
        objs[target]->drawFaces();
	}
	if (objInfos[target]->drawVertices()) {
        objs[target]->drawVertices();
	}
	if (objInfos[target]->drawWireframe()) {
        ofSetColor(0, 0, 0);
        objs[target]->drawWireframe();
	}
    if (objInfos[target]->drawNormals()) {
        ofSetColor(255, 0, 255);
        objs[target]->drawNormals(20, true);
	}
    ofPopMatrix();
	ofPopStyle();
    lights[0].disable();
    ofDisableLighting();
    ofFill();
    ofSetColor(lights[0].getDiffuseColor());
    lights[0].draw();
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


void testApp::guiChangeListener(eventFunc newListenerFunc) {
    if (cur_event_listener != NULL) {
        ofRemoveListener(gui->newGUIEvent,this, cur_event_listener);
    }
    ofAddListener(gui->newGUIEvent,this, newListenerFunc);
    cur_event_listener = newListenerFunc;
}

void testApp::guiMain() {
    gui->clearWidgets();
    gui->addLabel("Main Menu", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addLabelButton("Background", false);
    gui->addLabelButton("Objects", false);
    gui->addLabelButton("Lights", false);
    guiChangeListener(&testApp::guiMainEvent);
    gui->autoSizeToFitWidgets();
}


void testApp::guiMainEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Background") {
        contexts.second = &testApp::guiBackground;
    }
    else if (name == "Objects") {
        contexts.second = &testApp::guiObjects;
    }
}


void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();

	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		objInfos[0]->color()[0] = slider->getScaledValue();
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		objInfos[0]->color()[1] = slider->getScaledValue();
	}
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		objInfos[0]->color()[2] = slider->getScaledValue();
	}
    else if(name == "ALPHA")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        objInfos[0]->color()[3] = slider->getScaledValue();
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
    else if(name == "X")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofPoint tPos = objs[0]->getPosition();

		objs[0]->setPosition(rslider->getScaledValue(), tPos[1], tPos[2]);
	//	position.x = pad->getPercentValue().x*ofGetWidth();
	//	position.y = pad->getPercentValue().y*ofGetHeight();
	}
    else if(name == "Y")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[0]->getPosition();

		objs[0]->setPosition(tPos[0], rslider->getScaledValue(), tPos[2]);
	//	position.x = pad->getPercentValue().x*ofGetWidth();
	//	position.y = pad->getPercentValue().y*ofGetHeight();
	}
    else if(name == "Z")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[0]->getPosition();

		objs[0]->setPosition(tPos[0], tPos[1], rslider->getScaledValue());
	//	position.x = pad->getPercentValue().x*ofGetWidth();
	//	position.y = pad->getPercentValue().y*ofGetHeight();
	}
    else if (name == "THEME") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        gui->setTheme(slider->getScaledValue());
    }
}

void testApp::guiBackground() {
    gui->clearWidgets();
    gui->addLabel("Background", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addSlider("BG Red", 0, 255, backgroundColor.r);
    gui->addSlider("BG Green", 0, 255, backgroundColor.g);
    gui->addSlider("BG Blue", 0, 255, backgroundColor.b);
    gui->addSpacer();
    gui->addLabelButton("Back", false);
    gui->autoSizeToFitWidgets();
    guiChangeListener(&testApp::guiBackgroundEvent);
   // ofAddListener(gui->newGUIEvent,this,&testApp::guiBackgroundEvent);
}

void testApp::guiBackgroundEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

	if (name == "BG Red")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.r = rslider->getScaledValue();
	}
	else if (name == "BG Green")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.g = rslider->getScaledValue();
	}
	else if (name == "BG Blue")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.b = rslider->getScaledValue();
	} else if (name == "Back") {
	    contexts.second = &testApp::guiMain;
	}
}

void testApp::guiObjects() {
    gui->clearWidgets();
    gui->addLabel("Objects", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    cout << objInfos[target]->name() << endl;
    gui->addLabel("Current target: " + objInfos[target]->name(), OFX_UI_FONT_SMALL);
    gui->addLabelButton("Change target", false);
    gui->addSpacer();
    gui->addLabel("Draw");
    gui->addSpacer();
    gui->addToggle("Fill", objInfos[target]->fill());
    gui->addToggle("Faces", objInfos[target]->drawFaces());
    gui->addToggle("Vertices", objInfos[target]->drawVertices());
    gui->addToggle("Wireframe", objInfos[target]->drawWireframe());
    gui->addToggle("Normals", objInfos[target]->drawNormals());
    gui->addToggle("Axes", objInfos[target]->drawAxes());
    gui->addSpacer();
    gui->addLabel("Color");
    gui->addSpacer();
    gui->addSlider("Red", 0, 255, backgroundColor.r);
    gui->addSlider("Green", 0, 255, backgroundColor.g);
    gui->addSlider("Blue", 0, 255, backgroundColor.b);
    gui->addSpacer();
    gui->addLabel("Position");
    gui->addSpacer();
    gui->addSlider("X", -3000.0, 3000.0, objs[target]->getPosition()[0]);
	gui->addSlider("Y", -3000.0, 3000.0, objs[target]->getPosition()[1]);
    gui->addSlider("Z", -3000.0, 3000.0, objs[target]->getPosition()[2]);
    gui->addSpacer();
    switch (objInfos[target]->type()) {
    case BOX:
        {
            ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

            gui->addLabel("Box");
            gui->addSpacer();
            gui->addSlider("Width", 0.1, 3000.0, box->getWidth());
            gui->addSlider("Height", 0.1, 3000.0, box->getHeight());
            gui->addSlider("Depth", 0.1, 3000.0, box->getDepth());
            gui->addSlider("Width Resolution", 1., 100., box->getResolutionWidth());
            gui->addSlider("Height Resolution", 1., 100., box->getResolutionHeight());
            gui->addSlider("Depth Resolution", 1., 100., box->getResolutionDepth());
            break;
        }
    case SPHERE:
        gui->addLabel("Sphere");
        break;
    default:
        gui->addLabel("Primitive");
        break;
    }
//    gui->addLabel("Scaling");
//    gui->addSlider("X Scale", 0.1, 30.0, objInfos[target]->scaleX());
//	gui->addSlider("Y Scale", 0.1, 30.0, objInfos[target]->scaleY());
//    gui->addSlider("Z Scale", 0.1, 30.0, objInfos[target]->scaleZ());
    gui->addSpacer();
    gui->addLabelButton("Back", false);
    gui->autoSizeToFitWidgets();
    guiChangeListener(&testApp::guiObjectsEvent);
}


void testApp::guiObjectsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Fill") {
        objInfos[target]->toggleFill();
    }
    else if (name == "Faces")
	{
		objInfos[target]->toggleFill();
	}
	else if (name == "Vertices")
	{
		objInfos[target]->toggleVertices();
	}
	else if (name == "Wireframe")
	{
		objInfos[target]->toggleWireframe();
	}
	else if (name == "Normals")
	{
		objInfos[target]->toggleNormals();
	}
	else if (name == "Axes")
	{
		objInfos[target]->toggleAxes();
	}
	else if (name == "Red")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[target]->color()[0] = rslider->getScaledValue();
	}
	else if (name == "Green")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[target]->color()[1] = rslider->getScaledValue();
	}
	else if (name == "Blue")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[target]->color()[2] = rslider->getScaledValue();
	} else if (name == "X")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofPoint tPos = objs[target]->getPosition();

		objs[target]->setPosition(rslider->getScaledValue(), tPos[1], tPos[2]);
	} else if (name == "Y")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[target]->getPosition();

		objs[target]->setPosition(tPos[0], rslider->getScaledValue(), tPos[2]);
		cout << objs[target]->getPosition() << endl;
	} else if (name == "Z")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[target]->getPosition();

		objs[target]->setPosition(tPos[0], tPos[1], rslider->getScaledValue());
	} else if (name == "X Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[target]->setXScale(rslider->getValue());
	} else if (name == "Y Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

		objInfos[target]->setYScale(rslider->getValue());
	} else if (name == "Z Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

		objInfos[target]->setZScale(rslider->getValue());
	} else if (name == "Width")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setWidth(rslider->getValue());
	} else if (name == "Height")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setHeight(rslider->getValue());
	} else if (name == "Depth")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setDepth(rslider->getValue());
	} else if (name == "Width Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setResolutionWidth(rslider->getValue());
	} else if (name == "Height Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setResolutionHeight(rslider->getValue());
	} else if (name == "Depth Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[target]);

		box->setResolutionDepth(rslider->getValue());
	} else if (name == "Back") {
	    contexts.second = &testApp::guiMain;
	}
}
