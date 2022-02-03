#ifndef IMC_H
#define IMC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IMC; }
QT_END_NAMESPACE

class IMC : public QMainWindow
{
    Q_OBJECT

public:
    IMC(QWidget *parent = nullptr);
    ~IMC();
private slots:
    void on_btnCalcular_clicked();

    void on_action_Nuevo_triggered();

    void on_action_Abrir_triggered();

    void on_action_Guardar_triggered();

    void on_action_Calcular_triggered();


    void on_action_Salir_triggered();

private:
    Ui::IMC *ui;

    float m_altura;
    float m_peso;
    float m_imc;

    void limpiar ();
    void calcular();
    void guardar();
    void abrir();
    void mover(float st);

};
#endif // IMC_H
