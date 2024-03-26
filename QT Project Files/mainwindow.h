#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>

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
public slots:
    void timerDoSomething();
    void JSONsave();
    void JSONreading();
    void JSONuploading();
    void JSONclear();
private slots:
    void on_buttonCrear_clicked();

    void on_cBox_Biblio_currentIndexChanged(int index);

    void on_buttonBorrar_clicked();

    void on_buttonStart_clicked();

    void on_lineEdit_Name_textChanged(const QString &arg1);

    void on_buttonGuardar_clicked();

    void on_buttonImportar_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
};
#endif // MAINWINDOW_H
