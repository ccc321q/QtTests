
#include "MainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *pParent) :
    QMainWindow(pParent)
{
    pStatusLabel = new QLabel(tr("Listening for broadcasted messages"));
    pStatusLabel->setWordWrap(true);

    udpSocket.bind(45454, QUdpSocket::ShareAddress);
    connect(&udpSocket, &QUdpSocket::readyRead,
            this, &MainWindow::processPendingDatagrams);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(pStatusLabel);

    QWidget *pCentralWidget = new QWidget(this);
    setCentralWidget(pCentralWidget);

    pCentralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Receiver"));
}

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;
    
    while (udpSocket.hasPendingDatagrams())
    {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        udpSocket.readDatagram(datagram.data(), datagram.size());
        pStatusLabel->setText(tr("Received datagram: \"%1\"")
                             .arg(datagram.constData()));
    }
}