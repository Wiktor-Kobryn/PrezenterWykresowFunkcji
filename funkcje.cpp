#include "funkcje.h"
#include <QMainWindow>


void Funkcja::wypelnijScatterSeries()
{
   clear();
   for(double i = m_osLiczbowa->getXMin(); i <= m_osLiczbowa->getXMax(); i+= (1/m_osLiczbowa->getPktNaJedn()))
   {
       double y = obliczWartFun(i);
       if(y >= m_osLiczbowa->getYMin() && y <= m_osLiczbowa->getYMax())
       {
           append(i, y);
           qInfo() << i << ", " << y;
           QString pktX = QString::number(i);
           QString pktY = QString::number(y);
           addToVector(pktX, pktY);
       }
   }
}

////////////////////////////////////////////////////

void osLiczbowa::wpiszDane(double xMax, double yMax, double xMin, double yMin, double pktNaJedn)
{
    m_xMax = xMax;
    m_yMax = yMax;
    m_xMin = xMin;
    m_yMin = yMin;
    m_pktNaJednostke = pktNaJedn;
}

////////////////////////////////////////////////////

FLiniowa::FLiniowa(double wspA, double wspB, osLiczbowa *osLiczb)
{
    setA(wspA);
    setB(wspB);
    m_osLiczbowa = osLiczb;
    wypelnijScatterSeries();
}

void FLiniowa::setWspolczynniki(double wspA, double wspB)
{
    setA(wspA);
    setB(wspB);
}

double FLiniowa::obliczWartFun(double x)
{
    return (getA() * x + m_b);
}

QString FLiniowa::podajWzorFun()
{
    QString wzor = "y = ";
    wzor.append(QString::number(getA()));
    wzor.append("*x");
    if(m_b >= 0)
        wzor.append( " + " );
    else
        wzor.append( " - " );
    wzor.append(QString::number(abs(m_b)));

    return wzor;
}

void FLiniowa::zerujWsp()
{
    setA(0);
    m_b = 0;
}

////////////////////////////////////////////////////

void FSinus::setWspolczynniki(double wspA, double wspB, double wspF, double katFi)
{
    setA(wspA);
    setB(wspB);
    setF(wspF);
    setFi(katFi);
}

double FSinus::obliczWartFun(double x)
{
    double kat = 2 * PI * m_f * x + m_fi;
    return (getA() * sin(kat) + getB());
}

FSinus::FSinus(double wspA, double wspB, double wspF, double katFi, osLiczbowa *osLiczb)
{
    setWspolczynniki(wspA, wspB, wspF, katFi);
    m_osLiczbowa = osLiczb;
    wypelnijScatterSeries();
}

void FSinus::zerujWsp()
{
    setA(0);
    m_b = 0;
    m_fi = 0;
    m_f = 0;
}

QString FSinus::podajWzorFun()
{
    QString wzor = "y = ";
    wzor.append(QString::number(getA()));
    wzor.append("*sin(2*π*(");
    wzor.append(QString::number(m_f));
    wzor.append(")*x");
    if(m_fi >= 0)
        wzor.append( " + " );
    else
        wzor.append( " - " );
    wzor.append(QString::number(abs(m_fi)));
    if(m_b >= 0)
        wzor.append( ") + " );
    else
        wzor.append( ") - " );
    wzor.append(QString::number(abs(m_b)));

    return wzor;
}

////////////////////////////////////////////////////

FPierwiastkowa::FPierwiastkowa(double wspA, double wspD, osLiczbowa *osLiczb)
{
    setA(wspA);
    setD(wspD);
    m_osLiczbowa = osLiczb;
    wypelnijScatterSeries();
}

void FPierwiastkowa::setWspolczynniki(double wspA, double wspD)
{
    setA(wspA);
    setD(wspD);
}

double FPierwiastkowa::obliczWartFun(double x)
{
    return (getA() * sqrt(x) + m_d);
}

void FPierwiastkowa::zerujWsp()
{
    setA(0);
    m_d = 0;
}

QString FPierwiastkowa::podajWzorFun()
{
    QString wzor = "y = ";
    wzor.append(QString::number(getA()));
    wzor.append("*sqrt(x");
    if(m_d >= 0)
        wzor.append( ") + " );
    else
        wzor.append( ") - " );
    wzor.append(QString::number(abs(m_d)));

    return wzor;
}

////////////////////////////////////////////////////

FLogarytmiczna::FLogarytmiczna(double wspA, double wspB, double wspC, osLiczbowa *osLiczb)
{
    setBorderColor(Qt::transparent);
    setA(wspA);
    setB(wspB);
    setC(wspC);
    m_osLiczbowa = osLiczb;
    wypelnijScatterSeries();
}

void FLogarytmiczna::setWspolczynniki(double wspA, double wspB, double wspC)
{
    setA(wspA);
    setB(wspB);
    setC(wspC);
}

double FLogarytmiczna::obliczWartFun(double x)
{
    double logarytm = log(x)/log(m_b);
    return (getA() * logarytm + m_c);
}

void FLogarytmiczna::zerujWsp()
{
    setA(0);
    m_b = 2;
    m_c = 0;
}

QString FLogarytmiczna::podajWzorFun()
{
    QString wzor = "y = ";
    wzor.append(QString::number(getA()));
    wzor.append("*log");
    wzor.append(QString::number(m_b));
    if(m_c >= 0)
        wzor.append( "(x) + " );
    else
        wzor.append( "(x) - " );
    wzor.append(QString::number(abs(m_c)));

    return wzor;
}

////////////////////////////////////////////////////

double FWielomianowa::obliczWartFun(double x)
{
    double potegaX = 1;
    double y = 0;
    for(int i = 0; i < m_wspolczynniki.size(); i++)
    {
        y = y + (potegaX * m_wspolczynniki[i]);
        potegaX *= x;
    }
    return y;
}

FWielomianowa::FWielomianowa(double wspA0, osLiczbowa *osLiczb)
{
    m_wspolczynniki.push_back(wspA0);
    m_osLiczbowa = osLiczb;
    wypelnijScatterSeries();
}

void FWielomianowa::setNtyWspolczynnik(int n, double wspAn)
{
    if(n < m_wspolczynniki.size())
        m_wspolczynniki[n] = wspAn;
}

void FWielomianowa::dodajWspolczynnik(double wspAn)
{
    m_wspolczynniki.push_back(wspAn);
}

double FWielomianowa::getNtyWspolczynnik(int n)
{
    if(n < m_wspolczynniki.size())
        return m_wspolczynniki[n];
}

void FWielomianowa::zerujWsp()
{
    m_wspolczynniki.clear();
}

QString FWielomianowa::podajWzorFun()
{
    QString wzor = "y = ";
    wzor.append(QString::number(m_wspolczynniki[0]));

    for(int i = 1; i < m_wspolczynniki.size(); i++)
    {
        if(m_wspolczynniki[i] >= 0)
            wzor.append( " + " );
        else
            wzor.append( " - " );
        wzor.append(QString::number(abs(m_wspolczynniki[i])));
        wzor.append("*x^");
        wzor.append(QString::number(i));
    }

    return wzor;
}

//do tablicy pkt
///////

void FLiniowa::addToVector(QString pktX, QString pktY)
{
    QString punkty = pktX + ", " + pktY;
    tablicaPkt.push_back(punkty);
}
void FLogarytmiczna::addToVector(QString pktX, QString pktY)
{
    QString punkty = pktX + ", " + pktY;
    tablicaPkt.push_back(punkty);
}
void FSinus::addToVector(QString pktX, QString pktY)
{
    QString punkty = pktX + ", " + pktY;
    tablicaPkt.push_back(punkty);
}
void FPierwiastkowa::addToVector(QString pktX, QString pktY)
{
    QString punkty = pktX + ", " + pktY;
    tablicaPkt.push_back(punkty);
}
void FWielomianowa::addToVector(QString pktX, QString pktY)
{
    QString punkty = pktX + ", " + pktY;
    tablicaPkt.push_back(punkty);
}

vector<QString> FLiniowa::getVector()
{
    return tablicaPkt;
}

vector<QString> FSinus::getVector()
{
    return tablicaPkt;
}

vector<QString> FLogarytmiczna::getVector()
{
    return tablicaPkt;
}

vector<QString> FWielomianowa::getVector()
{
    return tablicaPkt;
}

vector<QString> FPierwiastkowa::getVector()
{
    return tablicaPkt;
}
