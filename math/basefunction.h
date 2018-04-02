#ifndef BASEFUNCTION_H
#define BASEFUNCTION_H

#include "quaternion.h"

class BaseFunction
{
public:
    virtual Quaternion    calculate(const Quaternion &q) const = 0;
    virtual BaseFunction* clone() const = 0;
    virtual ~BaseFunction()
    {}
};

#endif // BASEFUNCTION_H
