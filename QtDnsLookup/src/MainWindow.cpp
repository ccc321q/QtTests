
#include "MainWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>

#include <stdio.h>

MainWindow::MainWindow(QWidget *pParent) :
    QMainWindow(pParent)
{
    pStatusLabel = new QLabel(tr("..."));
    pStatusLabel->setWordWrap(true);

    auto pStartButton = new QPushButton(tr("&Lookup DNS"));
    connect(pStartButton, &QPushButton::clicked, this, &MainWindow::lookup);

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(pStartButton, QDialogButtonBox::ActionRole);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(pStatusLabel);
    mainLayout->addWidget(buttonBox);

    QWidget *pCentralWidget = new QWidget(this);
    setCentralWidget(pCentralWidget);

    pCentralWidget->setLayout(mainLayout);

    setWindowTitle(tr("DNS Lookup"));

    connect(&dnsLookup, &QDnsLookup::finished, this, &MainWindow::showResults);
}

void MainWindow::lookup()
{
    dnsLookup.setType(QDnsLookup::ANY);
    dnsLookup.setName("www.gmail.com");
    dnsLookup.lookup();
}

void MainWindow::showResults()
{
    if (dnsLookup.error() != QDnsLookup::NoError)
        printf("Error: %i (%s)\n", dnsLookup.error(), qPrintable(dnsLookup.errorString()));

    // CNAME records
    const QList<QDnsDomainNameRecord> cnameRecords = dnsLookup.canonicalNameRecords();
    for (const QDnsDomainNameRecord &record : cnameRecords)
        printf("%s\t%i\tIN\tCNAME\t%s\n", qPrintable(record.name()), record.timeToLive(), qPrintable(record.value()));

    // A and AAAA records
    const QList<QDnsHostAddressRecord> aRecords = dnsLookup.hostAddressRecords();
    for (const QDnsHostAddressRecord &record : aRecords) {
        const char *type = (record.value().protocol() == QAbstractSocket::IPv6Protocol) ? "AAAA" : "A";
        printf("%s\t%i\tIN\t%s\t%s\n", qPrintable(record.name()), record.timeToLive(), type, qPrintable(record.value().toString()));
    }

    // MX records
    const QList<QDnsMailExchangeRecord> mxRecords = dnsLookup.mailExchangeRecords();
    for (const QDnsMailExchangeRecord &record : mxRecords)
        printf("%s\t%i\tIN\tMX\t%u %s\n", qPrintable(record.name()), record.timeToLive(), record.preference(), qPrintable(record.exchange()));

    // NS records
    const QList<QDnsDomainNameRecord> nsRecords = dnsLookup.nameServerRecords();
    for (const QDnsDomainNameRecord &record : nsRecords)
        printf("%s\t%i\tIN\tNS\t%s\n", qPrintable(record.name()), record.timeToLive(), qPrintable(record.value()));

    // PTR records
    const QList<QDnsDomainNameRecord> ptrRecords = dnsLookup.pointerRecords();
    for (const QDnsDomainNameRecord &record : ptrRecords)
        printf("%s\t%i\tIN\tPTR\t%s\n", qPrintable(record.name()), record.timeToLive(), qPrintable(record.value()));

    // SRV records
    const QList<QDnsServiceRecord> srvRecords = dnsLookup.serviceRecords();
    for (const QDnsServiceRecord &record : srvRecords)
        printf("%s\t%i\tIN\tSRV\t%u %u %u %s\n", qPrintable(record.name()), record.timeToLive(), record.priority(), record.weight(), record.port(), qPrintable(record.target()));

    // TXT records
    const QList<QDnsTextRecord> txtRecords = dnsLookup.textRecords();
    for (const QDnsTextRecord &record : txtRecords) {
        QStringList values;
        const QList<QByteArray> dnsRecords = record.values();
        for (const QByteArray &ba : dnsRecords)
            values << "\"" + QString::fromLatin1(ba) + "\"";
        printf("%s\t%i\tIN\tTXT\t%s\n", qPrintable(record.name()), record.timeToLive(), qPrintable(values.join(' ')));
    }
}