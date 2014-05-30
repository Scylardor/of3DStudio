#include "testApp.h"

void testApp::guiLightProperties() {
    ofxUICanvas *sgui = getSecondaryGUI("lightProps");

    sgui->addLabel("Properties");
    sgui->addSpacer();
    sgui->addLabel("Attenuation");
    sgui->addSpacer();
    sgui->addSlider("Constant", 0., 1., lights[lightTarget].getAttenuationConstant());
    sgui->addSlider("Linear", 0., 1., lights[lightTarget].getAttenuationLinear());
    sgui->addSlider("Quadratic", 0., 1., lights[lightTarget].getAttenuationQuadratic());
    if (lights[lightTarget].getIsSpotlight() || lights[lightTarget].getIsDirectional()) {
        sgui->addSpacer();
        sgui->addLabel("Orientation");
        sgui->addSpacer();
        sgui->addSlider("Angle X", -360., 360., lights[lightTarget].getOrientationEuler()[0]);
        sgui->addSlider("Angle Y", -360., 360., lights[lightTarget].getOrientationEuler()[1]);
        sgui->addSlider("Angle Z", -360., 360., lights[lightTarget].getOrientationEuler()[2]);
    }
    if (lights[lightTarget].getIsSpotlight()) {
        sgui->addSpacer();
        sgui->addLabel("Spotlight");
        sgui->addSpacer();
        sgui->addSlider("Concentration", 0., 360., lights[lightTarget].getSpotConcentration());
        sgui->addSlider("Cut-Off", 0., 360., lights[lightTarget].getSpotlightCutOff());
    }
    sgui->autoSizeToFitWidgets();
    ofAddListener(sgui->newGUIEvent,this, &testApp::guiLightPropsEvent); // this function listens to the events of the secondary GUI too
}

void testApp::guiLightPropsEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();

    if (name == "Constant") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAttenuation(rslider->getValue(), lights[lightTarget].getAttenuationLinear(), lights[lightTarget].getAttenuationQuadratic());
    }
    else if (name == "Linear") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAttenuation(lights[lightTarget].getAttenuationConstant(), rslider->getValue(), lights[lightTarget].getAttenuationQuadratic());

    }
    else if (name == "Quadratic") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setAttenuation(lights[lightTarget].getAttenuationConstant(), lights[lightTarget].getAttenuationLinear(), rslider->getValue());
    }
    else if (name == "Angle X") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f o(rslider->getValue(), lights[lightTarget].getOrientationEuler()[1], lights[lightTarget].getOrientationEuler()[2]);

        lights[lightTarget].setOrientation(o);

    }
    else if (name == "Angle Y") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f o(lights[lightTarget].getOrientationEuler()[0], rslider->getValue(), lights[lightTarget].getOrientationEuler()[2]);

        lights[lightTarget].setOrientation(o);
    }
    else if (name == "Angle Z") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;
        ofVec3f o(lights[lightTarget].getOrientationEuler()[0], lights[lightTarget].getOrientationEuler()[1], rslider->getValue());

        lights[lightTarget].setOrientation(o);
    }
    else if (name == "Concentration") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setSpotConcentration(rslider->getValue());
    }
    else if (name == "Cut-Off") {
        ofxUISlider *rslider = (ofxUISlider *) e.widget;

        lights[lightTarget].setSpotlightCutOff(rslider->getValue());
    }
}
