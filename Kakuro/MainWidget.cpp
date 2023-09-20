#include "MainWidget.h"

#include "Puzzle.h"
#include "PuzzleDelegate.h"
#include "PuzzleModel.h"

#include "ui_mainwidget.h"

#include <QtWidgets/QFileDialog>

MainWidget::MainWidget(QWidget* parent) :
    QWidget(parent),
    m_UI{new Ui_MainWidget()},
    m_Puzzle{std::make_shared<Puzzle>()},
    m_PuzzleModel{new PuzzleModel()},
    m_PuzzleDelegate{new PuzzleDelegate()}
{
    m_PuzzleModel->setPuzzle(m_Puzzle);

    m_UI->setupUi(this);
    m_UI->m_PuzzleView->setShowGrid(true);
    m_UI->m_PuzzleView->horizontalHeader()->hide();
    m_UI->m_PuzzleView->verticalHeader()->hide();
    m_UI->m_PuzzleView->horizontalHeader()->setMinimumSectionSize(1);
    m_UI->m_PuzzleView->verticalHeader()->setMinimumSectionSize(1);
    m_UI->m_PuzzleView->setModel(m_PuzzleModel);
    m_UI->m_PuzzleView->setItemDelegate(m_PuzzleDelegate);

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
    auto file = QFile(QFileDialog::getOpenFileName(this, "Load Kakuro", QDir::currentPath(), "CSV (*.csv)"));

    if(!file.open(QIODevice::OpenModeFlag::ReadOnly))
        return;

    const auto kakuro_data = QString(file.readAll());

    file.close();

    if(kakuro_data.isEmpty())
        return;

    auto lines = kakuro_data.split("\n");

    if(lines.isEmpty())
        return;

    if(lines.last().isEmpty())
        lines.removeLast();

    if(lines.isEmpty())
        return;

    auto width = lines.first().split(",").size();
    auto height = lines.size();

    struct Field
    {
        using OptValue = std::optional<Value>;

        enum class Type
        {
            Empty,
            Cell,
            Line,
        };

        Type m_Type = Type::Empty;
        OptValue m_HValue = {};
        OptValue m_VValue = {};
    };

    auto board = std::vector<std::vector<Field>>(width, std::vector<Field>(height, Field{}));

    for(Index y = 0; y < height; y++)
    {
        const auto elements = lines[y].split(",");

        if(elements.size() != width)
            return;  // error case

        for(Index x = 0; x < width; x++)
        {
            const auto element = elements[x].trimmed();

            if(element == "-1")
                board[x][y].m_Type = Field::Type::Empty;
            else if(element == "0")
                board[x][y].m_Type = Field::Type::Cell;
            else
            {
                const auto line_elements = element.split("|");
                const auto line_elements_size = line_elements.size();

                if(line_elements_size != 2)
                    return;  // error case

                if(line_elements[0] == "-1" && line_elements[1] == "-1")
                    return;  // error case

                board[x][y].m_Type = Field::Type::Line;

                if(line_elements[0] != "-1")
                    board[x][y].m_HValue = line_elements[0].toInt();

                if(line_elements[1] != "-1")
                    board[x][y].m_VValue = line_elements[1].toInt();
            }
        }
    }

    auto input_lines = Puzzle::InputLines{};

    for(Index x = 0; x < width; x++)
        for(Index y = 0; y < height; y++)
        {
            const auto& field = board[x][y];

            if(field.m_Type != Field::Type::Line)
                continue;

            if(!field.m_HValue && !field.m_VValue)
                return; // error case

            if(field.m_HValue)
            {
                auto hlength = Index(0);

                for(Index w = x + 1; w < width; w++)
                {
                    if(board[w][y].m_Type != Field::Type::Cell)
                        break;

                    hlength++;
                }

                input_lines.push_back({*field.m_HValue, {x, y}, hlength, Orientation::Horinzontal});
            }

            if(field.m_VValue)
            {
                auto vlength = Index(0);

                for(Index h = y + 1; h < height; h++)
                {
                    if(board[x][h].m_Type != Field::Type::Cell)
                        break;

                    vlength++;
                }

                input_lines.push_back({*field.m_VValue, {x, y}, vlength, Orientation::Vertical});
            }
        }

    m_Puzzle->reset();
    for(const auto& input_line : input_lines)
        m_Puzzle->addLine(input_line);
    m_Puzzle->init();

    m_PuzzleModel->dataChanged();

    m_UI->m_PuzzleView->resizeColumnsToContents();
    m_UI->m_PuzzleView->resizeRowsToContents();
}