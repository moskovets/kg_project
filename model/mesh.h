#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include <vector>

class Mesh
{
    std::vector <Triangle> m_triangles;

public:
    void addTriangle(const Triangle &triangle);

    Triangle getTriangle(std::size_t index) const;

    std::size_t count() const;

    void addSphere(unsigned xnum, unsigned ynum, double radius); //TODO значения по умолчанию

};

#endif // MESH_H
