#include "logicalresult.h"

LogicalResult::LogicalResult(const std::vector<std::vector<bool>>& matrix, const std::vector<char>& c) : Result(), matrix(matrix), columns(c)
{
}

LogicalResult::LogicalResult(const LogicalResult& l) : Result(), columns(l.columns)
{
    for (unsigned int i = 0; i < l.matrix.size(); i++) {
        matrix.push_back(std::vector<bool>());
        for(unsigned int j = 0; j < l.matrix[i].size(); ++j)
            matrix[i].push_back(l.matrix[i][j]);
    }
}

LogicalResult& LogicalResult::operator =(const LogicalResult& l)
{
    if(this != &l) {
        for (auto i = l.columns.begin(); i != l.columns.end(); ++i)
            columns.push_back(*i);
        for (unsigned int i = 0; i < l.matrix.size(); i++) {
            matrix.push_back(std::vector<bool>());
            for(unsigned int j = 0; j < l.matrix[i].size(); ++j)
                matrix[i].push_back(l.matrix[i][j]);
        }
    }
    return *this;
}

LogicalResult::operator double() const
{
    double s = 0;
    for (std::vector<std::vector<bool>>::const_iterator i = matrix.begin(); i != matrix.end(); ++i)
        if ((*i)[i->size() - 1]) ++s;
    s = s / matrix.size() * 100;
    return s;
}

std::vector<char> LogicalResult::getColumnNames() const
{
    return columns;
}

std::vector<std::vector<bool>> LogicalResult::getMatrix() const
{
    return matrix;
}

void LogicalResult::stampa() const
{
    for(unsigned int i = 0; i < columns.size(); i++)
        std::cout << columns[i] << "\t";
    std::cout << "Ris: " << std::endl;
    for (std::vector<std::vector<bool>>::const_iterator i = matrix.begin(); i != matrix.end(); ++i) {
        for (std::vector<bool>::const_iterator j = i->begin(); j != i->end(); ++j)
            std::cout << *j << "\t";
        std::cout << std::endl;
    }
}

LogicalResult::~LogicalResult()
{
}
