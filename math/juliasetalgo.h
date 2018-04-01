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

    bool findSolution(const Quaternion &startQ, const Quaternion &endQ, Quaternion &res) const
    {
        if (m_set) {
            const int maxIter = 10000;
            Quaternion delta = (endQ - startQ) / maxIter;
            res = startQ;

            for (int i = 0; i < maxIter; i++) {
                if (m_set->isInSet(res))
                    return true;
                res = res + delta;
            }
        }
        return false;
    }

public:


    bool findMinSolutionByC(const Quaternion &startQ, double cMax, Quaternion &res) const
    {
        Quaternion endQ = startQ;
        endQ.setC(cMax);
        return findSolution(startQ, endQ, res);
    }

    bool findMinSolutionByD(const Quaternion &startQ, double dMax, Quaternion &res) const
    {
        Quaternion endQ = startQ;
        endQ.setD(dMax);
        return findSolution(startQ, endQ, res);
    }

};

#endif // JULIASETALGO_H
