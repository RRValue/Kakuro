#include "MainWidget.h"

#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent), m_UI{new Ui_MainWidget()}
{
    m_UI->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete m_UI;
}