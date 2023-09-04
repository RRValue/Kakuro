#include "Application.h"

#include <QtCore/QTimer>

int main(int argc, char** argv)
{
    Application app(argc, argv);

    QTimer::singleShot(0, &app, &Application::onRun);

    return app.exec();
}