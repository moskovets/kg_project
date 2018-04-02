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

bool JuliaSetAlgo::findSolution(const Quaternion &startQ, const Quaternion &endQ, Quaternion &res) const
{
    if (m_set) {
        const int maxIter = 1000;
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

bool JuliaSetAlgo::findMinSolutionByC(const Quaternion &startQ, double cMax, Quaternion &res) const
{
    Quaternion endQ = startQ;
    endQ.setC(cMax);
    return findSolution(startQ, endQ, res);
}

bool JuliaSetAlgo::findMinSolutionByD(const Quaternion &startQ, double dMax, Quaternion &res) const
{
    Quaternion endQ = startQ;
    endQ.setD(dMax);
    return findSolution(startQ, endQ, res);
}
