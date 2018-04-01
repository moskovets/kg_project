#include "model.h"

Vector4 Model::position() const
{
    return m_position;
}

void Model::setPosition(const Vector4 &position)
{
    m_position = position;
}

Mesh *Model::mesh() const
{
    return m_mesh;
}

void Model::setMesh(Mesh *mesh)
{
    m_mesh = mesh;
}

Model::Model(Mesh *mesh, Color color, Vector4 position) :
    m_mesh(mesh), m_color(color), m_position(position)
{

}

Color Model::color() const
{
    return m_color;
}

void Model::setColor(const Color &color)
{
    m_color = color;
}
