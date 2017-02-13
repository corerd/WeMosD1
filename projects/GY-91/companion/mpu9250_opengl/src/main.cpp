/* OpenGL Frame
   Designed by Philippe Lucidarme
   LISA - University of Angers
   Supported by the Cart-O-matic project (ANR CAROTTE)

   Contact : philippe.lucidarme@univ-angers.fr
   Website : http://5lair.free.fr

   sudo apt-get install freeglut3 freeglut3-dev

*/

//#include <QtGui/QApplication>
#include <QtWidgets/QApplication>
#include "mainwindow.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,800,600);


    // Connect to the Arduino
    if (!w.connect()) return 0;

    w.show();
    return a.exec();
}
