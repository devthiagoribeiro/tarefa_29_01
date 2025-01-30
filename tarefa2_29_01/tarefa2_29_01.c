#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define ledBlue 11
#define ledRed 12
#define ledGreen 13
#define btn 5

bool routine = false;  // Controla se a rotina está em execução
int currentState = 0;  // Controla o estado atual da rotina

// Função para controlar os LEDs
void ledsControl(int blue, int red, int green){
    gpio_put(ledBlue, blue);
    gpio_put(ledRed, red);
    gpio_put(ledGreen, green);
}

// Função de callback para controlar a rotina dos LEDs
int64_t turn_off_callback(alarm_id_t id, void *user_data){
    switch (currentState) {
        case 0:
            ledsControl(0, 1, 1);  // Vermelho e verde acesos
            currentState = 1;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agenda o próximo estado
            break;
        case 1:
            ledsControl(0, 0, 1);  // Apenas verde aceso
            currentState = 2;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agenda o próximo estado
            break;
        case 2:
            ledsControl(0, 0, 0);  // Todos os LEDs apagados
            routine = false;       // Finaliza a rotina
            currentState = 0;
            break;
    }
    return 0;  
}

int main()
{
    // Inicializa os pinos dos LEDs e do botão
    gpio_init(ledBlue);
    gpio_init(ledRed);
    gpio_init(ledGreen);
    gpio_init(btn);
    gpio_set_dir(ledBlue, GPIO_OUT);
    gpio_set_dir(ledRed, GPIO_OUT);
    gpio_set_dir(ledGreen, GPIO_OUT);
    gpio_set_dir(btn, GPIO_IN);
    gpio_pull_up(btn);  // Habilita o resistor de pull-up no botão

    stdio_init_all();  // Inicializa a comunicação serial (para debug)

    while (true) {
        // Verifica se o botão foi pressionado
        if (!gpio_get(btn) && !routine) {
            sleep_ms(50);  // Debounce simples
            if (!gpio_get(btn)) {  // Confirma o pressionamento
                routine = true;  // Inicia a rotina
                ledsControl(1, 1, 1);  // Liga todos os LEDs
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agenda o primeiro estado
            }
        }
        sleep_ms(1);
    }
}