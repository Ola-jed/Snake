#include "snake.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Snake");
    QCoreApplication::setOrganizationName("Snake");
    Snake w;
    w.show();
    return QApplication::exec();
}