#include "Application.h"

#include "Puzzle.h"

#include "MainWidget.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv), m_MainWidget{nullptr}, m_Puzzle{std::make_shared<Puzzle>()}
{
    setQuitOnLastWindowClosed(true);
}

Application::~Application()
{

}

void Application::onRun()
{
    m_Puzzle->addLine({17, {0, 1}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({6, {0, 2}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({14, {1, 0}, 2, Orientation::Vertical});
    m_Puzzle->addLine({9, {2, 0}, 2, Orientation::Vertical});
    m_Puzzle->init();
    m_Puzzle->solve();

    m_MainWidget = new MainWidget(m_Puzzle);
    m_MainWidget->show();
}