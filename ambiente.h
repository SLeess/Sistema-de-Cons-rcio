#ifndef AMBIENTE_H_INCLUDED
#define AMBIENTE_H_INCLUDED

struct dadosconsorcio{
    char Nome[51];
    char Telefone[51];
    char CPF[51];
    char Endereco[51];
    char CEP[20];
    char ID[20];

};

int novamentbusca;

typedef struct dadosconsorcio Dados;
Dados DigitarDados(int n);
void AtivarCliente();
int Contagem();
Dados PesquisarUsuario(Dados X, int f);
void TelaPaciente();
void printarDados(Dados X);
void CaixaPrincipal();
void BuscarCliente(int f);
void Interface(int n);
void caixa();
void OptFecharPagGrande();
void SimularConsorcio(int n);
void AlterarDados(Dados P, int n);
void procedimentoPadrao(Dados D);

#endif // AMBIENTE_H_INCLUDED
