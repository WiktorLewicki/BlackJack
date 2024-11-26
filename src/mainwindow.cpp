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
#include <QSlider>
#include <QVBoxLayout>
#include <QDialogButtonBox>
Game gra(0);
bool cp=false;
int gracz=1, krupier=1;
int showSliderDialog() {
    QDialog dialog;
    dialog.setWindowTitle("Wybierz liczbę talii");
    QSlider *slider = new QSlider(Qt::Horizontal, &dialog);
    slider->setRange(1, 8);
    QLabel *label = new QLabel("Wybierz liczbę talii używanych w grze: 1", &dialog);
    QObject::connect(slider, &QSlider::valueChanged, [&label](int value) {
        label->setText(QString("Wybierz liczbę talii używanych w grze: %1").arg(value));
    });
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, &dialog);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(label);
    layout->addWidget(slider);
    layout->addWidget(buttonBox);
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        return slider->value();
    } else {
        return -1;
    }
}
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
    ui->doubledown->setEnabled(false);
    ui->doubledown->hide();
    resetuj();
    int pm=showSliderDialog();
    while(pm==-1){
        pm=showSliderDialog();
    }
    gra.setuj_talie(pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resetuj(){
    QWidget* players[] = { ui->p1, ui->p2, ui->p3, ui->p4, ui->p5, ui->p6, ui->p7, ui->p8 };
    QWidget* dealers[] = { ui->d1, ui->d2, ui->d3, ui->d4, ui->d5, ui->d6, ui->d7, ui->d8 };
    for (int i = 0; i < 8; i++) {
        players[i]->hide();
    }
    for (int i = 0; i < 8; i++) {
        dealers[i]->hide();
    }
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

string give_name(int karta){
    string s="border-image: url(:/img/";
    if(karta==11) s+=to_string(14);
    else if(karta==10) s+=to_string(losowanie(4)+10);
    else s+=to_string(karta);
    s+=to_string(losowanie(4)+1);
    s+=".png)";
    return s;
}
void MainWindow::pokaz(string s, bool who) {
    QString qpm = QString::fromStdString(s);
    QWidget* players[] = { ui->p1, ui->p2, ui->p3, ui->p4, ui->p5, ui->p6, ui->p7, ui->p8 };
    QWidget* dealers[] = { ui->d1, ui->d2, ui->d3, ui->d4, ui->d5, ui->d6, ui->d7, ui->d8 };
    if (who == 0) {
        if (gracz >= 1 && gracz <= 8) {
            players[gracz - 1]->setStyleSheet(qpm);
            players[gracz - 1]->show();
            gracz++;
        }
    } else {
        if (krupier >= 1 && krupier <= 8) {
            dealers[krupier - 1]->setStyleSheet(qpm);
            dealers[krupier - 1]->show();
            krupier++;
        }
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
    bet_end();
}
void MainWindow::remis(){
    gra.zasil_konto(gra.kwota());
    update_money();
    QMessageBox msgBox;
    msgBox.setWindowTitle(":)");
    msgBox.setText("Remis!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    bet_end();
}
void MainWindow::BJ(){
    gra.zasil_konto(gra.kwota()*5/2);
    update_money();
    QMessageBox msgBox;
    msgBox.setWindowTitle(":)");
    msgBox.setText("BlackJack! Wygrałeś!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    bet_end();
}
void MainWindow::przegrana(){
    QMessageBox msgBox;
    msgBox.setWindowTitle(":(");
    msgBox.setText("Przegrałeś!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    bet_end();
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
    ui->pushButton->show();
    ui->pushButton->setEnabled(true);
    ui->doubledown->setEnabled(false);
    ui->doubledown->hide();
}
void wait(int milliseconds=400) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}
void MainWindow::on_bet_clicked()
{
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
    if(dd&1){
        QMessageBox msgBox;
        msgBox.setText("Stawka musi być parzysta");
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
    gra.new_game(dd);
    update_money();
    int g1=gra.give_card();
    int k1=gra.give_card();
    int g2=gra.give_card();
    gra.hit(g1, 0);
    gra.hit(g2, 0);
    gra.hit(k1, 1);
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
    ui->doubledown->setEnabled(true);
    ui->doubledown->show();
    if(gra.blackjack(0)){
        int hidden=gra.give_card();
        pokaz(give_name(hidden), 1);
        gra.hit(hidden, 1);
        if(gra.blackjack(1)){
            remis();
            return;
        }
        else BJ();
    }

}

void MainWindow::on_stand_clicked()
{
    ui->doubledown->hide();
    ui->doubledown->setEnabled(false);
    ui->hit->hide();
    ui->hit->setEnabled(false);
    ui->stand->hide();
    ui->stand->setEnabled(false);
    ui->math->hide();
    ui->math->setEnabled(false);
    int hidden=gra.give_card();
    pokaz(give_name(hidden), 1);
    gra.hit(hidden, 1);
    wait();
    if(gra.blackjack(1)){
        przegrana();
        return;
    }
    while(gra.ile(1)<17){
        int cur=gra.give_card();
        gra.hit(cur, 1);
        pokaz(give_name(cur), 1);
        if(gra.ile(1)==-1){
            break;
        }
        wait();
    }
    int pm=gra.akcja();
    if(pm==2) wygrana();
    else if(pm==1) remis();
    else przegrana();
}


void MainWindow::on_hit_clicked()
{
    ui->doubledown->setEnabled(false);
    ui->doubledown->hide();
    int cur=gra.give_card();
    gra.hit(cur, 0);
    pokaz(give_name(cur), 0);
    if(gra.ile(0)==-1||gra.ile(0)==21){
        cp=true;
        on_stand_clicked();
    }
}


void MainWindow::on_actionAutor_triggered()
{
    QMessageBox::information(nullptr, "Autor",
        "Autor: Wiktor Lewicki\nKontakt: viksolve@gmail.com");
}


void MainWindow::on_actionZasady_triggered()
{
    QMessageBox::information(nullptr, "Zasady",
        "Zasady są identyczne jak w kasynie.\nTyle samo punktów to remisy. BlackJack bije 21.\nKrupier dobiera jak ma 16 lub mniej.\n22 lub więcej to bust. Double Down to podwojenie stawki\ni dobranie tylko jednej karty.");
}

void MainWindow::on_math_clicked()
{
    long double sc=choose(gra);
    QString scString=QString::number(static_cast<double>(sc), 'f', 2);
    int wyb=choose(gra);
    QString message;
    if(wyb==2) message=QString("Double down");
    else if(wyb==1) message=QString("Hit");
    else message=QString("Stand");
    QMessageBox msgBox;
    msgBox.setWindowTitle("Obliczenia matematyczne");
    msgBox.setText(message);
    msgBox.exec();
}


void MainWindow::on_doubledown_clicked()
{
    if(!gra.double_down()){
        QString message;
        message=QString("Masz za mało kasy!");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Double down");
        msgBox.setText(message);
        msgBox.exec();
        return;
    }
    update_money();
    cp=false;
    on_hit_clicked();
    if(!cp) on_stand_clicked();
}

