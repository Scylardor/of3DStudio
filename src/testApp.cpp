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
    objInfos.push_back(new ObjInfo(BOX, "Box0"));
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
    objTarget = 0;
    lightTarget = 0;
}

//--------------------------------------------------------------
void testApp::update() {
    if (contexts.first != contexts.second) {
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
	for (size_t i = 0; i < lights.size(); i++) {
        lights[i].enable();
	}
	for (size_t i = 0; i < objs.size(); i++) {
        ofPushStyle();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(objInfos[i]->color());
        ofScale(objInfos[i]->scale()[0], objInfos[i]->scale()[1], objInfos[i]->scale()[2]);
        if (objInfos[i]->drawFaces()) // draws the shape "normally"
        {
            objs[i]->drawFaces();
        }
        if (objInfos[i]->drawAxes()) // draws axes of the shape
        {
            objs[i]->drawAxes(100);
        }

        if (objInfos[i]->drawVertices()) // draw vertices of the shape
        {
            objs[i]->drawVertices();
        }
        if (objInfos[i]->drawWireframe())
        {
            ofSetColor(0, 0, 0);
            objs[i]->drawWireframe();
        }
        if (objInfos[i]->drawNormals())
        {
            ofSetColor(255, 0, 255);
            objs[i]->drawNormals(20, true);
        }
        ofPopMatrix();
        ofPopStyle();
	}
	for (size_t i = 0; i < lights.size(); i++) {
        lights[i].disable();
	}
    ofDisableLighting();
    ofFill();
    for (size_t i = 0; i < lights.size(); i++) {
        ofSetColor(lights[i].getDiffuseColor());
        lights[i].draw();
	}

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

string testApp::getLightName(ofLight &light) {
    string lightName("");

    if (light.getIsPointLight()) {
        lightName = "Pointlight";
    } else if (light.getIsDirectional()) {
        lightName = "Directional";
    } else if (light.getIsSpotlight()) {
        lightName = "Spotlight";
    }
    stringstream ss("");

    ss << lightTarget;
    lightName += ss.str();
    return lightName;
}

ofxUICanvas *testApp::getSecondaryGUI(const string & name) {
    ofxUICanvas *toFind = NULL;

    for (size_t i = 0; i < guis.size(); i++)
    {
        if (guis[i]->getName() == name)
        {
            toFind = guis[i];
            break;
        }
    }
    return toFind;
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
    } else if (name == "Lights") {
        contexts.second = &testApp::guiLights;
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
    gui->addLabel("Current target: " + objInfos[objTarget]->name(), OFX_UI_FONT_SMALL);
    gui->addLabelButton("Change target", false);
    gui->addLabelToggle("Create new object", false);
    gui->addSpacer();
    gui->addLabel("Draw");
    gui->addSpacer();
    gui->addToggle("Faces", objInfos[objTarget]->drawFaces());
    gui->addToggle("Vertices", objInfos[objTarget]->drawVertices());
    gui->addToggle("Wireframe", objInfos[objTarget]->drawWireframe());
    gui->addToggle("Normals", objInfos[objTarget]->drawNormals());
    gui->addToggle("Axes", objInfos[objTarget]->drawAxes());
    gui->addSpacer();
    gui->addLabel("Color");
    gui->addSpacer();
    gui->addSlider("Red", 0, 255, objInfos[objTarget]->color()[0]);
    gui->addSlider("Green", 0, 255, objInfos[objTarget]->color()[1]);
    gui->addSlider("Blue", 0, 255, objInfos[objTarget]->color()[2]);
    gui->addSpacer();
    gui->addLabel("Position");
    gui->addSpacer();
    gui->addSlider("X", -3000.0, 3000.0, objs[objTarget]->getPosition()[0]);
	gui->addSlider("Y", -3000.0, 3000.0, objs[objTarget]->getPosition()[1]);
    gui->addSlider("Z", -3000.0, 3000.0, objs[objTarget]->getPosition()[2]);
    gui->addSpacer();
    switch (objInfos[objTarget]->type()) {
    case PLANE:
        gui->addLabel("Plane");
        break;
    case BOX:
        {
            ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

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
    case CONE:
        gui->addLabel("Cone");
        break;
    case CYLINDER:
        gui->addLabel("Cylinder");
        break;
    case ICOSPHERE:
        gui->addLabel("IcoSphere");
        break;
    default:
        gui->addLabel("Primitive");
        break;
    }
//    gui->addLabel("Scaling");
//    gui->addSlider("X Scale", 0.1, 30.0, objInfos[objTarget]->scaleX());
//	gui->addSlider("Y Scale", 0.1, 30.0, objInfos[objTarget]->scaleY());
//    gui->addSlider("Z Scale", 0.1, 30.0, objInfos[objTarget]->scaleZ());
    gui->addSpacer();
    gui->addLabelButton("Back", false);
    gui->autoSizeToFitWidgets();
    guiChangeListener(&testApp::guiObjectsEvent);
}

void testApp::guiObjectsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Create new object") {
        ofxUILabelToggle * lblBut = (ofxUILabelToggle *)e.widget;
        ofxUICanvas *newObjCanvas = getSecondaryGUI("newObjCanvas"); // get the GUI, or NULL if it's the first time

        if (lblBut->getValue()) { // If the button is ON : show the GUI !
            if (newObjCanvas == NULL) // first time
            {
                newObjCanvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
                guis.push_back(newObjCanvas);
                ofAddListener(newObjCanvas->newGUIEvent,this, &testApp::guiObjectsEvent); // this function listens to the events of the secondary GUI too
            }
            else { // If the new object GUI was just hidden, show it and reset widgets
                newObjCanvas->clearWidgets();
                newObjCanvas->setVisible(true);
            }
            // Initialize the "New object" secondary GUI
            newObjCanvas->setName("newObjCanvas");
            newObjCanvas->addLabel("New Object");
            newObjCanvas->addSpacer();
            vector<string> vnames;

            vnames.push_back("Plane");
            vnames.push_back("Box");
            vnames.push_back("Sphere");
            vnames.push_back("Cone");
            vnames.push_back("Cylinder");
            vnames.push_back("IcoSphere");
            ofxUIRadio *radio = newObjCanvas->addRadio("Object Type", vnames, OFX_UI_ORIENTATION_VERTICAL);

            radio->activateToggle("Plane");
            newObjCanvas->addSpacer();
            newObjCanvas->addLabelButton("OK", false);
            newObjCanvas->addLabelButton("Cancel", false);
            newObjCanvas->autoSizeToFitWidgets();
        } else { // If the button is OFF : hide the "New object" GUI
            newObjCanvas->setVisible(false);
        }
    }
    else if (name == "Change target") {
        cout << "old target: " << objTarget << endl;
        objTarget = (objTarget + 1) % objs.size();
        cout << "size: " << objs.size() << " total: " << objTarget << endl;
        guiObjects();
    }
    else if (name == "OK")
	{
	    ofxUICanvas *newObjCanvas = getSecondaryGUI("newObjCanvas");
        ofxUIRadio *radio = (ofxUIRadio *) newObjCanvas->getWidget("Object Type");
        ofxUILabelToggle * lblBut = (ofxUILabelToggle *)e.widget;
        of3dPrimitive *newObj = NULL;
        PrimitiveType type;
        string typeName;

        if (radio) {
            typeName = radio->getActiveName();
        } else {
            cerr << "guiObjectsEvent::ERROR: Object Type radio button is NULL" << endl;
        }
        // Set the object type according to the user's choice.
        if (typeName == "Plane") {
            newObj = new ofPlanePrimitive();
            type = PLANE;
        } else if (typeName == "Box") {
            newObj = new ofBoxPrimitive();
            type = BOX;
        } else if (typeName == "Sphere") {
            newObj = new ofSpherePrimitive();
            type = SPHERE;
        } else if (typeName == "Cone") {
            newObj = new ofConePrimitive();
            type = CONE;
        } else if (typeName == "Cylinder") {
            newObj = new ofCylinderPrimitive();
            type = CYLINDER;
        } else if (typeName == "IcoSphere") {
            newObj = new ofIcoSpherePrimitive();
            type = ICOSPHERE;
        }
        // Getting all the positions
//        vector<ofVec3f> positions;
//        for (int i = 0; i < lights.size(); i++) {
//            positions.push_back(lights[i].getPosition());
//        }
        // Adding the new light in the vector
        if (newObj) {
            stringstream ss("");

            objs.push_back(newObj);
            ss << objs.size();
            objInfos.push_back(new ObjInfo(type, radio->getActiveName() + ss.str()));
        }
//        lights.push_back(newLight);
//        // Restoring the old positions. (Adding a new light resets all positions to (0,0,0) )
//        for (int i = 0; i < positions.size(); i++) {
//            lights[i].setPosition(positions[i]);
//        }
        // Set the new light as the new target
        objTarget = objs.size()-1;
        cout << objTarget << endl;
        // Hide the 'new light' canvas
        newObjCanvas->setVisible(false);
        // Refresh the main canvas.
        guiObjects();
	}
    else if (name == "Cancel")
	{
        ofxUICanvas *newObjCanvas = getSecondaryGUI("newObjCanvas");
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) gui->getWidget("Create new object");

        newObjCanvas->setVisible(false);
        toggle->setValue(false);
	}
    else if (name == "Faces")
	{
		objInfos[objTarget]->toggleFaces();
	}
	else if (name == "Vertices")
	{
		objInfos[objTarget]->toggleVertices();
	}
	else if (name == "Wireframe")
	{
		objInfos[objTarget]->toggleWireframe();
	}
	else if (name == "Normals")
	{
		objInfos[objTarget]->toggleNormals();
	}
	else if (name == "Axes")
	{
		objInfos[objTarget]->toggleAxes();
	}
	else if (name == "Red")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[objTarget]->color()[0] = rslider->getScaledValue();
	}
	else if (name == "Green")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[objTarget]->color()[1] = rslider->getScaledValue();
	}
	else if (name == "Blue")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		objInfos[objTarget]->color()[2] = rslider->getScaledValue();
	} else if (name == "X")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofPoint tPos = objs[objTarget]->getPosition();

		objs[objTarget]->setPosition(rslider->getScaledValue(), tPos[1], tPos[2]);
	} else if (name == "Y")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[objTarget]->getPosition();

		objs[objTarget]->setPosition(tPos[0], rslider->getScaledValue(), tPos[2]);
	} else if (name == "Z")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPoint tPos = objs[objTarget]->getPosition();

		objs[objTarget]->setPosition(tPos[0], tPos[1], rslider->getScaledValue());
	} else if (name == "X Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->setXScale(rslider->getValue());
	} else if (name == "Y Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

		objInfos[objTarget]->setYScale(rslider->getValue());
	} else if (name == "Z Scale")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

		objInfos[objTarget]->setZScale(rslider->getValue());
	} else if (name == "Width")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setWidth(rslider->getValue());
	} else if (name == "Height")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setHeight(rslider->getValue());
	} else if (name == "Depth")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setDepth(rslider->getValue());
	} else if (name == "Width Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setResolutionWidth(rslider->getValue());
	} else if (name == "Height Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setResolutionHeight(rslider->getValue());
	} else if (name == "Depth Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setResolutionDepth(rslider->getValue());
	} else if (name == "Back") {
	    contexts.second = &testApp::guiMain;
	}
}


void testApp::guiLights() {
    gui->clearWidgets();
    gui->addLabel("Lights");
    gui->addSpacer();
    string lightName = getLightName(lights[lightTarget]);

    gui->addLabel("Current target: " + lightName, OFX_UI_FONT_SMALL);
    gui->addLabelButton("Change target", false);
    gui->addToggle("Create new light", false);
    gui->addSpacer();
    gui->addLabel("Position");
    gui->addSpacer();
    gui->addSlider("X", -3000.0, 3000.0, lights[lightTarget].getPosition()[0]);
	gui->addSlider("Y", -3000.0, 3000.0, lights[lightTarget].getPosition()[1]);
    gui->addSlider("Z", -3000.0, 3000.0, lights[lightTarget].getPosition()[2]);
    gui->addSpacer();
    gui->addLabel("Diffuse Color");
    gui->addSpacer();
    gui->addSlider("Diff. Red", 0, 255, ofMap(lights[lightTarget].getDiffuseColor()[0], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Diff. Green", 0, 255, ofMap(lights[lightTarget].getDiffuseColor()[1], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Diff. Blue", 0, 255, ofMap(lights[lightTarget].getDiffuseColor()[2], 0.0, 1.0, 0.0, 255.0));
    gui->addSpacer();
    gui->addLabel("Specular Color");
    gui->addSpacer();
    gui->addSlider("Spec. Red", 0, 255, ofMap(lights[lightTarget].getSpecularColor()[0], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Spec. Green", 0, 255, ofMap(lights[lightTarget].getSpecularColor()[1], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Spec. Blue", 0, 255, ofMap(lights[lightTarget].getSpecularColor()[2], 0.0, 1.0, 0.0, 255.0));
    gui->addSpacer();
    gui->addLabel("Ambient Color");
    gui->addSpacer();
    gui->addSlider("Amb. Red", 0, 255, ofMap(lights[lightTarget].getAmbientColor()[0], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Amb. Green", 0, 255, ofMap(lights[lightTarget].getAmbientColor()[1], 0.0, 1.0, 0.0, 255.0));
    gui->addSlider("Amb. Blue", 0, 255, ofMap(lights[lightTarget].getAmbientColor()[2], 0.0, 1.0, 0.0, 255.0));
    gui->addSpacer();
    gui->addLabelButton("Back", false);
    gui->autoSizeToFitWidgets();
    guiChangeListener(&testApp::guiLightsEvent);
}

void testApp::guiLightsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Change target") {
        lightTarget = (lightTarget + 1) % lights.size();
        guiLights();
    }
    if (name == "Create new light") { // The button to open the "New Light" secondary GUI has been clicked
        ofxUIToggle * toggle = (ofxUIToggle *) e.widget; // get the button
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLightCanvas"); // get the GUI, or NULL if it's the first time

        if (toggle->getValue()) { // If the button is ON : show the GUI !
            if (newLightCanvas == NULL) // first time
            {
                newLightCanvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
                guis.push_back(newLightCanvas);
                ofAddListener(newLightCanvas->newGUIEvent,this, &testApp::guiLightsEvent); // this function listens to the events of the secondary GUI too
            }
            else { // If the new light GUI was just hidden, show it and reset widgets
                newLightCanvas->clearWidgets();
                newLightCanvas->setVisible(true);
            }
            // Initialize the "New Light" secondary GUI
            newLightCanvas->setName("newLightCanvas");
            newLightCanvas->addLabel("New Light");
            newLightCanvas->addSpacer();
            vector<string> vnames;

            vnames.push_back("Point light");
            vnames.push_back("Directional light");
            vnames.push_back("Spotlight");
            ofxUIRadio *radio = newLightCanvas->addRadio("Light Type", vnames, OFX_UI_ORIENTATION_VERTICAL);

            radio->activateToggle("Point light");
            newLightCanvas->addSpacer();
            newLightCanvas->addLabelButton("OK", false);
            newLightCanvas->addLabelButton("Cancel", false);
            newLightCanvas->autoSizeToFitWidgets();
        } else { // If the button is OFF : hide the "New Light" GUI
            newLightCanvas->setVisible(false);
        }
    }
    else if (name == "OK") { // OK, let's create a new light !
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLightCanvas");
        ofxUIRadio *radio = (ofxUIRadio *) newLightCanvas->getWidget("Light Type");
        ofxUIToggle *toggle = (ofxUIToggle *) gui->getWidget("Create new light");
        ofLight newLight;
        // Set the light type according to the user's choice.
        if (radio->getActiveName() == "Point light") {
            newLight.setPointLight();
        } else if (radio->getActiveName() == "Directional light") {
            newLight.setDirectional();
        } else if (radio->getActiveName() == "Spotlight") {
            newLight.setSpotlight();
        }
        // Getting all the positions
        vector<ofVec3f> positions;
        for (int i = 0; i < lights.size(); i++) {
            positions.push_back(lights[i].getPosition());
        }
        // Adding the new light in the vector
        lights.push_back(newLight);
        // Restoring the old positions. (Adding a new light resets all positions to (0,0,0) )
        for (int i = 0; i < positions.size(); i++) {
            lights[i].setPosition(positions[i]);
        }
        // Set the new light as the new target
        lightTarget = lights.size()-1;
        // Hide the 'new light' canvas
        newLightCanvas->setVisible(false);
        // Refresh the main lights canvas.
        guiLights();
    }
    else if (name == "Cancel") { // Wait, don't create a new light after all !
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLightCanvas");
        ofxUIToggle *toggle = (ofxUIToggle *) gui->getWidget("Create new light");

        newLightCanvas->setVisible(false);
        toggle->setValue(false);
    }
    else if (name == "X") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget].getPosition();

        pos[0] = rslider->getValue();
        lights[lightTarget].setPosition(pos);
    }
    else if (name == "Y") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget].getPosition();

        pos[1] = rslider->getValue();
        lights[lightTarget].setPosition(pos);
    }
    else if (name == "Z") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget].getPosition();

        pos[2] = rslider->getValue();
        lights[lightTarget].setPosition(pos);
    }
    else if (name == "Diff. Red") {
        ofFloatColor liteColor = lights[lightTarget].getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setDiffuseColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Diff. Green") {
        ofFloatColor liteColor = lights[lightTarget].getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setDiffuseColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Diff. Blue") {
        ofFloatColor liteColor = lights[lightTarget].getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setDiffuseColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Spec. Red") {
        ofFloatColor liteColor = lights[lightTarget].getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setSpecularColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Spec. Green") {
        ofFloatColor liteColor = lights[lightTarget].getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setSpecularColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Spec. Blue") {
        ofFloatColor liteColor = lights[lightTarget].getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setSpecularColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Amb. Red") {
        ofFloatColor liteColor = lights[lightTarget].getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAmbientColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Amb. Green") {
        ofFloatColor liteColor = lights[lightTarget].getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAmbientColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Amb. Blue") {
        ofFloatColor liteColor = lights[lightTarget].getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAmbientColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    } else if (name == "Back") {
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLightCanvas");
        contexts.second = &testApp::guiMain;
        if (newLightCanvas) {
            newLightCanvas->setVisible(false);
            ofRemoveListener(newLightCanvas->newGUIEvent,this, &testApp::guiLightsEvent);
            delete newLightCanvas;
            guis.pop_back();
        }
    }
}


