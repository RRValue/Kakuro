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
    m_Puzzle->addLine({9, {2, 1}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({20, {0, 2}, 4, Orientation::Horinzontal});
    m_Puzzle->addLine({23, {0, 3}, 4, Orientation::Horinzontal});
    m_Puzzle->addLine({8, {0, 4}, 2, Orientation::Horinzontal});

    m_Puzzle->addLine({23, {1, 1}, 3, Orientation::Vertical});
    m_Puzzle->addLine({7, {2, 1}, 3, Orientation::Vertical});
    m_Puzzle->addLine({7, {3, 0}, 3, Orientation::Vertical});
    m_Puzzle->addLine({23, {4, 0}, 3, Orientation::Vertical});

    m_Puzzle->init();

    m_MainWidget = new MainWidget(m_Puzzle);
    
    connect(m_MainWidget, &MainWidget::reqSolve, this, &Application::onSolve);

    m_MainWidget->show();
}

void Application::onSolve()
{
    m_Puzzle->solve();
    m_MainWidget->update();
}