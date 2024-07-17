#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void resetuj();
    void pokaz(std::string s, bool who);
    void update_money();
    void wygrana();
    void przegrana();
    void bet_end();
    void on_bet_clicked();

    void on_stand_clicked();

    void on_hit_clicked();

    void on_actionAutor_triggered();

    void on_actionZasady_triggered();

    void on_math_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
