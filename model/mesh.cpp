#include "mesh.h"


void Mesh::addTriangle(const Triangle &triangle)
{
    m_triangles.push_back(triangle);
}

Triangle Mesh::getTriangle(std::size_t index) const
{
    std::size_t s = count();
    return m_triangles[index < s ? index : s - 1];
}

std::size_t Mesh::count() const
{
    return m_triangles.size();
}
