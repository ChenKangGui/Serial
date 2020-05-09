#ifndef MYSQLITE_H
#define MYSQLITE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QLabel>
#include <QLineEdit>
#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息

namespace Ui {
class mySqlite;
}

class mySqlite : public QMainWindow
{
    Q_OBJECT

public:
    explicit mySqlite(QWidget *parent = 0);
    ~mySqlite();

    //创建串口对象
    QSerialPort serial;
    void scene_Init();

private slots:
 //   void on_send_btn_pressed();
    void serialPort_readyRead();

    void on_checkSerial_Btn_pressed();

    void on_clear_Btn_pressed();

    void on_send_Btn_pressed();

    void on_open_Btn_pressed();

private:
    Ui::mySqlite *ui;
};

#endif // MYSQLITE_H
