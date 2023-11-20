/*Structs*/
#define MAX_CADASTROS 1000
/*MAX_CADASTROS é uma constante que define a quantidade de clientes que posso cadastrar no banco*/
#define MAX_OPERACOES 100

typedef struct {
  char tipo[13]; /*Tipo de operação (transferencia, saque ou deposito)*/
  double valor; /*O valor da operação*/
} Operacao;

typedef struct {
  char nome[50]; /*Nome de até 49 caracteres*/
  char cpf[12]; /*CPF de 11 caracteres*/
  char conta[6]; /*Char que irá armazenar contas Plus ou Comu*/
  double saldo; /*Variável saldo que suporta um número de até 64 bits*/
  char senha[11]; /*Senha de até 10 caracteres*/
  int num_operacoes; /*Váriavel para contar quantas operações já foram realizadas por esse cliente*/

  Operacao qtd_operacoes [MAX_OPERACOES]; /*A variável qtd_operacoes armazna a quantidade de operações que devem ser armazenadas as informações, da posição 0 a 99*/

} Cliente; /*O struct Cliente é reponsável por armazenar as informações nome, cpf, conta, saldo e senha dos clientes cadastrados*/


/*Funções*/
int novo_cliente(Cliente *cadastro, int *num_cadastros);

int apaga_cliente(Cliente *cadastro, int *num_cadastros);

int listar_clientes(Cliente *cadastro, int *num_cadastros);

int verifica_cpf_senha(char *cpf, char *senha, Cliente *cadastro, int *num_cadastros);

int verifica_cpf(char *cpf, Cliente *cadastro, int *num_cadastros);

int debito(Cliente *cadastro, int *num_cadastros);

int deposito(Cliente *cadastro, int *num_cadastros);

int extrato(Cliente *cadastro, int *num_cadastros);

int transferencia(Cliente *cadastro, int *num_cadastros);

int salvar_dados(Cliente *cadastro, int *num_cadastros, char *arquivo);

int carregar_dados(Cliente *cadastro, int *num_cadastros, char *arquivo);
