#include "banco.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
  
  Cliente cadastro[MAX_CADASTROS]; /*A variável num_cadastros é responsável por contar a quantidade de cadastros já realizados*/
  int num_cadastros = 0; /*O array cadastro define a quantidade de clientes que podem ser armazenados no banco, onde cada um assumirá uma posição em ordem crescente de 0 a 999*/

  int cod; /* Variável para armazenar códigos de retorno */
  char arquivo[100] = "banco"; /* Nome do arquivo para armazenar os dados do banco */

  cod = carregar_dados(cadastro, &num_cadastros, arquivo); /* Tenta carregar as tarefas do arquivo */
  if (cod != 0){ /* Se o arquivo não pôde ser aberto ele informa ao usuario */
    printf("Arquivo ainda não carregado, prossiga.\n\n\n");
    num_cadastros = 0; 
  }

  printf("Seja bem vindo ao Banco QuemPoupaTem!\n\n");

  printf("Abaixo, você poderá selecionar a operação que deseja seguir em seu programa conforme o seu número correspondente\n\n");
  int operacao = 8; /* Iniciando a variável com uma opção não válida para caso o usuário não selecionar nenhuma das opções, mão colher nenhum lixo de memmória e informar que é necessário escolher algo válido para prosseguir */
  
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
    int c;
    while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer de entrada, pois será preciso para não atrapalhar na execução das demais funções no programa */
  
    switch(operacao){
      case 1:
        novo_cliente(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 2:
        apaga_cliente(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 3:
        listar_clientes(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 4:
        debito(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 5:
        deposito(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 6:
       extrato(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 7:
        transferencia(cadastro, &num_cadastros);
          printf("\n");
      break;
  
      case 0:
        printf("Obrigado por utilizar os serviços do Banco QuemPoupaTem!\n");
      break;
  
      default:
        printf("Por favor, escolha uma operação válida\n\n");
    }
  
  } while (operacao != 0);
  
  cod = salvar_dados(cadastro, &num_cadastros, arquivo); /* Salva os dados no arquivo */
  if (cod != 0){ /* Se houve um problema ao salvar, informará ao usuario */
    printf("Problema ao salvar o arquivo\n\n");
  }

  return 0;
}