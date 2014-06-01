#include "testApp.h"

void testApp::guiLights() {
    gui->clearWidgets();
    gui->addLabel("Lights");
    gui->addSpacer();
    string lightName = getLightName(lights[lightTarget]);

    if (lights.size() > 0) {
        gui->addLabel("Current target: " + lightName, OFX_UI_FONT_SMALL);
        gui->addToggle("Invisible", !lightInfos[lightTarget]->visible());
        gui->addToggle("Enabled", lightInfos[lightTarget]->enabled());
        gui->addLabelButton("Remove this light", false);
        gui->addLabelButton("Change target", false);
    }
    gui->addLabelToggle("Create new light", false);
    gui->addSpacer();
    if (lights.size() > 0) {
        gui->addLabel("Position");
        gui->addSpacer();
        gui->addSlider("X", -3000.0, 3000.0, lights[lightTarget]->getPosition()[0]);
        gui->addSlider("Y", -3000.0, 3000.0, lights[lightTarget]->getPosition()[1]);
        gui->addSlider("Z", -3000.0, 3000.0, lights[lightTarget]->getPosition()[2]);
        gui->addSpacer();
        gui->addLabel("Diffuse Color");
        gui->addSpacer();
        gui->addSlider("Diff. Red", 0, 255, ofMap(lights[lightTarget]->getDiffuseColor()[0], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Diff. Green", 0, 255, ofMap(lights[lightTarget]->getDiffuseColor()[1], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Diff. Blue", 0, 255, ofMap(lights[lightTarget]->getDiffuseColor()[2], 0.0, 1.0, 0.0, 255.0));
        gui->addSpacer();
        gui->addLabel("Specular Color");
        gui->addSpacer();
        gui->addSlider("Spec. Red", 0, 255, ofMap(lights[lightTarget]->getSpecularColor()[0], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Spec. Green", 0, 255, ofMap(lights[lightTarget]->getSpecularColor()[1], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Spec. Blue", 0, 255, ofMap(lights[lightTarget]->getSpecularColor()[2], 0.0, 1.0, 0.0, 255.0));
        gui->addSpacer();
        gui->addLabel("Ambient Color");
        gui->addSpacer();
        gui->addSlider("Amb. Red", 0, 255, ofMap(lights[lightTarget]->getAmbientColor()[0], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Amb. Green", 0, 255, ofMap(lights[lightTarget]->getAmbientColor()[1], 0.0, 1.0, 0.0, 255.0));
        gui->addSlider("Amb. Blue", 0, 255, ofMap(lights[lightTarget]->getAmbientColor()[2], 0.0, 1.0, 0.0, 255.0));
        gui->addSpacer();
        gui->addLabelToggle("Properties", false);
        gui->addSpacer();
    }
    gui->addLabelButton("Back", false);
    gui->autoSizeToFitWidgets();
    guiChangeListener(&testApp::guiLightsEvent);
}


void testApp::guiLightsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Invisible") {
        lightInfos[lightTarget]->toggleVisibility();
    }
    else if (name == "Enabled") {
        lightInfos[lightTarget]->toggleEnable();
    }
    else if (name == "Remove this light") {
        // The if is due to a unwanted effect of hitting the button : sometimes the event is triggered twice.
        // If there is just one light left, this causes a crash. But if there's no more lights (lights.size() = 0)
        // we can avoid the crash by simply checking this value.
        if (lights.size() > 0) {
            vector<ofLight *>::iterator light = lights.begin()+lightTarget;
            vector<LightInfo *>::iterator lighti = lightInfos.begin()+lightTarget;

            delete (*lighti);
            lights.erase(light);
            lightInfos.erase(lighti);
            lightTarget = lights.size()-1;
        }
        contexts.first = NULL;
        contexts.second = &testApp::guiLights;
    }
    else if (name == "Change target") {
        lightTarget = (lightTarget + 1) % lights.size();
        guiLights();
    }
    else if (name == "Create new light") { // The button to open the "New Light" secondary GUI has been clicked
        ofxUILabelToggle * toggle = (ofxUILabelToggle *) e.widget; // get the button
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLight"); // get the GUI, or NULL if it's the first time

        hideSecondaryGUIS();
        if (toggle->getValue()) { // If the button is ON : show the GUI !
            showSecondaryGUI("newLight", &testApp::guiNewLight);
        } else { // If the button is OFF : hide the "New Light" GUI
            newLightCanvas->setVisible(false);
        }
    }
    else if (name == "X") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget]->getPosition();

        pos[0] = rslider->getValue();
        lights[lightTarget]->setPosition(pos);
    }
    else if (name == "Y") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget]->getPosition();

        pos[1] = rslider->getValue();
        lights[lightTarget]->setPosition(pos);
    }
    else if (name == "Z") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f pos = lights[lightTarget]->getPosition();

        pos[2] = rslider->getValue();
        lights[lightTarget]->setPosition(pos);
    }
    else if (name == "Diff. Red") {
        ofFloatColor liteColor = lights[lightTarget]->getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setDiffuseColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Diff. Green") {
        ofFloatColor liteColor = lights[lightTarget]->getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setDiffuseColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Diff. Blue") {
        ofFloatColor liteColor = lights[lightTarget]->getDiffuseColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setDiffuseColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Spec. Red") {
        ofFloatColor liteColor = lights[lightTarget]->getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setSpecularColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Spec. Green") {
        ofFloatColor liteColor = lights[lightTarget]->getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setSpecularColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Spec. Blue") {
        ofFloatColor liteColor = lights[lightTarget]->getSpecularColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setSpecularColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    }
    else if (name == "Amb. Red") {
        ofFloatColor liteColor = lights[lightTarget]->getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setAmbientColor(ofFloatColor(rslider->getNormalizedValue(), liteColor[1], liteColor[2]));
    }
    else if (name == "Amb. Green") {
        ofFloatColor liteColor = lights[lightTarget]->getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setAmbientColor(ofFloatColor(liteColor[0], rslider->getNormalizedValue(), liteColor[2]));
    }
    else if (name == "Amb. Blue") {
        ofFloatColor liteColor = lights[lightTarget]->getAmbientColor();
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget]->setAmbientColor(ofFloatColor(liteColor[0], liteColor[1], rslider->getNormalizedValue()));
    } else if (name == "Properties") {
        ofxUILabelToggle * button = (ofxUILabelToggle *) e.widget; // get the button

        hideSecondaryGUIS();
        if (button->getValue()) {
            showSecondaryGUI("lightProps", &testApp::guiLightProperties);
        }
    } else if (name == "Back") {
        destroySecondaryGUIs();
        contexts.second = &testApp::guiMain;
    }
}
