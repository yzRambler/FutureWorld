

//#include "vld.h"
#include "CFWEditor.h"
//#include <QtWidgets/QApplication>
#include <qapplication.h>
#include <qwidget.h>
//#include <qopenglwidget.h>
#include <qboxlayout.h>

#include "CFWEngineWidget.h"


#include <qtimer.h>
#include <QDebug>
#include <QWindow>


using namespace FW;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    CFWEditor w;

    w.Create();

    w.show();
    

    return a.exec();


}
