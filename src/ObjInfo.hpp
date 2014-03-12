#pragma once
#include "ofMain.h"

typedef enum PrimitiveType {
    PLANE,
    BOX,
    CONE,
    CYLINDER,
    SPHERE,
    ICOSPHERE
}   PrimType;

class ObjInfo {
public:
    ObjInfo(PrimType p_type) :
    m_draw(true), m_axes(false), m_faces(false), m_wire(false), m_norms(false), m_verts(false), m_color(ofColor::red), m_type(p_type)
    {}
    ~ObjInfo() {}

    void addMaterial(const ofMaterial & p_newMat);
    void addShader(const ofShader & p_newShdr);
    void setType(PrimType p_type);
    ofColor &color() { return m_color; }

    inline const vector<ofMaterial> &materials() const { return m_mats; }
    inline const vector<ofShader> &shaders() const { return m_shdrs; }
    inline PrimType type() const { return m_type; }
    inline bool axesDrawable() const { return m_axes; }
    inline bool facesDrawable() const { return m_axes; }
    inline bool wireframeDrawable() const { return m_axes; }
    inline bool normalsDrawable() const { return m_axes; }
    inline bool verticesDrawable() const { return m_axes; }
    inline bool isDrawable() const { return m_draw; }
    inline ofColor color() const { return m_color; }

private:
    bool m_draw;
    bool m_axes;
    bool m_faces;
    bool m_wire;
    bool m_norms;
    bool m_verts;
    ofColor m_color;
    PrimType m_type;
    vector<ofMaterial> m_mats;
    vector<ofShader> m_shdrs;
};
