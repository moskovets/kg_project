#ifndef JULIAFUNCTIONS_H
#define JULIAFUNCTIONS_H

#include "math/basefunction.h"

//q^2 + c
class Function1 : public BaseFunction
{
private:
    Quaternion m_c;

public:
    Function1(const Quaternion &c)
        : m_c(c)
    {

    }

    // BaseFunction interface
public:
    virtual Quaternion calculate(const Quaternion &q) const
    {
        return q.squaring() + m_c;
    }
    virtual BaseFunction *clone() const
    {
        return new Function1(m_c);
    }

};

class Function2 : public BaseFunction
{
private:
    Quaternion m_c;

public:
    Function2(const Quaternion &c)
        : m_c(c)
    {

    }

    // BaseFunction interface
public:
    virtual Quaternion calculate(const Quaternion &q) const
    {
        return (q * q).inverse() + m_c;
    }
    virtual BaseFunction *clone() const
    {
        return new Function2(m_c);
    }

};



#endif // JULIAFUNCTIONS_H
