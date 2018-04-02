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

void Mesh::addSphere(unsigned xnum, unsigned ynum, double radius)
{
    if (xnum % 2 == 1)
        xnum += 1;

    Vector4 vertex[200][200];
    for (unsigned x = 0; x < xnum; ++x) {
        for (unsigned y = 0; y < ynum - 1; ++y) {
            double teta = double(x) * M_PI / xnum;
            double phi = double(y) * M_PI * 2.0 / ynum;
            vertex[x][y] = Vector4(
                        radius * sin(teta) * cos(phi),
                        radius * cos(teta),
                        radius * sin(teta) * cos(phi)
                        );
        }
    }


    // Рисование
    for (unsigned x = 0; x < xnum - 1; ++x) {
        Vector4 ppv = vertex[x][0];
        Vector4 pv = vertex[x + 1][0];
        for (unsigned y = 0; y < ynum - 1; ++y) {
            if (y % 2 == 0) {
                Vector4 v[3] = {
                    ppv,
                    pv,
                    vertex[x][y + 1]
                };
                Vector4 n[3] = {
                    ppv.norm3(),
                    pv.norm3(),
                    vertex[x][y + 1].norm3()
                };
                ppv = pv;
                pv = vertex[x][y + 1];

                this->addTriangle(Triangle(v, n));
            } else {
                Vector4 v[3] = {
                    ppv,
                    pv,
                    vertex[x + 1][y]
                };
                Vector4 n[3] = {
                    ppv.norm3(),
                    pv.norm3(),
                    vertex[x + 1][y].norm3()
                };
                ppv = pv;
                pv = vertex[x + 1][y];

                this->addTriangle(Triangle(v, n));
            }
        }
        Vector4 v[3] = {
            ppv,
            pv,
            vertex[x][0]
        };
        Vector4 n[3] = {
            ppv.norm3(),
            pv.norm3(),
            vertex[x][0].norm3()
        };
        this->addTriangle(Triangle(v, n));
    }
}
