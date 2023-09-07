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
    m_Puzzle.addLine({13, {0, 0}, 4, Line::Orientation::Horinzontal});
    m_Puzzle.init();

    m_MainWidget = new MainWidget();
    m_MainWidget->show();
}