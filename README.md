<h1 align="center"> Self Balancing Robot </h1>
<p  align="center"> 
    This is a self balancing robot made with arduino, that is, a robot with 2 wheels that will have to balance itself. <br>
    :construction:  Project under construction  :construction:
</p>

<h2 align="center">  🔗 Resumo do projeto </h2>

- Será utilizado o motor driver TB6612FNG para controlar os 2 motores, conectados cada um a um encoder para ter mais precisão no controle.
- Poderemos controlar o robô por um controle remoto DIY baseado na transmissão por rádio (NRF24L01).
- E também pelo celular (bluetooth - HC-05) através de um app feio no MIT App Invetor.
- Através do acelerômetro/giroscópio de 3 eixos MPU6050 será medido a angulação do rôbo, que deverá sempre se manter a aproximadamente 90° no eixo x.
- Para fazer o controle, será usado o PID controller (controlador proporcional integral derivativo).
- O regulador buck step down vai fornecer +6V ao motores através da ponte-H, a bateria vai direto alimentar o arduino.
- Existe um limite mínimo de tensão da bateria para que o robô funcione normalmente, abaixo desse nível será sinalizado mau funcionamento.
- Possui um buzzer para emitir sinais sonoros, como de buzina, de aviso de baixa bateria, ou de aviso de obstáculo.
- Para ligar/desligar o carro haverá um interruptor para esse funcionamento.

<h2 align="center">  📁 Descrição dos arquivos </h2>

- Self-Balancing-Robot-main.ino -> arquivo que fica o programa principal
- diagrama.fzz -> arquivo que fica todas as ligações do projeto

<h2 align="center">  🛠️ Lista de itens </h2>

- 3 placas de acrílico preta ?cmX?cm
- 1 placa de fenolite ?cmX?cm
- Arduino nano
- 2 motores com encoder + 2 rodas
- 1 ponte-H TB6612FNG
- 1 NRF24L01
- 1 HC-05
- 1 MPU6050
- 1 HC-SR04
- 2 baterias de lítio de 4.2V + suporte
- 1 chave liga/desliga
- 1 regulador de tensão buck setp down LM2596
- 1 buzzer
- Divisor de tensão e led vermelho para medir/sinalizar nível da bateria
- Capacitores, resistores, diodo, parafusos, porcas, bornes KRE 2 vias, barras de pinos fêmea e macho, fios, solda.

<h2 align="center">  ✔️ Técnicas e tecnologias utilizadas </h2>

- ``Arduino``
- ``C++``
- ``POO``
- ``PID controller``
