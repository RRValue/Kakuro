#pragma once

#include "Puzzle.h"

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
    Puzzle m_Puzzle = {};
};