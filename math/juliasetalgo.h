#ifndef JULIASETALGO_H
#define JULIASETALGO_H

#include "juliaset.h"

class JuliaSetAlgo
{
    JuliaSet *m_set;

public:
    JuliaSetAlgo(JuliaSet *set = nullptr);

    virtual ~JuliaSetAlgo();

    void setSet(JuliaSet *set = nullptr);

private:

    bool findSolution(const Quaternion &startQ, const Quaternion &endQ, Quaternion &res) const;

public:


    bool findMinSolutionByC(const Quaternion &startQ, double cMax, Quaternion &res) const;

    bool findMinSolutionByD(const Quaternion &startQ, double dMax, Quaternion &res) const;

};

#endif // JULIASETALGO_H
