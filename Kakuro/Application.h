#pragma once

#include <QtWidgets/QApplication>

class MainWidget;

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application();

public slots:
    void onRun();

private:
    MainWidget* m_MainWidget;
};