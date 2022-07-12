#include<mbed.h>
#include<math.h>
#include<Servo.h>

#define int P_max = 10; 
#define int P_min = 0;

int main(void){

	int aux, Ang_n;

	Servo P1_ELEV(p21);
	Servo P1_ROT(p22);

	Servo P3_ELEV(p23);
	Servo P3_ROT(p24);

	Servo P5_ELEV(p25);
	Servo P5_ROT(p26);

	// Recebimento mensagem CAN (1 parte: motor, 2 parte: angulo)

	switch(){
		case 0:
			aux = P1_ELEV;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P1_ELEV = aux; //Atualização dos valores
		case 1:
			aux = P1_ROT;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P1_ROT = aux; //Atualização dos valores
		case 2:
			aux = P3_ELEV;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P3_ELEV = aux; //Atualização dos valores
		case 3:
			aux = P3_ROT;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P3_ROT = aux; //Atualização dos valores
		case 4:
			aux = P5_ELEV;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P5_ELEV = aux; //Atualização dos valores
		case 5:
			aux = P5_ROT;
			Ang_n = (Ang - P_min) / (P_max - P_min) //Normalização dos valores
			while (Ang_n > aux){
				aux += Ang_n/10;
			}
			while (Ang_n < aux){
				aux -= Ang_n/10;
			}
			P5_ROT = aux; //Atualização dos valores
	}
}