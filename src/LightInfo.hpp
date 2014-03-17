#pragma once

class LightInfo {
public:
    LightInfo(string name)
    : m_name(name), m_visible(true), m_enabled(true)
    {
    }

    ~LightInfo() { }


    void setName(const string & name) { m_name = name; }
    void toggleVisibility() { m_visible = !m_visible; }
    void toggleEnable() { m_enabled = !m_enabled; }

    const string & name() const { return m_name; }
    bool visible() const { return m_visible; }
    bool enabled() const { return m_enabled; }

    string m_name;
    bool m_visible;
    bool m_enabled;
};
