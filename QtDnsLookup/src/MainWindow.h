
#pragma once

#include <QMainWindow>
#include <QDnsLookup>

class QWidget;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *pParent = nullptr);

private slots:
    void lookup();
    void showResults();
    
private:
    QLabel *pStatusLabel;
    QDnsLookup dnsLookup;
};