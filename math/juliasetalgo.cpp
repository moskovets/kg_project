#include "juliasetalgo.h"

JuliaSetAlgo::JuliaSetAlgo(JuliaSet *set)
    : m_set(set)
{

}

JuliaSetAlgo::~JuliaSetAlgo()
{
    m_set = nullptr;
}

void JuliaSetAlgo::setSet(JuliaSet *set)
{
    m_set = set;
}
