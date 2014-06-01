#include "testApp.h"


void testApp::guiNewLight() {
    ofxUICanvas *sgui = getSecondaryGUI("newLight");

    sgui->addLabel("New Light");
    sgui->addSpacer();
    vector<string> vnames;

    vnames.push_back("Point light");
    vnames.push_back("Directional light");
    vnames.push_back("Spotlight");
    ofxUIRadio *radio = sgui->addRadio("Light Type", vnames, OFX_UI_ORIENTATION_VERTICAL);

    radio->activateToggle("Point light");
    sgui->addSpacer();
    sgui->addLabelButton("OK", false);
    sgui->addLabelButton("Cancel", false);
    sgui->autoSizeToFitWidgets();
    ofAddListener(sgui->newGUIEvent,this, &testApp::guiNewLightEvent); // this function listens to the events of the secondary GUI too
}

void testApp::guiNewLightEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "OK") { // OK, let's create a new light !
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLight");
        ofxUIRadio *radio = (ofxUIRadio *) newLightCanvas->getWidget("Light Type");
        ofLight * newLight = new ofLight();
        string selection = radio->getActiveName();
        stringstream nameStream("");

        // Set the light type according to the user's choice.
        if (selection == "Point light") {
            newLight->setPointLight();
        } else if (selection == "Directional light") {
            newLight->setDirectional();
        } else if (selection == "Spotlight") {
            newLight->setSpotlight();
        }
        lights.push_back(newLight);
        // Set the new light as the new target
        lightTarget = lights.size()-1;
        nameStream << selection << lightTarget;
        lightInfos.push_back(new LightInfo(nameStream.str()));

        // Hide the 'new light' canvas
        newLightCanvas->setVisible(false);
        // Refresh the main lights canvas.
        guiLights();
    }
    else if (name == "Cancel") { // Wait, don't create a new light after all !
        ofxUICanvas *newLightCanvas = getSecondaryGUI("newLight");
        ofxUIToggle *toggle = (ofxUIToggle *) gui->getWidget("Create new light");

        newLightCanvas->setVisible(false);
        toggle->setValue(false);
    }
}
