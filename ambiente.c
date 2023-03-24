#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "consorcio.h"
#include "ambiente.h"
#include "interface.h"

FILE *fpDadosCliente;

void procedimentoPadrao(Dados D){
    //Caminho Padrão de Salvamento de Dados de Cadastro de Pessoas
    AbrirArquivoCliente();
    SalvarNovoCliente(D);
    FecharArquivoCliente();
}

void AbrirArquivoCliente()
{
    fpDadosCliente = fopen("Cliente.txt", "rb+");
    if(fpDadosCliente == NULL)
    {
        fpDadosCliente = fopen("Cliente.txt", "wb+");
        if(fpDadosCliente == NULL)
        {
            printf("Nao Abriu Cliente.txt\n");
            exit(1);
        }
    }
}

void FecharArquivoCliente()
{
    fclose(fpDadosCliente);
}

void SalvarNovoCliente(Dados D)
{
    fseek(fpDadosCliente,0,SEEK_END);
    fwrite(&D, sizeof(Dados),1,fpDadosCliente);
    fflush(fpDadosCliente);
}

int Contagem(){
    FILE *F;
    int x = 1000;
    F = fopen("Cliente.txt", "rb+");
    if(F == NULL){
        Borda(31, 21, 7, 2, 0, 0);
        gotoxy(16, 22); printf("ID DE PESQUISA:");
        gotoxy(33, 22); printf("%.5d", x);
        return x;
    }
    else{
        fclose(F);
        AbrirArquivoCliente();
        Dados P;
        while(fread(&P,sizeof(Dados),1,fpDadosCliente)){
            x++;
        }
        FecharArquivoCliente();
    }
    Borda(31, 21, 7, 2, 0, 0);
    gotoxy(16, 22); printf("ID DE PESQUISA:");
    gotoxy(33, 22); printf("%.5d", x);
    return x;
}

Dados PesquisarUsuario(Dados X, int f)
{
    AbrirArquivoCliente();
    char IDoCPF[20];//, Xcpf[20];

    Dados P;

    //Tela de busca por ID ou CPF
    if(f == 0){
        gotoxy(27,7);
        scanf(" %s", &IDoCPF);
        fflush(stdin);
    }

    //Confirmação de Registro
    else if(f == 1){
        //sprintf(Xcpf, "%d", X.CPF);
        strcpy(IDoCPF, X.CPF);
        //gotoxy(2,32); printf("%s", IDoCPF);
    }

    //Busca para confirmação de consórcio
    //else if(f == 2){
        //strcpy(IDoCPF, X.ID);
    //}

    fseek(fpDadosCliente,0,SEEK_SET);
    while(fread(&P,sizeof(Dados),1,fpDadosCliente))
    {
        if(strcmp(P.ID,IDoCPF) == 0 || strcmp(P.CPF, IDoCPF) == 0)
        {
            FecharArquivoCliente();
            return P;
        }
    }
    strcpy(P.ID, "");
    //gotoxy(2,33); printf("<%s>", P.ID);
    FecharArquivoCliente();
    return P;
}

void printarDados(Dados X){
    gotoxy(27, 7); printf("%s", X.ID);
    gotoxy(27,10); printf("%s", X.Nome);
    gotoxy(27, 13); printf("%s", X.Telefone);
    gotoxy(27, 16); printf("%s", X.CPF);
    gotoxy(27, 19); printf("%s", X.CEP);
    return;
}

Dados DigitarDados(int n){
    Dados D;

    gotoxy(27, 7);
    scanf(" %[^\n]", D.Nome);

    if(n == 1){
        gotoxy(27, 10);
        scanf(" %[^\n]", D.Telefone);

        gotoxy(27, 13);
        scanf(" %s", D.CPF);

        gotoxy(27, 16);
        scanf(" %[^\n]", D.Endereco);

        gotoxy(27, 19);
        scanf(" %[^\n]", D.CEP);
    }

    return D;
}

void CaixaPrincipal(){
    Borda(0, 0, 118, 29, 1, 0);
    //textbackground(BLACK);
}

void Caixa(){
    Borda(26, 9, 30, 2, 0, 0);
    Borda(26, 12, 30, 2, 0, 0);
    Borda(26, 15, 30, 2, 0, 0);
    Borda(26, 18, 30, 2, 0, 0);
    return 0;
}

void Interface(int n){
    if (n == 0) Borda(14, 5, 52, 18, 1, 1);
    else if (n == 1){ Borda(2, 1, 114, 27, 1, 0);}
    else if(n == 3){ Borda(78, 5, 19, 19, 1, 0);}
    else if(n == 4){ Borda(78, 5, 24, 10, 1, 0);}
    else if(n == 5){ Borda(14, 5, 52, 19, 1, 1);}
    else if(n == 6) {
        Borda(4,2,30, 25, 1, 0);
        Borda(44,2,30, 25, 1, 0);
        Borda(84,2,30, 25, 1, 0);
    }
    else if (n == -3){ Borda(78, 5, 16, 16, 0, 0);}
    return 0;
}

void SimularConsorcio(int n){
    //N = 0 - Interface de Cadastro
    if(n == 0){Interface(5); gotoxy(16, 7); printf("     NOME: "); Borda(26, 6, 30, 2, 0, 0);}

    //N = 1 - Interface de Busca por ID ou CPF || N = 3 - Interface de dados pós busca por ID
    else if(n == 1 || n == 3){
        Interface(0); gotoxy(16, 7);
        if(n == 1){ printf(" CPF/ID: ");}
        else{printf("     ID: ");}

        Borda(26, 6, 30, 2, 0, 0);
    }

    //N = 0 - Interface de Cadastro
    if(n == 0){
        gotoxy(16, 10); printf(" TELEFONE: ");
        gotoxy(16, 13); printf("     CPF: ");
        gotoxy(16, 16); printf("ENDERECO: ");
        gotoxy(16, 19); printf("     CEP: ");
        Caixa();
    }

    //N = 3 - Interface de dados pós busca por ID
    else if(n == 3){
        gotoxy(16, 10); printf("     NOME: ");
        gotoxy(16, 13); printf(" TELEFONE: ");
        gotoxy(16, 16); printf("     CPF: ");
        gotoxy(16, 19); printf("     CEP: ");
        Caixa();
    }
}

void AlterarDados(Dados P, int d){
    AbrirArquivoCliente();

    //Marcador de posição no arquivo
    int n = atoi(P.ID);
    fseek(fpDadosCliente, n%1000 * sizeof(Dados), SEEK_SET);

    //Corrigir as Cores
    desbugar();

    //D = 0 - Mudar sem apagar os dados
    if(d == 0){
        SimularConsorcio(0);
        Dados K;
        K = DigitarDados(1);
        strcpy(K.ID, P.ID);
        fwrite(&K, sizeof(Dados), 1, fpDadosCliente);
    }

    //D = 1 - Apagar os Dados
    else if(d == 1){
        Interface(0);
        strcpy(P.ID, "");
        strcpy(P.CPF, "");
        fwrite(&P, sizeof(Dados), 1, fpDadosCliente);
    }

    FecharArquivoCliente();
    return P;
}

int novamentbusca;

void BuscarCliente(int f){
    char botaofinal[][51] = {"Fechar" };
    char opcoes[][51] = {"Nova Busca", "Alterar", "Apagar", "Novo Consorcio", "Listar Consorcios", "Fechar" }, nesco[][51] = {"Tentar Novamente", "Fechar"};
    int x[] = {80, 80, 80, 80, 80, 80}, y[] = {7, 10, 13, 16, 19, 22};
    int j[] = {60}, k[] = {23};
    int X[] = {18, 57}, Y[] = {23, 23};

    Dados D;

    int esscolha = 0, opt = 0;
    do{
        desbugar();
        if(novamentbusca == 1){
            novamentbusca = 0;
            //f = 0;
        }

        SimularConsorcio(1);
        D = PesquisarUsuario(D,0);

        if(strcmp(D.ID, "") == 0){
            gotoxy(30,14); printf("Usuario nao Encontrado");
            Borda(17, 22, 16, 2, 0, 0); Borda(56, 22, 6, 2, 0, 0);
            esscolha = menu(nesco, X, Y, esscolha, 2);
            if(esscolha == 0){
                novamentbusca = 1;
                //f = 1;
            }
            else{
                return 0;
            }
        }

        if(f == 1 && novamentbusca == 0){
            InvestimentoID(D.CPF);
        }

        else if(f == 2 && novamentbusca == 0){
            ConsorciosAtivos(D.CPF);
        }
        else if(f == 0 && novamentbusca == 0){
            Interface(3);

            SimularConsorcio(3);
            Borda(79,6,10,2,0,0);
            Borda(79,9,7,2,0,0);
            Borda(79,12,6,2,0,0);
            Borda(79,15,14,2,0,0);
            Borda(79,18,17,2,0,0);
            Borda(79,21,6,2,0,0);

            printarDados(D);

            do{
                textcolor(BLACK); textbackground(RED);
                esscolha = menu(opcoes, x, y, esscolha, 6);

                //Repetir a Busca
                if(esscolha == 0){
                    novamentbusca = 1;
                    break;
                }

                //Alterar os Dados sem apaga-los
                else if(esscolha == 1){
                    AlterarDados(D, 0);
                    gotoxy(17, 23); printf("Os dados de usuario foram atualizados!");
                    Borda(59,22,6,2,0,0);
                    opt = menu(botaofinal, j, k, opt, 1);
                    return 0;
                }

                //Apagar os Dados
                else if(esscolha == 2){
                    desbugar();
                    Interface(-3);
                    AlterarDados(D, 1);
                    gotoxy(24, 14); printf("Os dados do usuario foram deletados!");
                    Borda(59,22,6,2,0,0);
                    opt = menu(botaofinal, j, k, opt, 1);
                    return 0;
                }

                else if(esscolha == 3){
                    InvestimentoID(D.CPF);
                    return 0;
                }

                else if(esscolha == 4){
                    textcolor(WHITE); textbackground(RED);
                    ConsorciosAtivos(D.CPF);
                    return 0;
                }
                //Fechar a Tela
                else if(esscolha == 5){return 0;}
            }while(esscolha != -1);
        }
    }while(novamentbusca == 1);
    return 0;
}

void AtivarCliente()
{
    desbugar();
    SimularConsorcio(0);
    int Escolha = 0;
    //int x[] = {80, 80, 80, 80, 80}, y[] = {7, 10, 13, 16, 19};
    int X[]= {80, 80, 80};
    int Y[]= {7, 10, 13};
    int j[] = {47}, ki[] = {22};

    Dados D, confirm;
    char OpcoesConfirma[][51]= {"Confirmar e Prosseguir", "Confirmar e Sair","Cancelar Cadastro"};
    char optt[][51] = {"Voltar para o menu"};

        D = DigitarDados(1);
        int k = Contagem();
        sprintf(D.ID, "%d", k);

        confirm = PesquisarUsuario(D, 1);

        if(strcmp(confirm.ID,"") != 0){
            Interface(5);
            gotoxy(36,13); printf("ERRO!!");
            gotoxy(18,15);printf("Este CPF ja esta cadastrado, tente novamente!");
            Borda(46, 21, 18, 2, 0, 0);
            Escolha = menu(optt, j, ki, Escolha, 1);
            return 0;
        }

        Interface(4);
        Borda(79,6,22,2,0,0);
        Borda(79,9,22,2,0,0);
        Borda(79,12,22,2,0,0);

        Borda(31, 21, 7, 2, 0, 0);
        gotoxy(16, 22); printf("ID DE PESQUISA:");
        gotoxy(33, 22); printf("%.5d", k);
            textcolor(BLACK); textbackground(RED);
            Escolha = menu(OpcoesConfirma, X, Y, Escolha, 3);

            if(Escolha==0 || 1){
                //DEVERÁ SALVAR OS DADOS
                procedimentoPadrao(D);
                if(Escolha == 0) InvestimentoID(D.ID);
            }
            else if(Escolha==2)
            {
            }
}

void OptFecharPagGrande(){
    char botaofinal[][51] = {"Fechar" };
    int x[] = {110};
    int y[] = {1};

    int escolha = 0;

    Borda(109,0,6,2,0,0);
    escolha = menu(botaofinal, x, y, escolha, 1);
    if(escolha == 0){
    }
    return 0;
}
