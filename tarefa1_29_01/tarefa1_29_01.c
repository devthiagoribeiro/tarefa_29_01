#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Define os pinos dos LEDs
#define ledRed 11
#define ledYellow 12
#define ledGreen 13

// Array de estados dos LEDs: {vermelho, amarelo, verde}
const int ledStates[][3] = {
    {1, 0, 0},  // Estado 0: Vermelho
    {0, 1, 0},  // Estado 1: Amarelo
    {0, 0, 1}   // Estado 2: Verde
};

int currentState = 1;  // Índice do estado atual (começa com 1, já que o primeiro estado vermelho é acionado dentro da main)

// Função para controlar os LEDs
void ledsControl(int red, int yellow, int green){
    gpio_put(ledRed, red);      // Define o estado do LED vermelho
    gpio_put(ledYellow, yellow); // Define o estado do LED amarelo
    gpio_put(ledGreen, green);  // Define o estado do LED verde
}

// Função de callback chamada pelo timer a cada 3 segundos
bool repeating_timer_callback(struct repeating_timer *t){
    // Controla os LEDs com base no estado atual
    ledsControl(ledStates[currentState][0], ledStates[currentState][1], ledStates[currentState][2]);
    
    // Avança para o próximo estado (usando módulo para garantir que o índice volte a 0 após o último estado)
    currentState = (currentState + 1) % 3;  // 3 é o número de estados

    return true;  // Retorna true para manter o timer ativo
}

int main()
{
    // Inicializa os pinos dos LEDs como saída
    gpio_init(ledRed);
    gpio_init(ledYellow);
    gpio_init(ledGreen);
    gpio_set_dir(ledRed, GPIO_OUT);
    gpio_set_dir(ledYellow, GPIO_OUT);
    gpio_set_dir(ledGreen, GPIO_OUT);

    // Inicializa a comunicação serial (para debug, se necessário)
    stdio_init_all();

    // Configura um timer repetitivo para chamar a função de callback a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Configura um tempo inicial para a mensagem de 1 segundo
    absolute_time_t message_time = delayed_by_ms(get_absolute_time(), 1000);

    // Inicia o semáforo com o LED vermelho aceso
    ledsControl(1, 0, 0);

    // Loop principal
    while (true) {
        // Verifica se 1 segundo passou
        if(time_reached(message_time)){
            printf("1 segundo\n");  // Imprime uma mensagem a cada segundo
            message_time = delayed_by_ms(message_time, 1000);  // Atualiza o tempo para o próximo segundo
        }
        sleep_ms(1);  // Pausa o loop por 1 milissegundo para evitar uso excessivo da CPU
    }
}