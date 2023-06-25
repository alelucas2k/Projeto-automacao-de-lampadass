/*#include "stm32f4xx.h"
#include "Utility.h"
#include <stdio.h>

void USART2_Init(void)
{
    // Configuração do USART2
    // Por exemplo:
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;      // Habilita o clock do GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;     // Habilita o clock da USART2

    GPIOA->AFR[0] |= 0x7700;                  // Configura o pino PA2 como AF7 (USART2_TX)
    GPIOA->MODER |= GPIO_MODER_MODER2_1;      // Configura o pino PA2 como AF

    USART2->BRR = 0x0683;                     // Configura a taxa de baud rate para 9600
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Habilita a transmissão e a recepção

    USART2->CR1 |= USART_CR1_UE;              // Habilita a USART2
}

void USART2_SendChar(char ch)
{
    // Envio de caractere via USART2
    // Por exemplo:
    while (!(USART2->SR & USART_SR_TXE));      // Espera até que o registrador de transmissão esteja vazio
    USART2->DR = ch;                           // Envia o caractere
}

char USART2_ReceiveChar(void)
{
    // Recebimento de caractere via USART2
    // Por exemplo:
    while (!(USART2->SR & USART_SR_RXNE));     // Espera até que o caractere seja recebido
    return USART2->DR;                         // Retorna o caractere recebido
}

void RF433_Init(void)
{
    // Inicialização do módulo RF433 usando a biblioteca específica
    // Por exemplo:
    rf433_init(); // Função de inicialização fornecida pela biblioteca RF433
}

void RF433_SendData(const char* data)
{
    // Envio de dados via RF433 usando a biblioteca específica
    // Por exemplo:
    rf433_send(data); // Função de envio fornecida pela biblioteca RF433
}

void RF433_ReceiveData(char* buffer)
{
    // Recebimento de dados via RF433 usando a biblioteca específica
    // Por exemplo:
    rf433_receive(buffer); // Função de recebimento fornecida pela biblioteca RF433
}

int main(void)
{
    USART2_Init();
    RF433_Init();

    char sendData[] = "Hello, RF433!";
    RF433_SendData(sendData);

    char receivedData[20];
    RF433_ReceiveData(receivedData);
    printf("Received data: %s\n", receivedData);

    while (1)
    {
        // Outras operações
    }
}*/

#include "stm32f4xx.h"
#include "Utility.h"
#include <stdio.h>

int main(void){
	projeto();
}
void projeto();

void projeto(void){


	Utility_Init();
	USART1_Init();        //função que permite usar o printf no STM32

		    RCC->AHB1ENR |= 1;
		    RCC->AHB1ENR |= 1<<2;
		    GPIOA->MODER |= 0b11;                    //pino PA0 como entrada analógica
		    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;        //liga o clock do ADC1
		    ADC->CCR |= 0b01 << 16;                 //prescaler /4 (fADC=21MHz)
		    ADC1->SQR1 &= ~(0xF << 20);             //conversão de apenas um canal
		    ADC1->SQR3 &= ~(0x1F);                     //seleção do canal a ser convertido (IN_0)
		    ADC1->CR2 |= 1;                         //liga o conversor AD


		    while(1){
				ADC1->CR2 |= 1 << 30;             //inicia a conversão
				while(!(ADC1->SR & 0x02));         //aguarda o fim da conversão
				uint16_t leitura = ADC1->DR;     //faz a leitura do valor convertido
				printf("Leitura = %d\n", leitura);
				Delay_ms (500);
				if(leitura <= 150){
					RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;   // Habilita o clock do GPIOB
					GPIOB->MODER |= GPIO_MODER_MODER6_0;   // Configura o pino PB6 como saída
					GPIOB->OTYPER |= GPIO_OTYPER_OT_6;      // Defi-ne o tipo de saída do pino PB6 como pushpull

					GPIOB->ODR &= ~(1 << 6);   // Nível lógico baixo no pino PB6
				}
				else{
					 RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;   // Habilita o clock do GPIOB
					 GPIOB->MODER |= GPIO_MODER_MODER6_0;   // Configura o pino PB6 como saída
					 GPIOB->OTYPER |= GPIO_OTYPER_OT_6;      // Define o tipo de saída do pino PB6 como push-pull

					 GPIOB->ODR |= (1 << 6);    // Nível lógico alto no pino PB6
				}
		    }
}
