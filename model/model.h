#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "../graphic/color.h"

class Model
{
    Mesh   *m_mesh; //не владеет

    Color   m_color;
    Vector4 m_position;

public:
    Model(Mesh* mesh = nullptr, Color color = Color(0,255), Vector4 position = Vector4());

    Color color() const;
    void setColor(const Color &color);
    Vector4 position() const;
    void setPosition(const Vector4 &position);
    Mesh *mesh() const;
    void setMesh(Mesh *mesh);
};

#endif // MODEL_H
