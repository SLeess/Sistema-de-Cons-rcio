#ifndef CONSORCIO_H_INCLUDED
#define CONSORCIO_H_INCLUDED

struct consorcio{
    int dia, mes, hora, ano, seg, minu, conta, agencia, date, ID;
    char modalidade[51], banco[51], CPF[51];
    double valor;
    double mensalidades;
};

typedef struct consorcio CS;

void InvestimentoID(char CPF[51]);

void seguranca();

void contrato(char cpf[51]);

int confirmmenu();

double CalcularMensalidade();

void FecharArquivoConsorcio();

void SalvarNovoConsorcio(CS D);

void AbrirArquivoConsorcio();

void procedimento(CS D);

/////////////////////////////////////////////
void ConsorciosAtivos(char CPF[51]);

void BuscarConsorcios(char CPF[51], int n);

void registro(int ID);

#endif // CONSORCIO_H_INCLUDED
