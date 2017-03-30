/*******************************************************************************
   CEFET-MG - Eletrônica
   lcd8bits - Biblioteca de funções para MSP430 com LCD 16 x 2 operando a 8 bits.
            
                        MSP430              LCD 16 X 2 8 bits
                  -----------------          ------------
                 |                 |        |            |
                 |                 |        |            |
                 |             P3.7|------->|RS          |
                 |                 |        |            |
                 |             P3.6|------->|E           |
                 |                 |        |            | 
                 |                 |        |            |
                 |                 |        |            |
                 |                 |        |            |
                 |                 |        |            |
                 |                 |        |            |
                 |             P5.0|------->|D0          |
                 |                 |        |            |
                 |             P5.1|------->|D1          |
                 |                 |        |            |
                 |             P5.2|------->|D2          |
                 |                 |        |            |
                 |             P5.3|------->|D3          |
                 |                 |        |            |
                 |             P5.4|------->|D4          |
                 |                 |        |            |
                 |             P5.5|------->|D5          |
                 |                 |        |            |
                 |             P5.6|------->|D6          |
                 |                 |        |            |
                 |             P5.7|------->|D7          |
                 |                 |        |            |
                  -----------------          ------------
      
   Lucas de Sousa Arcanjo
   Agosto/2016
   Desenvolvido com o IAR Embedded Workbench Versão: 6.40.4
   Versão para o kit didático do Laboratório de Sistemas Microprocessados MSP430F1611.
   
   Enderson Neves Cruz
   Maio/2012
   Desenvolvido com IAR Embedded Workbench Versão: 5.40.6
   Versão para ser utilizada com modelos de MSP de 1 porta (exemplo:MSP430G2xxx).
   
   Funções para acionamento do LCD:
   Original: lcddemoG2211.c Copyright 2011, MSPSCI http://mspsci.blogspot.com
   Modificado e ampliado por: Enderson neves Cruz, 2011; Lucas de Sousa Arcanjo, 2016.

*******************************************************************************/

#ifndef LCD16_H_
#define LCD16_H_

/******************************************************************************/
// Bibliotecas a serem usadas
#include <msp430.h>

// Porta de dado e controle do LCM (Liquid Crystal Module)
#define LCM_DIR1 P5DIR
#define LCM_OUT  P5OUT
#define LCM_DIR2 P3DIR
#define LCM_CTL  P3OUT

// Definição dos bits e da mácara de envio para o LCD
#define RS  BIT7                  //ALTERADO DE BIT0 PARA BIT7 (P3)
#define EN  BIT6                  //ALTERADO DE BIT3 PARA BIT6 (P3)
#define D0  BIT0                  //
#define D1  BIT1
#define D2  BIT2
#define D3  BIT3                  //AMPLIADO
#define D4  BIT4
#define D5  BIT5
#define D6  BIT6
#define D7  BIT7
#define CONTROL (RS + EN)
#define MASK    (D0 + D1 + D2 + D3 + D4 + D5 + D6 + D7)

#define FALSE 0
#define TRUE  1

/*  Definição (Protótipo) das funções  */
void LCM_init(void);               // Configuração do LCD
void pulse(void);                  // Habilitação do LCD
void clear(void);                  // Limpar o LCD
void SendByte(char, char);         // Envio de um byte de comando/dado para o LCD
void MoveCursor(char, char);       // Posicionar o cursor no LCD
void Cursor (char);                // Ativa/desativa o cursor
void Erase(void);                  // Apaga um caractere no LCD
void PrintStr(char *);             // Escrever uma string no LCD
void PrintInt(long int num_int);   // Escrever um número inteiro no LCD

#endif /* LCD16_H_ */