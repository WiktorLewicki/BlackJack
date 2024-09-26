/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAutor;
    QAction *actionZasady;
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *stan_konta;
    QPushButton *pushButton;
    QPushButton *bet;
    QPushButton *stand;
    QPushButton *hit;
    QWidget *p1;
    QWidget *p2;
    QWidget *p3;
    QWidget *p4;
    QWidget *p5;
    QWidget *p6;
    QWidget *p7;
    QWidget *p8;
    QWidget *d1;
    QWidget *d2;
    QWidget *d3;
    QWidget *d4;
    QWidget *d5;
    QWidget *d6;
    QWidget *d7;
    QWidget *d8;
    QPushButton *math;
    QPushButton *doubledown;
    QMenuBar *menubar;
    QMenu *menuO_programie;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1025, 846);
        MainWindow->setMinimumSize(QSize(1025, 846));
        MainWindow->setMaximumSize(QSize(1025, 846));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionAutor = new QAction(MainWindow);
        actionAutor->setObjectName("actionAutor");
        actionZasady = new QAction(MainWindow);
        actionZasady->setObjectName("actionZasady");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-11, -1, 1041, 821));
        frame->setCursor(QCursor(Qt::ArrowCursor));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/tabela.png)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        stan_konta = new QLabel(frame);
        stan_konta->setObjectName("stan_konta");
        stan_konta->setGeometry(QRect(20, 640, 361, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        stan_konta->setFont(font);
        stan_konta->setStyleSheet(QString::fromUtf8("border-image: \"\";\n"
"color: black"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 690, 281, 41));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        pushButton->setFont(font1);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("border-image:url(:/white.jpg);\n"
"color: black"));
        bet = new QPushButton(frame);
        bet->setObjectName("bet");
        bet->setGeometry(QRect(910, 650, 100, 100));
        bet->setCursor(QCursor(Qt::PointingHandCursor));
        bet->setStyleSheet(QString::fromUtf8("border-image:url(:/bet.png)"));
        stand = new QPushButton(frame);
        stand->setObjectName("stand");
        stand->setGeometry(QRect(780, 650, 100, 100));
        stand->setCursor(QCursor(Qt::PointingHandCursor));
        stand->setStyleSheet(QString::fromUtf8("border-image:url(:/stand.png)"));
        hit = new QPushButton(frame);
        hit->setObjectName("hit");
        hit->setGeometry(QRect(650, 650, 100, 100));
        hit->setCursor(QCursor(Qt::PointingHandCursor));
        hit->setStyleSheet(QString::fromUtf8("border-image:url(:/hit.png)"));
        p1 = new QWidget(frame);
        p1->setObjectName("p1");
        p1->setGeometry(QRect(30, 510, 101, 131));
        p1->setStyleSheet(QString::fromUtf8(""));
        p2 = new QWidget(frame);
        p2->setObjectName("p2");
        p2->setGeometry(QRect(150, 510, 101, 131));
        p2->setStyleSheet(QString::fromUtf8(""));
        p3 = new QWidget(frame);
        p3->setObjectName("p3");
        p3->setGeometry(QRect(280, 510, 101, 131));
        p3->setStyleSheet(QString::fromUtf8(""));
        p4 = new QWidget(frame);
        p4->setObjectName("p4");
        p4->setGeometry(QRect(400, 510, 101, 131));
        p4->setStyleSheet(QString::fromUtf8(""));
        p5 = new QWidget(frame);
        p5->setObjectName("p5");
        p5->setGeometry(QRect(530, 510, 101, 131));
        p5->setStyleSheet(QString::fromUtf8(""));
        p6 = new QWidget(frame);
        p6->setObjectName("p6");
        p6->setGeometry(QRect(650, 510, 101, 131));
        p6->setStyleSheet(QString::fromUtf8(""));
        p7 = new QWidget(frame);
        p7->setObjectName("p7");
        p7->setGeometry(QRect(790, 510, 101, 131));
        p7->setStyleSheet(QString::fromUtf8(""));
        p8 = new QWidget(frame);
        p8->setObjectName("p8");
        p8->setGeometry(QRect(910, 510, 101, 131));
        p8->setStyleSheet(QString::fromUtf8(""));
        d1 = new QWidget(frame);
        d1->setObjectName("d1");
        d1->setGeometry(QRect(20, 30, 101, 131));
        d1->setStyleSheet(QString::fromUtf8(""));
        d2 = new QWidget(frame);
        d2->setObjectName("d2");
        d2->setGeometry(QRect(150, 30, 101, 131));
        d2->setStyleSheet(QString::fromUtf8(""));
        d3 = new QWidget(frame);
        d3->setObjectName("d3");
        d3->setGeometry(QRect(280, 30, 101, 131));
        d3->setStyleSheet(QString::fromUtf8(""));
        d4 = new QWidget(frame);
        d4->setObjectName("d4");
        d4->setGeometry(QRect(400, 30, 101, 131));
        d4->setStyleSheet(QString::fromUtf8(""));
        d5 = new QWidget(frame);
        d5->setObjectName("d5");
        d5->setGeometry(QRect(520, 30, 101, 131));
        d5->setStyleSheet(QString::fromUtf8(""));
        d6 = new QWidget(frame);
        d6->setObjectName("d6");
        d6->setGeometry(QRect(650, 30, 101, 131));
        d6->setStyleSheet(QString::fromUtf8(""));
        d7 = new QWidget(frame);
        d7->setObjectName("d7");
        d7->setGeometry(QRect(780, 30, 101, 131));
        d7->setStyleSheet(QString::fromUtf8(""));
        d8 = new QWidget(frame);
        d8->setObjectName("d8");
        d8->setGeometry(QRect(910, 30, 101, 131));
        d8->setStyleSheet(QString::fromUtf8(""));
        math = new QPushButton(frame);
        math->setObjectName("math");
        math->setGeometry(QRect(390, 650, 100, 100));
        math->setCursor(QCursor(Qt::PointingHandCursor));
        math->setStyleSheet(QString::fromUtf8("border-image:url(:/math.jpg)"));
        doubledown = new QPushButton(frame);
        doubledown->setObjectName("doubledown");
        doubledown->setGeometry(QRect(520, 650, 100, 100));
        doubledown->setCursor(QCursor(Qt::PointingHandCursor));
        doubledown->setStyleSheet(QString::fromUtf8("border-image:url(:/doubledown.png)"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1025, 25));
        menubar->setStyleSheet(QString::fromUtf8(""));
        menuO_programie = new QMenu(menubar);
        menuO_programie->setObjectName("menuO_programie");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuO_programie->menuAction());
        menuO_programie->addAction(actionAutor);
        menuO_programie->addAction(actionZasady);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BlackJack by Wiktor Lewicki", nullptr));
        actionAutor->setText(QCoreApplication::translate("MainWindow", "Autor", nullptr));
        actionZasady->setText(QCoreApplication::translate("MainWindow", "Zasady", nullptr));
        stan_konta->setText(QCoreApplication::translate("MainWindow", "Stan konta: 0 EUR", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "ZASIL KONTO", nullptr));
        bet->setText(QString());
        stand->setText(QString());
        hit->setText(QString());
        math->setText(QString());
        doubledown->setText(QString());
        menuO_programie->setTitle(QCoreApplication::translate("MainWindow", "O programie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
