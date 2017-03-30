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

#include "lcd8bits.h"

/*********************************** FUNÇÔES DO LCD *******************************************/ 

/* *********************************************************************************************
   Função: pulse (Habilita_LCD)
   Função de habilitação do LCD
   Descrição: Seta o bit Enable (E) aguarda a temporização (~15ms) e reseta
*/
void pulse(void) 
{    
    LCM_CTL |= EN;
    __delay_cycles(2000);
    
    LCM_CTL &= ~EN;
    __delay_cycles(2000);
}

/* *********************************************************************************************
   Função de envio de um byte de comando ou dado para o LCD
   Descrição: O dado ou comando a ser enviado é de 8 bits
   Entrada: 8 bits a serem enviados e definição se é dado (TRUE) ou comando (FALSE)
   Saída: 8 bits do comando ou dado
*/
void SendByte(char ByteToSend, char IsData) 
{
    
    LCM_OUT = ByteToSend;
  
    if (IsData == TRUE) LCM_CTL |= RS;      // Seta o bit RS se for um dado a ser enviado 
    else LCM_CTL &= ~RS;                    // Reseta o bit RS se for um comando a ser enviado
    pulse();                                // Habilita o LCD (E=1) depois desabilita (E=0)

    LCM_OUT = 0x00;
}

/* *********************************************************************************************
   Função: LCM_init (Programa_LCD)
   Função de configuração do LCD
*/
void LCM_init(void) 
{
    LCM_DIR1 |= MASK;
    LCM_DIR2 |= CONTROL;
    LCM_OUT &= ~MASK;
   
    SendByte(0x38, FALSE);                    // Display de 8 bits de dados – 2 linha – Matriz 5x8
    SendByte(0x0C, FALSE);                    // Display ativo e cursor inativo
    SendByte(0x06, FALSE);                    // Deslocamento do cursor p/ direita
    SendByte(0x01, FALSE);                    // Limpeza do display
}

/* *********************************************************************************************
   Função: Clear (Limpa_LCD)
   Função para limpar o LCD
*/
void clear(void) 
{
    SendByte(0x01, FALSE);    // Comando para limpeza do LCD (0x01)
    SendByte(0x02, FALSE);    // Comando para retorna o cursor para a 1 coluna da 1 Linha
    __delay_cycles(100000);
}

/* *********************************************************************************************
   Função: MoveCursor (Posiciona_cursor)
   Função para posicionar o cursor no LCD
*/
void MoveCursor(char Row, char Col) 
{
    char address;
    if (Row == 0) address = 0;
    else address = 0x40;
    address |= Col;
    SendByte(0x80|address, FALSE);
}

/* *********************************************************************************************
   Função: Cursor
   Função para ativar/desativar cursor
*/
void Cursor (char activate)
{
  if (activate == TRUE)
    SendByte(0x0D, FALSE);
  else if (activate == FALSE)
    SendByte(0x0C, FALSE);
}

/* *********************************************************************************************
   Função: Erase
   Função para apagar um caractere da tela
*/
void Erase(void)
{
  SendByte(0x10, FALSE);
  SendByte(0x20, FALSE);
  SendByte(0x10, FALSE);
}

/* *********************************************************************************************
   Função: PrintStr (Mostra_string)
   Função para escrever uma string no LCD
*/
void PrintStr(char *Text) 
{
    char *c;                          // Ponteiro da string
    c = Text;                         // Endereço inicial da string
    while ((c != 0) && (*c != 0)) {   // Enquanto não é o fim da string (00h) 
        SendByte(*c, TRUE);           // Envia caracter apontada para ser exibido no LCD
        c++;                          // Atualiza ponteiro
    }
} 

/* *********************************************************************************************
   Função: PrintNum (Mostra_numero) 
   Função para escrever um número inteiro no LCD 
   O número deve ser < 10.000
*/
void PrintInt(long int num_inteiro)
{
        unsigned char u_milhar, centenas, dezenas, unidades;
        
        u_milhar = num_inteiro / 1000;
        SendByte((u_milhar + 0x30), TRUE);

        centenas = ((num_inteiro - u_milhar*1000)-1) / 100;
        SendByte((centenas + 0x30), TRUE);

        dezenas=(num_inteiro%100)/10;
        SendByte((dezenas + 0x30), TRUE);

	unidades=num_inteiro%10;
        SendByte((unidades + 0x30), TRUE);
}