#include "snake.hpp"

Snake::Snake(QWidget *parent)
        : QWidget(parent)
{
    initializeComponents();
    applyLayout();
    applyStyle();
    setFixedSize(BOARD_WIDTH,BOARD_HEIGHT);
    connect(easy,&QPushButton::clicked,this,&Snake::OnEasyGame);
    connect(medium,&QPushButton::clicked,this,&Snake::OnMediumGame);
    connect(hard,&QPushButton::clicked,this,&Snake::OnHardGame);
    connect(scores,&QPushButton::clicked,this,&Snake::onScores);
}

void Snake::initializeComponents()
{
    easy   = new QPushButton("Easy",this);
    medium = new QPushButton("Medium",this);
    hard   = new QPushButton("Hard",this);
    scores = new QPushButton("Scores",this);
}

// Layout management
void Snake::applyLayout()
{
    auto *lay = new QGridLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lay->addWidget(easy,0,0);
    lay->addWidget(medium,0,1);
    lay->addWidget(hard,1,0);
    lay->addWidget(scores,1,1);
    setLayout(lay);
}

// Applying style to the window and to the buttons
void Snake::applyStyle()
{
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,size(),QGuiApplication::primaryScreen()->availableGeometry()));
    setWindowIcon(QIcon(":assets/snake.ico"));
    setWindowTitle("Snake");
    easy->setFixedSize(100,100);
    medium->setFixedSize(100,100);
    hard->setFixedSize(100,100);
    scores->setFixedSize(100,100);
    setStyleSheet(STYLE);
}

// Slots :
void Snake::OnEasyGame()
{
    level = EASY;
    startGame();
}

void Snake::OnMediumGame()
{
    level = MEDIUM;
    startGame();
}

void Snake::OnHardGame()
{
    level = HARD;
    startGame();
}

void Snake::onScores()
{
    auto const listScore {scoreManager.selectAll()};
    auto *table  = new QTableWidget(listScore.size(),1);
    table->resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
    table->setWindowTitle("History");
    table->setFixedSize(width(),height());
    const int columnWidth {table->width()};
    table->setColumnWidth(0,columnWidth);
    table->setHorizontalHeaderItem(0,new QTableWidgetItem("Scores"));
    int i{0};
    foreach(const auto &temp, listScore)
    {
        table->setItem(i,0,new QTableWidgetItem(QString::number(temp),0));
        i++;
    }
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->show();
}

// Methods :
void Snake::startGame()
{
    delete easy;
    delete medium;
    delete hard;
    delete scores;
    setStyleSheet("background-color:#000;");
    dots = NUMBER_OF_DOTS_AT_START;
    for(int i{0};i<NUMBER_OF_DOTS_AT_START;i++)
    {
        x[i] = STARTING_POSITION - (i*10);
        y[i] = STARTING_POSITION;
    }
    locateApple();
    timerId = startTimer(delay);
}

void Snake::locateApple()
{
    int r {QRandomGenerator::global()->bounded(10,30)};
    appleAbsciss  = (r * DOT_SIZE);
    r = QRandomGenerator::global()->bounded(10,30);
    appleOrdinate = (r * DOT_SIZE);
}

void Snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    doDrawing();
}

void Snake::doDrawing()
{
    QPainter qp{this};
    if (inGame)
    {
        qp.drawImage(appleAbsciss, appleOrdinate, apple);
        for (int z{0}; z < dots; z++)
        {
            qp.drawImage(x[z], y[z],(z == 0) ? head : dot);
        }
    }
    else
    {
        gameOver();
    }
}

void Snake::gameOver()
{
    QSound::play(":assets/snakehit.wav");
    scoreManager.insertScore(dots - NUMBER_OF_DOTS_AT_START);
    if(dots >= scoreManager.selectBestScore())
    {
        QMessageBox::information(this,"Game over","Best score record!!! : "+QString::number(dots));
    }
    else
    {
        QMessageBox::critical(this,"Game Over","Game Over : Score ("+QString::number(dots)+")");
    }
    qApp->quit();
}

void Snake::checkApple()
{
    // If the head is at the same place that an apple the snake eats the apple and the game becomes more dificult
    if ((x[0] == appleAbsciss) && (y[0] == appleOrdinate))
    {
        QSound::play(":assets/apple_bite.wav");
        switch(level)
        {
            case EASY :
                break;
            case MEDIUM:
                timerId = startTimer((10-MEDIUM)*75);
                break;
            case HARD:
                timerId = startTimer((10-HARD)*75);
                break;
            default:
                break;
        }
        dots++;
        locateApple();
    }
}

void Snake::move()
{
    for (int z = dots; z > 0; z--)
    {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }
    if (leftDirection)
    {
        x[0] -= DOT_SIZE;
    }
    if (rightDirection)
    {
        x[0] += DOT_SIZE;
    }
    if (upDirection)
    {
        y[0] -= DOT_SIZE;
    }
    if (downDirection)
    {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision()
{
    for (int z {dots}; z > 0; z--)
    {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z]))
        {
            inGame = false;
        }
    }
    inGame = !((x[0] >= BOARD_WIDTH) || (x[0] < 0) || (y[0] >= BOARD_HEIGHT) || (y[0] < 0)) && inGame;
    if(!inGame)
    {
        killTimer(timerId);
    }
}

void Snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    if (inGame)
    {
        checkApple();
        checkCollision();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e)
{
    const int key {e->key()};
    const bool leftDirectionPossible{(key == Qt::Key_Left) && (!rightDirection)};
    const bool rightDirectionPossible{(key == Qt::Key_Right) && (!leftDirection)};
    const bool upDirectionPossible{(key == Qt::Key_Up) && (!downDirection)};
    const bool downDirectionPossible{(key == Qt::Key_Down) && (!upDirection)};
    if (leftDirectionPossible)  moveLeft();
    if (rightDirectionPossible) moveRight();
    if (upDirectionPossible)    moveUp();
    if (downDirectionPossible)  moveDown();
    QWidget::keyPressEvent(e);
}

// Move the snake
void Snake::moveUp()
{
    upDirection    = true;
    rightDirection = false;
    leftDirection  = false;
}

void Snake::moveDown()
{
    downDirection  = true;
    rightDirection = false;
    leftDirection  = false;
}

void Snake::moveLeft()
{
    leftDirection = true;
    upDirection   = false;
    downDirection = false;
}

void Snake::moveRight()
{
    rightDirection = true;
    upDirection    = false;
    downDirection  = false;
}

Snake::~Snake()
{}