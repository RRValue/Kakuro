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
    m_MainWidget = new MainWidget();
    m_MainWidget->show();
}