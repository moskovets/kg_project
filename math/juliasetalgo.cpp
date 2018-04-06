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

bool JuliaSetAlgo::findSolution2(const Quaternion &startQ, const Quaternion &endQ, Quaternion &res) const
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

bool JuliaSetAlgo::findSolution(const Quaternion &startQ, const Quaternion &endQ, Quaternion &res) const
{
    double eps = 0.1;
    double dMax = (endQ - startQ).length();
    Quaternion dir = (endQ - startQ).normalization();
    Quaternion q = startQ;
    while (true) {
        double dMin = m_set->dMin(q);
        q = q + dir * dMin;
        if (dMin < eps) {
            res = q;
            return true;
        }
        if ((q - startQ).length() > dMax)
            return false;
    }
}

bool JuliaSetAlgo::findMinSolutionByC(const Quaternion &startQ, double cMax, Quaternion &res) const
{
    Quaternion endQ = startQ;
    endQ.setC(cMax);
    //if(findSolution2(startQ, endQ, res))
    //    return findSolution(startQ, endQ, res);
    //else
    //    return false;
    return findSolution2(startQ, endQ, res);
}

bool JuliaSetAlgo::findMinSolutionByD(const Quaternion &startQ, double dMax, Quaternion &res) const
{
    Quaternion endQ = startQ;
    endQ.setD(dMax);
    return findSolution(startQ, endQ, res);
}
