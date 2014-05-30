#include "testApp.h"

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
