#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>
#include <QChartView>
#include <QScatterSeries>
#include "funkcje.h"
#include <list>
#include <qdebug.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Program;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program *app = nullptr);
    ~MainWindow();

public slots:
    void on_verifyFAIL(const QString);
    void on_verifyOKosi();

private slots:
    void on_dodajFunButton_clicked();
    void on_zmienZakresOsiLicz_clicked();
    void on_zmienPktNaJednBut_clicked();


    void on_usunFunkcjeBut_clicked();

    void on_zmienOpisyOsiBut_clicked();

    void on_eksportPNG_clicked();

    void on_eksportTXT_clicked();

    void on_info_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    Program* m_app = nullptr;

    QChartView *m_widokWykresow;
};
#endif // MAINWINDOW_H
