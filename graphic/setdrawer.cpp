#include "setdrawer.h"


SetDrawer::SetDrawer(uint32_t h, uint32_t w, unsigned xnum, unsigned ynum, double radius, const Light &light, const Color &fonColor)
{
    std::shared_ptr<FrameBuffer> frame(new FrameBuffer(h, w, fonColor));
    m_drawer = new Drawer3D(frame, DME_GURO, light);
    m_render = new Render(frame);
    m_mesh = new Mesh();
    m_mesh->addSphere(xnum, ynum, radius);
    m_mesh->deleteUnvisibleTriangles();
    m_model.setMesh(m_mesh);
}

SetDrawer::~SetDrawer()
{
    delete m_mesh;
    delete m_render;
    delete m_drawer;

    m_mesh = nullptr;
    m_render = nullptr;
    m_drawer = nullptr;
}

void SetDrawer::rotateLight(double xAngle, double yAngle, double zAngle)
{
    m_drawer->rotateLight(xAngle, yAngle, zAngle);
}

void SetDrawer::setPixel(const Vector4 &position, const Color &color)
{
    m_model.setColor(color);
    m_model.setPosition(position);

    m_drawer->drawModel(m_model);
}

QImage SetDrawer::getImage()
{
    m_drawer->swap();
    return m_render->getImage();
}
