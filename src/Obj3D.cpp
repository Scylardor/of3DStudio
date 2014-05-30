#include "Obj3D.hh"

AObject::AObject(int p_type, string p_name)
:   m_faces(true), m_wire(false), m_verts(false),
    m_norms(false), m_axes(false), m_color(ofColor::white),
    m_type(p_type), m_name(p_name), m_scale(ofVec3f(1.,1.,1.))
{

}

AObject::~AObject()
{

}
