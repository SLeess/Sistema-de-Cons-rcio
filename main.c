#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "consorcio.h"
#include "ambiente.h"

void TelaPrincipal(){
    //textbackground(DARK_GRAY);
    CaixaPrincipal();
    Borda(19,2, 80, 8, 1, 0);
    textcolor(LIGHT_RED);
    gotoxy(21, 3); printf("CCCCCC  OOOOOOOO  NNN NNNN  SSSSSS  OOOOOOOO  RRRRRRR  CCCCCC   III   OOOOOOOO");
    gotoxy(21, 4); printf("CCCCCC  OOOOOOOO  NNNNNNNN  SSSSSS  OOOOOOOO  RRR  RRR CCCCCC  IIIII  OOOOOOOO");
    gotoxy(21, 5); printf("CCC     OOO  OOO  NNN  NNN  SSS     OOO  OOO  RRR  RRR CCC     IIIII  OOO  OOO");
    textcolor(RED);
    gotoxy(21, 6); printf("CCC     OOO  OOO  NNN  NNN  SSSSSS  OOO  OOO  RRR RRR  CCC     IIIII  OOO  OOO");
    textcolor(MAGENTA);
    gotoxy(21, 7); printf("CCC     OOO  OOO  NNN  NNN     SSS  OOO  OOO  RRRRRR   CCC     IIIII  OOO  OOO");
    gotoxy(21, 8); printf("CCCCCC  OOOOOOOO  NNN  NNN  SSSSSS  OOOOOOOO  RRR RRR  CCCCCC  IIIII  OOOOOOOO");
    gotoxy(21, 9); printf("CCCCCC  OOOOOOOO  NNN  NNN  SSSSSS  OOOOOOOO  RRR  RRR CCCCCC  IIIII  OOOOOOOO");
    textcolor(WHITE);
    //textbackground(BLACK);
    Borda(86, 9, 8, 2, 1, 0);
    gotoxy(88, 10); printf("YALEN");
}

int main()
{
    char opcoes[][51] = {"    Cadastrar    ", "    Pesquisar    ", " Fazer Consorcio ","Listar Consorcios", "Encerrar Programa" };
    int escolha = 0, mn;
    int X[]= {49, 49, 49, 49, 49};
    int Y[]= {14, 17, 20, 23, 26};

    while(1){
        system("cls");

        TelaPrincipal();
        //Interface(1);

        Borda(48,13,17,2,0,0);
        Borda(48,16,17,2,0,0);
        Borda(48,19,17,2,0,0);
        Borda(48,22,17,2,0,0);
        Borda(48,25,17,2,0,0);

        escolha = menu(opcoes, X, Y, escolha, 5);

        CaixaPrincipal();

        if (escolha == 0){
            AtivarCliente();
        }

        else if(escolha == 1){
            BuscarCliente(0);
        }

        else if(escolha == 2){
            BuscarCliente(1);
        }

        else if (escolha == 3){
            BuscarCliente(2);
            //ConsorciosAtivos("1234567890");
        }
        else if (escolha == 4){
            gotoxy(0,29);
            exit(1);
        }
        textbackground(BLACK);
    }

    gotoxy(0, 25);
    return 0;
}
