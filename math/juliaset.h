#ifndef JULIASET_H
#define JULIASET_H

#include "basefunction.h"

#include "float.h"

//sqrt(DBL_MAX) / 2
#define BIG_NUMBER 6.7039e+153

class JuliaSet
{
private:
    BaseFunction *m_function;
    double        m_radius;
    unsigned int  m_maxIter;

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

    double dMin(const Quaternion &h0, double alpha = 5, int maxIter = 50, double bigNumber = BIG_NUMBER) const;

};

#endif // JULIASET_H
