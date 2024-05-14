#include "oknododajfunkcje.h"
#include "ui_oknododajfunkcje.h"

OknoDodajFunkcje::OknoDodajFunkcje(FLiniowa *fLin, FSinus *fSin, FPierwiastkowa *fPierw,
                                   FLogarytmiczna *fLog, FWielomianowa *fWielom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoDodajFunkcje),
    m_outLin(fLin), m_outLog(fLog), m_outPierw(fPierw), m_outSin(fSin), m_outWielom(fWielom)
{
    ui->setupUi(this);

    connect(this, SIGNAL(finished(int)), this, SLOT(on_finished(int)));
    ui->kolorLabel->setStyleSheet("border: 1px solid black");

    m_outLin->zerujWsp();
    m_outLog->zerujWsp();
    m_outPierw->zerujWsp();
    m_outSin->zerujWsp();
    m_outWielom->zerujWsp();

    m_kolorFun.setRgb(255, 255, 255);

    for(int i = 0; i < m_tabNazwPunktow.size(); i++)
    {
        ui->wyborZnacznikaCBox->addItem(m_tabNazwPunktow[i]);
    }
}

OknoDodajFunkcje::~OknoDodajFunkcje()
{
    delete ui;
}

void OknoDodajFunkcje::on_finished(int arg)
{
    Q_UNUSED(arg);
    deleteLater();
}

void OknoDodajFunkcje::on_wspLinASpinBox_valueChanged(double argA)
{
    m_outLin->setA(argA);
    ui->wzorLinLabel->setText(m_outLin->podajWzorFun());
}


void OknoDodajFunkcje::on_wspLinBSpinBox_valueChanged(double argB)
{
    m_outLin->setB(argB);
    ui->wzorLinLabel->setText(m_outLin->podajWzorFun());
}


void OknoDodajFunkcje::on_kolorButton_clicked()
{
    m_kolorFun = QColorDialog::getColor();

    QString kolorStr = " background-color : " ;
    kolorStr += m_kolorFun.name();
    if(m_kolorFun.isValid())
    {
        ui->kolorLabel->setStyleSheet(kolorStr);
    }
}


void OknoDodajFunkcje::on_anulujBut_clicked()
{
    emit anulujSignal();
    close();
}


void OknoDodajFunkcje::on_dodajFunBut_clicked()
{
    QScatterSeries::MarkerShape shape = (QScatterSeries::MarkerShape)ui->wyborZnacznikaCBox->currentIndex();
    switch ((TypFunkcji)ui->tabWidget->currentIndex())
    {
        default: case TypFunkcji::Liniowa:
        if(m_kolorFun.isValid())
            m_outLin->setColor(m_kolorFun);
        m_outLin->setMarkerShape(shape);
        emit dodajLinSignal();
        break;
    case TypFunkcji::Sinusoidalna:
        if(m_kolorFun.isValid())
            m_outSin->setColor(m_kolorFun);
        m_outSin->setMarkerShape(shape);
        emit dodajSinSignal();
        break;
    case TypFunkcji::Logarytmiczna:
        if(m_kolorFun.isValid())
            m_outLog->setColor(m_kolorFun);
        m_outLog->setMarkerShape(shape);
        emit dodajLogSignal();
        break;
    case TypFunkcji::Pierwiastkowa:
        if(m_kolorFun.isValid())
            m_outPierw->setColor(m_kolorFun);
        m_outPierw->setMarkerShape(shape);
        emit dodajPierwSignal();
        break;
    case TypFunkcji::Wielomianowa:
        if(m_kolorFun.isValid())
            m_outWielom->setColor(m_kolorFun);
        m_outWielom->setMarkerShape(shape);
        emit dodajWielomSignal();
        break;
    }
    close();
}


void OknoDodajFunkcje::on_wspSinASpinBox_valueChanged(double argA)
{
    m_outSin->setA(argA);
    ui->wzorSinLabel->setText(m_outSin->podajWzorFun());
}


void OknoDodajFunkcje::on_wspSinBSpinBox_valueChanged(double argB)
{
    m_outSin->setB(argB);
    ui->wzorSinLabel->setText(m_outSin->podajWzorFun());
}


void OknoDodajFunkcje::on_wspSinFSpinBox_valueChanged(double argF)
{
    m_outSin->setF(argF);
    ui->wzorSinLabel->setText(m_outSin->podajWzorFun());
}


void OknoDodajFunkcje::on_wspSinFiSpinBox_valueChanged(double argFi)
{
    m_outSin->setFi(argFi);
    ui->wzorSinLabel->setText(m_outSin->podajWzorFun());
}


void OknoDodajFunkcje::on_wspLogASpinBox_valueChanged(double argA)
{
    m_outLog->setA(argA);
    ui->wzorLogLabel->setText(m_outLog->podajWzorFun());
}


void OknoDodajFunkcje::on_wspLogBSpinBox_valueChanged(double argB)
{
    if(argB == 1.0)
    {
        ui->wspLogBSpinBox->setValue(2.0);
    }
    else
    {
        m_outLog->setB(argB);
        ui->wzorLogLabel->setText(m_outLog->podajWzorFun());
    }
}


void OknoDodajFunkcje::on_wspLogCSpinBox_valueChanged(double argC)
{
    m_outLog->setC(argC);
    ui->wzorLogLabel->setText(m_outLog->podajWzorFun());
}


void OknoDodajFunkcje::on_wspPierwASpinBox_valueChanged(double argA)
{
    m_outPierw->setA(argA);
    ui->wzorPierwLabel->setText(m_outPierw->podajWzorFun());
}


void OknoDodajFunkcje::on_wspPierwBSpinBox_valueChanged(double argD)
{
    m_outPierw->setD(argD);
    ui->wzorPierwLabel->setText(m_outPierw->podajWzorFun());
}


void OknoDodajFunkcje::on_dodajWspWielomLabel_clicked()
{
    m_outWielom->dodajWspolczynnik(ui->wspWielomSpinBox->value());
    ui->wzorWielomLabel->setText(m_outWielom->podajWzorFun());
}

