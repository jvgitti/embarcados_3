/* ###################################################################
**     Filename    : main.c
**     Project     : EA076 - Projeto 3
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-01-13, 22:37, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief Main do Projeto
** @mainpage EA076 - Projeto 3 : Armazenamento de Dados, Display e teclado
** @authors Guilherme Bithencourt Martinelli (168923) e Joao Victor Gitti Aredes (170715) - Grupo 06
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Display.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "SM1.h"
#include "BackLight.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "L1.h"
#include "BitIoLdd2.h"
#include "L2.h"
#include "BitIoLdd3.h"
#include "L3.h"
#include "BitIoLdd4.h"
#include "L4.h"
#include "BitIoLdd5.h"
#include "C1.h"
#include "ExtIntLdd1.h"
#include "C2.h"
#include "ExtIntLdd2.h"
#include "C3.h"
#include "ExtIntLdd3.h"
#include "Memoria.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "ESP.h"
#include "ASerialLdd1.h"
#include "PC.h"
#include "ASerialLdd2.h"
#include "UTIL1.h"
#include "RTC1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "VERM.h"
#include "LEDpin2.h"
#include "BitIoLdd6.h"
#include "VERD.h"
#include "LEDpin3.h"
#include "BitIoLdd7.h"
#include "AZUL.h"
#include "LEDpin4.h"
#include "BitIoLdd8.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*!
** @brief Componente do RTC
*/
LDD_TDeviceData *DeviceDataPtr;

/*!
** @brief Struct do RTC que armazena Data e Hora
*/
LDD_RTC_TTime DataHora;

/*!
 * @brief Tecla que foi pressionada no teclado. 
 * Se as teclas de 0 a 9 forem pressionadas (variavel tecla = 0 a 9); 
 * Se a tecla * for pressionada (variavel tecla = 10); 
 * Se a tecla # for pressionada (variavel tecla = 12);
 * Quando variavel tecla = 255 significa que nehuma tecla foi pressionada (funciona como uma flag)
 */

volatile uint8_t tecla = 255;

/*!
 * @brief Buffer de 16 bytes 
 */
volatile uint8_t buf[16];

/*!
** @brief Variavel para indicar se houve inscricao nos 6 topicos do MQTT
*/
uint8_t count_sub = 6;

/*!
** @brief buffer de comando a ser escrito
*/
uint8_t cmd[100] = {0}; 

/*!
** @brief string do topico
*/
uint8_t top[50] = {0};
	
/*!
** @brief string do parametro do topico
*/
uint8_t par[50] = {0};
	
/*!
** @brief scanner 1 de string
*/
uint8_t scan = 0; 
	
/*!
** @brief scanner 2 de string
*/
uint8_t scan_2 = 0; 

/*!
** @brief buffer da mensagem recebida
*/
volatile uint8_t rcv[100] = {0}; 
	
/*!
** @brief posicao no buffer rcv
*/
volatile uint8_t posit = 0; 

/*!
** @brief flag para sinalizar que a mensagem foi recebida
*/
volatile char message = 0; 

/*!
** @brief flag para indicar que deve-se atualizar a data/hora do display
*/
uint8_t flagdata = 0;

/*!
** @brief variavel para guardar o dia
*/
uint8_t dia;

/*!
** @brief variavel para guardar o mes
*/
uint8_t mes;

/*!
** @brief variavel para guardar o ano
*/
uint8_t ano;

/*!
** @brief variavel para guardar o segundo
*/
uint8_t segundo;

/*!
** @brief variavel para guardar o minuto
*/
uint8_t minuto;

/*!
** @brief variavel para guardar a hora
*/
uint8_t hora;

/*!
** @brief string para montar a data no formato DD/MM/AAAA
*/
uint8_t data[10];

/*!
** @brief string para montar o horario no formato HH:MM:SS
*/
uint8_t horario[8];

/*!
** @brief string de acesso para confirmar acao do supervisor
*/
uint8_t string_acesso[10] = "123abc";

/*!
** @brief string de acesso que foi inserida nos topicos do MQTT
*/
uint8_t string_acesso_recebida[14];

/*!
** @brief nome de usuario registrado atraves do MQTT
*/
uint16_t nome[16] = {0};

/*!
** @brief ID registrado atraves do MQTT
*/
uint8_t ID;

/*!
** @brief senha registrada atraves do MQTT
*/
uint16_t senha;

/*!
** @brief string para conter a senha de 4 digitos na forma de 2 bytes (MSB e LSB) para escrita na memoria
*/
uint16_t senha_formatada_1[2];

/*!
** @brief flag para indicar que os proximos digitos a serem digitados serao referentes a senha
*/
uint8_t flagsenha = 0;

/*!
** @brief ID inserido pelo teclado
*/
uint8_t ID_teclado = 0;

/*!
** @brief string para armazenar o ID inserido no teclado no formato de string
*/
uint8_t ID_string[2] = {0};

/*!
** @brief senha inserida pelo teclado
*/
uint16_t senha_teclado = 0;

/*!
** @brief variavel de auxilio na leitura da senha gravada da memoria
*/
uint16_t dig1[2] = {0};

/*!
** @brief variavel de auxilio na escrita de * no display referentes a senha
*/
int i=0;

/*!
** @brief variavel para auxilio na montagem de strings
*/
int j=0;

/*!
** @brief senha lida da memoria
*/
uint16_t senha_memoria = 0;

/*!
** @brief String de uma posicao somente para conferir o primeiro o byte (ou caractere) de uma posicao da memoria
** para concluir se tal posicao esta vazia ou nao
*/
char read[1]; 

/*!
** @brief Enviar comando para o ESP e recebe o caracter da string como argumento
*/
void SendCmd(uint8_t * s){ 
	while(*s){ //Permanece dentro do while ate o caracter da string de comando nao for 0 (fim da string)
		while(ESP_SendChar(*s)); //Envia o caracter para o ESP
			s++; //incrementa a posicao em que o ponteiro esta apontando
	}
}
	
/*!
** @brief Enviar string para o PC e recebe o caracter da string como argumento - Mesma ideia da funcao SendCmd 
*/
void SendPC(uint8_t * s){
	while(*s){
		while(PC_SendChar(*s));	
			s++;
	}
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
/*!
** @brief A main faz o processamento da conexao Wi-fi, das teclas pressionadas,
** das publicacoes no MQTT, do display e da escrita e leitura da memoria
*/
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  
  strcpy(cmd, "CONNWIFI \"nome_da_rede\",\"senha_da_rede\"\r\n"); // Comando automatico para conexao com a rede wifi
  SendCmd(cmd); //Envia o comando da conexao wifi para o ESP
  while(message == 0); //Certificar-se que o ESP recebeu a mensagem, pois o codigo saira desse while quando a flag message = 1 (mensagem recebida)
  message = 0; //Zera a flag
  
  if (UTIL1_strcmp(rcv, "CONNECT WIFI\r\n")){ //Comparacao da string de resposta do ESP com a CONNECT WIFI (0- VERDADEIRO, 1- FALSO)
 	  SendPC("WIFI NAO CONECTA\r\n"); //Escreve no PC que nao conectou no WIFI
   } else { //Caso as duas strings sejam iguais
   	  strcpy(cmd, "CONNMQTT \"137.135.83.217\",1883,\"client_ID\"\r\n"); // Comando automatico para conexao com o servidor broker MQTT
   	  SendCmd(cmd); // Envia o comando da conexao broker MQTT para o ESP
   	  while(message == 0);
   	  message = 0;
   	  if(UTIL1_strcmp(rcv, "CONNECT MQTT\r\n")) { //Comparacao da string de resposta do ESP com a CONNECT MQTT (0- VERDADEIRO, 1- FALSO)
   		  SendPC("MQTT NAO CONECTA\r\n"); //Escreve no PC que nao conectou no MQTT
   	  } else {
   		  
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/data\"\r\n"); //Comando para assinar o topico de insercao de data
   		  	SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		  	while(message == 0);
   		  	message = 0;
   		    if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		  		SendPC("ERRO NO SUBSCRIBE DO DIR\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		  		count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		  	} 
   		  	  		 
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/hora\"\r\n"); //Comando para assinar o topico de insercao de hora
   		  	SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		  	while(message == 0);
   		  	message = 0;
   		  	if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		  	  	 SendPC("ERRO NO SUBSCRIBE DO POWER\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		  	  	 count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		  	}
   		  	  		 
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/resposta\"\r\n"); //Comando para assinar o topico de resposta do sistema
   		  	SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		  	while(message == 0);
   		  	message = 0;
   		  	if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		  	  	  SendPC("ERRO NO SUBSCRIBE DO MODE\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		  	  	  count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		  	}
   		  	
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/log\"\r\n"); //Comando para assinar o topico de log das entradas de usuario
   		    SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		    while(message == 0);
   		    message = 0;
   		    if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		    	   SendPC("ERRO NO SUBSCRIBE DO LIMIAR\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		    	   count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		    }
   		    
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/apaga\"\r\n"); //Comando para assinar o topico de apagar
   		    SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		    while(message == 0);
   		    message = 0;
   		    if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		    	   SendPC("ERRO NO SUBSCRIBE DO LIMIAR\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		    	   count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		    }
   		    
   		  	strcpy(cmd, "SUBSCRIBE \"EA076/168923/user\"\r\n"); //Comando para assinar o topico de cadastro de usuario
   		    SendCmd(cmd); //Envia o comando da assinatura de topico para o ESP
   		    while(message == 0);
   		    message = 0;
   		    if(UTIL1_strcmp(rcv, "OK SUBSCRIBE\r\n")) { //Comparacao da string de resposta do ESP com o OK SUBSCRIBE (0- VERDADEIRO, 1- FALSO)
   		    	   SendPC("ERRO NO SUBSCRIBE DO LIMIAR\r\n"); //Escreve no PC que ocorreu erro no subscribe
   		    	   count_sub--; //1 dos 6 topicos para subscribe nao aconteceu
   		    }
   		  	  		 
   		  	if (count_sub == 6) {
   		  	  	  SendPC("Concluido\r\n"); //Procedimento de SUBSCRIBE foi concluido com exito
   		  	}
   		  	count_sub = 6;	
   	   }
  }
  
  
  DeviceDataPtr = RTC1_Init(NULL, TRUE); //Fazendo a inicializacao do RTC
  
  AZUL_On(); //LED Azul de espera eh aceso
  
  // Display_SetContrast(70); //Contraste do Display eh programado para 70
  // Display_WriteLineStr(1, "Digite seu ID:"); // Escrita no Display
 
/*
  DataHora.Day = 0x01; // Manipulacao do RTC
  DataHora.Month = 01;
  DataHora.Year = 2021;
  DataHora.Hour = 00;
  DataHora.Minute = 00;
  DataHora.Second = 00;
  
  RTC1_SetTime(DeviceDataPtr, &DataHora);
 
  */
  
  for(;;) {
	  
	  if(tecla != 255){ // Quando uma tecla for pressionada
		  
		  if(flagsenha == 0){ // Os digitos teclados serao referentes ao ID
		  
			  if(tecla == 10){ // Caso a tecla seja * = ENTER
			  
				  Memoria_ReadBlock(ID_teclado*16, read, 1); //Leitura do primeiro byte na respectiva posicao do ID inserido
			  
				  if(read[0] == 255){ // Caso a posicao esteja vazia significa que o ID inserido nao existe
					  AZUL_Off(); // Procedimento para indicar o ID nao existente
					  VERM_On();
					  WAIT1_Waitms(5000);
					  VERM_Off();
					  AZUL_On();
					  Display_ClearLine(2);
					  ID_teclado = 0;
					  tecla = 255;
				  } else { // Caso o ID exista na memoria, a flagsenha eh acionada
					  tecla = 255;
					  flagsenha = 1;
					  //Display_WriteLineStr(3, "Digite sua senha:");
				  }
			 
			  } else if(tecla == 13){ // Caso a tecla seja # = apagar
				  ID_teclado = 0;
				  flagsenha = 0;
				  tecla = 255;
			  
			  } else { // Caso a tecla seja somente um numero
				  ID_teclado = ID_teclado*10 + tecla; //Manipulacao das teclas apertadas para formar um numero de ID
			  
				  ID_string[0] = (ID_teclado/10) + 0x30;
				  ID_string[1] = (ID_teclado%10) + 0x30;

				  // Display_WriteLineStr(2, ID_string); //Reproducao do ID inserido no display
				  tecla = 255;
			  
				  ID_string[0] = 0;
				  ID_string[1] = 0;
			  }
		  tecla = 255; // Tecla volta para o seu valor inicial (em espera)
		  
		  } else { // Caso a flagsenha esteja ativada, os dados inseridos serao referentes a senha
			  
			  if(tecla == 10){ // Caso a tecla seja * = ENTER
				  
				  flagsenha = 0;
				  
				  Memoria_ReadBlock((ID_teclado*16), dig1, 8); // Leitura da memoria para puxar a senha registrada
				  
				  senha_memoria = dig1[0] * 256 + dig1[1]; // Montagem do numero da senha
				  
				  ID_teclado = 0; 
				  
				  
				  if(senha_memoria == senha_teclado){ // Caso a senha inserida esteja correta
					  AZUL_Off(); // Procedimento para indicar acesso permitido
					  VERD_On();
					  WAIT1_Waitms(5000);
					  VERD_Off();
					  AZUL_On();
					  
					  senha_memoria = 0;
					  senha_teclado = 0;
					  flagsenha = 0;
					  i=0;
					  tecla = 255;
				  } else { //Caso a senha inserida esteja incorreta
					  AZUL_Off(); // Procedimento para indicar acesso negado
					  VERM_On();
					  WAIT1_Waitms(5000);
					  VERM_Off();
					  AZUL_On();
					  
					  senha_memoria = 0;
					  senha_teclado = 0;
					  flagsenha = 0; 
					  i = 0;
					  tecla = 255;
				  }

				  
			  } else if(tecla == 13){ // Caso a tecla seja # = apagar
				  ID_teclado = 0;
				  flagsenha = 0;
				  tecla = 255;
				  
			  } else { // Caso a tecla seja somente um numero
			  
				  senha_teclado = senha_teclado*10 + tecla; // Montagem do numero da senha inserido pelo usuario
				  i++;
			  
				  if(i==0){ // Escrita de * display durante o momento de insercao de senha
					  Display_WriteLineStr(4, "*");
				  }
				  if(i==1){
					  Display_WriteLineStr(4, "**");
				  }
				  if(i==2){
					  Display_WriteLineStr(4, "***");
				  }
				  if(i=3){
					  Display_WriteLineStr(4, "****");
				  }
				  
			  tecla = 255;
			  
			  }
		  } 
	  }
	  
	  
	  /*// Atualizacao da data/hora fazendo uso do RTC
	  
	  if(flagdata == 1){
		  
		  flagdata = 0;
		 
		  RTC1_GetTime(DeviceDataPtr, &DataHora);
		  dia = DataHora.Day;
		  mes = DataHora.Month;
		  ano = DataHora.Year;
		  hora = DataHora.Hour;
		  minuto = DataHora.Minute;
		  segundo = DataHora.Second;
		  
		  data[0] = (dia/10) + 0x30;
		  data[1] = (dia%10) + 0x30;
		  data[2] = '/';
		  data[3] = (mes/10) + 0x30;
		  data[4] = (mes%10) + 0x30;
		  data[5] = '/';
		  data[6] = (ano/1000) + 0x30;
		  ano = ano%1000;
		  data[7] = (ano/100) + 0x30;
		  ano = ano%100;
		  data[8] = (ano/10) + 0x30;
		  data[9] = (ano%10) + 0x30;
		  data[10] = 0;

		  
		  horario[0] = (hora/10) + 0x30;
		  horario[1] = (hora%10) + 0x30;
		  horario[2] = ':';
		  horario[3] = (minuto/10) + 0x30;
		  horario[4] = (minuto%10) + 0x30;
		  horario[5] = ':';
		  horario[6] = (segundo/10) + 0x30;
		  horario[7] = (segundo%10) + 0x30;	
		  horario[8] = 0;
		  
	  }
	  
	  */
	  
	  if(message) { // Se chegou uma mensagem vinda do broker
	  		  message = 0;
	  		  if(UTIL1_strFind(rcv, "MESSAGE") == -1) { //Verificar se recebeu uma string contendo MESSAGE
	  			  SendPC(rcv); //Se nao for uma string de MESSAGE, retorna para o PC justamente o que ele recebeu (provavelmente um erro)
	  		  } else { //Caso seja uma MESSAGE, ele entre nesse else para separar o topico de mensagem
	  			  scan = 0;
	  		    	  		  
	  		  //Scan de Inicio de topico
	  		      while(rcv[scan] != '['){ //Enquanto o caracter da posicao do scan nao for o [, o scan eh incrementado
	  		    	  scan++;
	  		      }
	  		      scan++; //O scan apontara para a posicao logo depois do [ = Primeiro caracter do topico
	  		      scan_2 = 0;
	  		    	  		  
	  		  //Scan ate o Fim do topico
	  		      while(rcv[scan] != ']'){ //Enquanto o caracter da posicao do scan na mensagem recebida nao for o ] :
	  		    	  top[scan_2] = rcv[scan]; //Coloca na string de topico o caracter da posicao do scan
	  		    	  scan++; //Incrementa os dois ponteiros scans
	  		    	  scan_2++;
	  		      }
	  		      top[scan_2] = 0; //A String de topico eh finalizada com o 0
	  		    	  		  
	  		   //Scan de inicio do parametro do topico - Mesmo procedimento anterior
	  		      while(rcv[scan] != '['){
	  		    	  scan++;
	  		      }
	  		      scan++;
	  		      scan_2 = 0;
	  		    	  		  
	  		   //Scan ate o fim do parametro do topico - Mesmo procedimento anterior
	  		      while(rcv[scan] != ']'){
	  		    	  par[scan_2] = rcv[scan];//Coloca na string de parametro do topico o caracter da posicao do scan
	  		    	  scan++;
	  		    	  scan_2++;
	  		      }
	  		      par[scan_2] = 0; //A String de parametro do topico eh finalizada com o 0
	  		  
	  		    // Interpretacao do comando
	  		      
	  		      if(UTIL1_strcmp(top, "EA076/168923/user") == 0) { //Se o topico for de registro de usuario
	  		    	  
	  		    	  for(j=0; j<14; j++){ // Limpar variaveis
	  		    		string_acesso_recebida[j] = 0;
	  		    		nome[j] = 0;
	  		    	  }
	  		    	  
	  		    	  scan = 1;
	  		    	  scan_2 = 0;
	  		    	  
	  		    	while(par[scan] != '"'){ // Montagem da string de acesso inserida pelo usuario no MQTT
	  		    		string_acesso_recebida[scan_2] = par[scan];
	  		    		scan++;
	  		    		scan_2++;
	  		    	}
	  		    	string_acesso_recebida[scan_2] = 0;
	  		    	scan_2 = 0;
	  		    	scan = scan + 3;
	  		    	
	  		    	while(par[scan] != '"'){ // Montagem do nome de usuario inserido pelo usuario no MQTT
	  		    		nome[scan_2] = par[scan];
	  		    		scan++;
	  		    		scan_2++;
	  		    	}
	  		    	nome[scan_2] = 0;
	  		    	scan_2 = 0;
	  		    	scan = scan + 3;
	  		    	
	  		    	ID = 0;
	  		    	
	  		    	while(par[scan] != '"'){ // Montagem do numero de ID inserido pelo usuario no MQTT
	  		    		ID = ID*10;
	  		    		ID = ID + (par[scan] - 0x30);
	  		    		scan++;
	  		    	}
	  		    	
	  		    	scan = scan + 3;
	  		    	
	  		    	senha = 0;
	  		    	
	  		    	while(par[scan] != '"'){ // Montagem do numero da senha inserido pelo usuario no MQTT
	  		    		senha = senha*10;
	  		    		senha = senha + (par[scan] - 0x30);
	  		    		scan++;
	  		    	}
	  		    	scan = 0;
	  		    	
	  		    	if(UTIL1_strcmp(string_acesso_recebida, string_acesso) == 0){ // Caso a string de acesso esteja correta
	  		    		strcpy(cmd, "PUBLISH \"EA076/168923/resposta\",\"String de acesso OK\"\r\n"); // Publicacao no topico de resposta
	  		    		SendCmd(cmd);
	  		    		
	  		    		Memoria_ReadBlock(ID*16, read, 1); // Leitura do primeiro byte no respectivo endereco do ID inserido
	  		    		
	  		    		if(read[0] == 255){ // Caso esse ID ainda esteja vazio para registro
	  		    		
	  		    			senha_formatada_1[0] = senha/256; // Formatacao da senha em 2 bytes (MSB e LSB)
	  	
	  		    			senha_formatada_1[1] = (senha%256);
	  		    			
	  		    			Memoria_WriteBlock(ID*16, senha_formatada_1, 8); // Gravacao da senha na memoria
	  		    			
	  		    			strcpy(cmd, "PUBLISH \"EA076/168923/resposta\",\"Usuario adicionado\"\r\n"); 
	  		    			
	  		    			SendCmd(cmd);
	  		    		} else { // Caso o ID inserido ja esteja gravado na memoria
	  		    			strcpy(cmd, "PUBLISH \"EA076/168923/resposta\",\"ID ja existente\"\r\n");
	  		    			SendCmd(cmd);
	  		    		}
	  		    		
	  		    		
	  		    	} else { // Caso a string de acesso esteja invalida
	  		    		strcpy(cmd, "PUBLISH \"EA076/168923/resposta\",\"String de acesso invalida\"\r\n");
	  		    		SendCmd(cmd);
	  		    	} 
	  		      }   
	  		  }
	  }	  
  }
  
 
  
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
