#include "MainWidget.h"

#include "PuzzleDelegate.h"
#include "PuzzleModel.h"

#include "ui_mainwidget.h"

MainWidget::MainWidget(const PuzzlePtr& puzzle, QWidget* parent) :
    QWidget(parent), m_UI{new Ui_MainWidget()}, m_PuzzleModel{new PuzzleModel()}, m_PuzzleDelegate{new PuzzleDelegate()}
{
    m_PuzzleModel->setPuzzle(puzzle);

    m_UI->setupUi(this);
    m_UI->m_PuzzleView->setShowGrid(true);
    m_UI->m_PuzzleView->horizontalHeader()->hide();
    m_UI->m_PuzzleView->verticalHeader()->hide();
    m_UI->m_PuzzleView->horizontalHeader()->setMinimumSectionSize(1);
    m_UI->m_PuzzleView->verticalHeader()->setMinimumSectionSize(1);
    m_UI->m_PuzzleView->setModel(m_PuzzleModel);
    m_UI->m_PuzzleView->setItemDelegate(m_PuzzleDelegate);

    m_UI->m_PuzzleView->resizeColumnsToContents();
    m_UI->m_PuzzleView->resizeRowsToContents();

    connect(m_UI->m_SolveBtn, &QPushButton::clicked, this, &MainWidget::reqSolve);
}

MainWidget::~MainWidget()
{
    delete m_PuzzleModel;
    delete m_PuzzleDelegate;
    delete m_UI;
}