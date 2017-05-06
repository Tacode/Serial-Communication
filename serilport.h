#ifndef SERILPORT_H
#define SERILPORT_H

#include <QWidget>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QString>
#include<QByteArray>
#include<QDebug>
namespace Ui {
class SerilPort;
}

class SerilPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerilPort(QWidget *parent = 0);
    ~SerilPort();
private slots:
    void Read_Data();

    void on_B_Open_clicked();

    void on_B_Clear_clicked();

    void on_B_Sent_clicked();

private:
    Ui::SerilPort *ui;
    QSerialPort *serial;
};

#endif // SERILPORT_H
