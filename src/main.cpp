#include "snake.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Snake");
    QCoreApplication::setOrganizationName("Snake");
    QApplication a(argc, argv);
    Snake w;
    w.show();
    return QApplication::exec();
}