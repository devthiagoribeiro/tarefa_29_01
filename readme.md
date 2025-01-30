# TAREFA - AS_U4C5O1234E_29_01_2025

Este repositório contém a implementação de duas atividades relacionadas ao uso de temporizadores e LEDs com o microcontrolador Raspberry Pi Pico W, utilizando o Pico SDK e o simulador Wokwi.

## Atividade 1: Temporizador Periódico (Semáforo)

### Descrição
Nesta atividade, foi implementado um semáforo utilizando um temporizador periódico com a função `add_repeating_timer_ms()`. O semáforo alterna entre três estados (vermelho, amarelo e verde) a cada 3 segundos.

### Componentes Utilizados
- Microcontrolador Raspberry Pi Pico W.
- 03 LEDs (vermelho, amarelo e verde).
- 03 Resistores de 330 Ω.

### Funcionamento
1. O semáforo inicia com o LED vermelho aceso.
2. Após 3 segundos, o LED amarelo é aceso.
3. Após mais 3 segundos, o LED verde é aceso.
4. O ciclo se repete indefinidamente.

### Código
O código principal está no arquivo [tarefa1_29_01.c](./tarefa1_29_01/tarefa1_29_01.c). A função de callback `repeating_timer_callback()` é responsável por alternar os estados dos LEDs.

### Como Executar
1. Abra o simulador Wokwi.
2. Carregue o código `tarefa1_29_01.c`.
3. Conecte os LEDs aos pinos GPIO do Raspberry Pi Pico W conforme a configuração sugerida.
4. Execute a simulação e observe o funcionamento do semáforo.

[verificando que os leds alternam corretamente a cada 3 segundos](https://drive.google.com/file/d/1aNX68ON3uIO9iTQiY7dueCdGBBX9vmeJ/view?usp=sharing)

---

## Atividade 2: Temporizador de Um Disparo (One Shot)

### Descrição
Nesta atividade, foi implementado um sistema de temporização para o acionamento de LEDs utilizando a função `add_alarm_in_ms()`. O sistema é acionado por um botão (pushbutton) e os LEDs mudam de estado a cada 3 segundos.

### Componentes Utilizados
- Microcontrolador Raspberry Pi Pico W.
- 03 LEDs (azul, vermelho e verde).
- 03 Resistores de 330 Ω.
- 01 Botão (Pushbutton).

### Funcionamento
1. Ao pressionar o botão, todos os LEDs são acesos.
2. Após 3 segundos, dois LEDs permanecem acesos.
3. Após mais 3 segundos, apenas um LED permanece aceso.
4. Após mais 3 segundos, todos os LEDs são apagados.
5. O botão só pode ser pressionado novamente após o término da rotina.

### Código
O código principal está no arquivo [tarefa2_29_01.c](./tarefa2_29_01/tarefa2_29_01.c). A função de callback `turn_off_callback()` é responsável por alternar os estados dos LEDs.

### Como Executar
1. Abra o simulador Wokwi.
2. Carregue o código `one_shot.c`.
3. Conecte os LEDs e o botão aos pinos GPIO do Raspberry Pi Pico W conforme a configuração sugerida.
4. Execute a simulação e observe o funcionamento do sistema ao pressionar o botão.

[verificando que o botão aciona a sequência de LEDs e se ele só pode ser pressionado novamente após o término da rotina.](https://drive.google.com/file/d/14J2MAruIkmR0KNBOsao2nwHtLU6GLHho/view?usp=sharing)

---
> **Obs.: Todos os códigos foram testados na placa BitDogLab**

## Requisitos
- Ambiente de desenvolvimento: VS Code.
- Kit de Desenvolvimento de Software: Pico SDK.
- Simulador: Wokwi integrado ao VS Code.
- Linguagem de programação: C.