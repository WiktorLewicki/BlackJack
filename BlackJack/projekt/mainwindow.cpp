#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "silnik.cpp"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QTimer>
Game gra;
int gracz=1, krupier=1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hit->hide();
    ui->hit->setEnabled(false);
    ui->stand->hide();
    ui->stand->setEnabled(false);
    ui->math->hide();
    ui->math->setEnabled(false);
    resetuj();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resetuj(){
    ui->p1->hide();
    ui->p2->hide();
    ui->p3->hide();
    ui->p4->hide();
    ui->p5->hide();
    ui->p6->hide();
    ui->p7->hide();
    ui->p8->hide();
    ui->d1->hide();
    ui->d2->hide();
    ui->d3->hide();
    ui->d4->hide();
    ui->d5->hide();
    ui->d6->hide();
    ui->d7->hide();
    ui->d8->hide();
}
void MainWindow::on_pushButton_clicked()
{
    bool k=false;
    QWidget window;
    int dd = QInputDialog::getInt(&window, "Doładowanie konta",
        "Ile ze swoich wakacyjnych oszczędności chcesz wpłacić?", 1,
        1, 10000, 1, &k);
    gra.zasil_konto(dd);
    if(!k) return;
    update_money();
}

string give_name(pair<int, int> karta){
    string s="border-image: url(:/img/";
    s+=to_string(karta.first);
    s+=to_string(karta.second);
    s+=".png)";
    return s;
}
void MainWindow::pokaz(string s, bool who){
    QString qpm = QString::fromStdString(s);
    if(who==0){
        if(gracz==1){
            ui->p1->setStyleSheet(qpm);
            ui->p1->show();
        }
        else if(gracz==2){
            ui->p2->setStyleSheet(qpm);
            ui->p2->show();
        }
        else if(gracz==3){
            ui->p3->setStyleSheet(qpm);
            ui->p3->show();
        }
        else if(gracz==4){
            ui->p4->setStyleSheet(qpm);
            ui->p4->show();
        }
        else if(gracz==5){
            ui->p5->setStyleSheet(qpm);
            ui->p5->show();
        }
        else if(gracz==6){
            ui->p6->setStyleSheet(qpm);
            ui->p6->show();
        }
        else if(gracz==7){
            ui->p7->setStyleSheet(qpm);
            ui->p7->show();
        }
        else{
            ui->p8->setStyleSheet(qpm);
            ui->p8->show();
        }
        gracz++;
    }
    else{
        if(krupier==1){
            ui->d1->setStyleSheet(qpm);
            ui->d1->show();
        }
        else if(krupier==2){
            ui->d2->setStyleSheet(qpm);
            ui->d2->show();
        }
        else if(krupier==3){
            ui->d3->setStyleSheet(qpm);
            ui->d3->show();
        }
        else if(krupier==4){
            ui->d4->setStyleSheet(qpm);
            ui->d4->show();
        }
        else if(krupier==5){
            ui->d5->setStyleSheet(qpm);
            ui->d5->show();
        }
        else if(krupier==6){
            ui->d6->setStyleSheet(qpm);
            ui->d6->show();
        }
        else if(krupier==7){
            ui->d7->setStyleSheet(qpm);
            ui->d7->show();
        }
        else{
            ui->d8->setStyleSheet(qpm);
            ui->d8->show();
        }
        krupier++;
    }

}
void MainWindow::update_money(){
    string pm="Stan konta: ";
    pm+=to_string(gra.kasa());
    pm+=" EUR";
    QString qpm = QString::fromStdString(pm);
    ui->stan_konta->setText(qpm);
}
void MainWindow::wygrana(){
    gra.zasil_konto(gra.kwota()*2);
    update_money();
    QMessageBox msgBox;
    msgBox.setWindowTitle(":)");
    msgBox.setText("Wygrałeś!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::przegrana(){
    QMessageBox msgBox;
    msgBox.setWindowTitle(":(");
    msgBox.setText("Przegrałeś!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::bet_end(){
    ui->pushButton->show();
    ui->pushButton->setEnabled(true);
    ui->hit->hide();
    ui->hit->setEnabled(false);
    ui->stand->hide();
    ui->stand->setEnabled(false);
    ui->math->hide();
    ui->math->setEnabled(false);
    ui->bet->show();
    ui->bet->setEnabled(true);
}
void wait(int milliseconds=400) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}
void MainWindow::on_bet_clicked()
{
    gra.clear();
    resetuj();
    gracz=1;
    krupier=1;
    if(gra.czy_tasowanie()){
        QMessageBox msgBox;
        msgBox.setText("Karty zostały przetasowane!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    bool k=false;
    QWidget window;
    int dd = QInputDialog::getInt(&window, "Stawianie zakładu",
        "Za jaką kwotę chcesz postawić zakład?", 1,
        1, 1000000, 1, &k);
    if(!k) return;
    if(dd>gra.kasa()){
        QMessageBox msgBox;
        msgBox.setText("Nie masz tyle pieniędzy");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    ui->pushButton->hide();
    ui->pushButton->setEnabled(false);
    ui->bet->hide();
    ui->bet->setEnabled(false);
    gra.postaw(dd);
    gra.zasil_konto(-dd);
    update_money();
    auto g1=gra.give();
    auto k1=gra.give();
    auto g2=gra.give();
    gra.insert(g1.first, 0);
    gra.insert(g2.first, 0);
    gra.insert(k1.first, 1);
    pokaz(give_name(g1), 0);
    wait();
    pokaz(give_name(k1), 1);
    wait();
    pokaz(give_name(g2), 0);
    wait();
    ui->d2->setStyleSheet("border-image: url(:/back.png)");
    ui->d2->show();
    ui->hit->show();
    ui->hit->setEnabled(true);
    ui->stand->show();
    ui->stand->setEnabled(true);
    ui->math->show();
    ui->math->setEnabled(true);
    if(gra.judge(0)==21){
        pair<int, int>hidden=gra.give();
        pokaz(give_name(hidden), 1);
        gra.insert(hidden.first, 1);
        wygrana();
        bet_end();
    }

}

void MainWindow::on_stand_clicked()
{
    ui->hit->hide();
    ui->hit->setEnabled(false);
    ui->stand->hide();
    ui->stand->setEnabled(false);
    ui->math->hide();
    ui->math->setEnabled(false);
    pair<int, int>hidden=gra.give();
    pokaz(give_name(hidden), 1);
    gra.insert(hidden.first, 1);
    wait();
    while(gra.judge(1)<17){
        auto cur=gra.give();
        gra.insert(cur.first, 1);
        pokaz(give_name(cur), 1);
        if(gra.judge(1)==-1){
            wygrana();
            bet_end();
            return;
        }
        wait();
    }
    if(gra.judge(1)>=gra.judge(0)) przegrana();
    else wygrana();
    ui->pushButton->show();
    ui->pushButton->setEnabled(true);
    bet_end();
}


void MainWindow::on_hit_clicked()
{
    auto cur=gra.give();
    gra.insert(cur.first, 0);
    pokaz(give_name(cur), 0);
    if(gra.judge(0)==-1){
        pair<int, int>hidden=gra.give();
        pokaz(give_name(hidden), 1);
        przegrana();
        bet_end();
    }
    else if(gra.judge(0)==21) on_stand_clicked();
}


void MainWindow::on_actionAutor_triggered()
{
    QMessageBox::information(nullptr, "Autor",
        "Autor: Wiktor Lewicki\nKontakt: viksolve@gmail.com");
}


void MainWindow::on_actionZasady_triggered()
{
    QMessageBox::information(nullptr, "Zasady",
        "W talii są 52 karty. Tasowanie następuje w momencie,\nkiedy zostanie mniej niż 16 kart.\nKrupier musi grać dalej jeżeli ma mniej niż 17.\nW przypadku remisu, wygrywa krupier.\nBlackJack jest tylko wtedy, gdy jest 21\nw pierwszch dwóch kartach.\nW przypadku asów, są one liczone zawsze\nnajkorzystniej dla gracza i krupiera.");
}

void MainWindow::on_math_clicked()
{
    long double hc=gra.hit_chances();
    long double sc=stand_chances(gra);
    QString hcString=QString::number(static_cast<double>(hc), 'f', 2);
    QString scString=QString::number(static_cast<double>(sc), 'f', 2);
    QString message=QString("Jeżeli zdecydujesz się na hit, masz %1 % szans, że nie zrobisz bust'a.\n"
                              "Szanse na wygraną przy standzie wynoszą %2 %.").arg(hcString, scString);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Obliczenia matematyczne");
    msgBox.setText(message);
    msgBox.exec();
}

