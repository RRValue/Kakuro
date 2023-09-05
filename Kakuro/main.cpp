#include "Application.h"

#include <QtCore/QTimer>

#include <set>
#include <vector>

using Value = unsigned int;
using ValuetSet = std::set<Value>;
using ValueVector = std::vector<Value>;

ValuetSet getPossibleValues(const Value& product, const unsigned int& cellCount)
{
    if(cellCount == 0 || cellCount > 9)
        return {};

    auto pos_vector = ValueVector(cellCount);
    std::iota(std::begin(pos_vector), std::end(pos_vector), 1);

    auto s = std::accumulate(std::begin(pos_vector), std::end(pos_vector), 0);

    return {};
}

int main(int argc, char** argv)
{
    getPossibleValues(12, 4);

    Application app(argc, argv);

    QTimer::singleShot(0, &app, &Application::onRun);

    return app.exec();
}