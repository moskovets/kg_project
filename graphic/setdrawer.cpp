#include "setdrawer.h"


SetDrawer::SetDrawer(uint32_t h, uint32_t w, unsigned xnum, unsigned ynum, double radius, Vector4 lightVector)
{
    std::shared_ptr<FrameBuffer> frame(new FrameBuffer(h, w));
    m_drawer = new Drawer3D(frame, DME_GURO, lightVector);
    m_render = new Render(frame);
    m_mesh = new Mesh();
    m_mesh->addSphere(xnum, ynum, radius);
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
