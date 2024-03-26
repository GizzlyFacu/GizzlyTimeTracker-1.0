#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <nlohmann/json.hpp>
#include <QFile>
#include <memory>
#include <vector>
#include <QDebug>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer=new QTimer(this);
    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(timerDoSomething()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------
struct Datos{
    QString name;
    int seg;
};

nlohmann::json jsonFile;
QFile jsonExport("settings.txt");

std::vector<std::unique_ptr<Datos>> datosVector;
//------------------------------------------

void CrearDatos(QString nameDato = "default name", int segDato=0){
    std::unique_ptr<Datos> newDato = std::make_unique<Datos>();
    newDato->name=nameDato;
    newDato->seg=segDato;
    datosVector.push_back(std::move(newDato));
}

void MainWindow::on_buttonCrear_clicked()
{
    CrearDatos();
    ui->cBox_Biblio->addItem(datosVector.back()->name);
}


void MainWindow::on_cBox_Biblio_currentIndexChanged(int index)
{
    if(ui->cBox_Biblio->count()>0){
        ui->lineEdit_Name->setText(datosVector[index]->name);
        ui->labelHour->setText(QString::number(
            datosVector[ui->cBox_Biblio->currentIndex()]->seg
            ));
    }
    else {
        ui->lineEdit_Name->setText("zzz");
    }
    m_timer->stop();
    ui->buttonStart->setText("Iniciar");

}


void MainWindow::on_buttonBorrar_clicked()
{

    if (ui->cBox_Biblio->count()>0){
        JSONclear();
        auto posicion = datosVector.begin()+ui->cBox_Biblio->currentIndex();
        datosVector.erase(posicion);
        ui->cBox_Biblio->removeItem(ui->cBox_Biblio->currentIndex());
    }
}


void MainWindow::on_buttonStart_clicked()
{

        if(m_timer->isActive()==false && ui->cBox_Biblio->count()>0)   {
            m_timer->start(1000);
            ui->buttonStart->setText("Detener");
            qDebug()<<"el timer se ha iniciado";

            ui->buttonBorrar->setEnabled(0);
            ui->buttonCrear->setEnabled(0);
            ui->buttonImportar->setEnabled(0);


        }
        else{
            m_timer->stop();
            ui->buttonStart->setText("Iniciar");
            qDebug()<<"el timer se ha apagado";

            ui->buttonBorrar->setEnabled(1);
            ui->buttonCrear->setEnabled(1);
            ui->buttonImportar->setEnabled(1);
        }
}

void MainWindow::timerDoSomething()
{
    if(ui->cBox_Biblio->count()>0){

        datosVector[ui->cBox_Biblio->currentIndex()]->seg++;
        /*
        ui->labelHour->setText(QString::number(
            datosVector[ui->cBox_Biblio->currentIndex()]->seg
            ));
        */
        int segundos=datosVector[ui->cBox_Biblio->currentIndex()]->seg;
        int horas, minutos, segundos_restantes;
        // Calcula las horas
        horas = segundos / 3600;

        // Calcula los segundos restantes después de quitar las horas
        segundos_restantes = segundos % 3600;

        // Calcula los minutos
        minutos = segundos_restantes / 60;

        // Calcula los segundos finales
        segundos_restantes = segundos_restantes % 60;

        // Imprime el resultado en formato HH:MM:SS
        QString shownText=QString::number(horas) + ":" + QString::number(minutos) + ":" + QString::number(segundos_restantes);
        ui->labelHour->setText(shownText);
    }


}



void MainWindow::on_lineEdit_Name_textChanged(const QString &arg1)
{
    if (!datosVector.empty()){
        ui->cBox_Biblio->setItemText(ui->cBox_Biblio->currentIndex(),arg1);
        datosVector[ui->cBox_Biblio->currentIndex()]->name=arg1;
    }

}


void MainWindow::on_buttonGuardar_clicked()
{
    if(ui->cBox_Biblio->count()>0){
        JSONsave();
    }
    else{
        qDebug()<<"no hay items que guardar";
        jsonFile={};
        if(jsonExport.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&jsonExport);
            out<<QString::fromStdString(jsonFile.dump(4));
            jsonExport.close();
        }
    }

}

void MainWindow::JSONsave()
{
    {
        for(int i=0; i<(ui->cBox_Biblio->count());i++){
            std::string listIndex=std::to_string(i);
            std::string listName=datosVector[i]->name.toStdString();
            std::string listSegs=std::to_string(datosVector[i]->seg);

            jsonFile[listIndex][listName]=listSegs;
        }
        jsonExport.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&jsonExport);

        out<<QString::fromStdString(jsonFile.dump(4));

        jsonExport.close();
    }
    jsonExport.close();
}

void MainWindow::JSONreading(){
    if(jsonExport.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&jsonExport);
        QString data= in.readAll();
        jsonFile=nlohmann::json::parse(data.toStdString());
        qDebug()<<jsonFile.dump();
        if(jsonFile.dump()=="{}"){
            qDebug()<<"está vacio";
            jsonExport.close();
            return;
        };

        jsonExport.close();
        JSONuploading();
    }
    else{
        qDebug()<<"no se han encontrado el archivo de configuraciones";
    }
    jsonExport.close();
}

void MainWindow::JSONuploading(){
    QString nameDato;
    QString segDatoCrudo;
    int segDato;

    for(auto& index : jsonFile.items()){
        qDebug()<<"aniadiendo items en el index: "<<index.key();

        for(auto& data : jsonFile[index.key()].items()){

            nameDato = QString::fromStdString(data.key());
            segDatoCrudo = QString::fromStdString(jsonFile[index.key()][data.key()].get<std::string>());
            segDato = segDatoCrudo.toInt();

            qDebug()<<"Name: "<<nameDato;
            qDebug()<<"Segs: "<<segDato;

            CrearDatos(nameDato,segDato);
            ui->cBox_Biblio->addItem(datosVector.back()->name);
            ui->cBox_Biblio->setCurrentIndex(static_cast<int>(datosVector.size())-1);
        }

    }
}

void MainWindow::JSONclear()
{

    //leyendo primero la informacion a modificar
    QString data;
    if(jsonExport.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&jsonExport);
        data=in.readAll();


        //modificando
        jsonFile=nlohmann::json::parse(data.toStdString());
        jsonFile.erase(std::to_string(ui->cBox_Biblio->currentIndex()));
        jsonExport.close();

        //exportando el archivo modificado
        jsonExport.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&jsonExport);
        out<<QString::fromStdString(jsonFile.dump(4));
        jsonExport.close();
    }
    jsonExport.close();
}

void MainWindow::on_buttonImportar_clicked()
{
    JSONreading();
}

