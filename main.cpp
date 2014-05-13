#include <QApplication>
#include "editmsgdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EditMsgDialog deeps;
    deeps.show();

    return app.exec();
}
