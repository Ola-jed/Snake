#include "snake.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Snake w;
    w.show();
    return QApplication::exec();
}