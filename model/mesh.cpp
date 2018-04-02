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
    if (ynum % 2 == 1)
        ynum += 1;

    Vector4 vertex[xnum][ynum + 1];
    for (unsigned x = 0; x < xnum; ++x) {
        for (unsigned y = 0; y < ynum; ++y) {
            double teta = double(x) * M_PI / xnum;
            double phi = double(y) * M_PI * 2.0 / ynum;
            vertex[x][y] = Vector4(
                        radius * sin(teta) * cos(phi),
                        radius * cos(teta),
                        radius * sin(teta) * cos(phi)
                        );
        }
        vertex[x][ynum] = vertex[x][0];
    }


    // Рисование
    for (unsigned x = 0; x < xnum - 1; ++x) {
        Vector4 ppv = vertex[x][0];
        Vector4 pv = vertex[x + 1][0];
        unsigned y = 0;
        for (unsigned y_iter = 0; ; ++y_iter) {
            if (y_iter % 2 == 0) {
                if(y >= ynum + 1)
                    break;
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
                y++;

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
    }
}
