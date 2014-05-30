#include "testApp.h"

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
