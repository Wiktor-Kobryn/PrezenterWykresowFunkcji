#include "mainwindow.h"
#include "program.h"

Program::Program(QObject *parent)
    :QObject (parent)
{
    m_wykresy->legend()->hide();
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();

    m_axisX->setMin(m_wykresy->getXMin());
    m_axisX->setMax(m_wykresy->getXMax());
    m_axisY->setMin(m_wykresy->getYMin());
    m_axisY->setMax(m_wykresy->getYMax());
    m_wykresy->setAxisX(m_axisX);
    m_wykresy->setAxisY(m_axisY);

    m_wykresy->setTheme(QChart::ChartThemeBlueCerulean);
    m_wykresy->setDropShadowEnabled(true);

    m_fontOsi.setFamily("Trebuchet MS");
    m_fontOsi.setBold(true);
    m_fontOsi.setPointSize(11);
}

void Program::updateAxes()
{
    m_wykresy->axisX()->setRange(m_wykresy->getXMin(), m_wykresy->getXMax());
    m_wykresy->axisY()->setRange(m_wykresy->getYMin(), m_wykresy->getYMax());
    zmienOpisOsiX();
    zmienOpisOsiY();
}

void Program::updateWykresy()
{
    m_wykresy->createDefaultAxes();
}

void Program::dodajFunkcje()
{
    m_okienkoDodFun = new OknoDodajFunkcje(&m_nowaFLin, &m_nowaFSin, &m_nowaFPierw, &m_nowaFLog, &m_nowaFWielom, nullptr);

    connect(m_okienkoDodFun, SIGNAL(anulujSignal()), this, SLOT(on_anulujSignal()));
    connect(m_okienkoDodFun, SIGNAL(dodajLinSignal()), this, SLOT(on_dodajLinSignal()));
    connect(m_okienkoDodFun, SIGNAL(dodajSinSignal()), this, SLOT(on_dodajSinSignal()));
    connect(m_okienkoDodFun, SIGNAL(dodajLogSignal()), this, SLOT(on_dodajLogSignal()));
    connect(m_okienkoDodFun, SIGNAL(dodajPierwSignal()), this, SLOT(on_dodajPierwSignal()));
    connect(m_okienkoDodFun, SIGNAL(dodajWielomSignal()), this, SLOT(on_dodajWielomSignal()));
    m_okienkoDodFun->exec();
}

void Program::rozlaczSygnaly()
{
    disconnect(m_okienkoDodFun, SIGNAL(anulujSignal()), this, SLOT(on_anulujSignal()));
    disconnect(m_okienkoDodFun, SIGNAL(dodajLinSignal()), this, SLOT(on_dodajLinSignal()));
    disconnect(m_okienkoDodFun, SIGNAL(dodajSinSignal()), this, SLOT(on_dodajSinSignal()));
    disconnect(m_okienkoDodFun, SIGNAL(dodajLogSignal()), this, SLOT(on_dodajLogSignal()));
    disconnect(m_okienkoDodFun, SIGNAL(dodajPierwSignal()), this, SLOT(on_dodajPierwSignal()));
    disconnect(m_okienkoDodFun, SIGNAL(dodajWielomSignal()), this, SLOT(on_dodajWielomSignal()));
}

void Program::on_anulujSignal()
{
    rozlaczSygnaly();
    m_okienkoDodFun = nullptr;
}

void Program::on_dodajLinSignal()
{
    FLiniowa *nowaFLin = new FLiniowa(m_nowaFLin.getA(), m_nowaFLin.getB(), m_wykresy);
    nowaFLin->setColor(m_nowaFLin.color());
    nowaFLin->setMarkerShape(m_nowaFLin.markerShape());
    m_funkcjeLin.push_back(nowaFLin);
    m_wykresy->addSeries(nowaFLin);

    m_wykresy->createDefaultAxes();
    updateAxes();
    rozlaczSygnaly();
}

void Program::on_dodajSinSignal()
{
    FSinus *nowaFSin = new FSinus(m_nowaFSin.getA(), m_nowaFSin.getB(), m_nowaFSin.getF(), m_nowaFSin.getFi(), m_wykresy);
    nowaFSin->setColor(m_nowaFSin.color());
    nowaFSin->setMarkerShape(m_nowaFSin.markerShape());
    m_funkcjeSin.push_back(nowaFSin);
    m_wykresy->addSeries(nowaFSin);

    m_wykresy->createDefaultAxes();
    updateAxes();
    rozlaczSygnaly();
}

void Program::on_dodajLogSignal()
{
    FLogarytmiczna *nowaFLog = new FLogarytmiczna(m_nowaFLog.getA(), m_nowaFLog.getB(), m_nowaFLog.getC(), m_wykresy);
    nowaFLog->setColor(m_nowaFLog.color());
    nowaFLog->setMarkerShape(m_nowaFLog.markerShape());
    m_funkcjeLog.push_back(nowaFLog);
    m_wykresy->addSeries(nowaFLog);

    m_wykresy->createDefaultAxes();
    updateAxes();
    rozlaczSygnaly();
}

void Program::on_dodajPierwSignal()
{
    FPierwiastkowa *nowaFPierw = new FPierwiastkowa(m_nowaFPierw.getA(), m_nowaFPierw.getD(), m_wykresy);
    nowaFPierw->setColor(m_nowaFPierw.color());
    nowaFPierw->setMarkerShape(m_nowaFPierw.markerShape());
    m_funkcjePierw.push_back(nowaFPierw);
    m_wykresy->addSeries(nowaFPierw);

    m_wykresy->createDefaultAxes();
    updateAxes();
    rozlaczSygnaly();
}

void Program::on_dodajWielomSignal()
{
    FWielomianowa *nowaFWielom = new FWielomianowa(m_nowaFWielom.getA(), m_wykresy);
    nowaFWielom->setColor(m_nowaFWielom.color());
    nowaFWielom->setMarkerShape(m_nowaFWielom.markerShape());

    for(int i = 1; i < m_nowaFWielom.getIloscWsp(); i++)
    {
        nowaFWielom->dodajWspolczynnik(m_nowaFWielom.getNtyWspolczynnik(i));
    }
    nowaFWielom->wypelnijScatterSeries();
    m_funkcjeWielom.push_back(nowaFWielom);
    m_wykresy->addSeries(nowaFWielom);

    m_wykresy->createDefaultAxes();
    updateAxes();
    rozlaczSygnaly();
}

void Program::verifyDaneOsi(double xMax, double yMax, double xMin, double yMin)
{
    if(xMax == m_wykresy->getXMax() && xMin == m_wykresy->getXMin() &&
            yMax == m_wykresy->getYMax() && yMin == m_wykresy->getYMin())
    {
        emit verifyFAIL(QString("Brak zmian"));
    }
    else if(xMax == xMin)
        emit verifyFAIL(QString("Brak osi x!"));
    else if(xMax < xMin)
        emit verifyFAIL(QString("Nieprawidlowe wartości osi x!"));
    else if(yMax == yMin)
        emit verifyFAIL(QString("Brak osi y!"));
    else if(yMax < yMin)
        emit verifyFAIL(QString("Nieprawidlowe wartości osi y!"));
    else
    {
        m_wykresy->setXMax(xMax);
        m_wykresy->setXMin(xMin);
        m_wykresy->setYMin(yMin);
        m_wykresy->setYMax(yMax);
        updateAllFunkcje();
        emit verifyOKosi();
    }
}

void Program::zmienPktNaJedn(double pktNaJedn)
{
    if(pktNaJedn > 0 && pktNaJedn != m_wykresy->getPktNaJedn())
    {
       m_wykresy->setPktNaJednostke(pktNaJedn);
       updateAllFunkcje();
    }
}

void Program::updateAllFunkcje()
{
    list<FLiniowa*>::iterator iterLin = m_funkcjeLin.begin();
    list<FPierwiastkowa*>::iterator iterPierw = m_funkcjePierw.begin();
    list<FLogarytmiczna*>::iterator iterLog = m_funkcjeLog.begin();
    list<FSinus*>::iterator iterSin = m_funkcjeSin.begin();
    list<FWielomianowa*>::iterator iterWielom = m_funkcjeWielom.begin();

    while(iterLin != m_funkcjeLin.end())
    {
        (*iterLin)->clear();
        (*iterLin)->wypelnijScatterSeries();
        iterLin++;
    }
    while(iterSin != m_funkcjeSin.end())
    {
        (*iterSin)->clear();
        (*iterSin)->wypelnijScatterSeries();
        iterSin++;
    }
    while(iterLog != m_funkcjeLog.end())
    {
        (*iterLog)->clear();
        (*iterLog)->wypelnijScatterSeries();
        iterLog++;
    }
    while(iterPierw != m_funkcjePierw.end())
    {
        (*iterPierw)->clear();
        (*iterPierw)->wypelnijScatterSeries();
        iterPierw++;
    }
    while(iterWielom != m_funkcjeWielom.end())
    {
        (*iterWielom)->clear();
        (*iterWielom)->wypelnijScatterSeries();
        iterWielom++;
    }
    updateAxes();
}

void Program::usunAllFunkcje()
{
    m_wykresy->removeAllSeries();
    m_funkcjeLin.clear();
    m_funkcjeLog.clear();
    m_funkcjePierw.clear();
    m_funkcjeSin.clear();
    m_funkcjeWielom.clear();
    updateAxes();
}

void Program::zmienOpisyOsi(QString opisOsiX, QString opisOsiY, QString tytulWykresu)
{
    if(opisOsiX.isEmpty())
    {
        m_wykresy->axisX()->setTitleVisible(false);
        m_opisOsiX.clear();
    }
    else
    {
        m_opisOsiX = opisOsiX;
        zmienOpisOsiX();
    }

    if(opisOsiY.isEmpty())
    {
        m_wykresy->axisY()->setTitleVisible(false);
        m_opisOsiY.clear();
    }
    else
    {
        m_opisOsiY = opisOsiY;
        zmienOpisOsiY();
    }

    if(tytulWykresu.isEmpty())
    {
        m_wykresy->setTitle("");
    }
    else
    {
        m_wykresy->setTitleFont(m_fontOsi);
        m_wykresy->setTitle(tytulWykresu);
    }
}

void Program::zmienOpisOsiX()
{
    m_wykresy->axisX()->setTitleVisible(true);
    m_wykresy->axisX()->setTitleFont(m_fontOsi);
    m_wykresy->axisX()->setTitleText(m_opisOsiX);
}

void Program::zmienOpisOsiY()
{
    m_wykresy->axisY()->setTitleVisible(true);
    m_wykresy->axisY()->setTitleFont(m_fontOsi);
    m_wykresy->axisY()->setTitleText(m_opisOsiY);
}

void Program::wybierzPlikDoExportTxt()
{
    QString nazwaPliku;
    nazwaPliku = QFileDialog::getSaveFileName(GUI, "Wskaż plik","","Plik tekstowy (*.txt)");
    exportDoTxt(nazwaPliku);
}

void Program::wybierzPlikDoExportPng(QPixmap pixmap)
{
    QString nazwaPliku;
    nazwaPliku = QFileDialog::getSaveFileName(GUI, "Wskaż plik","","Plik graficzny (*.png)");
    exportDoPng(pixmap, nazwaPliku);
}

void Program::exportDoTxt(QString nazwaPliku)
{
    QFile file(nazwaPliku);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Funkcje liniowe:";
        for(auto item : m_funkcjeLin)
        {
            out<<"\n"<<item->podajWzorFun()<<", punkty: [";
            for(auto ite : item->getVector())
            {
                out<<"("<<ite<<") ";
            }
            out<<"]";
        }
        out<<"\nFunkcje logarytmiczne:";
        for(auto item : m_funkcjeLog)
        {
            out<<"\n"<<item->podajWzorFun()<<", punkty: [";
            for(auto ite : item->getVector())
            {
                out<<"("<<ite<<") ";
            }
            out<<"]";
        }
        out<<"\nFunkcje sinusoidalne:";
        for(auto item : m_funkcjeSin)
        {
            out<<"\n"<<item->podajWzorFun()<<", punkty: [";
            for(auto ite : item->getVector())
            {
                out<<"("<<ite<<") ";
            }
            out<<"]";
        }
        out<<"\nFunkcje pierwiastkowe:";
        for(auto item : m_funkcjePierw)
        {
            out<<"\n"<<item->podajWzorFun()<<", punkty: [";
            for(auto ite : item->getVector())
            {
                out<<"("<<ite<<") ";
            }
            out<<"]";
        }
        out<<"\nFunkcje wielomianowe:";
        for(auto item : m_funkcjeWielom)
        {
            out<<"\n"<<item->podajWzorFun()<<", punkty: [";
            for(auto ite : item->getVector())
            {
                out<<"("<<ite<<") ";
            }
            out<<"]";
        }
        file.close();
    }
}

void Program::exportDoPng(QPixmap pixmap, QString nazwaPliku)
{
    pixmap.save(nazwaPliku, "PNG");
}

void Program::info()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Info");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Autorzy:\nWiktor Kobryń IPpp20\nDamian Barczak IPpp20");
    msgBox.setInformativeText("Program wykonany w ramach projektu z przedmiotu Programowanie Komputerów");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}
