# ATTA
Projeto final da matéria **SEM0544 - Sistemas Embarcados (2022)**

## Alunos
* [Leandro Yuji Kanno](https://github.com/L-Yuji) (NºUSP 10883811)
* [Vinícius Motta Benatti](https://github.com/benattiv) (NºUSP 10820762)

## Introdução
Visto que a automação de processos têm permeado diversas áreas do cotidiano, a necessidade de novas tecnologias aplicáveis às mais diversas funções tem crescido progressivamente. Perante o exposto, um Sistema Embarcado, diferentemente de um computador, é geralmente gerenciado por um microcontrolador inteiramente dedicado ao controle de uma função ou de um sistema específico. Ou seja, é construído para executar uma tarefa específica, podendo funcionar isoladamente ou em conjunto com outros sistemas.

Sendo assim, o projeto tem o objetivo de arquitetar um sistema embarcado e programá-lo de forma a implementar a lógica de caminhada de um robô hexápode. Tornando este hardware apto a servir com base para diversas aplicações futuras como, por exemplo, a adição de uma câmera para realizar vistorias em ambientes de difícil acesso. Ademais, o projeto proposto viabiliza a prática de conteúdos teóricos passados nas aulas expositivas.

### Proposta
O projeto possui o objetivo de implementar o movimento de caminhada de um robô hexápode. Para isso, o hardware utilizado é composto por 12 servomotores de aeromodelismo, sendo dois motores por perna: um responsável pela elevação e o outro pela translação; uma placa Toradex VF50, responsável por controlar todo o sistema e duas MBEDs, que funcionarão como sistemas escravos controlando os servos. A princípio, o foco foi no desenvolvimento do código da caminhada, de forma a deixá-lo funcional e preparado para a comunicação entre dispositivos. Infelizmente, como ambos os membros do grupo estão fazendo estágio fora de São Carlos, não foi possível realizar testes práticos com os códigos de forma presencial utilizando o hardware disponibilizado.

## Desenvolvimento
A primeira etapa do desenvolvimento foi delinear a lógica de funcionamento do sistema. Com o objetivo de possibilitar, posteriormente, a elaboração de um algoritmo funcional para o controle do movimento do robô. 

Uma das primeiras dificuldades encontradas foi o fato de a Toradex não apresentar saídas de PWM suficientes para todos os motores. Dessa forma, surgiu a necessidade da utilização de 2 MBEDs com o papel de placas auxiliares (sistemas escravos) para controlar os motores. Cada uma foi responsável pelo controle das pernas pares e  ímpares, como ilustrado na figura abaixo. Entretanto, com seu uso surge outro empecilho: a comunicação entre as placas. Dentre as diversas soluções possíveis para este problema, foi decidido utilizar o protocolo CAN para realizar o envio de dados e a sincronização entre as três placas.

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

Após a definição do hardware, o projeto passa a ser segmentado em duas partes: uma para desenvolvimento do código da movimentação e outra, para o algoritmo responsável pela comunicação entre as três placas, seguindo o protocolo CAN.

### Movimentação
Para a elaboração da lógica da caminhada diferentes tipos de movimentação eram possíveis. Visando tornar o código mais leve, a orientação seguida na programação descreve a movimentação independente entre as pernas pares e ímpares. Além de fornecer um algoritmo mais leve, este tipo de caminhada também gera uma maior estabilidade, pois sempre haverá no mínimo 3 pernas em contato com o solo. Para auxiliar o desenvolvimento deste código, foi construído o fluxograma abaixo.

![Caminhada](https://user-images.githubusercontent.com/90531157/177643280-b7854ac2-6927-4a58-9bca-78a4a54f6e1e.jpg)

A partir dessas diretrizes, a escrita do código [Formiga.c](Formiga.c) responsável por todo o comando do movimento das pernas foi iniciada. Nele, o controle dos motores é realizado por meio de uma lógica incremental das variáveis que, ao chegarem a um valor final, são enviadas para as MBEDs via protocolo CAN. Para facilitar esta implementação do movimento, ele foi dividido em 4 etapas, sendo elas:
* 1 - Elevação da perna;
* 2 - Translação (frente ou trás);
* 3 - Abaixamento da perna;
* 4 - Retornar à posição inicial.

Além disso, foi concebido o algoritmo [mbed.c](mbed.c) responsável por rodar nas MBEDs, através do recebimento das variáveis, normalização e envio para os motores por meio da biblioteca Servo.h. Com o objetivo de reduzir a quantidade de envios de dados, necessários para a movimentação, entre as placas a Toradex é responsável por enviar o valor final da posição dos servos. Enquanto a MBED possui o papel de realizar a normalização e o incremento nos motores até atingir um valor final. Os códigos para ambas as MBEDs são iguais, mudando apenas o controle de quais pernas são encarregadas: de  1, 3 e 5 para 2, 4 e 6.

### Protocolo CAN
O protocolo de comunicação em série Controller Area Network (CAN), desenvolvido nos anos 80 pela Bosch GmbH, permite o controle em tempo real com elevado nível de segurança, sendo possível integração multi-mestre com múltiplos destinatários (multicast). Cada mensagem transmitida no nó é acompanhada por um identificador, que, através dele, é informada tanto a prioridade quanto se o receptor deve ou não processá-la.
O CAN é um sistema de barramento serial em que cada mensagem contém, no máximo, 8 bytes ou 40 bits. Contudo, é possível o envio de mensagens maiores através da segmentação. Para o projeto desenvolvido o tamanho padrão das mensagens é suficiente, visto que são necessárias duas informações por motor: qual motor está sendo movido e o valor de sua posição final, totalizando no mínimo 12 dos 40 bits.

A mensagem contendo a posição final é enviada aos MBEDs, que, a partir dela, coordenam os motores cuja competência confere à placa, pares ou ímpares, para a execução do movimento. O protocolo CAN0 é acessível via Linux na placa Colibri VF50 através dos pinos 196/194 ou, o CAN1, por meio dos pinos 63/55, contudo, são necessárias alterações, cujas instruções fornecidas pelo fabricante podem ser encontradas na página https://developer.toradex.com/linux-bsp/how-to/peripheral-access/can-linux/#bsp5. 

![Config CAN](https://user-images.githubusercontent.com/90531157/182658771-19529594-8db5-466a-9d74-f192e97adb32.jpeg)

Já as MBEDs têm, por padrão, o protocolo CAN acessível através dos pinos 29/30.

## Resultados e discussão
A princípio, como a comunicação entre placas não havia sido desenvolvida, o código da caminhada ([Formiga.c](Formiga.c)) foi verificado por meio de printfs e scanfs que, posteriormente, seriam substituídos pelo envio de dados via protocolo CAN, de forma a buscar com que o sistema funcionasse conforme traçado no planejamento inicial. Essa avaliação teve como objetivo a análise comparativa entre as saídas e o esperado teórico para a movimentação síncrona das pernas. Todavia, devido a contratempos, a implementação da comunicação não pode ser realizada.

Sabendo disso, o cross-compile do código foi testado à distância, utilizando o SDK para gerar o executável em arquitetura ARM.  Dessa forma, foi possível testar o código no sistema embarcado por meio das placas disponibilizadas pelos professores via AnyDesk.

![caminhada](https://user-images.githubusercontent.com/90531157/182653525-9d54adf1-4003-4eab-9c34-5298089a4916.png)

Na imagem acima encontram-se os valores que seriam enviados para as MBEDs, onde seriam normalizados e repassados para os servomotores. Os seis conjuntos de dados correspondem a um ciclo completo do programa, conforme o fluxograma apresentado anteriormente. Deles, os três primeiros conjuntos são referentes às pernas ímpares, enquanto os que se encontram após a sincronização são referentes às pernas pares. Cabe observar que os valores variam de motor para motor, visto que as entradas iniciais são aleatórios e seriam definidos posteriormente de maneira empírica. Assim,  os resultados obtidos são coerentes com os testes do código responsável pela lógica do movimento do robô.

Já sobre o código [mbed.c](mbed.c), não foi possível testá-lo nas MBEDs devido a ambos os membros estarem fora de São Carlos, não podendo utilizar a placa disponibilizada.

## Conclusão
Apesar da impossibilidade de implementação prática dos códigos e visualização do sistema eletromecânico devido ao acesso impossibilitado dos membros, afastados de São Carlos por estagiar em cidades distantes, foram, através das práticas realizadas em sala de aula e programação remota, alcançados os fins acadêmicos da disciplina, como a familiarização com o Linux e, no contexto de sistemas embarcados, seus módulos, protocolos, terminologias e paradigmas. 
