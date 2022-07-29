# ATTA
Projeto final da matéria **SEM0544 - Sistemas Embarcados (2022)**

## Alunos
* [Leandro Yuji Kanno](https://github.com/L-Yuji) (NºUSP 10883811)
* [Vinícius Motta Benatti](https://github.com/benattiv) (NºUSP 10820762)

## Introdução

## Proposta
O projeto possui o objetivo de implementar o movimento de caminhada de um robô hexapode. O hardware utilizado é composto por 12 servo motores de aeromodelismo, sendo 2 para cada perna, uma placa Toradex VF50, responsável por controlar todo o sistema, e duas MBEDS, que funcionarão como sistemas escravos controlando os servos. A princípio, focamos no desenvolviemnto do código da caminhada, buscando deixa-lo funcional e preparado para a cominicação entre dispositivos. Infelizmente, como ambos os membros do grupo estão fazendo estágio fora de São Carlos, não foi possível realizar testes práticos com os códigos desenvolvidos utilizando o hardware disponibilizado.

## Desenvolvimento
A primeira etapa do desenvolvimento foi projetar a lógica do funcionamento do sistema, para depois programar o movimento do robô e a comunicação entre as placas. 

Como a Toradex não apresenta saídas de PWM suficientes para todos os motores, decidimos utilizar 2 MBEDS como placas auxiliares (sistemas escravos) para controlar os motores, deixando uma delas com as pernas pares e a outra com as ímpares como mostrado na figura abaixo.

![Formiga](https://user-images.githubusercontent.com/90531157/177629817-9f1fb4b1-df85-41d5-8581-431c12337dc5.jpg)

<table>
  <tr>
    <td><img src="Toradex.jpg" width=400></td>
    <td><img src="mbed.jpg" width=450></td>
  </tr>
    <tr>
    <td>Toradex VF50 </td>
     <td>MBED</td>
  </tr>
 </table>

Após a definição do hardware, dividimos o projeto em duas partes, uma para desenvolver o código da movimentação e outra para desenvolver o código para a comunicação entres as três placas por meio do protocolo CAN.

### Movimentação
Durante o desenvolvimento da lógica da caminhada nos deparamos com diferentes tipos de movimentos possíveis. Visando tornar o código mais leve, decidimos programar o movimento de forma que as pernas pares e ímpares possuam movimentos separados. Esse tipo de caminhada também gera uma maior estabilidade, pois sempre haverão no mínimo 3 pernas em contato com o solo. Para auxilixar o desenvolvimento do código, produzimos o fluxograma abaixo.

![Caminhada](https://user-images.githubusercontent.com/90531157/177643280-b7854ac2-6927-4a58-9bca-78a4a54f6e1e.jpg)

A partir disso começamos a desenvolver o código [Formiga.c](Formiga.c), que é responsável por todo o controle do movimento das pernas. Ele realiza o controle dos motores por meio de uma lógica incremental das variáveis que, ao chegarem ao valor final, serão enviadas para as MBEDs via protocolo CAN. Para facilitar a implementação do movimento, ele foi dividido em 4 estapas, sendo elas:
* 1 - Elevação da perna;
* 2 - Translação (frente ou trás);
* 3 - Abaixamento da perna;
* 4 - Retornar a posição inicial.

Além disso, também realizamos o desenvolvimento do código [mbed.c](mbed.c) que irá rodar nas MBEDs, sendo responsável pelo recebimento das variáveis, normalização e envio para os motores por meio da biblioteca Servo.h. Para reduzir a quantidade de envios necessários para a movimentação, a toradex envia o valor final dos servos e a MBED é responsável por realizar o incremento nos motores até atingir o valor normalizado. Os códigos para ambas as MBEDs são iguais, mudando apenas os motores 1, 3 e 5 para 2, 4 e 6.

### Protocolo CAN
O protocolo de comunicação em série Controller Area Network (CAN), desenvolvido nos anos 80 pela Bosch GmbH, permite o controle em tempo real com elevado nível de segurança, sendo possível integração multi-mestre com múltiplos destinatários (multicast). Cada mensagem transmitida no nó é acompanhada por um identificador, que, através dele, é informada tanto a prioridade quanto se o receptor deve ou não processá-la.
O CAN é um sistema de barramento série em que cada mensagem contém, no máximo, 8 bytes ou 40 bits. Contudo, é possível o envio de mensagens maiores através da segmentação. Para o projeto desenvolvido o tamanho padrão das mensagens é suficiente, visto que são necessárias duas informações por motor: o ângulo, de 0º a 180º, e o sentido do movimento, totalizando no mínimo 12 dos 40 bits.

A mensagem contendo a posição final é enviada aos MBEDs, que, a partir dela, coordena os motores cuja competência confere à placa, pares ou ímpares, para a execução do movimento. O protocolo CAN0 é acessível via Linux na placa Colibri VF50 através dos pinos 196/194 ou, o CAN1, por meio dos pinos 63/55, contudo, são necessárias alterações, cujas instruções fornecidas pelo fabricante podem ser encontradas na página https://developer.toradex.com/linux-bsp/how-to/peripheral-access/can-linux/#bsp5. Já as MBEDs têm, por padrão, o protocolo CAN acessível através dos pinos 29/30.

## Conclusão
Apesar da impossibilidade de implementação prática dos códigos e visualização do sistema eletromecânico devido ao acesso impossibilitado dos membros, afastados de São Carlos por estagiar em cidades distantes, foram, através das práticas realizadas em sala de aula e programação remota, alcançados os fins acadêmicos da disciplina, como a familiarização com o Linux e, no contexto de sistemas embarcados, seus módulos, protocolos, terminologias e paradigmas. 
