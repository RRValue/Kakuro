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
    MainWidget(const PuzzlePtr& puzzle, QWidget* parent = nullptr);
    ~MainWidget();

private:
    Ui_MainWidget* m_UI;
    PuzzleModel* m_PuzzleModel;
    PuzzleDelegate* m_PuzzleDelegate;
};