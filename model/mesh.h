#ifndef MESH_H
#define MESH_H

#include "triangle.h"
#include <vector>
#include <iostream>

class Mesh
{
    std::vector <Triangle> m_triangles;

public:
    void addTriangle(const Triangle &triangle);

    Triangle getTriangle(std::size_t index) const;

    std::size_t count() const;

    void addSphere(unsigned xnum, unsigned ynum, double radius); //TODO значения по умолчанию

    void deleteUnvisibleTriangles();

    std::ostream& operator <<(std::ostream &os) const;
};

#endif // MESH_H
