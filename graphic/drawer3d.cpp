#include "drawer3d.h"


Vector4 Drawer3D::lightVector() const
{
    return m_camera.lightVector();
}

void Drawer3D::setLightVector(const Vector4 &lightVector)
{
    m_camera.setLightVector(lightVector.norm3());
}

Matrix4 Drawer3D::projectingMatr() const
{
    return m_projectingMatr;
}

void Drawer3D::setProjectingMatr(const Matrix4 &projectingMatr)
{
    m_projectingMatr = projectingMatr;
}

double Drawer3D::m_intensity(const Vector4 &normal) const
{
    double res = (-normal) * m_camera.lightVector();
    if(res > 0.1) {
        return res;
    }
    return 0.1;
}


/*
void Drawer3D::m_drawFlatTriangle(const Triangle &triangle, const Color &color)
{
    double dx = triangle.getVertex(0).x() > triangle.getVertex(2).x() ? 1 : -1;

    Vector4 normal = triangle.getAverageNormal();

    double inten = m_intensity(normal);
    Color c = color;
    c.setR(c.r() * inten);
    c.setG(c.g() * inten);
    c.setB(c.b() * inten);

    for(double x = (triangle.getVertex(2).x()) - 1; x * dx < (triangle.getVertex(0).x() + 1) * dx; x += dx) {
        double y02 = (interpolate((triangle.getVertex(0).x()), (triangle.getVertex(0).y()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).y()), x));
        double y12 = (interpolate((triangle.getVertex(1).x()), (triangle.getVertex(1).y()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).y()), x));
        double z02 = (interpolate((triangle.getVertex(0).x()), (triangle.getVertex(0).z()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        double z12 = (interpolate((triangle.getVertex(1).x()), (triangle.getVertex(1).z()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        for(double y = (std::min(y02, y12)) - 1; y < (std::max(y02, y12) + 1); y += 1) {
            double z = interpolate(y02, z02,
                                   y12, z12, y);
            m_frame->getBuffer()->addPixel(round(x), round(y), z, c);
        }
    }
}
*/
/*
void Drawer3D::m_drawFlatTriangle(const Triangle &triangle, const Color &color)
{
    int dx = triangle.getVertex(0).x() > triangle.getVertex(2).x() ? 1 : -1;

    Vector4 normal = triangle.getAverageNormal();

    double inten = m_intensity(normal);
    Color c = color;
    c.setR(c.r() * inten);
    c.setG(c.g() * inten);
    c.setB(c.b() * inten);

    for(int x = round(triangle.getVertex(2).x()); x * dx <= round(triangle.getVertex(0).x()) * dx; x += dx) {
        double y02 = (interpolate((triangle.getVertex(0).x()), (triangle.getVertex(0).y()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).y()), x));
        double y12 = (interpolate((triangle.getVertex(1).x()), (triangle.getVertex(1).y()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).y()), x));
        double z02 = (interpolate((triangle.getVertex(0).x()), (triangle.getVertex(0).z()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        double z12 = (interpolate((triangle.getVertex(1).x()), (triangle.getVertex(1).z()),
                                 (triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        for(uint32_t y = round(std::min(y02, y12)); y <= round(std::max(y02, y12)); y++) {
            double z = interpolate(y02, z02,
                                   y12, z12, y);
            m_frame->getBuffer()->addPixel(x, round(y), z, c);
        }
    }
}

*/
void Drawer3D::m_drawGuroTriangle(const Triangle &triangle, const Color &color)
{

    int dx = triangle.getVertex(0).x() > triangle.getVertex(2).x() ? 1 : -1;

    //Vector4 normal = triangle.getAverageNormal();


    double x0 = triangle.getVertex(0).x();
    double x1 = triangle.getVertex(1).x();
    double x2 = triangle.getVertex(2).x();
    for(int x = round(triangle.getVertex(2).x()); x * dx <= round(triangle.getVertex(0).x()) * dx; x += dx) {
        double y02 = round(interpolate(round(triangle.getVertex(0).x()), round(triangle.getVertex(0).y()),
                                 round(triangle.getVertex(2).x()), round(triangle.getVertex(2).y()), x));
        double y12 = round(interpolate(round(triangle.getVertex(1).x()), round(triangle.getVertex(1).y()),
                                 round(triangle.getVertex(2).x()), round(triangle.getVertex(2).y()), x));
        double z02 = (interpolate(round(triangle.getVertex(0).x()), (triangle.getVertex(0).z()),
                                 round(triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        double z12 = (interpolate(round(triangle.getVertex(1).x()), (triangle.getVertex(1).z()),
                                 round(triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        Vector4 n02 = interpolate(triangle.getNormal(0), triangle.getNormal(2), (x - x0) / (x2 - x0));
        Vector4 n12 = interpolate(triangle.getNormal(1), triangle.getNormal(2), (x - x1) / (x2 - x1));
        for(int32_t y = (std::min(y02, y12)); y <= (std::max(y02, y12)); y++) {
            if (y >= 0 && x >= 0)
            {
                double z = interpolate(y02, z02, y12, z12, y);
                Vector4 normal = interpolate(n02, n12, (y - y02) / (y12 - y02));

                double inten = m_intensity(normal);
                Color c =  m_camera.calculateColor(color, inten);

                m_frame->getBuffer()->addPixel(x, round(y), z, c);
            }
        }
    }
}

void Drawer3D::m_drawFlatTriangle(const Triangle &triangle, const Color &color)
{
    int dx = triangle.getVertex(0).x() > triangle.getVertex(2).x() ? 1 : -1;

    Vector4 normal = triangle.getAverageNormal();

    double inten = m_intensity(normal);
    Color c = m_camera.calculateColor(color, inten);

    for(int x = round(triangle.getVertex(2).x()); x * dx <= round(triangle.getVertex(0).x()) * dx; x += dx) {
        int y02 = round(interpolate(round(triangle.getVertex(0).x()), round(triangle.getVertex(0).y()),
                                 round(triangle.getVertex(2).x()), round(triangle.getVertex(2).y()), x));
        int y12 = round(interpolate(round(triangle.getVertex(1).x()), round(triangle.getVertex(1).y()),
                                 round(triangle.getVertex(2).x()), round(triangle.getVertex(2).y()), x));
        double z02 = (interpolate(round(triangle.getVertex(0).x()), (triangle.getVertex(0).z()),
                                 round(triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        double z12 = (interpolate(round(triangle.getVertex(1).x()), (triangle.getVertex(1).z()),
                                 round(triangle.getVertex(2).x()), (triangle.getVertex(2).z()), x));
        for(int32_t y = (std::min(y02, y12)); y <= (std::max(y02, y12)); y++) {
            if (x > 0 && y > 0)
            {
                double z = interpolate(y02, z02, y12, z12, y);
                m_frame->getBuffer()->addPixel(x, y, z, c);
            }
        }
    }
}
void Drawer3D::m_drawVerticalTriangle(const Triangle &triangle, const Color &color)
{
    switch(m_mode) {
    case DME_FLAT:
        m_drawFlatTriangle(triangle, color);
        break;
    case DME_GURO:
        m_drawGuroTriangle(triangle, color);
        break;
    }
}

void Drawer3D::m_drawTriangle(const Triangle &triangle, const Color &color)
{
    //перевод в экранные координаты
    double x[4], y[4], z[4];
    uint32_t h = m_frame->getBuffer()->height();
    uint32_t w = m_frame->getBuffer()->width();
    Triangle tr = triangle;
    tr.toScreenCoord(w, h);
    tr = tr.sortX();
    for(int i = 0; i < 3; i++) {
        Vector4 v = tr.getVertex(i);
        x[i] = v.x();
        y[i] = v.y();
        z[i] = v.z();


 /*       x[i] = (v.x() + 1) * (w / 2.);
        y[i] = (v.y() + 1) * (h / 2.);
        z[i] = v.z();
        */
//            x[i] = round((v.x()/v.w() + 1) * (w / 2.0));
//            y[i] = round((v.y()/v.w() + 1) * (h / 2.0));
//            z[i] = v.z()/v.w(); // TODO W

    }

    //порисовать
    //if (x[0] > w || x[2] < 0)
    //    return;

    if (fabs(x[1] - x[0]) < EPS_COORD) {
        //02 - 12
        Vector4 v[3] = { Vector4(x[0], y[0], z[0]),
                         Vector4(x[1], y[1], z[1]),
                         Vector4(x[2], y[2], z[2]) };
        Vector4 n[3] = { tr.getNormal(0),
                         tr.getNormal(1),
                         tr.getNormal(2) };
        Triangle tr = Triangle(v, n);
        m_drawVerticalTriangle(tr, color);
        return;
    } else if (fabs(x[2] - x[0]) < EPS_COORD) {
        //01 - 12
        Vector4 v[3] = { Vector4(x[0], y[0], z[0]),
                         Vector4(x[2], y[2], z[2]),
                         Vector4(x[1], y[1], z[1]) };
        Vector4 n[3] = { tr.getNormal(0),
                         tr.getNormal(2),
                         tr.getNormal(1) };
        Triangle tr = Triangle(v, n);
        m_drawVerticalTriangle(tr, color);
        return;
    }

    x[3] = (x[1]); // riund
    y[3] = (interpolate(x[0], y[0], x[2], y[2], x[3]));
    z[3] = interpolate(x[0], z[0], x[2], z[2], x[3]);
    Vector4 n_3 = interpolate(tr.getNormal(0), tr.getNormal(2), (x[3] - x[0]) / (x[2] - x[0]));


    {
        //01 - 03
        Vector4 v[3] = { Vector4(x[1], y[1], z[1]),
                         Vector4(x[3], y[3], z[3]),
                         Vector4(x[0], y[0], z[0]) };
        Vector4 n[3] = { tr.getNormal(1),
                         n_3,
                         tr.getNormal(0) };
        Triangle tr = Triangle(v, n);
        m_drawVerticalTriangle(tr, color);
    }

    {
        //21 - 23
        Vector4 v[3] = { Vector4(x[1], y[1], z[1]),
                         Vector4(x[3], y[3], z[3]),
                         Vector4(x[2], y[2], z[2]) };
        Vector4 n[3] = { tr.getNormal(1),
                         n_3,
                         tr.getNormal(2) };
        Triangle tr = Triangle(v, n);
        m_drawVerticalTriangle(tr, color);
    }

}

Drawer3D::Drawer3D(std::shared_ptr<FrameBuffer> &frame, DrawerModeEnum mode, const Camera &camera) :
    m_frame(frame), m_mode(mode), m_camera(camera)
{
    //m_projectingMatr = Matrix4::createPerspectiveMatrix(0.1, 1000, (double) frame->getBuffer()->width() / frame->getBuffer()->height(), M_PI_2);
    m_projectingMatr = Matrix4::createDiagMatrix(1);
}

void Drawer3D::swap()
{
    m_frame->swap();
}

void Drawer3D::setMode(DrawerModeEnum mode)
{
    m_mode = mode;
}

void Drawer3D::rotateCamera(double xAngle, double yAngle, double zAngle)
{
    m_camera.rotate(xAngle, yAngle, zAngle);
    //TODO перерисовку
}

void Drawer3D::drawModel(const Model &model)
{
    Mesh* mesh = model.mesh();
    Matrix4 moveMatr = Matrix4::createMoveMatrix(model.position());
    Matrix4 resMatr = moveMatr * m_projectingMatr;
    Color color = model.color();

    for (size_t i = 0; i < mesh->count(); i++) {
        Triangle tr = mesh->getTriangle(i);
        tr.multVertex(resMatr);
        //TODO
        if (tr.getVertex(0).w() > 0.01 && tr.getVertex(1).w() > 0.01 && tr.getVertex(2).w() > 0.01 &&
            tr.getVertex(0).z() > 0.01 && tr.getVertex(1).z() > 0.01 && tr.getVertex(2).z() > 0.01)
            m_drawTriangle(tr, color);
    }
}

DrawerModeEnum Drawer3D::mode() const
{
    return m_mode;
}

double interpolate(double x1, double y1, double x2, double y2, double x)
{
    //x - x1    y - y1
    //x2 - x1   y2 - y1
    if (fabs(x1 - x2) < EPS_VECTOR) {
        return y1;
    }
    return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}

Vector4 interpolate(const Vector4 &v1, const Vector4 &v2, double aspect)
{
    // я не бесполезен!
    if (aspect != aspect)
        return v1;

    Vector4 res;
    res.setX(v1.x() + (v2.x() - v1.x()) * aspect);
    res.setY(v1.y() + (v2.y() - v1.y()) * aspect);
    res.setZ(v1.z() + (v2.z() - v1.z()) * aspect);
    return res;
}
