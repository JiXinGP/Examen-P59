#include "imc.h"
#include "ui_imc.h"
#include <cstdlib>
#include <QMessageBox>
#include <QFile>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>


IMC::IMC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IMC)
{
    ui->setupUi(this);
}

IMC::~IMC()
{
    delete ui;
}

void IMC::limpiar()
{
    ui->inAltura->setValue(0);
    ui->inPeso->setValue(0);

}

void IMC::calcular()
{
    float altura = ui->inAltura->value();
    float peso = ui->inPeso->value();
    if (peso==0 || altura==0){
        QMessageBox::warning(this,"Advertencia", "La altura o el peso esatá vacio" );
        return;
    }
    float st= (peso/(altura*altura))*10000;
    ui->outIMC->setText(QString:: number(st)+ " kg/m²");
    ui->outAltura->setText(QString::number(altura)+" cm");
    ui->outActual->setText(QString::number(peso)+ " kg");
    ui->outMax->setText((QString::number(peso)+" kg"));
    ui->outMin->setText((QString::number(peso)+ " kg"));
    if(st < 18.5){
        ui->outimc->setText("Bajo peso");
    }else if(st < 24.9){
        ui->outimc->setText("Normal");
    }else if(st < 29.9){
        ui->outimc->setText("Sobrepeso");
    }else if(st >=30){
        ui->outimc->setText("Obeso");
    }
    mover(st);

    limpiar ();
}

void IMC::guardar()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un 'stream' de texto
        QTextStream salida(&archivo);
          //           +"Altura: *"+ QString ::number(altura)+"*\n"
             //       +"Peso: "+QString::number(peso)+"\n"
               //     +"IMC: "+ QString::number(st);
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 5000);
    }else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
    }
    // Cerrar el archivo
    archivo.close();

}

void IMC::abrir()
{

}

void IMC::mover(float st)
{
    if(st <=12 || st <= 18.5 ){
        ui->outLinea->setGeometry(10,0,0,80);
    }else if(st <= 20||st <= 24.5){
        ui->outLinea->setGeometry(90,0,0,80);
    }else if(st <= 25||st <= 29.9){
        ui->outLinea->setGeometry(150,0,0,80);
    }else if(st <= 34||st >38){
        ui->outLinea->setGeometry(300,0,0,80);
    }
}


void IMC::on_btnCalcular_clicked()
{
    calcular();
}


void IMC::on_action_Nuevo_triggered()
{
    limpiar();
    ui->outIMC->clear();
    ui->outActual->clear();
    ui->outAltura->clear();

}


void IMC::on_action_Abrir_triggered()
{
    abrir();
}


void IMC::on_action_Guardar_triggered()
{
    guardar();
}


void IMC::on_action_Calcular_triggered()
{
    calcular();
}


void IMC::on_action_Salir_triggered()
{
    close();
}

