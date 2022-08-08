#include<mbed.h>
#include<math.h>
#include<Servo.h>

int P_max = 10; // Valor máximo para a normalização
int P_min = 0; // Valor mínimo para a normalização
CAN CAN_msg(p30, p29);

int main(void)
{

    int aux, Ang_n, motor;
    // Definição dos servos e configuração da pinagem
    // Perna 1
    Servo P1_ELEV(p21);
    Servo P1_ROT(p22);
    // Perna 3
    Servo P3_ELEV(p23);
    Servo P3_ROT(p24);
    // Perna 5
    Servo P5_ELEV(p25);
    Servo P5_ROT(p26);

    while (1) {
        CANMessage msg;
        if(CAN_msg.read(msg)) {
            // Recebimento mensagem CAN (1 parte: motor, 2 parte: angulo)
            motor = msg.data[0];
            float ang = msg.data[1];
            switch(motor) {
                case 0:
                    aux = P1_ELEV;
                    float Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) { // Elevação
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) { // Retorno
                        aux -= Ang_n/10;
                    }
                    P1_ELEV = aux; //Atualização dos valores
                case 1:
                    aux = P1_ROT;
                    Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) {
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) {
                        aux -= Ang_n/10;
                    }
                    P1_ROT = aux; //Atualização dos valores
                case 2:
                    aux = P3_ELEV;
                    Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) {
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) {
                        aux -= Ang_n/10;
                    }
                    P3_ELEV = aux; //Atualização dos valores
                case 3:
                    aux = P3_ROT;
                    Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) {
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) {
                        aux -= Ang_n/10;
                    }
                    P3_ROT = aux; //Atualização dos valores
                case 4:
                    aux = P5_ELEV;
                    Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) {
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) {
                        aux -= Ang_n/10;
                    }
                    P5_ELEV = aux; //Atualização dos valores
                case 5:
                    aux = P5_ROT;
                    Ang_n = (ang - P_min) / (P_max - P_min); //Normalização dos valores
                    while (Ang_n > aux) {
                        aux += Ang_n/10;
                    }
                    while (Ang_n < aux) {
                        aux -= Ang_n/10;
                    }
                    P5_ROT = aux; //Atualização dos valores
            }
            }
    }
}