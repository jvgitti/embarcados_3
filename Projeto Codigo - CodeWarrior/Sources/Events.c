/* ###################################################################
**     Filename    : Events.c
**     Project     : EA076 - Projeto 3
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-01-13, 22:37, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief Arquivo .c que trata das funcoes dos componentes do Processor Expert
**         .
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*!
 * @brief Tecla que foi pressionada no teclado. Variavel declarada na main.
 */
extern volatile uint8_t tecla;

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  C3_OnInterrupt (module Events)
**
**     Component   :  C3 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*!
 * @brief Interrupcao para descobrir qual tecla da terceira coluna foi pressionada
 */
void C3_OnInterrupt(void)
{
	L2_SetInput(); //Garante nivel logico 1 
	L3_SetInput();
	L4_SetInput(); 
	WAIT1_Waitms(100); //Funcao usada para evitar que a varredura aconteca durante o bouncing do botao
	if(!C3_GetVal()) {
		tecla = 3; // Tecla 3 que foi pressionada (col 3, lin 1)
	
	} else {
		L2_SetOutput(); //Garante nivel logico 0
		WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
		if(!C3_GetVal()) {
			tecla = 6; // Tecla 6 que foi pressionada (col 3, lin 2)
	
		} else {
			L3_SetOutput(); //Garante nivel logico 0
			WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
			if(!C3_GetVal()) {
				tecla = 9; // Tecla 9 que foi pressionada (col 3, lin 3)
				
			} else {
				L4_SetOutput(); //Garante nivel logico 0
				WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
				if(!C3_GetVal()) {
					tecla = 12; // Tecla # que foi pressionada (col 4, lin 4) que assume valor 12
					
				}
			}
		}
	}
	L2_SetOutput(); //Por garantia, define-se todos como output novamente para caso de nem todos os if e else tenham sido percorridos
	L3_SetOutput();
	L4_SetOutput();
	WAIT1_Waitus(10);	
}

/*
** ===================================================================
**     Event       :  C2_OnInterrupt (module Events)
**
**     Component   :  C2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*!
 * @brief Interrupcao para descobrir qual tecla da segunda coluna foi pressionada
 */
void C2_OnInterrupt(void)
{
	L2_SetInput(); //Garante nivel logico 1 
	L3_SetInput();
	L4_SetInput(); 
	WAIT1_Waitms(100); //Funcao usada para evitar que a varredura aconteca durante o bouncing do botao
	if(!C2_GetVal()) {
		tecla = 2; // Tecla 2 que foi pressionada (col 2, lin 1)
		
	} else {
		L2_SetOutput(); //Garante nivel logico 0
		WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
		if(!C2_GetVal()) {
			tecla = 5; // Tecla 5 que foi pressionada (col 2, lin 2)
			
		} else {
			L3_SetOutput(); //Garante nivel logico 0
			WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
			if(!C2_GetVal()) {
				tecla = 8; // Tecla 8 que foi pressionada (col 2, lin 3)
				
			} else {
				L4_SetOutput(); //Garante nivel logico 0
				WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
				if(!C2_GetVal()) {
					tecla = 0; // Tecla 0 que foi pressionada (col 2, lin 4)
					
				}
			}
		 }
	}
	L2_SetOutput(); //Por garantia, define-se todos como output novamente para caso de nem todos os if e else tenham sido percorridos
	L3_SetOutput();
	L4_SetOutput();
	WAIT1_Waitus(10);
}

/*
** ===================================================================
**     Event       :  C1_OnInterrupt (module Events)
**
**     Component   :  C1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*!
 * @brief Interrupcao para descobrir qual tecla da primeira coluna foi pressionada
 */
void C1_OnInterrupt(void)
{
  L2_SetInput(); //Garante nivel logico 1 
  L3_SetInput();
  L4_SetInput(); 
  WAIT1_Waitms(100); //Funcao usada para evitar que a varredura aconteca durante o bouncing do botao
  if(!C1_GetVal()) {
	  tecla = 1; // Tecla 1 que foi pressionada (col 1, lin 1)
	  
  } else {
	  L2_SetOutput(); //Garante nivel logico 0
	  WAIT1_Waitms(10); //Tempo para garantir a passagem da linha de saida para a entrada
	  if(!C1_GetVal()) {
		  tecla = 4; // Tecla 4 que foi pressionada (col 1, lin 2)
		  
	  } else {
		  L3_SetOutput(); //Garante nivel logico 0
		  WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
		  if(!C1_GetVal()) {
			  tecla = 7; // Tecla 7 que foi pressionada (col 1, lin 3)
			  
		  } else {
			  L4_SetOutput(); //Garante nivel logico 0
			  WAIT1_Waitus(10); //Tempo para garantir a passagem da linha de saida para a entrada
			  if(!C1_GetVal()) {
				  tecla = 10; // Tecla * que foi pressionada (col 1, lin 4) que assume valor 10
				  
			  }
		  }
	  }
  }
  L2_SetOutput(); //Por garantia, define-se todos como output novamente para caso de nem todos os if e else tenham sido percorridos
  L3_SetOutput();
  L4_SetOutput();
  WAIT1_Waitus(10);
}

/*
** ===================================================================
**     Event       :  PC_OnError (module Events)
**
**     Component   :  PC [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PC_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PC_OnRxChar (module Events)
**
**     Component   :  PC [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PC_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PC_OnTxChar (module Events)
**
**     Component   :  PC [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PC_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ESP_OnError (module Events)
**
**     Component   :  ESP [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ESP_OnRxChar (module Events)
**
**     Component   :  ESP [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*!
** @brief  Funcao que trata a chegada de caracter ao ESP para montar uma string
*/
void ESP_OnRxChar(void)
{
	  extern volatile uint8_t rcv[100]; //buffer da mensagem (resposta) recebida
	  extern volatile uint8_t posit; //posição no buffer rcv
	  extern volatile char message; //flag para sinalizar que a mensagem foi recebida
	  uint8_t c;
	  
	  ESP_RecvChar(&c); // lê o caracter e colocar na variável c criada
	  rcv[posit] = c; // aloca o caracter recebido no posição x do buffer rcv
	  posit++; // incrementa a posição do buffer rcv para apontar para o próximo slot vazio 
	  if(c == 0x0A){ // se o caracter for quebra de linha
		  rcv[posit] = 0; // coloca um 0 no fim do buffer rcv para determinar o fim da string
	  	  posit = 0; // zera a posição do buffer
	  	  message = 1; 
	  }
}

/*
** ===================================================================
**     Event       :  ESP_OnTxChar (module Events)
**
**     Component   :  ESP [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ESP_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*!
** @brief  Interrupcao para que, a cada 1 segundo, uma flag de atualizacao de data/hora seja ativada
*/
void TI1_OnInterrupt(void)
{
	extern uint8_t flagdata;
	flagdata = 1;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
