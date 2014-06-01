#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableDepthTest();

	ofSpherePrimitive *sph = new ofSpherePrimitive();
	ofLight *pointlight = new ofLight();

    sph->setGlobalPosition(50, 70, -100);
    pointlight->setPointLight();
    pointlight->setPosition(100, 100, 0);
    objs.push_back(sph);
    objInfos.push_back(new ObjInfo(SPHERE, "Sphere0"));
    objInfos[0]->color() = ofColor::cadetBlue;
    lights.push_back(pointlight);
    lightInfos.push_back(new LightInfo("Pointlight0"));
    //set some sketch parameters
    //Background Color
    backgroundColor = ofColor(233, 52, 27);
    gui = new ofxUICanvas();
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
    ofBackgroundGradient(ofColor::white, ofColor::black, OF_GRADIENT_CIRCULAR);
//	ofBackground(backgroundColor);
	cam.begin();
	ofEnableLighting();
	ofSetSmoothLighting(true);
    for (size_t j = 0; j < lights.size(); j++) {
        if (lightInfos[j]->enabled()) {
            lights[j]->enable();
        }
    }
	for (size_t i = 0; i < objs.size(); i++) {
        ofImage & objTexture = objInfos[i]->texture();

        if (objTexture.isAllocated()) {
            objTexture.getTextureReference().bind();
            objs[i]->mapTexCoordsFromTexture(objTexture.getTextureReference());
        }
        objInfos[i]->material().begin();
        ofPushStyle();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(objInfos[i]->color());
        if (objInfos[i]->drawFaces()) // draws the shape "normally"
        {
            objs[i]->drawFaces();
        }
        if (objInfos[i]->drawAxes())
        {
            objs[i]->drawAxes(100);
        }
        if (objInfos[i]->drawVertices())
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
        if (objTexture.isAllocated()) {
            objTexture.getTextureReference().unbind();
        }
	}
    for (size_t j = 0; j < lights.size(); j++) {
        if (lightInfos[j]->enabled()) {
            lights[j]->disable();
        }
    }
    ofDisableLighting();
    ofFill();
    for (size_t i = 0; i < lights.size(); i++) {
        if (lightInfos[i]->visible()) {
            ofSetColor(lights[i]->getDiffuseColor());
            lights[i]->draw();
        }
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

const string testApp::getLightName(ofLight * light) const {
    string lightName("");

    if (light->getIsPointLight()) {
        lightName = "Pointlight";
    } else if (light->getIsDirectional()) {
        lightName = "Directional";
    } else if (light->getIsSpotlight()) {
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

void testApp::showSecondaryGUI(const string & name, ctxtFunc build_gui) {
    ofxUICanvas *sgui = getSecondaryGUI(name);

    if (sgui) {
        sgui->setVisible(true);
    } else {
        sgui = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
        sgui->setName(name);
        guis.push_back(sgui);
    }
    sgui->clearWidgets();
    (this->*build_gui)();
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















