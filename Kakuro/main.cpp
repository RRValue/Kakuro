#include "Application.h"

#include <QtCore/QTimer>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using Value = unsigned int;
using ValuetSet = std::set<Value>;
using ValueVector = std::vector<Value>;

ValuetSet getPossibleValuesForSum(const Value& summ, const unsigned int& cellCount)
{
    if(cellCount == 0 || cellCount > 9)
        return {};

    auto values = ValueVector(9);
    std::iota(std::begin(values), std::end(values), 1);

    auto perm = std::vector<Value>(9, Value(0));
    std::fill_n(std::begin(perm), cellCount, Value(1));

    auto result = ValuetSet();

    do
    {
        auto perm_value = std::vector<Value>(9, Value(0));
        for(unsigned int i = 0; i < 9; i++)
            perm_value[i] = values[i] * perm[i];

        perm_value.erase(std::remove(std::begin(perm_value), std::end(perm_value), 0), std::end(perm_value));

        const auto perm_result = std::accumulate(std::begin(perm_value), std::end(perm_value), 0);

        if(perm_result == summ)
            result.insert(std::cbegin(perm_value), std::cend(perm_value));

    } while(std::prev_permutation(std::begin(perm), std::end(perm)));

    return result;
}

int main(int argc, char** argv)
{
    const auto pos = getPossibleValuesForSum(12, 4);

    Application app(argc, argv);

    QTimer::singleShot(0, &app, &Application::onRun);

    return app.exec();
}