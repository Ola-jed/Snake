#include "snake.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Snake");
    QCoreApplication::setOrganizationName("Snake");
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);
    Snake w;
    w.show();
    return QApplication::exec();
}