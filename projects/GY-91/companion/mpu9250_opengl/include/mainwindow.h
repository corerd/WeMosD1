#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <rOc_timer.h>
#include <rOc_serial.h>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <objectgl.h>
#include <QMenuBar>
#include <QMessageBox>
#include <MadgwickAHRS.h>


#define         DEVICE_NAME     "/dev/ttyACM0"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    MainWindow(QWidget *parent = 0, int w=600, int h=400);
    ~MainWindow();


    bool                    connect();

protected slots:
    // Redraw the scene
    void                    onTimer_UpdateDisplay();

    // Get raw data from Arduini
    void                    onTimer_ReadData();

    // Open the about dialog box
    void                    handleAbout();

protected:

    // Overload of the resize event
    void                    resizeEvent(QResizeEvent *);

private:

    // Layout of the window
    QGridLayout             *gridLayout;
    QWidget                 *gridLayoutWidget;

    // Central widget (where the openGL window is drawn)
    QWidget                 *centralWidget;

    // OpenGL object
    ObjectOpenGL            *Object_GL;

    // Serial device for communicating with the Arduino
    rOc_serial mpu9250;

};

#endif // MAINWINDOW_H
