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
    m_faces(true), m_wire(false), m_verts(false), m_norms(false),
    m_axes(false), m_color(ofColor::white), m_type(p_type),
    m_name(p_name), m_scale(ofVec3f(1.,1.,1.))
    {

    }

    ~ObjInfo()
    {

    }

    void resetMaterial() {
        ofMaterial reset;

        m_mat = reset;
    }
    inline void addShader(const ofShader & p_newShdr) {
       m_shdrs.push_back(p_newShdr);
    }

    inline void setType(PrimType p_type) {
        m_type = p_type;
    }

    inline void toggleFaces() {
        m_faces = !m_faces;
    }

    inline void toggleVertices() {
        m_verts = !m_verts;
    }

    inline void toggleWireframe() {
        m_wire = !m_wire;
    }

    inline void toggleNormals() {
        m_norms = !m_norms;
    }

    inline void toggleAxes() {
        m_axes = !m_axes;
    }

    inline void setScale(float scaleX, float scaleY, float scaleZ) {
        m_scale = ofVec3f(scaleX, scaleY, scaleZ);
    }

    inline void setXScale(float scaleX) {
        m_scale[0] = scaleX;
    }

    inline void setYScale(float scaleY) {
        m_scale[1] = scaleY;
    }

    inline void setZScale(float scaleZ) {
        m_scale[2] = scaleZ;
    }

    inline const ofMaterial &material () const {
        return m_mat;
    }

    inline ofMaterial &material() {
        return m_mat;
    }

    inline const vector<ofShader> &shaders() const {
        return m_shdrs;
    }

    inline PrimType type() const {
        return m_type;
    }

    inline bool drawFaces() const {
        return m_faces;
    }

    inline bool drawVertices() const {
        return m_verts;
    }

    inline bool drawWireframe() const {
        return m_wire;
    }

    inline bool drawNormals() const {
        return m_norms;
    }

    inline bool drawAxes() const {
        return m_axes;
    }

    inline ofColor color() const {
        return m_color;
    }

    inline ofColor & color() {
        return m_color;
    }

    const inline string & name() const {
        return m_name;
    }

    inline string & name() {
        return m_name;
    }

    const inline ofImage & texture() const {
        return m_texture;
    }

    inline ofImage & texture() {
        return m_texture;
    }

    inline const ofVec3f &scale() const {
        return m_scale;
    }

    inline float scaleX() const {
        return m_scale[0];
    }

    inline float scaleY() const {
        return m_scale[1];
    }

    inline float scaleZ() const {
        return m_scale[2];
    }

private:
    bool m_faces;
    bool m_wire;
    bool m_verts;
    bool m_norms;
    bool m_axes;
    ofColor m_color;
    PrimType m_type;
    string m_name;
    ofVec3f m_scale;
    ofMaterial m_mat;
    ofImage m_texture;
    vector<ofShader> m_shdrs;
};
