#include "serilport.h"
#include "ui_serilport.h"

SerilPort::SerilPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerilPort)
{
    ui->setupUi(this);
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        QSerialPort  serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite)){
            ui->cBox_Port->addItem(serial.portName());
            serial.close();
        }
    }
    ui->cBox_Baud->setCurrentIndex(3);
    ui->B_Sent->setEnabled(false);

}

SerilPort::~SerilPort()
{
    delete ui;
    delete serial;
}

void SerilPort::Read_Data()
{
    QByteArray buf;
    buf=serial->readAll();
    if(!buf.isEmpty()){
        QString str=ui->ReceiveText->toPlainText();
        str+=tr(buf);
        ui->ReceiveText->clear();
        ui->ReceiveText->append(str);
    }
    buf.clear();
}

void SerilPort::on_B_Open_clicked()
{
    if(ui->B_Open->text()==tr("打开串口"))
    {
        serial=new QSerialPort;
        serial->setPortName(ui->cBox_Port->currentText());
        if(!serial->open(QIODevice::ReadWrite)){
            qDebug() <<"Do Not Open the Port";
        }
        //设置波特率
        serial->setBaudRate(ui->cBox_Baud->currentText().toInt());

        //设置数据位数
        switch(ui->cBox_Data->currentIndex())
        {
        case 8:serial->setDataBits(QSerialPort::Data8);break;
        default: break;
        }
         //设置奇偶校验
        switch(ui->cBox_Jiaoyan->currentIndex())
        {
        case 0:serial->setParity(QSerialPort::NoParity);break;
        default:break;
        }
        //设置停止位
        switch (ui->cBox_Stop->currentIndex()) {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);break;
        default:
            break;
        }

        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        ui->cBox_Port->setEnabled(false);
        ui->cBox_Baud->setEnabled(false);
        ui->cBox_Data->setEnabled(false);
        ui->cBox_Jiaoyan->setEnabled(false);
        ui->cBox_Stop->setEnabled(false);
        ui->B_Open->setText(tr("关闭串口"));
        ui->B_Sent->setEnabled(true);
        connect(serial,SIGNAL(readyRead()),this,SLOT(Read_Data()));
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->cBox_Port->setEnabled(true);
        ui->cBox_Baud->setEnabled(true);
        ui->cBox_Data->setEnabled(true);
        ui->cBox_Jiaoyan->setEnabled(true);
        ui->cBox_Stop->setEnabled(true);
        ui->B_Open->setText(tr("打开串口"));
        ui->B_Sent->setEnabled(false);
    }

}

void SerilPort::on_B_Clear_clicked()
{
    ui->ReceiveText->clear();
}

void SerilPort::on_B_Sent_clicked()
{
    if(!ui->SentText->toPlainText().isEmpty()){
          if(serial->write(ui->SentText->toPlainText().toLatin1())>0){
                   qDebug()<<"Sent successed";
          }

    }

}
