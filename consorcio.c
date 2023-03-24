#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "consorcio.h"
#include "interface.h"
#include "ambiente.h"

//Contrato Selecionado Atual
CS A;

//Função de descrição do interesse do usuário em participar de um consórcio
void InvestimentoID(char CPF[51]){
    textbackground(BLACK);
    textbackground(RED);
    char opt[][51] = {"Motos", "Carros", "Imoveis", "Servicos", "Fechar"};
    int p[] = {7, 7, 7, 7, 110}, q[] = {8,11, 14, 17, 1}, escolha = 0, escolha2 = 0;
//--------------------------PART 1---------------------------//

    Interface(1);
    Interface(6);

    for(int k = 0; k <= 15; k+=15){
        for(int j = 0; j <= 15; j+=3){
            Borda(k+6,7+j,10, 2, 0, 0);
        }
    }

    Borda(109,0,6,2,0,0);
    gotoxy(6, 4); printf("Selecione:");
    gotoxy(6, 5); printf("Opcoes de Consorcios:");

    textcolor(BLACK); textbackground(RED);
    escolha = menu(opt, p, q, escolha, 5);

//--------------------------PART 2---------------------------//

    int p2[] = {47, 47, 47, 47, 47, 47}, q2[] = {8, 11, 14, 17, 20, 23};

    if(escolha != 4){
        textcolor(WHITE); textbackground(RED);
        //Borda(44,2,30, 25, 1, 0);
        gotoxy(46, 3); printf("Selecione a faixa de preco");
        gotoxy(46, 5); printf("Faixas disponiveis:");

        for(int k = 0; k <= 15; k+=15){
            for(int j = 0; j <= 15; j+=3){
                Borda(k+46,7+j,10, 2, 0, 0);
            }
        }
    }
    int t = 0;
    if(escolha == 0){
        int vall[]= {8000, 15000, 20000, 25000, 30000, 45000};
        char val[][51] = {"R$8.000","R$15.000", "R$20.000", "R$25.000", "R$30.000", "R$45.000"};
        escolha2 = menu(val, p2, q2, escolha2, 6);
        strcpy(A.modalidade, opt[escolha]);
        A.valor = vall[escolha2];
    }
    else if(escolha == 1){
        double vall[]= {18000, 25000, 40000, 60000, 90000, 100000};
        char val[][51] = {"R$18.000","R$25.000", "R$40.000", "R$60.000", "R$90.000", "R$100.000"};
        escolha2 = menu(val, p2, q2, escolha2, 6);
        strcpy(A.modalidade, opt[escolha]);
        A.valor = vall[escolha2];
    }

    else if(escolha == 2){
        double vall[]= {150000, 180000, 200000, 240000, 300000, 500000};
        char val[][51] = {"R$150.000","R$180.000", "R$200.000", "R$240.000", "R$300.000", "R$500.000"};
        escolha2 = menu(val, p2, q2, escolha2, 6);
        strcpy(A.modalidade, opt[escolha]);
        A.valor = vall[escolha2];
    }
    else if(escolha == 3){

    }
    else if(escolha == 4){
        return 0;
    }

//--------------------------PART 3---------------------------//
    textcolor(WHITE); textbackground(RED);

    gotoxy(86, 3); printf("Preencha os dados:");
    //gotoxy(86, 5); printf("Valor Total:");
    gotoxy(86, 5); printf("Prazo desejado(em meses): ");
    Borda(87, 6, 12, 2, 0, 0);
    gotoxy(86, 9); printf("- Prazo minimo: 12 meses -");

    gotoxy(86, 15); printf("Instituicao/Banco filiado:");
    Borda(87, 16, 24, 2, 0, 0);

    gotoxy(86, 19); printf("Conta:");
    Borda(87, 20, 24, 2, 0, 0);

    gotoxy(86, 23); printf("Agencia:");
    Borda(87, 24, 24, 2, 0, 0);

    //Confirmador de prazo mínimo
    while(1){
        Borda(87, 6, 12, 2, 0, 0);
        gotoxy(88, 7);
        scanf(" %d", &A.date);

        if(A.date >= 12){
            gotoxy(86, 11); printf("                      ");
            break;
        }
        gotoxy(86, 11); printf("Erro! Digite novamente");
        getchar();
    }

    seguranca();
    gotoxy(88, 17);scanf(" %[^\n]", A.banco);
    seguranca();
    gotoxy(88, 21);scanf(" %d", &A.conta);
    gotoxy(88, 25);scanf(" %d", &A.agencia);
    fflush(stdin);

    Interface(1);

    A.mensalidades = CalcularMensalidade();

    contrato(CPF);

    escolha = confirmmenu();

    if(escolha == 1) return 0;

    //NECESSITA-SE GUARDAR OS DADOS DO STRUCT CONSORCIO
    procedimento(A);

    Interface(1);
    gotoxy(50, 15); printf("Dados Salvos com Sucesso");

    escolha = confirmmenu();
}

int confirmmenu(){
    char opt4[][51] = {"Confirmar", "Cancelar"};
    int v[] = {97, 108}, u[] = {1, 1};
    // escolha = 0;
    Borda(96, 0, 9, 2, 0, 0);
    Borda(107, 0, 8, 2, 0, 0);
    int x = 0;
    x = menu(opt4, v, u, x, 2);
    return x;
}

double CalcularMensalidade(){
    int porcentagem= A.valor*2/100;
    double valorporparcela= (porcentagem + A.valor)/A.date;

return valorporparcela;
}

void contrato(char cpf[51]){
    struct tm *d;
    time_t seconds;

    time(&seconds);
    d = localtime(&seconds);

    A.dia = d->tm_mday;
    A.mes = d->tm_mon + 1;
    A.ano = d->tm_year + 1900;
    A.hora = d->tm_hour;
    A.minu = d->tm_min;
    A.seg = d->tm_sec;

    Dados D;
    //sprintf(D.CPF, "%d", cpf);
    strcpy(D.CPF, cpf);
    strcpy(A.CPF, D.CPF);

    D = PesquisarUsuario(D,1);
    A.ID = ContagemC();

    Borda(32, 2, 10, 2, 0, 0);
    gotoxy(6, 3); printf("Contrato de consorcio:");
    gotoxy(35,3); printf("%s", A.modalidade);

    gotoxy(6, 5); printf("Contrato n°");
    Borda(18, 4, 8, 2, 0, 0);
    gotoxy(20, 5); printf("%1.d", A.ID);////

    gotoxy(6, 8); printf("Cliente:");
    Borda(15, 7, 41, 2, 0, 0);
    gotoxy(17, 8); printf("%s", D.Nome);

    gotoxy(6, 11); printf("CPF:");
    Borda(12, 10, 13, 2, 0, 0);
    gotoxy(14, 11); printf("%s", A.CPF);

    gotoxy(6, 14); printf("END.:"); gotoxy(6, 17); printf("CEP:");
    Borda(12, 13, 44, 2, 0, 0); Borda(12, 16, 12, 2, 0, 0);
    gotoxy(14, 14); printf("%s", D.Endereco);
    gotoxy(14, 17); printf("%s", D.CEP);

    gotoxy(6, 20); printf("FONE:");
    Borda(12, 19, 16, 2, 0, 0);
    gotoxy(14, 20); printf("%s", D.Telefone);

    gotoxy(6, 23); printf("Data do Consorcio:");
    Borda(25, 22, 12, 2, 0, 0);
    gotoxy(27, 23); printf("%d/%d/%d\n", A.dia, A.mes, A.ano);

    gotoxy(6, 26); printf("Hora:");
    Borda(12, 25, 9, 2, 0, 0);
    gotoxy(14, 26); printf("%d:%d:%d\n", A.hora, A.minu, A.seg);

    Borda(65, 5, 45, 21, 0, 0);

    gotoxy(68, 8); printf("Valor Total:");
    Borda(93, 7, 12, 2, 0, 0);
    gotoxy(95, 8); printf("R$%.2lf", A.valor);

    gotoxy(68, 11); printf("N° de Parcelas / meses: ");
    Borda(93, 10, 12, 2, 0, 0);
    gotoxy(95, 11); printf("%d", A.date);

    gotoxy(68, 14); printf("Taxa de Servico:");
    Borda(93, 13, 12, 2, 0, 0);
    gotoxy(95, 14); printf("%.2f %%", 2.0);

    gotoxy(68, 17); printf("Valor das Parcelas:");
    Borda(93, 16, 12, 2, 0, 0);
    gotoxy(95, 17); printf("R$%.2f", A.mensalidades);

    //gotoxy(2,31); printf("%s", cpf);

    gotoxy(68, 21); printf("Banco:");
    Borda(75, 20, 20, 2, 0, 0);

    gotoxy(68, 24); printf("Conta:");
    gotoxy(89, 24); printf("Agencia:");
    Borda(75, 23, 10, 2, 0, 0);
    Borda(98, 23, 10, 2, 0, 0);

    gotoxy(77, 21); printf("%s", A.banco);
    gotoxy(77, 24); printf("%d", A.conta);
    gotoxy(100, 24); printf("%d", A.agencia);
}

FILE *fpConsorcio;
char fpCS[] = "Consorcio.txt";

int ContagemC(){
    FILE *F;
    int x = 10000;
    F = fopen(fpCS, "rb+");
    if(F == NULL){
        return x;
    }
    else{
        fclose(F);
        AbrirArquivoConsorcio();
        CS P;
        while(fread(&P,sizeof(CS),1,fpConsorcio)){
            x++;
        }
        FecharArquivoConsorcio();
    }
    return x;
}

void procedimento(CS D){
    //Caminho Padrão de Salvamento de Dados de Consorcios
    AbrirArquivoConsorcio();
    SalvarNovoConsorcio(D);
    FecharArquivoConsorcio();
}

void AbrirArquivoConsorcio()
{
    fpConsorcio = fopen(fpCS, "rb+");
    if(fpConsorcio == NULL)
    {
        fpConsorcio = fopen(fpCS, "wb+");
        if(fpConsorcio == NULL)
        {
            printf("Nao Abriu Consorcio.txt\n");
            exit(1);
        }
    }
}

void FecharArquivoConsorcio()
{
    fclose(fpConsorcio);
}

void SalvarNovoConsorcio(CS D)
{
    fseek(fpConsorcio,0,SEEK_END);
    fwrite(&D, sizeof(CS),1,fpConsorcio);
    fflush(fpConsorcio);
}

void seguranca(){
    //Função de segurança de buffer
    getchar();
    return;
}
/////////////////////////////////////////////////

void BuscarConsorcios(char CPF[51], int n){
    AbrirArquivoConsorcio();
    int j = 4, k = 0, value = 0;
    CS P;
    //strcmp(P.CPF, CPF);

    fseek(fpConsorcio,0,SEEK_SET);

    while(fread(&P,sizeof(CS),1,fpConsorcio))
    {
        //if(((fread(&P,sizeof(CS),1,fpConsorcio)) != EOF) == EOF) break;
        if(n > 0 && strcmp(P.CPF,CPF) == 0){
            value = 1;
            n--;
        }
        else if(strcmp(P.CPF,CPF) == 0)
        {
            Borda(5, j-1, 62, 3, 0, 0);
            gotoxy(6, j); printf("Modalidade: %s - Data de Contrato: %i/%i/%i - ID: %i", P.modalidade, P.dia, P.mes, P.ano, P.ID);
            gotoxy(9, j+1); printf("Valor: R$%.2lf", P.valor);
            j+= 4; k++;
            if(k == 6) break;
        }
    }
    if(k == 0 && value == 0){
        gotoxy(9, j+4); printf("Este usuario nao possui mais Consorcios ativos");
    }
    else if(k == 0 && value == 1){
        gotoxy(9, j+4); printf("Pagina disponivel");
    }
    FecharArquivoConsorcio();
}

void ConsorciosAtivos(char CPF[51]){
    char lek[][51] = {" >>> ", "Abrir", " <<< ", "Fechar"};
    char fec[][51] = {"Fechar"};
    int ba[] = {80, 80, 80, 100}, be[] = {11, 13, 15, 1}, opit = 0;
    int fin[] = {100}, jak[] = {1};
    Interface(1);
    Borda(79, 10, 5, 6, 0, 0);
    //Borda(78, 5, 19, 19, 1, 0);}
    //Interface(3);
    int qtd = 0;
    BuscarConsorcios(CPF, 0);

    do{
        Borda(99, 0, 6, 2, 0, 0);
        Borda(1, 26, 6, 2, 0, 0);
        gotoxy(2, 27); printf("Pag: %d", qtd+1);
        textcolor(WHITE); textbackground(RED);
        opit = menu(lek, ba, be, opit, 4);
        if(opit == 3) return 0;
        else if(opit == 1) break;
        else if(opit == 0){
            qtd++;
        }

        else if(opit == 2){
            if(qtd > 0) qtd--;
        }
        Interface(1);
        Borda(79, 10, 5, 6, 0, 0);
        BuscarConsorcios(CPF, 6*qtd);
        //gotoxy(2, 27); printf("Pag: %d", qtd+1);
    }while(opit != 3);
    int id;
    Borda(79, 19, 30, 8, 0, 0);
    gotoxy(81, 21); printf("Digite o ID:");
    Borda(80, 22, 28, 2, 0, 0);
    gotoxy(81, 23); scanf("%d", &id);
    textcolor(WHITE); textbackground(RED);
    getchar();

    //Falta a função de Abrir o Contrato Desejado em Específico
    Interface(1);
    textcolor(WHITE); textbackground(RED);
    registro(id);
    textcolor(WHITE); textbackground(RED);
    opit = 0;
    Borda(99, 0, 6, 2, 0, 0);
    opit = menu(fec, fin, jak, opit, 1);
    //scanf("%d", &id);

}

void registro(int ID)
{
    CS P;
    AbrirArquivoConsorcio();
    fseek(fpConsorcio,0,SEEK_SET);
    while(fread(&P,sizeof(CS),1,fpConsorcio))
    {
        if(P.ID == ID) break;
    }
    FecharArquivoConsorcio();

    Dados Pessoa;
    strcmp(Pessoa.CPF, P.CPF);

    Pessoa = PesquisarUsuario(Pessoa, 1);

    Borda(32, 2, 10, 2, 0, 0);
    gotoxy(6, 3); printf("Contrato de consorcio:");
    gotoxy(35,3); printf("%s", P.modalidade);

    gotoxy(6, 5); printf("Contrato n°");
    Borda(18, 4, 8, 2, 0, 0);
    gotoxy(20, 5); printf("%1.d", P.ID);////

    gotoxy(6, 8); printf("Cliente:");
    Borda(15, 7, 41, 2, 0, 0);
    gotoxy(17, 8); printf("%s", Pessoa.Nome);

    gotoxy(6, 11); printf("CPF:");
    Borda(12, 10, 13, 2, 0, 0);
    gotoxy(14, 11); printf("%s", P.CPF);

    gotoxy(6, 14); printf("END.:"); gotoxy(6, 17); printf("CEP:");
    Borda(12, 13, 44, 2, 0, 0); Borda(12, 16, 12, 2, 0, 0);
    gotoxy(14, 14); printf("%s", Pessoa.Endereco);
    gotoxy(14, 17); printf("%s", Pessoa.CEP);

    gotoxy(6, 20); printf("FONE:");
    Borda(12, 19, 16, 2, 0, 0);
    gotoxy(14, 20); printf("%s", Pessoa.Telefone);

    gotoxy(6, 23); printf("Data do Consorcio:");
    Borda(25, 22, 12, 2, 0, 0);
    gotoxy(27, 23); printf("%d/%d/%d\n", P.dia, P.mes, P.ano);

    gotoxy(6, 26); printf("Hora:");
    Borda(12, 25, 9, 2, 0, 0);
    gotoxy(14, 26); printf("%d:%d:%d\n", P.hora, P.minu, P.seg);

    Borda(65, 5, 45, 21, 0, 0);

    gotoxy(68, 8); printf("Valor Total:");
    Borda(93, 7, 12, 2, 0, 0);
    gotoxy(95, 8); printf("R$%.2lf", P.valor);

    gotoxy(68, 11); printf("N° de Parcelas / meses: ");
    Borda(93, 10, 12, 2, 0, 0);
    gotoxy(95, 11); printf("%d", P.date);

    gotoxy(68, 14); printf("Taxa de Servico:");
    Borda(93, 13, 12, 2, 0, 0);
    gotoxy(95, 14); printf("%.2f %%", 2.0);

    gotoxy(68, 17); printf("Valor das Parcelas:");
    Borda(93, 16, 12, 2, 0, 0);
    gotoxy(95, 17); printf("R$%.2f", P.mensalidades);

    //gotoxy(2,31); printf("%s", cpf);

    gotoxy(68, 21); printf("Banco:");
    Borda(75, 20, 20, 2, 0, 0);

    gotoxy(68, 24); printf("Conta:");
    gotoxy(89, 24); printf("Agencia:");
    Borda(75, 23, 10, 2, 0, 0);
    Borda(98, 23, 10, 2, 0, 0);

    gotoxy(77, 21); printf("%s", P.banco);
    gotoxy(77, 24); printf("%d", P.conta);
    gotoxy(100, 24); printf("%d", P.agencia);
}
