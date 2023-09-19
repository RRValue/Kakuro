#include "MainWidget.h"

#include "Puzzle.h"
#include "PuzzleDelegate.h"
#include "PuzzleModel.h"

#include "ui_mainwidget.h"

#include <QtWidgets/QFileDialog>

MainWidget::MainWidget(QWidget* parent) :
    QWidget(parent), m_UI{new Ui_MainWidget()}, m_Puzzle{std::make_shared<Puzzle>()}, m_PuzzleModel{new PuzzleModel()}, m_PuzzleDelegate{new PuzzleDelegate()}
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

    m_PuzzleModel->setPuzzle(m_Puzzle);

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

    connect(m_UI->m_SolveBtn, &QPushButton::clicked, this, &MainWidget::onSolve);
    connect(m_UI->m_LoadBtn, &QPushButton::clicked, this, &MainWidget::onLoad);
}

MainWidget::~MainWidget()
{
    delete m_PuzzleModel;
    delete m_PuzzleDelegate;
    delete m_UI;
}

void MainWidget::onSolve()
{
    m_Puzzle->solve();
    m_PuzzleModel->dataChanged();
}

void MainWidget::onLoad()
{
    QFileDialog::getOpenFileName(this, "Load Kakuro", QDir::currentPath(), "CSV (*.csv)");
}