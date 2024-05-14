#include "mainwindow.h"
#include "program.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Program *app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_app(app)
{   
    ui->setupUi(this);
    m_app->setGUI(this);

    connect(m_app, SIGNAL(verifyOKosi()), this, SLOT(on_verifyOKosi()));
    connect(m_app, SIGNAL(verifyFAIL(QString)), this, SLOT(on_verifyFAIL(QString)));

    m_widokWykresow = new QChartView(app->getWykresyPtr());

    m_widokWykresow->setRenderHint(QPainter::Antialiasing);
    m_widokWykresow->setParent(ui->prezenterWykresow);
    m_app->updateWykresy();

    ui->xMaxSpinBox->setValue(m_app->getMaxOsiX());
    ui->xMinSpinBox->setValue(m_app->getMinOsiX());
    ui->yMaxSpinBox->setValue(m_app->getMaxOsiY());
    ui->yMinSpinBox->setValue(m_app->getMinOsiY());
    ui->pktNaJednSpinBox->setValue(m_app->getPktNaJednWykresu());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dodajFunButton_clicked()
{
    m_app->dodajFunkcje();
}

void MainWindow::on_zmienZakresOsiLicz_clicked()
{
    m_app->verifyDaneOsi(ui->xMaxSpinBox->value(), ui->yMaxSpinBox->value(), ui->xMinSpinBox->value(), ui->yMinSpinBox->value());
}

void MainWindow::on_verifyOKosi()
{
    ui->komunikatBleduLabel->clear();
}

void MainWindow::on_verifyFAIL(const QString reason)
{
    ui->komunikatBleduLabel->setText(reason);
}

void MainWindow::on_zmienPktNaJednBut_clicked()
{
    m_app->zmienPktNaJedn(ui->pktNaJednSpinBox->value());
}


void MainWindow::on_usunFunkcjeBut_clicked()
{
    m_app->usunAllFunkcje();
}


void MainWindow::on_zmienOpisyOsiBut_clicked()
{
    m_app->zmienOpisyOsi(ui->jednOsiXTEdit->toPlainText(), ui->jednOsiYTEdit->toPlainText(), ui->tytulWykresuTEdit->toPlainText());
}

void MainWindow::on_eksportPNG_clicked()
{
    QPixmap pixmap = m_widokWykresow->grab();
    m_app->wybierzPlikDoExportPng(pixmap);
}


void MainWindow::on_eksportTXT_clicked()
{
    m_app->wybierzPlikDoExportTxt();
}


void MainWindow::on_info_clicked()
{
    m_app->info();
}

