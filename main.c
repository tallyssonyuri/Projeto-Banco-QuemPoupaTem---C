#include <stdio.h>
#include "banco.h"

void inicio (){
  /*A função inicio() apresenta as saudações ao usuário e marca o começo do software*/
  
  printf("Seja bem vindo ao Banco QuemPoupaTem!\n\n");
}

void menu(){
  /*A função menu() apresenta o menu em um loop infinito, até que o usuário opte por sair, digitando 0*/
  
  printf("Abaixo, você poderá selecionar a operação que deseja seguir em seu programa conforme o seu número correspondente\n\n");
  int operacao = 1;

  do{
    printf("1. Novo cliente\n");
    printf("2. Apaga cliente\n");
    printf("3. Listar clientes\n");
    printf("4. Débito\n");
    printf("5. Depósito\n");
    printf("6. Extrato\n");
    printf("7. Transferência entre contas\n");
    printf("0. Sair\n\n");
    
    printf("Digite o número da operação desejada: ");
    scanf(" %d", &operacao);
    printf("\n");

    switch(operacao){
      case 1:
        novo_cliente();
      break;

      case 2:
        apaga_cliente();
      break;

      case 3:
        listar_clientes();
      break;

      case 4:
        debito();
      break;
        
      case 5:
        deposito();
      break;

      case 6:
       extrato();
      break;

      case 7:
        transferencia();
      break;

      case 0:
        printf("Obrigado por utilizar os serviços do Banco QuemPoupaTem!\n");
      break;
      
      default:
        printf("Por favor, escolha uma operação válida\n\n");
    }
    
  } while (operacao != 0);
}

int novo_cliente(){
  return printf("Ok!\n\n");
}

int apaga_cliente(){
  return printf("Ok!\n\n");
}

int listar_clientes(){
  return printf("Ok!\n\n");
}

int debito(){
  return printf("Ok!\n\n");
}

int deposito(){
  return printf("Ok!\n\n");
}

int extrato(){
  return printf("Ok!\n\n");
}

int transferencia(){
  return printf("Ok!\n\n\n");
}

int main() {
  inicio();

  menu();
}