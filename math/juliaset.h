#ifndef JULIASET_H
#define JULIASET_H

#include "basefunction.h"

class JuliaSet
{
private:
    double        m_radius;
    unsigned int  m_maxIter;
    BaseFunction *m_function;

public:
    JuliaSet(BaseFunction *f, double r = 1000, unsigned int max_iter = 50);

    JuliaSet(const JuliaSet &set);

    JuliaSet(JuliaSet &&set);

    JuliaSet& operator =(const JuliaSet &set);

    JuliaSet& operator =(JuliaSet &&set);

    virtual ~JuliaSet();

    bool isInSet(const Quaternion &q) const;

    const BaseFunction *function() const;
    unsigned int maxIter() const;
    double radius() const;
};

#endif // JULIASET_H
