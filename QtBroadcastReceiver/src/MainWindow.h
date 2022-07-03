
#pragma once

#include <QMainWindow>
#include <QUdpSocket>

class QWidget;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *pParent = nullptr);

private slots:
    void processPendingDatagrams();
    
private:
    QLabel *pStatusLabel;
    QUdpSocket udpSocket;
};