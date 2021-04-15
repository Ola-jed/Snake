#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "style.hpp"
#include "scoremanager.hpp"
#include <array>
#include <QTime>
#include <QStyle>
#include <QSound>
#include <QImage>
#include <QScreen>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QRandomGenerator>

class Snake : public QWidget
{
    Q_OBJECT

    public:
        explicit Snake(QWidget *parent = nullptr);
        ~Snake();

    protected:
        void paintEvent(QPaintEvent *) override;
        void timerEvent(QTimerEvent *) override;
        void keyPressEvent(QKeyEvent *) override;

    private:
        QPushButton *easy;
        QPushButton *medium;
        QPushButton *hard;
        QPushButton *scores;

        const QImage dot {":assets/dot.png"};
        const QImage head {":assets/head.png"};
        const QImage apple {":assets/apple.png"};

        static const int BOARD_WIDTH {500};
        static const int BOARD_HEIGHT {500};
        static const int DOT_SIZE {10};
        static const int ALL_DOTS {900};
        static const int NUMBER_OF_DOTS_AT_START {3};
        static const int STARTING_POSITION{50};
        static const int EASY {0};
        static const int MEDIUM {1};
        static const int HARD {2};
        const int RANDOM_POSITION {QRandomGenerator::global()->bounded(10,30)};

        int delay {100};
        int timerId;
        int level;
        int dots {NUMBER_OF_DOTS_AT_START};
        int appleAbsciss;
        int appleOrdinate;
        std::array<int,ALL_DOTS> x;
        std::array<int,ALL_DOTS> y;
        bool leftDirection {false};
        bool rightDirection {true};
        bool upDirection {false};
        bool downDirection {false};
        bool inGame {true};

        // Functions
        void move();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void startGame();
        void locateApple();
        void checkApple();
        void checkCollision();
        void doDrawing();
        void gameOver();
        void initializeComponents();
        void applyLayout();
        void applyStyle();

        ScoreManager scoreManager{};

    private slots:
        void OnEasyGame();
        void OnMediumGame();
        void OnHardGame();
        void onScores();
};
#endif // SNAKE_HPP