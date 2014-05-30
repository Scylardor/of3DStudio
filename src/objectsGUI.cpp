#include "testApp.h"

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
        vector<of3dPrimitive *>::iterator obj = objs.begin()+objTarget;
        vector<ObjInfo *>::iterator obji = objInfos.begin()+objTarget;

        delete (*obj);
        objs.erase(objs.begin()+objTarget);
        delete (*obji);
        objInfos.erase(obji);
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
