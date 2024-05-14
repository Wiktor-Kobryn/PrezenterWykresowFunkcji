#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <QtCharts>
#include <QScatterSeries>
#include <qdebug.h>
#include <cmath>
#include <vector>
using namespace std;

enum class TypFunkcji
{
    Liniowa = 0,
    Sinusoidalna = 1,
    Logarytmiczna = 2,
    Pierwiastkowa = 3,
    Wielomianowa = 4
};

class osLiczbowa;

class Funkcja : public QScatterSeries
{
public:
    void setWspolczynniki(double wspA) { m_a = wspA; }
    osLiczbowa *m_osLiczbowa = nullptr;

    virtual double obliczWartFun(double x) = 0;
    void wypelnijScatterSeries();
    virtual void addToVector(QString pktX, QString pktY) = 0;
    void setA(double wspA) { m_a = wspA; }
    double getA() { return m_a; }

    Funkcja() {setBorderColor(Qt::transparent);}

private:
    double m_a = 0;
};

//os liczbowa
class osLiczbowa : public QChart
{
    double m_xMax = 5, m_yMax = 5, m_xMin = 0, m_yMin = 0, m_pktNaJednostke = 2;
public:
    void wpiszDane(double xMax, double yMax, double xMin, double yMin, double pktNaJedn);

    void setXMax(double xMax) {m_xMax = xMax;}
    void setXMin(double xMin) {m_xMin = xMin;}
    void setYMax(double yMax) {m_yMax = yMax;}
    void setYMin(double yMin) {m_yMin = yMin;}
    void setPktNaJednostke(double pktNaJedn) {m_pktNaJednostke = pktNaJedn;}

    double getXMax() {return m_xMax;}
    double getXMin() {return m_xMin;}
    double getYMax() {return m_yMax;}
    double getYMin() {return m_yMin;}
    double getPktNaJedn() {return m_pktNaJednostke;}
};

//funkcja liniowa
class FLiniowa : public Funkcja
{
    double m_b = 0;
    vector<QString> tablicaPkt;
public:
    void setB(double wspB) { m_b = wspB; }
    double getB() { return m_b; }
    vector<QString> getVector();
    void addToVector(QString pktX, QString pktY) override;
    void setWspolczynniki(double wspA, double wspB);
    double obliczWartFun(double x) override;
    void zerujWsp();
    QString podajWzorFun();

    FLiniowa(double wspA, double wspB, osLiczbowa *osLiczb);
    FLiniowa() {};
};

//funkcja pierwiastkowa
class FPierwiastkowa : public Funkcja
{
    double m_d = 0;
    vector<QString> tablicaPkt;
public:
    void setD(double wspD) { m_d = wspD; }
    double getD() { return m_d; }
    void zerujWsp();
    vector<QString> getVector();
    void addToVector(QString pktX, QString pktY) override;
    void setWspolczynniki(double wspA, double wspD);
    double obliczWartFun(double x) override;
    QString podajWzorFun();

    FPierwiastkowa(double wspA, double wspD, osLiczbowa *osLiczb);
    FPierwiastkowa() {};
};

//funkcja sinusoidalna
class FSinus: public Funkcja
{
    double m_b = 0, m_fi = 0, m_f = 0;
    const double PI = 3.14;
    vector<QString> tablicaPkt;
public:
    void setFi(double katFi) { m_fi = katFi; }
    double getFi() { return m_fi; }
    void setB(double wspB) { m_b = wspB; }
    double getB() { return m_b; }
    void setF(double wspF) { m_f = wspF; }
    double getF() { return m_f; }
    void zerujWsp();
    QString podajWzorFun();
    vector<QString> getVector();
    void addToVector(QString pktX, QString pktY) override;
    void setWspolczynniki(double wspA, double wspB, double wspF, double katFi);
    double obliczWartFun(double x) override;

    FSinus(double wspA, double wspB, double wspF, double katFi, osLiczbowa *osLiczb);
    FSinus() {};
};

//funkcja logarytmiczna
class FLogarytmiczna: public Funkcja
{
    double m_b = 2; // b > 0 && b != 1
    double m_c = 0;
    vector<QString> tablicaPkt;
public:
    void setB(double wspB) { m_b = wspB; }
    double getB() { return m_b; }
    void setC(double wspC) { m_c = wspC; }
    double getC() { return m_c; }
    void zerujWsp();
    QString podajWzorFun();
    vector<QString> getVector();
    void addToVector(QString pktX, QString pktY) override;
    void setWspolczynniki(double wspA, double wspB, double wspC);
    double obliczWartFun(double x) override;

    FLogarytmiczna(double wspA, double wspB, double wspC, osLiczbowa *osLiczb);
    FLogarytmiczna() {};
};

//funkcja wielomianowa
class FWielomianowa: public Funkcja
{
    vector<double> m_wspolczynniki;
    vector<QString> tablicaPkt;
public:
    void setNtyWspolczynnik(int n, double wspAn);
    void dodajWspolczynnik(double wspAn);
    int getIloscWsp() { return m_wspolczynniki.size(); };
    double getNtyWspolczynnik(int n);
    void zerujWsp();
    vector<QString> getVector();
    QString podajWzorFun();
    void addToVector(QString pktX, QString pktY) override;
    double obliczWartFun(double x) override;
    FWielomianowa(double wspA0, osLiczbowa *osLiczb);
    FWielomianowa() {};
};

#endif // FUNKCJE_H
