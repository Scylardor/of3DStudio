#include "testApp.h"


void testApp::guiObjectProperties() {
    ofxUICanvas *ObjCanvas = getSecondaryGUI("ObjCanvas"); // get the GUI, or NULL if it's the first time

    if (ObjCanvas == NULL) // first time
    {
        ObjCanvas = new ofxUICanvas(gui->getGlobalCanvasWidth(), 0, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
        ObjCanvas->setName("ObjCanvas");
        guis.push_back(ObjCanvas);
        ofAddListener(ObjCanvas->newGUIEvent,this, &testApp::guiObjectPropertiesEvent); // this function listens to the events of the secondary GUI too
    }
    else { // If the new object GUI was just hidden, show it and reset widgets
        ObjCanvas->clearWidgets();
        ObjCanvas->setVisible(true);
    }
    // Initialize the object properties secondary GUI
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


void guiObjectProperties_aux(ofBoxPrimitive * box, ofxUICanvas * ObjCanvas) {
        ObjCanvas->addLabel("Box");
        ObjCanvas->addSpacer();
        ObjCanvas->addSlider("Width", 0.1, 3000.0, box->getWidth());
        ObjCanvas->addSlider("Height", 0.1, 3000.0, box->getHeight());
        ObjCanvas->addSlider("Depth", 0.1, 3000.0, box->getDepth());
        ObjCanvas->addSlider("Width Resolution", 1., 100., box->getResolutionWidth());
        ObjCanvas->addSlider("Height Resolution", 1., 100., box->getResolutionHeight());
        ObjCanvas->addSlider("Depth Resolution", 1., 100., box->getResolutionDepth());
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
