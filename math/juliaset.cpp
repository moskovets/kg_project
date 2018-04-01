#include "juliaset.h"

const BaseFunction *JuliaSet::function() const
{
    return m_function;
}

unsigned int JuliaSet::maxIter() const
{
    return m_maxIter;
}

double JuliaSet::radius() const
{
    return m_radius;
}

JuliaSet::JuliaSet(BaseFunction *f, double r, unsigned int max_iter) :
    m_function(f), m_radius(r), m_maxIter(max_iter)
{
    if (!m_function) {
        throw "error: function is null";
    }
}

JuliaSet::JuliaSet(const JuliaSet &set)
{
    m_radius   = set.m_radius;
    m_maxIter  = set.m_maxIter;
    m_function = set.m_function->clone();
}

JuliaSet::JuliaSet(JuliaSet &&set)
{
    m_radius   = set.m_radius;
    m_maxIter  = set.m_maxIter;
    m_function = set.m_function;

    set.m_function = nullptr;
    set.m_radius   = 0;
    set.m_maxIter  = 0;
}

JuliaSet &JuliaSet::operator =(const JuliaSet &set)
{
    if (this != &set) {
        m_radius   = set.m_radius;
        m_maxIter  = set.m_maxIter;
        m_function = set.m_function->clone();
    }
    return *this;
}

JuliaSet &JuliaSet::operator =(JuliaSet &&set)
{
    m_radius   = set.m_radius;
    m_maxIter  = set.m_maxIter;
    m_function = set.m_function;

    set.m_function = nullptr;
    set.m_radius   = 0;
    set.m_maxIter  = 0;
    return *this;
}

JuliaSet::~JuliaSet()
{
    delete m_function;
    m_function = nullptr;
}

bool JuliaSet::isInSet(const Quaternion &q) const
{
    bool resFlag = true;
    Quaternion next;
    Quaternion curr = q;
    unsigned int iter = 0;

    while (resFlag && iter < m_maxIter) {
        double len = curr.length();
        next = m_function->calculate(curr);
        iter++;
        if (len > m_radius)
            resFlag = false;
        else
            curr = next;
    }

    return resFlag;
}
/*
bool JuliaSet::isInSet(const Quaternion &q) const
{
    bool resFlag = true;
    Quaternion next;
    Quaternion curr = q;
    unsigned int iter = 0;

    while (resFlag && iter < m_maxIter) {
        double len = curr.length();
        next = m_function->calculate(curr);
        iter++;
        if (len > m_radius)
            resFlag = false;
        else
            curr = next;
    }

    return resFlag;
}

 * */
