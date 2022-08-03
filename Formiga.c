#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Para reduzir o código os valores dos motores foram armazenados em matrizes rotação e elevação
// Composição das Matrizes: P1 P4
//                          P2 P5
//                          P3 P6
// MatrizControle: Px_Elev_Subir
//                 Px_Rot_Avancar
//                 Px_Elev_Descer
//                 Px_Rot_Recuar
// Definir matrizes iniciais (repouso)
const int MatrizElevInicial[3][2] = {
	{60, 65},
	{50, 80},
	{50, 90}
};
const int MatrizRotInicial[3][2] = {
	{100, 40},
	{75, 25},
	{80, 60}
};
// Matrizes para o controle dos motores
int MatrizControle[4][1] = {
	{0},
	{0},
	{0},
	{0}
};
int MatrizElevacao[3][2];
int MatrizRotacao[3][2];

// Variável para sincronização dos movimentos (fase entre os dois conjuntos de pernas)
bool P1_SINC = 0;

int dir = 1; // Direção do movimento: Repouso (0), Frente (1), Direita (2), Esquerda (3), Trás (4)
int delay_speed = 1; // Velocidade da formiga (através do controle do delay entre incrementos)
int delay_inicial = 1; // Velocidade de retorno à posição inicial (para evitar movimento abrupto e brusco)

//Variáveis DUMMY simulando comunicação Linux
int DUMMY_LINUX_CONNECTION = 1; // Checar se a conexão está funcionando
int DUMMY_LINUX_DATA = 1; // Dado recebido pela comunicação

void sleep(unsigned int);

void MoverPerna(int i, int j) {
	printf("Elevação inicial: %d\n", MatrizElevacao[i][j]);
	printf("Rotação inicial: %d\n", MatrizRotacao[i][j]);
	//Parte 1: levantar a perna
	while (MatrizControle[0][0] <= 10){
		MatrizElevacao[i][j] += MatrizControle[0][0]*2;
		MatrizControle[0][0]++;
	}
	// CAN
	printf("1 - Elevação: %d\n", MatrizElevacao[i][j]); //inicialmente os printf foram utilizados para testar o código
	//Parte 2: rotacionar perna para frente
	while (MatrizControle[1][0] <= 30){
		MatrizRotacao[i][j] += MatrizControle[1][0];
		MatrizControle[1][0]++;
	}
	// CAN
	printf("2 - Rotação: %d\n", MatrizRotacao[i][j]);
	//Parte 3: abaixar a perna
	while (MatrizControle[2][0] <=10){
		MatrizElevacao[i][j] -= MatrizControle[2][0]*2;
		MatrizControle[2][0]++;
	}
	// CAN
	printf("3 - Elevação: %d\n", MatrizElevacao[i][j]);
	//Parte 4: retornar a perna para a posição inicial
	while (MatrizControle[3][0] <= 30){
		MatrizRotacao[i][j] -= MatrizControle[3][0];
		MatrizControle[3][0]++;
	}
	// CAN
	printf("4 - Rotação: %d\n", MatrizRotacao[i][j]);
	//Parte 5: resetar valores da MatrizControle
	while (MatrizControle[3][0] >= 30){
		MatrizControle[0][0] = 0;
		MatrizControle[1][0] = 0;
		MatrizControle[2][0] = 0;
		MatrizControle[3][0] = 0;		
	}
}

void MoverPernaRev(int i, int j) {
		//Parte 1: levantar a perna
	while (MatrizControle[0][0] <= 10){
		MatrizElevacao[i][j] += MatrizControle[0][0]*2;
		MatrizControle[0][0]++;
	}
	// CAN
	//Parte 2: rotacionar perna para tras
	while (MatrizControle[1][0] <= 30){
		MatrizRotacao[i][j] -= MatrizControle[1][0];
		MatrizControle[1][0]++;
	}
	// CAN
	//Parte 3: abaixar a perna
	while (MatrizControle[2][0] <=10){
		MatrizElevacao[i][j] -= MatrizControle[2][0]*2;
		MatrizControle[2][0]++;
	}
	// CAN
	//Parte 4: retornar a perna para a posição inicial
	while (MatrizControle[3][0] <= 30){
		MatrizRotacao[i][j] += MatrizControle[3][0];
		MatrizControle[3][0]++;
	}
	// CAN
	//Parte 5: resetar valores da MatrizControle
	while (MatrizControle[3][0] >= 30){
		MatrizControle[0][0] = 0;
		MatrizControle[1][0] = 0;
		MatrizControle[2][0] = 0;
		MatrizControle[3][0] = 0;		
	}
}

void PosicaoInicial() {
	// Retornat para a posição inicial
	for (int i = 0; i<3; i++){
		for (int j = 0; j<2; j++){
			if (MatrizElevacao[i][j] > MatrizElevInicial[i][j]){
				while (MatrizElevacao[i][j] > MatrizElevInicial[i][j]){
					MatrizElevacao[i][j]--;
				}
			}
			if (MatrizElevacao[i][j] < MatrizElevInicial[i][j]){
				while (MatrizElevacao[i][j] < MatrizElevInicial[i][j]){
					MatrizElevacao[i][j]++;
				}
			}
			if (MatrizRotacao[i][j] > MatrizRotInicial[i][j]){
				while (MatrizRotacao[i][j] > MatrizRotInicial[i][j]){
					MatrizRotacao[i][j]--;
				}
			}
			if (MatrizRotacao[i][j] < MatrizRotInicial[i][j]){
				while (MatrizRotacao[i][j] < MatrizRotInicial[i][j]){
					MatrizRotacao[i][j]--;
				}
			}
		}
	}
}

int main(void) {

	int aux;

	// Posições atuais recebem os valores iniciais
	for(int i = 0; i<3; i++){
		for(int j = 0; j<2; j++){
			MatrizElevacao[i][j] = MatrizElevInicial[i][j];
			MatrizRotacao[i][j] = MatrizRotInicial[i][j];
		}
	}

  	while(1) {

  		// Checar recebimento de dados (LINUX)
    	if (DUMMY_LINUX_CONNECTION > 0) {
      	dir = DUMMY_LINUX_DATA;  // Leitura do dado

	      	// FRENTE
	      	if (dir == 1){
	        	MoverPerna(0, 0);
	        	MoverPerna(1, 1);
	        	MoverPerna(2, 0);
	        	printf("Sinc? ");
	        	scanf("%d", &aux);
	        	P1_SINC = aux;
	        	if (P1_SINC == 1){
	        		MoverPerna(0, 1);
	        		MoverPerna(1, 0);
	        		MoverPerna(2, 1);
	        	}
	      	}
	      	// DIREITA
	      	if (dir == 2) {
	        	MoverPernaRev(0, 0);
	        	MoverPernaRev(1, 1);
	        	MoverPerna(2, 0);
	        	printf("Sinc? ");
	        	scanf("%d", &aux);
	        	P1_SINC = aux;
	        	if (P1_SINC == 1){
	          		MoverPernaRev(0, 1);
	          		MoverPerna(1, 0);
	          		MoverPerna(2, 1);
	        	}
	      	}
	      	// ESQUERDA
	      	if (dir == 3){
	        	MoverPerna(0, 0);
	        	MoverPerna(1, 1);
	        	MoverPernaRev(2, 0);
	        	printf("Sinc? ");
	        	scanf("%d", &aux);
	        	P1_SINC = aux;
	        	if (P1_SINC == 1){
	          		MoverPerna(0, 1);
	          		MoverPernaRev(1, 0);
	          		MoverPernaRev(2, 1);
	        	}
	      	}
	      	// TRÁS
	      	if (dir == 4){
	        	MoverPernaRev(0, 0);
	        	MoverPernaRev(1, 1);
	        	MoverPernaRev(2, 0);
	        	printf("Sinc? ");
	        	scanf("%d", &aux);
	        	P1_SINC = aux;
	        	if (P1_SINC == 1){
          			MoverPernaRev(0, 1);
        			MoverPernaRev(1, 0);
        			MoverPernaRev(2, 1);
        		}
      		}
      		// POSIÇÃO INICIAL (REPOUSO) 
      		if (dir == 0) {
        		PosicaoInicial();
      		}
    	}

    	// Sem sinal (Bluetooth) => Posição Inicial (Repouso)
    	else {
      		dir = 0;
      		PosicaoInicial();
    	}
    
    	// Delay para controlar velocidade do movimento
    	sleep(delay_speed); 
 	}
}
