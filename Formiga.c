// Para reduzir o código os valores dos motores foram armazenados em matrizes rotação e elevação
// Composição das Matrizes: M1 M4
//                          M2 M5
//                          M3 M6

// MatrizControle: Mx_Elev_Subir
//                 Mx_Rot_Avancar
//                 Mx_Elev_Descer
//                 Mx_Rot_Recuar


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

//Matrizes para o controle dos motores
int MatrizControle[4][1] = {
	{0},
	{0},
	{0},
	{0}
};
int MatrizElevacao[3][2];
int MatrizRotacao[3][2];

// Posições atuais recebem os valores iniciais
for(int i = 0, i<3, i++){
	for (int j = 0; j<2; j++)
	{
		MatrizElevacao[i][j] = MatrizElevInicial[i][j];
		MatrizRotacao[i][j] = MatrizRotInicial[i][j];
	}
}

// Variável para sincronização dos movimentos (fase entre os dois conjuntos de pernas)

boolean P1_SINC = LOW;

int dir = 0; // Direção do movimento: Repouso (0), Frente (1), Direita (2), Esquerda (3), Trás (4)
int delay_speed = 50; // Velocidade da formiga (através do controle do delay entre incrementos)
int delay_inicial = 1; // Velocidade de retorno à posição inicial (para evitar movimento abrupto e brusco)

//Variáveis DUMMY simulando comunicação Linux
int DUMMY_LINUX_CONNECTION; // Checar se a conexão está funcionando
int DUMMY_LINUX_DATA; // Dado recebido pela comunicação

void main() {

  while(1) {

  // Checar recebimento de dados (LINUX)
    if (DUMMY_LINUX_CONNECTION > 0) {
      dir = DUMMY_LINUX_DATA;  // Leitura do dado

      // FRENTE
      if (dir == 1) {
        MoverPerna(P1);5
        MoverPerna(P3);
        MoverPerna(P5);
        if (P1_SINC == HIGH) {
        	MoverPerna(P2);
        	MoverPerna(P4);
        	MoverPerna(P6);
        }
      }
      // DIREITA
      if (dir == 2) {
        MoverPernaRev(P1);
        MoverPernaRev(P3);
        MoverPerna(P5);
        if (P1_SINC == HIGH) {
          	MoverPernaRev(P2);
          	MoverPerna(P4);
          	MoverPerna(P6);
        }
      }
      // ESQUERDA
      if (dir == 3) {
        MoverPerna(P1);
        MoverPerna(P3);
        MoverPernaRev(P5);
        if (P1_SINC == HIGH) {
          	MoverPerna(P2);
          	MoverPernaRev(P4);
          	MoverPernaRev(P6);
        }
      }
      // TRÁS
      if (dir == 4) {
        MoverPernaRev(P1);
        MoverPernaRev(P3);
        MoverPernaRev(P5);
        if (P1_SINC == HIGH) {
          	MoverPernaRev(P2);
        	MoverPernaRev(P4);
        	MoverPernaRev(P6);
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
    delay(delay_speed); 
  }
}

void MoverPerna() {

}

void MoverPernaRev() {

}