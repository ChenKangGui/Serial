#include "mysqlite.h"
#include "ui_mysqlite.h"
#include <QMessageBox>

mySqlite::mySqlite(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mySqlite)
{
    ui->setupUi(this);

    scene_Init();
}

mySqlite::~mySqlite()
{
    delete ui;
}

void mySqlite::scene_Init()
{
    this->setFixedSize(1050, 830);
    this->setWindowTitle("Nicholas的助手");

    ui->serial->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serial->addItem(info.portName());
    }
}


void mySqlite::serialPort_readyRead()
{
    //从接收缓冲区中读取数据
    QByteArray buffer = serial.readAll();

    //从界面中读取以前收到的数据
    QString recv = ui->recv_Label->document()->toPlainText();
    recv += QString(buffer);
    //清空以前的显示
    ui->recv_Label->clear();
    //重新显示
    ui->recv_Label->append(recv);
}

void mySqlite::on_checkSerial_Btn_pressed()
{
    ui->serial->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serial->addItem(info.portName());
    }
}

void mySqlite::on_clear_Btn_pressed()
{
    ui->recv_Label->clear();
}

void mySqlite::on_send_Btn_pressed()
{
    QByteArray data = ui->send_Label->text().toUtf8();
    serial.write(data);
}

void mySqlite::on_open_Btn_pressed()
{
    if(ui->open_Btn->text() == "打开串口")
    {
        //设置串口名
        serial.setPortName(ui->serial->currentText());

        //设置波特率
        serial.setBaudRate(ui->bound->currentText().toInt());
        //设置数据位数
        switch (ui->data->currentText().toInt())
        {
            case 8: serial.setDataBits(QSerialPort::Data8); break;
            default: break;

        }
        //设置奇偶校验
        switch (ui->parity->currentText().toInt())
        {
            case 0: serial.setParity(QSerialPort::NoParity); break;
            default: break;
        }
        switch(ui->stop->currentText().toInt())
        {
            case 1: serial.setStopBits(QSerialPort::OneStop); break;
            case 2: serial.setStopBits(QSerialPort::TwoStop); break;
            default: break;
        }

        //设置流控制
        serial.setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if(serial.open(QIODevice::ReadWrite)!=true)
        {
            QMessageBox::about(NULL, "提示", "无法打开串口！");
            return;
        }
        QObject::connect(&serial, &QSerialPort::readyRead, this, &mySqlite::serialPort_readyRead);
        ui->open_Btn->setText("关闭串口");
    }
    else
    {
        serial.close();
        ui->open_Btn->setText("打开串口");
        //ui->send_Btn->setEnabled(false);
    }
}
