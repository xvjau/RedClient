#include <QtGui/QApplication>
#include "RedClient.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    RedClient foo;
    foo.show();
    return app.exec();
}
