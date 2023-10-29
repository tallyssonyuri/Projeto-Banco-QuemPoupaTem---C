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


/*As variáveis externas abaixo são necessárias estarem declaradas dessa forma pois nas duas vezes que incluo o arquivo .h em um arquivo.c, uma cópia da variável é criada gerando erros de compilação*/

extern int num_cadastros; /*A variável num_cadastros é responsável por contar a quantidade de cadastros já realizados*/

extern Cliente cadastro[MAX_CADASTROS]; /*O array cadastro define a quantidade de clientes que podem ser armazenados no banco, onde cada um assumirá uma posição em ordem crescente de 0 a 999*/

/*Funções*/ 

void inicio();

void abertura();

void menu();

int novo_cliente();

int apaga_cliente();

int listar_clientes();

int verifica_cpf_senha(char *cpf, char *senha);

int verifica_cpf(char *cpf);

int debito();

int deposito();

int extrato();

int transferencia();