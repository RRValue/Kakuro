#pragma once

#include <QtWidgets/QWidget>

class Ui_MainWidget;
class Puzzle;
class PuzzleModel;
class PuzzleDelegate;

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    using PuzzlePtr = std::shared_ptr<Puzzle>;

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private slots:
    void onSolve();
    void onLoad();

private:
    Ui_MainWidget* m_UI;
    PuzzlePtr m_Puzzle;
    PuzzleModel* m_PuzzleModel;
    PuzzleDelegate* m_PuzzleDelegate;
};