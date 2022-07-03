
#include "MainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *pParent) :
    QMainWindow(pParent)
{
    pStatusLabel = new QLabel(tr("Ready to broadcast datagrams on port 45454"));
    pStatusLabel->setWordWrap(true);

    pStartButton = new QPushButton(tr("&Start"));
    auto quitButton = new QPushButton(tr("&Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(pStartButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(pStartButton, &QPushButton::clicked, this, &MainWindow::startBroadcasting);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(&timer, &QTimer::timeout, this, &MainWindow::broadcastDatagram);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(pStatusLabel);
    mainLayout->addWidget(buttonBox);

    QWidget *pCentralWidget = new QWidget(this);
    setCentralWidget(pCentralWidget);

    pCentralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Sender"));
}

void MainWindow::startBroadcasting()
{
    pStartButton->setEnabled(false);
    timer.start(1000);
}

void MainWindow::broadcastDatagram()
{
    pStatusLabel->setText("Broadcasting...");

    const QByteArray datagram = "Hi hello..." + QByteArray::number(messageNo);
    auto sentAmount = udpSocket.writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    if (sentAmount > 0)
    {
        qDebug() << "Sent success";
        ++messageNo;
    }
    else
    {
        qDebug() << "Sent failed";
    }
}