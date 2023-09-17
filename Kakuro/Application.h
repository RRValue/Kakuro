#pragma once

#include <QtWidgets/QApplication>

class Puzzle;
class MainWidget;

class Application : public QApplication
{
    Q_OBJECT

private:
    using PuzzlePtr = std::shared_ptr<Puzzle>;

public:
    Application(int& argc, char** argv);
    ~Application();

public slots:
    void onRun();

private slots:
    void onSolve();

private:
    MainWidget* m_MainWidget;
    PuzzlePtr m_Puzzle = {};
};