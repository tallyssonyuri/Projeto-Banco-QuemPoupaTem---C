#include "banco.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int novo_cliente(Cliente *cadastro, int *num_cadastros){
  printf("NOVO CLIENTE\n\n");
  printf("Informe a abaixo as informações a respeito do cliente\n\n");
  
  if(*num_cadastros >= MAX_CADASTROS) { /*Caso o número de cadastros tenha atingido o limite, não será possível prosseguir com o cadastro*/
    printf("Não é possível cadastrar mais clientes. Limite atingido.\n\n");
    return -1;
}
  
  char nome[50]; /*Nome de até 49 caracteres*/
  char cpf[12]; /*CPF de 11 caracteres*/
  char conta[6]; /*Char que irá armazenar contas Plus ou Comum*/
  double saldo; /*Variável saldo que suporta um número de até 64 bits*/
  char senha[11]; /*Senha de até 10 caracteres*/
  char buffer[50]; /*Buffer temporário para leitura*/
  
  printf("Digite o nome: ");
  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = 0; /*Remove a nova linha no final, se houver*/

  printf("Digite o CPF: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;  /*Remove a nova linha no final, se houver*/
  strcpy(cpf, buffer); /*Copia o conteúdo do buffer para cpf*/

  for(int i = 0; i < *num_cadastros; i++) { /*Caso o CPF seja encontrado dentro do armazenamento, não será possível prosseguir com o novo cadastro*/
    if(strcmp(cadastro[i].cpf, cpf) == 0) {
      printf("\nCPF já cadastrado.\n\n");
      return -1;
    }
  }

  do {
    printf("Digite o tipo de conta (A - Comum ou B - Plus): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    char tipo_conta = tolower(buffer[0]);/*Transformo o que foi digitado em minusculo para futuras verificações e não influencie no decorrer do código*/

    /*Caso a conta não for digitado como uma das opções informadas, pedirá para o usuário digitar até que seja válido*/
    if (tipo_conta == 'a') {
      strcpy(conta, "Comum"); /*Se for 'A', a conta = Comum*/
    } else if (tipo_conta == 'b') {
      strcpy(conta, "Plus"); /*Se for 'B', a conta = Plus*/
    } else {
      printf("\nEntrada inválida. Por favor, digite A para Conta Comum ou B para Conta Plus.\n\n");
    }
  } while (strcmp(conta, "Comum") != 0 && strcmp(conta, "Plus") != 0);

  int num; /*A variável num será responsável por validar se o usuário digitou um numero e não uma letra*/
  do {
    printf("Digite o saldo inicial: R$ ");
    num = scanf("%lf", &saldo);
    while (getchar() != '\n');
    if (num == 0) { /*Caso a variável receber alguma letra, retornará 0 que signifca falso na linguagem C, e solicitará o usuário digitar novamente*/
      printf("\nEntrada inválida. Por favor, digite um número.\n\n");
      }
  } while (num == 0);

  printf("Digite a senha: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0; /*Remove a nova linha no final, se houver*/
  strcpy(senha, buffer); /* Copia o conteúdo do buffer para senha)*/
  
  strcpy(cadastro[*num_cadastros].nome, nome);
  strcpy(cadastro[*num_cadastros].cpf, cpf);
  strcpy(cadastro[*num_cadastros].conta, conta);
  cadastro[*num_cadastros].saldo = saldo;
  strcpy(cadastro[*num_cadastros].senha, senha);
  cadastro[*num_cadastros].num_operacoes = 0;

  (*num_cadastros)++;
  printf("\nCliente cadastrado com sucesso!\n\n");

  return 0;
}

int apaga_cliente(Cliente *cadastro, int *num_cadastros) {
  printf("DELETAR CLIENTES\n\n");

  if(*num_cadastros == 0) { /*Caso não exista nenhum usuário cadastrado, a variável num_cadastros contém 0 e será informado ao usuário quando essa condição for válida*/
    printf("Nenhum cliente cadastrado.\n\n");
    return -1;
  }
  
  char cpf[12]; /*Variável que irá receber o CPF do cliente*/
  char buffer[50]; /*Variável que receber a entrada do cliente*/

  /*Seguindo a mesma lógica de demais funções, lê a entrada do usuário dentro da variável de entrada e depois a adiciona dentro da variável cpf*/
  printf("Digite o CPF do cliente que deseja deletar: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf, buffer);

  for(int i = 0; i < *num_cadastros; i++) { /*Esse laço de repetição percorre todos os clientes cadastrados*/
    if(strcmp(cadastro[i].cpf, cpf) == 0) { /*Se o CPF digitado for igual ao CPF cadastrado */
        for(int j = i; j < *num_cadastros - 1; j++) { /*Move todos os CPFs cadastrados uma posição para trás, apagando assim o CPF cadastrados*/
          cadastro[j] = cadastro[j + 1];
        }
        (*num_cadastros)--; /*E a variável que armazena o numero de cadastros diminui 1 na contagem*/
        printf("\nCliente deletado com sucesso!\n\n");
        return 0;
    }
  }
  printf("\nCliente não encontrado.\n\n"); /*Caso o laço percorrer por compelto e não achar o CPF, será informado ao usuário*/
  return -1;
}

int listar_clientes(Cliente *cadastro, int *num_cadastros) {
  printf("CLIENTES CADASTRADOS\n\n");
  if(*num_cadastros == 0) { /*Caso não exista nenhum usuário cadastrado, a variável num_cadastros contém 0 e será informado ao usuário quando essa condição for válida*/
      printf("Nenhum cliente cadastrado.\n\n");
      return -1;
  }
  for(int i = 0; i < *num_cadastros; i++) { /*Caso for maior que 0, este laço gerará um loop que percorre o array cadastro que contém o struct com as informações dos clientes, listando elas uma a uma*/
    printf("\n\n");
    printf("Cliente %d\n\n", i+1);
    printf("Nome: %s\n", cadastro[i].nome);
    printf("CPF: %s\n", cadastro[i].cpf);
    printf("Tipo de Conta: %s\n", cadastro[i].conta);
    printf("Saldo: R$ %.2lf\n", cadastro[i].saldo);
  }
  printf("\n");
  return 0;
}

int verifica_cpf_senha(char *cpf, char *senha,  Cliente *cadastro, int *num_cadastros) { /*Essa função tem como objetivo validar se o CPF e Senha estão corretos com o cadastrado, para assim permir ou não a execução do restante do programa*/
  for(int i = 0; i < *num_cadastros; i++) {
    if(strcmp(cadastro[i].cpf, cpf) == 0 && strcmp(cadastro[i].senha, senha) == 0) { /*Retorna 0 se amabas variáveis forem iguais, sendo o método usado para validação*/
      return i; /*Retorna o indice do cliente dentro do array se o CPF e Senha estiverem corretos caso for encontrado o cadastro com essa condição*/
    }
  }
  return -1; /*Retorna -1 caso um ou ambos dados não estiverem corretos*/
}

int verifica_cpf(char *cpf, Cliente *cadastro, int *num_cadastros) { /*Essa função tem como objetivo validar se o CPF está correto com o cadastrado, para assim permir ou não a execução do restante do programa*/
  for(int i = 0; i < *num_cadastros; i++) {
    if(strcmp(cadastro[i].cpf, cpf) == 0) { /*Retorna 0 se amabas variáveis forem iguais, sendo o método usado para validação*/
      return i; /*Retorna o indice do cliente dentro do array se o CPF estiver correto caso for encontrado o cadastro com essa condição*/
    }
  }
  return -1; /*Retorna -1 caso um ou ambos dados não estiverem corretos*/
}

int debito(Cliente *cadastro, int *num_cadastros) {
  printf("DEBITO\n\n");

  if(*num_cadastros == 0) { /*Caso não exista nenhum usuário cadastrado, a variável num_cadastros contém 0 e será informado ao usuário quando essa condição for válida*/
    printf("Nenhum cliente cadastrado.\n\n");
    return -1;
  }

  char cpf[12]; /*Variável responsável pelo armazenamento do CPF*/
  char senha[11]; /*Variável responsável pelo armazenamento da senha*/
  double valor; /*Variável que vai recebr o valor do débito*/
  char buffer[50]; /*Variável que recebe a entrada temporária dos usuários*/
  int num; /*Variável para validção se o valor da transação é um número*/

  /*As duas entradas abaixo seguem a mesma lógica por trás das entradas da função novo_cliente()*/
  printf("Digite o CPF: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf, buffer);

  printf("Digite a senha: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(senha, buffer);

  do {
    printf("Digite o valor a ser debitado: R$ ");
    num = scanf("%lf", &valor);
    while (getchar() != '\n');
    if (num == 0) {
      printf("\nEntrada inválida. Por favor, digite um número.\n\n");
    }
  } while (num == 0);

  int cliente_indice = verifica_cpf_senha(cpf, senha, cadastro, num_cadastros); /*A variável cliente_indice recebe a posição dentro do array que o cpf e senha foram encontrados*/

  if(cliente_indice != -1) { /*E a operação só será executada se o indice for diferente de -1, que é o retorno da função verifica_cpf_senha() caso não seja encontrado a condição*/
    double taxa; /*A variável taxa recebe o valor da taxa do cliente*/
    double limite; /*A variável limite recebe o valor máximo de limite negativo do cliente*/
    if(strcmp(cadastro[cliente_indice].conta, "Comum") == 0) { /*Se a conta do cliente for o mesmo que "Comum", segue as condições abaixo*/
      taxa = 0.05;
      limite = -1000.0;
    } else if(strcmp(cadastro[cliente_indice].conta, "Plus") == 0) { /*Se a conta do cliente for o mesmo que "Plus", segue as condições abaixo*/
      taxa = 0.03;
      limite = -5000.0;
    }
    double debito = valor * (1 + taxa); /*O valor do débito é o resultado + a cobrança da taxa*/
    if(cadastro[cliente_indice].saldo - debito >= limite) { /*Se o saldo - o débito não ultrapassar o liminte negativo, é possível realizar a operação*/
      cadastro[cliente_indice].saldo -= debito;

      if (cadastro[cliente_indice].num_operacoes == MAX_OPERACOES) { /*Se o número máximo de operações foi atingido, remova a operação mais antiga*/
        for (int i = 0; i < cadastro[cliente_indice].num_operacoes - 1; i++) {
          cadastro[cliente_indice].qtd_operacoes[i] = cadastro[cliente_indice].qtd_operacoes[i + 1];
        }
        cadastro[cliente_indice].num_operacoes--;
      }

      /*Adicione a operação ao registro de operações do cliente*/
strcpy(cadastro[cliente_indice].qtd_operacoes[cadastro[cliente_indice].num_operacoes].tipo, "Débito");
      cadastro[cliente_indice].qtd_operacoes[cadastro[cliente_indice].num_operacoes].valor = debito;
      cadastro[cliente_indice].num_operacoes++;

      /*Abra o arquivo para gravação*/
      FILE *file;
      char filename[16];
      sprintf(filename, "%s.txt", cpf);
      file = fopen(filename, "a");
      if (file == NULL) {
          printf("\nNão foi possível abrir o arquivo.\n\n");
          return -1;
      }
      
      fprintf(file, "Operação: Débito, Valor: R$ %.2f\n", debito); /*Escreve a operação no arquivo*/
      fclose(file); /*Fecha o arquivo*/

      printf("\nDébito realizado com sucesso! Seu novo saldo é R$ %.2f\n\n", cadastro[cliente_indice].saldo);
      return 0;
      } else {
      printf("\nNão foi possível realizar o débito. O saldo ficaria abaixo do limite permitido.\n\n");
      return -1;
      }

    } else {
    printf("CPF ou senha incorretos.\n");
    return -1;
    }
  }

int deposito(Cliente *cadastro, int *num_cadastros) {
  printf("DEPOSITO\n\n");

  if(*num_cadastros == 0) { /*Caso não exista nenhum usuário cadastrado, a variável num_cadastros contém 0 e será informado ao usuário quando essa condição for válida*/
    printf("Nenhum cliente cadastrado.\n\n");
    return -1;
  }

  char cpf[12]; /*Variável que armazena o CPF do cliente*/
  double valor; /*Variável que armazena o valor do depósito*/
  char buffer[50]; /*Variável que armazena a entrada do cliente*/
  int num; /*Variável usada para validação numérica*/

  /*Mesma lógica de entrada das funções anteriores*/
  printf("Digite o CPF: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf, buffer);

  do { /*Caso o valor não for um número, não será possível prosseguir atéser digitado um número*/
    printf("Digite o valor a ser depositado: R$ ");
    num = scanf("%lf", &valor);
    while (getchar() != '\n');
    if (num == 0) {
      printf("\nEntrada inválida. Por favor, digite um número.\n\n");
    }
  } while (num == 0);

  int cliente_indice = verifica_cpf(cpf, cadastro, num_cadastros); /*A variável cliente_indice recebe a posição do CPF encontrado dentro do array*/

  if(cliente_indice != -1) {
    cadastro[cliente_indice].saldo += valor;
    
    if (cadastro[cliente_indice].num_operacoes == MAX_OPERACOES) { /*Se o número máximo de operações foi atingido, remova a operação mais antiga*/
      for (int i = 0; i < cadastro[cliente_indice].num_operacoes - 1; i++) {
        cadastro[cliente_indice].qtd_operacoes[i] = cadastro[cliente_indice].qtd_operacoes[i + 1];
      }
      cadastro[cliente_indice].num_operacoes--;
    }

    /*Adicione a operação ao registro de operações do cliente*/
    strcpy(cadastro[cliente_indice].qtd_operacoes[cadastro[cliente_indice].num_operacoes].tipo, "Depósito");
    cadastro[cliente_indice].qtd_operacoes[cadastro[cliente_indice].num_operacoes].valor = valor;
    cadastro[cliente_indice].num_operacoes++;

    /*Abra o arquivo para gravação*/
    FILE *file;
    char filename[16];
    sprintf(filename, "%s.txt", cpf);
    file = fopen(filename, "a");
    if (file == NULL) {
        printf("\nNão foi possível abrir o arquivo.\n\n");
        return -1;
    }

    /*Escreve a operação no arquivo*/
    fprintf(file, "Operação: Depósito, Valor: R$ %.2f\n", valor);
    /* Feche o arquivo*/
    fclose(file);

    printf("\nDepósito realizado com sucesso! Seu novo saldo é R$ %.2f\n\n", cadastro[cliente_indice].saldo);
    return 0;

  } else {
    printf("CPF incorreto.\n\n");
    return -1;
  }
  return -1;
  }

int extrato(Cliente *cadastro, int *num_cadastros) {
  printf("EXTRATO\n\n");
  printf("Informe a abaixo as informações a respeito do cliente\n\n");

  char cpf[12]; /*Variável que recebe o CPF do cliente*/
  char senha[11]; /*Variável que recebe a senha*/
  char buffer[50]; /*A variável que recebe a entrada de dados*/

  /*Entrada de dados da mesma forma que as funções anteriores*/
  printf("Digite o CPF: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf, buffer);

  printf("Digite a senha: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(senha, buffer);

  int index = verifica_cpf_senha(cpf, senha, cadastro, num_cadastros); /*A variável index recebe a condição de verificação de CPF e Senha*/
  if (index == -1) {
    printf("\nCPF ou senha incorretos.\n\n");
    return -1;
  }

  FILE *file; /*Declara um ponteiro para um arquivo*/
  char filename[16]; /*Declara uma string para armazenar o nome do arquivo*/
  sprintf(filename, "%s.txt", cpf); /*Formata o nome do arquivo com o CPF fornecido*/
  file = fopen(filename, "r"); /*Abre o arquivo para leitura*/
  if (file == NULL) { /*Verifica se o arquivo foi aberto corretamente*/
    printf("\nNão foi possível abrir o arquivo de extrato.\n\n"); /*Imprime uma mensagem de erro se o arquivo não puder ser aberto*/
    return -1;
  }

  printf("\nExtrato para CPF: %s\n\n", cpf); /*Imprime o CPF para o qual o extrato será exibido*/

  char line[256]; /*Declara uma string para armazenar cada linha do arquivo*/
  while (fgets(line, sizeof(line), file)) { /*Lê cada linha do arquivo até o final*/
    printf("%s", line); /*Imprime a linha atual*/
  }
  fclose(file); /*Fecha o arquivo*/
  return 0;
}

int transferencia(Cliente *cadastro, int *num_cadastros) {
  printf("TRANSFERÊNCIAS\n\n");

  if(*num_cadastros == 0) { /*Caso não exista nenhum usuário cadastrado, a variável num_cadastros contém 0 e será informado ao usuário quando essa condição for válida*/
    printf("Nenhum cliente cadastrado.\n\n");
    return -1;
  }

  char cpf_origem[12]; /*Variável que armazena o CPF de origem*/
  char senha[11]; /*Variável que armazena a senha*/
  char cpf_destino[12]; /*Variável que armazena o CPF do destinatário*/
  double valor; /*Variável que armazena o valor da transferência*/
  char buffer[50]; /*Variável que armazena a entrada dos dados*/
  int num; /*Variável usada para condição de entrada numérica*/

  /*Mesma lógica de entrada das outras funções*/
  printf("Digite o CPF (Origem): ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf_origem, buffer);

  printf("Digite a senha: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(senha, buffer);

  printf("Digite o CPF (Destino): ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  strcpy(cpf_destino, buffer);

  do { /*Mesma lógica de entrada de valor numérico de outras funções*/
    printf("Digite o valor a ser transferido: R$ ");
    num = scanf("%lf", &valor);
    while (getchar() != '\n');
    if (num == 0) {
      printf("\nEntrada inválida. Por favor, digite um número.\n\n");
    }
  } while (num == 0);

  int cliente_origem_indice = verifica_cpf_senha(cpf_origem, senha, cadastro, num_cadastros); /*Variável que recebe a posição do cliente da origem da transferência*/

  if(cliente_origem_indice != -1) { /*Caso o CPF e senha estiverem válidos, o programa irá prosseguir*/
    int cliente_destino_indice = verifica_cpf(cpf_destino, cadastro, num_cadastros); /*Variável que recebe a posição do cliente de destino da transferência*/

    if(cliente_destino_indice != -1) { /*Caso o CPF e destino estiver correto, o programa irá prosseguir*/
      double taxa; /*Variável que recebe o valor da taxa*/
      double limite; /*Variável que recebe o valor do limite negativo do cliente de origem*/
      if(strcmp(cadastro[cliente_origem_indice].conta, "Comum") == 0) { /*Caso a conta for Comum, recebe as condições abaixo*/
        taxa = 0.05;
        limite = -1000.0;
      } else if(strcmp(cadastro[cliente_origem_indice].conta, "Plus") == 0) { /*Caso a conta for Plus, recebe as condições abaixo*/
        taxa = 0.03;
        limite = -5000.0;
      }
      double transferencia = valor * (1 + taxa); /*A variável transferencia recebe o valor da transferencia + a cobrança da taxa*/
      if(cadastro[cliente_origem_indice].saldo - transferencia >= limite) { /*Se o limite negativo permitir do CPF de origem permitir a transferência junto a cobrança da taxa, o programa seguirá*/
        cadastro[cliente_origem_indice].saldo -= transferencia; /*O saldo do cliente de origem será debitado pelo valor da transferência + cobrança da taxa*/
        cadastro[cliente_destino_indice].saldo += valor; /*O saldo do cliente de destino será creditado pelo valor da transferência sem taxas*/

        if (cadastro[cliente_origem_indice].num_operacoes == MAX_OPERACOES) {  /*Se o número máximo de operações foi atingido, remova a operação mais antiga*/
          for (int i = 0; i < cadastro[cliente_origem_indice].num_operacoes - 1; i++) {
            cadastro[cliente_origem_indice].qtd_operacoes[i] = cadastro[cliente_origem_indice].qtd_operacoes[i + 1];
          }
          cadastro[cliente_origem_indice].num_operacoes--;
        }

        /*Adiciona a operação ao registro de operações do cliente*/
        strcpy(cadastro[cliente_origem_indice].qtd_operacoes[cadastro[cliente_origem_indice].num_operacoes].tipo, "Transferência");
        cadastro[cliente_origem_indice].qtd_operacoes[cadastro[cliente_origem_indice].num_operacoes].valor = transferencia;
        cadastro[cliente_origem_indice].num_operacoes++;

        /*Abre o arquivo para gravação*/
        FILE *file;
        char filename[16];
        sprintf(filename, "%s.txt", cpf_origem);
        file = fopen(filename, "a");
        if (file == NULL) {
            printf("\nNão foi possível abrir o arquivo.\n\n");
            return -1;
        }

        /*Escreva a operação no arquivo*/
        fprintf(file, "Operação: Transferência para %s, Valor: R$ %.2f\n", cpf_destino, transferencia);
        /*Feche o arquivo*/
        fclose(file);
      
        printf("\nTransferência realizada com sucesso! Seu novo saldo é R$ %.2f\n\n", cadastro[cliente_origem_indice].saldo); /*Indica o saldo atual do cliente de origem*/
        return 0;
      } else {
        printf("\nNão foi possível realizar a transferência. O saldo ficaria abaixo do limite permitido.\n\n");
        return -1;
      }
    } else { /*Caso não for possível transferir por conta do limite negativo, informará a mensagem ao usuário*/
      printf("\nCPF do destinatário não encontrado.\n\n");
      return -1;
    }
  } else { /*Caso o CPF ou senha de origem não estiverem de acordo*/
    printf("\nCPF ou senha de origem incorretos.\n\n");
    return -1;
  }
  return -1;
}

int salvar_dados(Cliente *cadastro, int *num_cadastros, char *arquivo) { /* Função para salvar os dados dos clientes em um arquivo */
  
  FILE *file = fopen(arquivo, "wb"); /* Abre o arquivo em modo de escrita binária */
  if (file == NULL) { /* Se o arquivo não pôde ser aberto, imprime uma mensagem de erro e retorna 1 */
      printf("Não foi possível abrir o arquivo para gravação.\n\n");
      return 1;
  }
  /* Escreve o número de cadastros no arquivo */
  fwrite(num_cadastros, sizeof(int), 1, file);
  /* Escreve os dados dos clientes no arquivo */
  fwrite(cadastro, sizeof(Cliente), *num_cadastros, file);
  /* Fecha o arquivo */
  fclose(file);

  /* Retorna 0 para indicar que a função foi executada com sucesso */
  return 0;
}

int carregar_dados(Cliente *cadastro, int *num_cadastros, char *arquivo) { /* Função para carregar os dados dos clientes de um arquivo */
  FILE *file = fopen(arquivo, "rb");/* Abre o arquivo em modo de leitura binária */
  if (file == NULL) {   /* Se o arquivo não pôde ser aberto, imprime uma mensagem de erro e retorna 1 */
      printf("Não foi possível abrir o arquivo para leitura.\n\n");
      return 1;
  }
  /* Lê o número de cadastros do arquivo */
  fread(num_cadastros, sizeof(int), 1, file);
  /* Lê os dados dos clientes do arquivo */
  fread(cadastro, sizeof(Cliente), *num_cadastros, file);
  /* Fecha o arquivo */
  fclose(file);

  /* Retorna 0 para indicar que a função foi executada com sucesso */
  return 0;
}
