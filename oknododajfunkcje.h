#ifndef OKNODODAJFUNKCJE_H
#define OKNODODAJFUNKCJE_H

#include <QDialog>
#include "funkcje.h"
#include <array>
#include <QString>
#include <QColor>
using namespace std;

namespace Ui {
class OknoDodajFunkcje;
}

class OknoDodajFunkcje : public QDialog
{
    Q_OBJECT

public:
    explicit OknoDodajFunkcje(FLiniowa *fLin, FSinus *fSin, FPierwiastkowa *fPierw,
                              FLogarytmiczna *fLog, FWielomianowa *fWielom, QWidget *parent = nullptr);
    ~OknoDodajFunkcje();

signals:
    void anulujSignal();
    void dodajLinSignal();
    void dodajSinSignal();
    void dodajPierwSignal();
    void dodajLogSignal();
    void dodajWielomSignal();

private slots:
    void on_finished(int);
    void on_kolorButton_clicked();
    void on_anulujBut_clicked();
    void on_dodajFunBut_clicked();

    void on_wspLinASpinBox_valueChanged(double argA);
    void on_wspLinBSpinBox_valueChanged(double argB);

    void on_wspSinASpinBox_valueChanged(double argA);
    void on_wspSinBSpinBox_valueChanged(double argB);
    void on_wspSinFSpinBox_valueChanged(double argF);
    void on_wspSinFiSpinBox_valueChanged(double argFi);

    void on_wspLogASpinBox_valueChanged(double argA);
    void on_wspLogBSpinBox_valueChanged(double argB);
    void on_wspLogCSpinBox_valueChanged(double argC);

    void on_wspPierwASpinBox_valueChanged(double argA);
    void on_wspPierwBSpinBox_valueChanged(double argD);

    void on_dodajWspWielomLabel_clicked();

private:
    Ui::OknoDodajFunkcje *ui;

    FLiniowa *m_outLin;
    FSinus *m_outSin;
    FPierwiastkowa *m_outPierw;
    FLogarytmiczna *m_outLog;
    FWielomianowa *m_outWielom;
    QColor m_kolorFun;

    array<QString, 6> m_tabNazwPunktow = {"punkt", "kwadrat", "romb", "trójkąt", "gwiazda", "pięciokąt"};
};

#endif // OKNODODAJFUNKCJE_H
