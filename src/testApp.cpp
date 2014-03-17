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
    for (size_t j = 0; j < lights.size(); j++) {
        lights[j].enable();
    }
	for (size_t i = 0; i < objs.size(); i++) {
        objInfos[i]->material().begin();

        ofPushStyle();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(objInfos[i]->color());
      //  ofScale(objInfos[i]->scale()[0], objInfos[i]->scale()[1], objInfos[i]->scale()[2]);

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
        objInfos[i]->material().end();

	}
    for (size_t j = 0; j < lights.size(); j++) {
        lights[j].disable();
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

void testApp::destroySecondaryGUIs() {
    for (int i = 0; i < guis.size(); i++) {
        guis[i]->setVisible(false);
        ofRemoveListener(guis[i]->newGUIEvent,this, cur_event_listener);
        delete guis[i];
    }
    guis.clear();
}

void testApp::hideSecondaryGUIS() {
    for (int i = 0; i < guis.size(); i++) {
        guis[i]->setVisible(false);
    }
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
    if (objTarget >= 0) {
        gui->addLabel("Current target: " + objInfos[objTarget]->name(), OFX_UI_FONT_SMALL);
        gui->addLabelButton("Change target", false);
    } else {
        gui->addLabel("Current target: None", OFX_UI_FONT_SMALL);
    }
    gui->addLabelToggle("Create new object", false);
    if (objTarget >= 0) {
        gui->addLabelToggle("Remove this object", false);
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
    gui->addLabelToggle("Materials", false);
    gui->addLabelToggle("Other Properties", false);
    }
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
            // Close the materials GUI if necessary
            if (getSecondaryGUI("MatCanvas") && getSecondaryGUI("MatCanvas")->isVisible()) {
                    getSecondaryGUI("MatCanvas")->setVisible(false);
            }
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
        objTarget = (objTarget + 1) % objs.size();
        matTarget = 0;
        guiObjects();
        if (getSecondaryGUI("MatCanvas") && getSecondaryGUI("MatCanvas")->isVisible()) {
            guiMaterials();
        }
    }
    else if (name == "Remove this object") {
        ofxUILabelToggle * lblBut = (ofxUILabelToggle *)e.widget;
        ofxUICanvas *rmObjCanvas = getSecondaryGUI("rmObjCanvas"); // get the GUI, or NULL if it's the first time

        if (lblBut->getValue()) { // If the button is ON : show the GUI !
            hideSecondaryGUIS();
            if (rmObjCanvas == NULL) // first time
            {
                rmObjCanvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
                guis.push_back(rmObjCanvas);
                ofAddListener(rmObjCanvas->newGUIEvent,this, &testApp::guiObjectsEvent); // this function listens to the events of the secondary GUI too
            }
            else { // If the GUI was just hidden, show it and reset widgets
                rmObjCanvas->clearWidgets();
                rmObjCanvas->setVisible(true);
            }
            // Initialize the secondary GUI
            rmObjCanvas->setName("rmObjCanvas");
            rmObjCanvas->addLabel("Warning");
            rmObjCanvas->addSpacer();
            rmObjCanvas->addLabel("Are you sure you want to remove this object ?", OFX_UI_FONT_SMALL);
            rmObjCanvas->addSpacer();
            rmObjCanvas->addLabelButton("Yes", false);
            rmObjCanvas->addLabelButton("No", false);
            rmObjCanvas->autoSizeToFitWidgets();
        } else { // If the button is OFF : hide the GUI
            rmObjCanvas->setVisible(false);
        }
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
	}
	else if (name == "Materials") {
        ofxUILabelToggle * lblBut = (ofxUILabelToggle *)e.widget;
        ofxUICanvas *canvas = getSecondaryGUI("MatCanvas"); // get the GUI, or NULL if it's the first time

        if (lblBut->getValue()) { // If the button is ON : show the GUI !
                hideSecondaryGUIS();
            if (canvas == NULL) // first time
            {
                canvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
                canvas->setName("MatCanvas");
                guis.push_back(canvas);
                ofAddListener(canvas->newGUIEvent,this, &testApp::guiMaterialsEvent); // this function listens to the events of the secondary GUI too
            }
            else { // If the new object GUI was just hidden, show it and reset widgets
                canvas->setVisible(true);
            }
            guiMaterials();
        } else {
            canvas->setVisible(false);
        }

	}
	else if (name == "Other Properties") {
        ofxUILabelToggle * lblBut = (ofxUILabelToggle *)e.widget;
        ofxUICanvas *ObjCanvas = getSecondaryGUI("ObjCanvas"); // get the GUI, or NULL if it's the first time

        if (lblBut->getValue()) { // If the button is ON : show the GUI !
            hideSecondaryGUIS();
            guiObjectProperties();
        } else { // If the button is OFF : hide the "New object" GUI
            ObjCanvas->setVisible(false);
        }
	}
	 else if (name == "Back") {
	    destroySecondaryGUIs();
	    contexts.second = &testApp::guiMain;
	}

	// Create New Object GUI events
	//-----------------------------
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
        // Adding the new light in the vector
        if (newObj) {
            stringstream ss("");

            objs.push_back(newObj);
            ss << objs.size();
            objInfos.push_back(new ObjInfo(type, radio->getActiveName() + ss.str()));
        }
        // Set the new light as the new target
        objTarget = objs.size()-1;
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

	// Remove Object GUI events
	//-----------------------------
	else if (name == "Yes") {
        ofxUICanvas *rmObjCanvas = getSecondaryGUI("rmObjCanvas");

        objs.erase(objs.begin()+objTarget);
        objInfos.erase(objInfos.begin()+objTarget);
        if (objs.size() == 0) {
            objTarget = -1;
        } else {
            objTarget = (objTarget + 1) % objs.size();
        }
        rmObjCanvas->setVisible(false);
        guiObjects(); // refresh GUI
	}
	else if (name == "No") {
        ofxUICanvas *rmObjCanvas = getSecondaryGUI("rmObjCanvas");
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) gui->getWidget("Remove this object");

        rmObjCanvas->setVisible(false);
        toggle->setValue(false);
	}

}

void testApp::guiObjectProperties() {
    ofxUICanvas *ObjCanvas = getSecondaryGUI("ObjCanvas"); // get the GUI, or NULL if it's the first time

    if (ObjCanvas == NULL) // first time
    {
        ObjCanvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
        guis.push_back(ObjCanvas);
        ofAddListener(ObjCanvas->newGUIEvent,this, &testApp::guiObjectPropertiesEvent); // this function listens to the events of the secondary GUI too
    }
    else { // If the new object GUI was just hidden, show it and reset widgets
        ObjCanvas->clearWidgets();
        ObjCanvas->setVisible(true);
    }
    // Initialize the "New object" secondary GUI
    ObjCanvas->setName("ObjCanvas");
    switch (objInfos[objTarget]->type())
    {
    case PLANE:
    {
        ofPlanePrimitive *plane = reinterpret_cast<ofPlanePrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("Plane");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Width", 0.1, 3000.0, plane->getWidth());
        ObjCanvas->addSlider("Height", 0.1, 3000.0, plane->getHeight());
        ObjCanvas->addSlider("Columns", 1., 100., plane->getNumColumns());
        ObjCanvas->addSlider("Rows", 1., 100., plane->getNumRows());
        break;
    }
    case BOX:
    {
        ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("Box");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Width", 0.1, 3000.0, box->getWidth());
        ObjCanvas->addSlider("Height", 0.1, 3000.0, box->getHeight());
        ObjCanvas->addSlider("Depth", 0.1, 3000.0, box->getDepth());
        ObjCanvas->addSlider("Width Resolution", 1., 100., box->getResolutionWidth());
        ObjCanvas->addSlider("Height Resolution", 1., 100., box->getResolutionHeight());
        ObjCanvas->addSlider("Depth Resolution", 1., 100., box->getResolutionDepth());
        break;
    }
    case SPHERE:
    {
        ofSpherePrimitive *sphere = reinterpret_cast<ofSpherePrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("Sphere");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Radius", 1.0, 3000.0, sphere->getRadius());
        ObjCanvas->addSlider("Resolution", 1.0, 100.0, sphere->getResolution());
        break;
    }

    case CONE:
    {
        ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("Cone");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Radius", 1.0, 3000.0, cone->getRadius());
        ObjCanvas->addSlider("Height", 1.0, 3000.0, cone->getHeight());
        ObjCanvas->addSlider("Radius Resolution", 1.0, 100.0, cone->getResolutionRadius());
        ObjCanvas->addSlider("Height Resolution", 1.0, 100.0, cone->getResolutionHeight());
        ObjCanvas->addSlider("Cap Resolution", 1.0, 100.0, cone->getResolutionCap());
        break;
    }
    case CYLINDER:
    {
        ofCylinderPrimitive *cylinder = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("Cylinder");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Radius", 1.0, 3000.0, cylinder->getRadius());
        ObjCanvas->addSlider("Height", 1.0, 3000.0, cylinder->getHeight());
        ObjCanvas->addSlider("Radius Resolution", 1.0, 100.0, cylinder->getResolutionRadius());
        ObjCanvas->addSlider("Height Resolution", 1.0, 100.0, cylinder->getResolutionHeight());
        ObjCanvas->addSlider("Cap Resolution", 1.0, 100.0, cylinder->getResolutionCap());
        break;
    }
    case ICOSPHERE:
    {
        ofIcoSpherePrimitive *sphere = reinterpret_cast<ofIcoSpherePrimitive*>(objs[objTarget]);

        ObjCanvas->addLabel("IcoSphere");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Radius", 1.0, 1000.0, sphere->getRadius());
        // Here a very little window for resolution because icosphere is very consuming to render at high resolution.
        // Be safe out there. Don't blow up your system by asking a resolution 100 Icosphere.
        ObjCanvas->addSlider("Resolution", 1.0, 5.0, sphere->getResolution());
        break;
    }
    default:
        ObjCanvas->addLabel("Primitive");
        break;
    }
    ObjCanvas->autoSizeToFitWidgets();
}

void testApp::guiObjectPropertiesEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    // PLANE options
    //--------------
    if (name == "Columns")
	{
	    ofxUISlider *rslider = (ofxUISlider *) e.widget;
	    ofPlanePrimitive *plane = reinterpret_cast<ofPlanePrimitive*>(objs[objTarget]);

	    plane->setColumns(rslider->getValue());
	}
    else if (name == "Rows")
	{
	    ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofPlanePrimitive *plane = reinterpret_cast<ofPlanePrimitive*>(objs[objTarget]);

        plane->setRows(rslider->getValue());
	}

	// BOX options
	//------------
	else if (name == "Width") // This possibility is shared by both the Box and the Plane
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

        if (objInfos[objTarget]->type() == BOX) { // if it's a box
            ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

            box->setWidth(rslider->getValue());
        } else { // if it's a plane
            ofPlanePrimitive *plane = reinterpret_cast<ofPlanePrimitive*>(objs[objTarget]);

            plane->setWidth(rslider->getValue());
        }
	}
	else if (name == "Height") // This possibility is shared by both the Box, the Cone, the Cylinder and the Plane
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

        if (objInfos[objTarget]->type() == BOX) { // if it's a box
            ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

            box->setHeight(rslider->getValue());
        } else if (objInfos[objTarget]->type() == PLANE) { // if it's a plane
            ofPlanePrimitive *plane = reinterpret_cast<ofPlanePrimitive*>(objs[objTarget]);

            plane->setHeight(rslider->getValue());
        } else if (objInfos[objTarget]->type() == CONE) { // then it's a cone
            ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

            cone->setHeight(rslider->getValue());
        } else { // or a cylinder
            ofCylinderPrimitive *cyl = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

            cyl->setHeight(rslider->getValue());
        }
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
	} else if (name == "Height Resolution") // This is shared by both the Box and the Cone and the Cylinder
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;

		if (objInfos[objTarget]->type() == BOX) {
            ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

            box->setResolutionHeight(rslider->getValue());
		} else if (objInfos[objTarget]->type() == CONE) { // if it's a cone
            ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

            cone->setResolutionHeight(rslider->getValue());
		} else {
            ofCylinderPrimitive *cyl = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

            cyl->setResolutionHeight(rslider->getValue());
		}

	} else if (name == "Depth Resolution")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		ofBoxPrimitive *box = reinterpret_cast<ofBoxPrimitive*>(objs[objTarget]);

		box->setResolutionDepth(rslider->getValue());
	}

    // SPHERE options
    //--------------
    else if (name == "Radius") // This possibility is shared by both the Sphere, the Cone, the Cylinder and the IcoSphere
	{
	    ofxUISlider *rslider = (ofxUISlider *) e.widget;

        if (objInfos[objTarget]->type() == SPHERE) { // if it's a sphere
            ofSpherePrimitive *sphere = reinterpret_cast<ofSpherePrimitive*>(objs[objTarget]);

            sphere->setRadius(rslider->getValue());
        } else if (objInfos[objTarget]->type() == ICOSPHERE) { // if it's an icosphere
            ofIcoSpherePrimitive *sphere = reinterpret_cast<ofIcoSpherePrimitive*>(objs[objTarget]);

            sphere->setRadius(rslider->getValue());
        } else if (objInfos[objTarget]->type() == CONE)  { // then it's a cone !
            ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

            cone->setRadius(rslider->getValue());
        } else { // or a cylinder
            ofCylinderPrimitive *cyl = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

            cyl->setRadius(rslider->getValue());
        }
	}
    else if (name == "Resolution")
	{
	    ofxUISlider *rslider = (ofxUISlider *) e.widget;
        if (objInfos[objTarget]->type() == SPHERE) { // if it's a sphere
            ofSpherePrimitive *sphere = reinterpret_cast<ofSpherePrimitive*>(objs[objTarget]);

            sphere->setResolution(rslider->getValue());
        } else { // if it's an icosphere
            ofIcoSpherePrimitive *sphere = reinterpret_cast<ofIcoSpherePrimitive*>(objs[objTarget]);

            sphere->setResolution(rslider->getValue());
        }
	}

    // CONE options
    //-------------
    else if (name == "Radius Resolution") { // This option is shared by the cylinder
            ofxUISlider *rslider = (ofxUISlider *) e.widget;

            if (objInfos[objTarget]->type() == CONE) {
            ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

            cone->setResolutionRadius(rslider->getValue());
        } else { // Cylinder
            ofCylinderPrimitive *cyl = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

            cyl->setResolutionRadius(rslider->getValue());
        }
    } else if (name == "Cap Resolution") { // This option is shared by the cylinder
            ofxUISlider *rslider = (ofxUISlider *) e.widget;

            if (objInfos[objTarget]->type() == CONE) {
                ofConePrimitive *cone = reinterpret_cast<ofConePrimitive*>(objs[objTarget]);

                cone->setResolutionCap(rslider->getValue());
            } else { // Cylinder
                ofCylinderPrimitive *cyl = reinterpret_cast<ofCylinderPrimitive*>(objs[objTarget]);

                cyl->setResolutionCap(rslider->getValue());
            }
    }
}






void testApp::guiMaterials() {
    ofxUICanvas *canvas = getSecondaryGUI("MatCanvas"); // get the GUI, or NULL if it's the first time
    canvas->clearWidgets();
    canvas->addLabel("Material");
    canvas->addSpacer();
    canvas->addLabelToggle("Reset material", false);
    ofMaterial &mat = objInfos[objTarget]->material();

        canvas->addLabel("Diffuse Color");
        canvas->addSpacer();
        canvas->addSlider("Diff. Red", 0, 255, ofMap(mat.getDiffuseColor()[0], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Diff. Green", 0, 255, ofMap(mat.getDiffuseColor()[1], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Diff. Blue", 0, 255, ofMap(mat.getDiffuseColor()[2], 0.0, 1.0, 0.0, 255.0));
        canvas->addSpacer();
        canvas->addLabel("Specular Color");
        canvas->addSpacer();
        canvas->addSlider("Spec. Red", 0, 255, ofMap(mat.getSpecularColor()[0], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Spec. Green", 0, 255, ofMap(mat.getSpecularColor()[1], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Spec. Blue", 0, 255, ofMap(mat.getSpecularColor()[2], 0.0, 1.0, 0.0, 255.0));
        canvas->addSpacer();
        canvas->addLabel("Ambient Color");
        canvas->addSpacer();
        canvas->addSlider("Amb. Red", 0, 255, ofMap(mat.getAmbientColor()[0], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Amb. Green", 0, 255, ofMap(mat.getAmbientColor()[1], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Amb. Blue", 0, 255, ofMap(mat.getAmbientColor()[2], 0.0, 1.0, 0.0, 255.0));
        canvas->addSpacer();
        canvas->addLabel("Emissive Color");
        canvas->addSpacer();
        canvas->addSlider("Emi. Red", 0, 255, ofMap(mat.getEmissiveColor()[0], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Emi. Green", 0, 255, ofMap(mat.getEmissiveColor()[1], 0.0, 1.0, 0.0, 255.0));
        canvas->addSlider("Emi. Blue", 0, 255, ofMap(mat.getEmissiveColor()[2], 0.0, 1.0, 0.0, 255.0));
        canvas->addSpacer();
        canvas->addSlider("Shininess", 0, 255, mat.getShininess());
    canvas->autoSizeToFitWidgets();
}





void testApp::guiMaterialsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Reset material") {
        objInfos[objTarget]->resetMaterial();
        guiMaterials();
    }
    else if (name == "Diff. Red") {
        ofFloatColor matColor = objInfos[objTarget]->material().getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setDiffuseColor(ofFloatColor(rslider->getNormalizedValue(), matColor[1], matColor[2]));
    }
    else if (name == "Diff. Green") {
        ofFloatColor matColor = objInfos[objTarget]->material().getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setDiffuseColor(ofFloatColor(matColor[0], rslider->getNormalizedValue(), matColor[2]));
    }
    else if (name == "Diff. Blue") {
        ofFloatColor matColor = objInfos[objTarget]->material().getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setDiffuseColor(ofFloatColor(matColor[0], matColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Spec. Red") {
        ofFloatColor matColor = objInfos[objTarget]->material().getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setSpecularColor(ofFloatColor(rslider->getNormalizedValue(), matColor[1], matColor[2]));
    }
    else if (name == "Spec. Green") {
        ofFloatColor matColor = objInfos[objTarget]->material().getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setSpecularColor(ofFloatColor(matColor[0], rslider->getNormalizedValue(), matColor[2]));
    }
    else if (name == "Spec. Blue") {
        ofFloatColor matColor = objInfos[objTarget]->material().getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setSpecularColor(ofFloatColor(matColor[0], matColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Amb. Red") {
        ofFloatColor matColor = objInfos[objTarget]->material().getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setAmbientColor(ofFloatColor(rslider->getNormalizedValue(), matColor[1], matColor[2]));
    }
    else if (name == "Amb. Green") {
        ofFloatColor matColor = objInfos[objTarget]->material().getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setAmbientColor(ofFloatColor(matColor[0], rslider->getNormalizedValue(), matColor[2]));
    }
    else if (name == "Amb. Blue") {
        ofFloatColor matColor = objInfos[objTarget]->material().getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setAmbientColor(ofFloatColor(matColor[0], matColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Emi. Red") {
        ofFloatColor matColor = objInfos[objTarget]->material().getEmissiveColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setEmissiveColor(ofFloatColor(rslider->getNormalizedValue(), matColor[1], matColor[2]));
    }
    else if (name == "Emi. Green") {
        ofFloatColor matColor = objInfos[objTarget]->material().getEmissiveColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setEmissiveColor(ofFloatColor(matColor[0], rslider->getNormalizedValue(), matColor[2]));
    }
    else if (name == "Emi. Blue") {
        ofFloatColor matColor = objInfos[objTarget]->material().getEmissiveColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setEmissiveColor(ofFloatColor(matColor[0], matColor[1], rslider->getNormalizedValue()));
    }

    else if (name == "Shininess") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        objInfos[objTarget]->material().setShininess(rslider->getValue());
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
            newLight.setOrientation( ofVec3f(0, 90, 0) );
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
        destroySecondaryGUIs();
        contexts.second = &testApp::guiMain;
    }
}


