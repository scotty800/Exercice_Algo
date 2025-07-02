#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SIZE 64
#define MAX_MSG_LEN 128
#define TIMEOUT_TICKS 5

typedef struct RxBuffer
{
    char data[SIZE];
    int head;
    int tail;
} RxBuffer;

int rxbuffer_is_empty(RxBuffer *buf)
{
    return buf->head == buf->tail;
}

int rxbuffer_is_full(RxBuffer *buf)
{
    return (buf->head + 1) % SIZE == buf->tail;
}

void rxbuffer_push(RxBuffer *buf, char c)
{
    if (rxbuffer_is_full(buf))
    {
        printf("Buffer is full ! ");
        return;
    }

    buf->data[buf->head] = c;
    buf->head = (buf->head + 1) % SIZE;
}

char rxbuffer_pop(RxBuffer *buf)
{
    if (rxbuffer_is_empty(buf))
    {
        printf("Buffer is empty !");
        return '\0';
    }

    c = buf->data[buf->tail];
    buf->tail = (buf->tail + 1) % SIZE;
    return c;
}
//----------------------------------------UART_RX-----------------------------//
typedef enum RxState
{
    RX_IDLE,
    RX_RECEIVING,
    RX_DONE,
    RX_ERROR 
}

typedef struct UART_RX
{
    RxBuffer Uart_Buffer;
    RxState Uart_State;
    int msg_index;
    char message[MAX_MSG_LEN];
    int timer_timeout;
}

void uart_rx_interrupt(UART_RX *uart, char c)
{
    if (uart->Uart_State == RX_IDLE && c != '\n')
    {
        uart->Uart_State == RX_RECEIVING
        uart->msg_index = 0;
    }

    if (uart->Uart_State == RX_RECEIVING)
    {
        uart->tick_timer = TIMEOUT_TICKS;
        if (uart->msg_index >= MAX_MSG_LEN)
        {
            uart_rx_is_error(&uart);
        }
        uart->message[uart->msg_index++] = c;
        rxbuffer_push(&uart->Uart_Buffer, c);

        if (c == '\n')
        {
            uart->message[uart->msg_index] = '\0';
            uart->Uart_State == RX_DONE;
        }
    }
}

void uart_rx_reset(UART_RX *uart)
{
    uart->Uart_State = RX_IDLE;
    uart->Uart_Buffer.head = 0;
    uart->Uart_Buffer.tail = 0;
    uart->msg_index = 0;
    uart->timer_timeout = 0;
}

int uart_rx_is_error(UART_RX *uart)
{
    if (uart->msg_index >= MAX_MSG_LEN -1)
    {
        return uart->Uart_State == RX_ERROR;
    }
}

void uart_rx_tick(UART_RX *uart)
{
    if (uart->Uart_State != RX_RECEIVING)
    {
        return;
    }

    if (uart->timer_timeout > 0)
    {
        uart->tick_timer--;
    }

    if (uart->timer_timeout == 0)
    {
        printf("⏱️ Timeout de réception atteint !\n");
        uart->Uart_State == RX_ERROR;
    }
}

//----------------------------------------UART_TX-----------------------------//
typedef struct UART_TX
{
    RxBuffer Tx_buffer;
    int busy;
} UART_TX;

void uart_tx_send_char(UART_TX *uart, char c)
{
    rxbuffer_push(uart->tx_buffer, c);
}

void uart_tx_tick(UART_TX *uart)
{
    char c;
    if (uart->busy)
    {
        uart->busy = 0;
        return;
    }

    if (!buffer_is_empty(&uart->tx_buffer))
    {
        c = rxbuffer_pop(&uart->tx_buffer);
        printf("UART TX : '%c'\n", c);
        uart->busy = 1;
    }
}



int main()
{
    UART_RX uart;
    uart_rx_reset(&uart);
    char *simulate_input = "HELLO";
    char c;
    int i;

    for (i = 0; simulate_input[i] != '\0'; i++)
    {
        c = simulate_input[i];

        uart_rx_tick(&uart);
        uart_tx_tick(&uart);
        uart_rx_interrupt(&uart, c);

        printf("Caractère reçu : '%c' | État : %s | Message partiel : \"%.*s\"\n", c, uart.Uart_State, uart.msg_index, uart.message);

        if (uart->Uart_State == RX_DONE)
        {
            printf("Message complet reçu : \"%s\"\n\n", uart.message);
            uart_rx_reset(&uart);
        }
        if (uart_rx_is_error(&uart)) 
        {
            printf("Erreur détectée : dépassement ou caractère invalide.\n\n");
            uart_rx_reset(&uart);
        }
        
    }

}

