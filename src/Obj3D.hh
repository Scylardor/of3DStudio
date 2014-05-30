#ifndef OBJ_HH_INCLUDED
#define OBJ_HH_INCLUDED

#include "ofMain.h"

// An enum to specify which type of 3D primitive the object is.
// As 3DObj only keeps an of3DPrimitive pointer, we can't "remember" otherwise.
//typedef enum PrimitiveType2 {
//    PLANE,
//    BOX,
//    CONE,
//    CYLINDER,
//    SPHERE,
//    ICOSPHERE
//}   PrimType2;

class AObject {
public:
    AObject() {}
    AObject(int p_type, string p_name);
    ~AObject();

    // Setters

    inline void addShader(const ofShader & p_newShdr) {
       m_shdrs.push_back(p_newShdr);
    }

    inline void setType(int p_type) {
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

    void setMaterial(const ofMaterial &  p_mat=ofMaterial()) {
        m_mat = p_mat;
    }

    // Getters

    inline const ofMaterial &material () const {
        return m_mat;
    }

    inline ofMaterial &material() {
        return m_mat;
    }

    inline const vector<ofShader> &shaders() const {
        return m_shdrs;
    }

    inline int type() const {
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

    inline ofColor &color() {
        return m_color;
    }

    const inline string &name() const {
        return m_name;
    }

    inline string & name() {
        return m_name;
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
    int m_type;
    string m_name;
    ofVec3f m_scale;
    ofMaterial m_mat;
    vector<ofShader> m_shdrs;
};


template <class T>
class Obj3D : public AObject, public T {
public:
    Obj3D(int p_type, string p_name)
    {

    }

    ~Obj3D()
    {

    }

};


#endif // OBJ_HH_INCLUDED
