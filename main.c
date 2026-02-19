#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "millis.h"

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
#define LED_RED_PIN 4
#define LED_YELLOW_PIN 3
#define LED_GREEN_PIN 2

int main(void) {
    
    // DATA DIRECTION REGISTER B
    BIT_SET(DDRB, LED_RED_PIN);
    BIT_SET(DDRB, LED_YELLOW_PIN);
    BIT_SET(DDRB, LED_GREEN_PIN);

    millis_init();
    sei();
    
    millis_t millis_since_last_loop = 0;
    millis_t current_millis = 0;
    millis_t delta_millis = 0;

    BIT_SET(PORTB, LED_RED_PIN);
    BIT_CLEAR(PORTB, LED_YELLOW_PIN);
    BIT_CLEAR(PORTB, LED_GREEN_PIN);

    while (1) {
        current_millis = millis_get();
        delta_millis = current_millis - millis_since_last_loop;

        if (delta_millis >= 14000) {
            BIT_CLEAR(PORTB, LED_YELLOW_PIN);
            BIT_SET(PORTB, LED_RED_PIN);

            millis_since_last_loop = current_millis; // Behöver bara uppdateras i slutet på loopen
        }
        else if (delta_millis >= 12000) {
            BIT_CLEAR(PORTB, LED_GREEN_PIN);
            BIT_SET(PORTB, LED_YELLOW_PIN);
        }
        else if (delta_millis >= 7000) {
            BIT_CLEAR(PORTB, LED_YELLOW_PIN);
            BIT_SET(PORTB, LED_GREEN_PIN);
        }
        else if (delta_millis >= 5000) {
            BIT_CLEAR(PORTB, LED_RED_PIN);
            BIT_SET(PORTB, LED_YELLOW_PIN);
        }
    }
	return 0;
}