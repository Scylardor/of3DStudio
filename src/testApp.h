#pragma once

#include "ofMain.h"

#include "ofxUI.h"

#include "ObjInfo.hpp"

class testApp : public ofBaseApp{
public:
    typedef void (testApp::*ctxtFunc)();
    typedef void (testApp::*eventFunc)(ofxUIEventArgs &e);
    typedef enum Context {
        MAIN = 0,
        BACKGROUND
    }   Context;

    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void guiChangeListener(eventFunc ListenerFunc);
    void destroySecondaryGUIs();
    void guiMain();
    void guiMainEvent(ofxUIEventArgs &e);


    void guiEvent(ofxUIEventArgs &e);


    void guiBackground();
    void guiBackgroundEvent(ofxUIEventArgs &e);


    void guiObjects();
    void guiObjectsEvent(ofxUIEventArgs &e);
    void guiMaterials();
    void guiMaterialsEvent(ofxUIEventArgs &e);

    void guiLights();
    void guiLightsEvent(ofxUIEventArgs &e);
    void guiNewLightEvent(ofxUIEventArgs &e);

    ofxUICanvas *getSecondaryGUI(const string & name);
    string getLightName(ofLight &light);

    ofxUICanvas *gui;
    vector<of3dPrimitive *> objs;
    vector<ObjInfo *> objInfos;
    vector<ofLight> lights;
    ofColor backgroundColor;
    ofEasyCam cam;
    int objTarget;
    int lightTarget;
    int matTarget;
    pair<ctxtFunc, ctxtFunc> contexts;
    eventFunc cur_event_listener;
    bool change;
    vector<ofxUICanvas *> guis;
};
