#include "Application.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{

}

Application::~Application()
{

}

void Application::onRun()
{
    exit(0);
}