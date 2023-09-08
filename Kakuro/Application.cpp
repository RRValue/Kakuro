#include "Application.h"

#include "MainWidget.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv), m_MainWidget{nullptr}
{
    setQuitOnLastWindowClosed(true);
}

Application::~Application()
{

}

void Application::onRun()
{
    m_Puzzle.addLine({17, {0, 0}, 2, Orientation::Horinzontal});
    m_Puzzle.addLine({6, {0, 1}, 2, Orientation::Horinzontal});
    m_Puzzle.addLine({14, {0, 0}, 2, Orientation::Vertical});
    m_Puzzle.addLine({9, {1, 0}, 2, Orientation::Vertical});
    m_Puzzle.init();

    m_MainWidget = new MainWidget();
    m_MainWidget->show();
}