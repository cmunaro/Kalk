#include "functionresult.h"

FunctionResult::FunctionResult(const std::vector<std::pair<double, double>> v) : Result(), points(v.begin(), v.end()) {}

FunctionResult::FunctionResult(const FunctionResult& f) : Result(), points(f.points) {}

FunctionResult& FunctionResult::operator =(const FunctionResult& f)
{
    if(this != &f) {
        points = std::vector<std::pair<double, double>>(f.points.begin(), f.points.end());
    }
    return *this;
}

FunctionResult::operator double() const
{
    double s = 0;
    for (auto i = points.begin(); i != points.end(); ++i)
        s += i->second;
    s /= points.size();
    return s;
}

std::vector<std::pair<double, double>> FunctionResult::getPoints() const
{
    return points;
}

void FunctionResult::stampa() const
{
    std::cout << "X\tY" << std::endl;
    for(unsigned int i = 0; i < points.size(); i++){
        std::cout << points[i].first << "\t";
        std::cout << points[i].second << "\t";
        std::cout << std::endl;
    }
}

