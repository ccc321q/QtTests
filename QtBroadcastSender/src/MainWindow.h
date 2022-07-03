
#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>

class QWidget;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *pParent = nullptr);

private slots:
    void startBroadcasting();
    void broadcastDatagram();
    
private:
    QLabel *pStatusLabel;
    QPushButton *pStartButton;
    QUdpSocket udpSocket;
    QTimer timer;
    int messageNo = 1;
};