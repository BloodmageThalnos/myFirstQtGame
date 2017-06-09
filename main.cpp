#include <main.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game* G=new game(1000,800,700);
    G->init();
    G->start();
    return a.exec();
}
