#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include "funkcje.h"
#include "oknododajfunkcje.h"
#include "mainwindow.h"
#include <list>
#include <QtCharts>
#include <QChartView>
#include <QScatterSeries>

using namespace std;

class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr) {GUI = ui;}
    osLiczbowa* getWykresyPtr() { return m_wykresy; }
    void updateWykresy();
    void dodajFunkcje();
    void verifyDaneOsi(double xMax, double yMax, double xMin, double yMin);
    double getMaxOsiX() { return m_wykresy->getXMax(); }
    double getMaxOsiY() { return m_wykresy->getYMax(); }
    double getMinOsiX() { return m_wykresy->getXMin(); }
    double getMinOsiY() { return m_wykresy->getYMin(); }
    double getPktNaJednWykresu() { return m_wykresy->getPktNaJedn(); }
    void zmienPktNaJedn(double pktNaJedn);
    void usunAllFunkcje();
    void zmienOpisyOsi(QString opisOsiX, QString opisOsiY, QString tytulWykresu);
    void exportDoTxt(QString nazwaPliku);
    void exportDoPng(QPixmap pixmap, QString nazwaPliku);
    void wybierzPlikDoExportTxt();
    void wybierzPlikDoExportPng(QPixmap pixmap);
    void info();
signals:
    void verifyFAIL(const QString);
    void verifyOKosi();

public slots:
    void on_anulujSignal();
    void on_dodajLinSignal();
    void on_dodajSinSignal();
    void on_dodajLogSignal();
    void on_dodajPierwSignal();
    void on_dodajWielomSignal();

private:
    MainWindow *GUI = nullptr;

    list<FPierwiastkowa*> m_funkcjePierw;
    list<FLogarytmiczna*> m_funkcjeLog;
    list<FLiniowa*> m_funkcjeLin;
    list<FSinus*> m_funkcjeSin;
    list<FWielomianowa*> m_funkcjeWielom;

    osLiczbowa *m_wykresy = new osLiczbowa;
    OknoDodajFunkcje *m_okienkoDodFun;

    FLiniowa m_nowaFLin;
    FSinus m_nowaFSin;
    FPierwiastkowa m_nowaFPierw;
    FLogarytmiczna m_nowaFLog;
    FWielomianowa m_nowaFWielom;

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    QFont m_fontOsi;

    void rozlaczSygnaly();
    void updateAllFunkcje();
    void updateAxes();
    void zmienOpisOsiX();
    void zmienOpisOsiY();
    QString m_opisOsiX, m_opisOsiY;
};

#endif // PROGRAM_H
