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
    m_Puzzle->addLine({14, {1, 1}, 3, Orientation::Horinzontal});
    m_Puzzle->addLine({8, {1, 2}, 3, Orientation::Horinzontal});
    m_Puzzle->addLine({4, {0, 3}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({8, {3, 3}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({10, {0, 4}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({12, {3, 4}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({17, {2, 5}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({14, {5, 5}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({8, {2, 6}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({10, {5, 6}, 2, Orientation::Horinzontal});
    m_Puzzle->addLine({10, {3, 7}, 3, Orientation::Horinzontal});
    m_Puzzle->addLine({9, {3, 8}, 3, Orientation::Horinzontal});

    m_Puzzle->addLine({7, {1, 2}, 2, Orientation::Vertical});
    m_Puzzle->addLine({10, {2, 0}, 4, Orientation::Vertical});
    m_Puzzle->addLine({8, {3, 0}, 2, Orientation::Vertical});
    m_Puzzle->addLine({14, {3, 4}, 2, Orientation::Vertical});
    m_Puzzle->addLine({43, {4, 0}, 8, Orientation::Vertical});
    m_Puzzle->addLine({4, {5, 2}, 2, Orientation::Vertical});
    m_Puzzle->addLine({11, {5, 6}, 2, Orientation::Vertical});
    m_Puzzle->addLine({11, {6, 4}, 4, Orientation::Vertical});
    m_Puzzle->addLine({16, {7, 4}, 2, Orientation::Vertical});

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