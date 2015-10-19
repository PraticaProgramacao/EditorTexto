/*
Author: Lucas Simas
Description: Controla os comandos de teclado (input)
*/

//Definição das 'booleans'
#define FALSE 0
#define TRUE 1

//Definição dos codigos de comando
#define UP_ARROW 1
#define DOWN_ARROW 2 
#define LEFT_ARROW 3
#define RIGHT_ARROW 4
#define SAVE_FILE 5
#define OPEN_FILE 6
#define BACKSPACE 7
#define DELETE 8
#define ENTER 9
typedef struct TKeyboard {
	char Key;
	int Command; //Indica o comando que foi dado pelo usuário, caso seja 0, indica uma letra
}Keyboard;

/* Retorna a tecla/comando que foi dado pelo usuário */
Keyboard GetUserInput();