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

class Object {
public:
    Object();
    ~Object() {}

    void addMaterial(const ofMaterial & p_newMat);
    void addShader(const ofShader & p_newShdr);
    void setType(PrimType p_type);

    inline const vector<ofMaterial> &materials() { return m_mats; }
    inline const vector<ofShader> &shaders() { return m_shdrs; }
    inline PrimType type() { return m_type; }
    inline bool axesDrawable() { return m_axes; }
    inline bool facesDrawable() { return m_axes; }
    inline bool wireframeDrawable() { return m_axes; }
    inline bool normalsDrawable() { return m_axes; }
    inline bool verticesDrawable() { return m_axes; }
    inline bool isDrawable() { return m_draw; }

private:
    PrimType m_type;
    vector<ofMaterial> m_mats;
    vector<ofShader> m_shdrs;
    bool m_draw;
    bool m_axes;
    bool m_faces;
    bool m_wire;
    bool m_norms;
    bool m_verts;
    ofColor m_color;
};
