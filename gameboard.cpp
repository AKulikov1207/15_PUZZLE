#include "gameboard.h"
#include <algorithm>
#include <random>

GameBoard::GameBoard(const size_t boardDimension, QObject *parent)
    : QAbstractListModel{parent}, m_dimension {boardDimension}, m_boardSize {m_dimension * m_dimension}
{
    m_rawBoard.resize(m_boardSize);
    std::iota(m_rawBoard.begin(), m_rawBoard.end(), 1);
    shuffle();
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const int rowIndex {index.row()};

    if(!isPositionValid(rowIndex)) {
        return {};
    }

    return QVariant::fromValue(m_rawBoard[rowIndex].value);
}

void GameBoard::shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    do {
        std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
    } while (!isBoardValid());
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardSize;
}

bool GameBoard::isBoardValid() const
{
    int inv {0};
    for (size_t i {0}; i < m_boardSize; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (m_rawBoard[j].value > m_rawBoard[i].value)
                ++inv;
        }
    }

    const size_t start_point = 1;

    for (size_t i = 0; i < m_boardSize; ++i) {
        if (m_rawBoard[i].value == m_boardSize) {
            inv += start_point + i / m_dimension;
        }
    }

    return (inv % 2) == 0;
}

size_t GameBoard::dimension() const
{
    return m_dimension;
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}
