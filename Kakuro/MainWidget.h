#pragma once

#include <QtWidgets/QWidget>

class Ui_MainWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    Ui_MainWidget* m_UI;
};