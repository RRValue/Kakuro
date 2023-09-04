#pragma once

#include <QtWidgets/QApplication>

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

public slots:
    void onRun();
};