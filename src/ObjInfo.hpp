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
    ObjInfo(PrimType p_type, string p_name) :
    m_draw(true), m_axes(false), m_faces(false), m_wire(false), m_norms(false), m_verts(false), m_color(ofColor::red), m_type(p_type), m_name(p_name),
    m_scale(ofVec3f(1.,1.,1.))
    {}
    ~ObjInfo() {}

    void addMaterial(const ofMaterial & p_newMat);
    void addShader(const ofShader & p_newShdr);
    void setType(PrimType p_type);
    void toggleFill() { m_draw = !m_draw; }
    void toggleFaces() { m_faces = !m_faces; }
    void toggleVertices() { m_verts = !m_verts; }
    void toggleWireframe() { m_wire = !m_wire; }
    void toggleNormals() { m_norms = !m_norms; }
    void toggleAxes() { m_axes = !m_axes; }
    void setScale(float scaleX, float scaleY, float scaleZ) { m_scale = ofVec3f(scaleX, scaleY, scaleZ); }
    void setXScale(float scaleX) { m_scale[0] = scaleX; }
    void setYScale(float scaleY) { m_scale[1] = scaleY; }
    void setZScale(float scaleZ) { m_scale[2] = scaleZ; }

    inline const vector<ofMaterial> &materials() const { return m_mats; }
    inline const vector<ofShader> &shaders() const { return m_shdrs; }
    inline PrimType type() const { return m_type; }
    inline bool fill() const { return m_draw; }
    inline bool drawFaces() const { return m_faces; }
    inline bool drawVertices() const { return m_verts; }
    inline bool drawWireframe() const { return m_wire; }
    inline bool drawNormals() const { return m_norms; }
    inline bool drawAxes() const { return m_axes; }
    inline ofColor color() const { return m_color; }
    inline ofColor &color() { return m_color; }
    const inline string &name() const { return m_name; }
    inline string & name() { return m_name; }
    inline const ofVec3f &scale() const { return m_scale; }
    inline float scaleX() const { return m_scale[0]; }
    inline float scaleY() const { return m_scale[1]; }
    inline float scaleZ() const { return m_scale[2]; }

private:
    bool m_draw;
    bool m_axes;
    bool m_faces;
    bool m_wire;
    bool m_norms;
    bool m_verts;
    ofColor m_color;
    PrimType m_type;
    string m_name;
    ofVec3f m_scale;
    vector<ofMaterial> m_mats;
    vector<ofShader> m_shdrs;
};
