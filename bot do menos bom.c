/********************************************************************
  Bot-exemplo do jogo Uno
  Esta é uma versão do jogo de baralho Uno, com algumas diferenças:
  A primeira é que este é um jogo baseado em turnos. Ou seja, um jogador só age quando
  for sua vez. Logo, não haverá a opção de gritar "UNO" quando um jogador tiver apenas
  uma carta. A regra de dizer UNO foi deixada de fora. Porém, para descontrair e liberar
  todo o nervosismo da partida, seu bot pode falar o que quiser na sua vez (com seu
  devido respeito!).
  A segunda é que ele é jogado com as cartas do baralho tradicional. Ou seja, ao invés de
  cores, teremos naipes (copas, espadas, ouro e paus) e, ao invés de cartas especiais (como
  "Compre duas" ou "Passe a vez"), teremos cartas do baralho como Valete, Damas, Rei, Ás
  e Coringa. Estas cartas substituem as cartas especiais do Uno, seguindo a correspondência:
    "COMPRE 4"   : C = CORINGA
    "COMPRE 2"   : V = VALETE
    "VOLTA"      : D = DAMA
    "PULA A VEZ" : R = REI
    "MUDE A COR" : A = ÀS (muda o naipe)
  
  A partida será jogada com um único baralho. Assim, teremos quatro cartas de um valor. Por
  exemplo, 7♥, 7♦, 7♣, 7♠, com exceção do coringa, que há apenas duas: um vermelho e um preto.
  Porém, para seguir o padrão das cartas, os coringas terão também um naipe, mas serão apenas
  dos naipes: ♥ (coringa vermelho) e ♣ (coringa preto).
  O jogo é gerenciado por um "simulador" que irá controlar o jogo, dando a vez ao bot da
  rodada. O bot deve ler os dados da entrada-padrão (via scanf) no formato especificado pelo
  simulador, caso contrário ele se perderá e será eliminado da partida.
  O bot também deve enviar suas ações para o simulador via saída-padrão (via printf) no formato
  esperado pelo simulador, novamente sob pena de ser eliminado da partida.
  As cartas do baralho sempre são no formato "ValorNaipe".
  Nesse formato, Valor é um dos valores das cartas tradicionais, ou seja, A, 2, 3, 4, 5, 6,
  7, 8, 9, 10, V (valete), D (dama), R (rei) e C (coringa), e Naipe é um dos seguintes naipes:
  ♥, ♦, ♣, ♠.
  Os naipes são caracteres no formato ascii estendidos, que possuem uma representação maior
  que um byte (char). Isso significa que eles deve ser tratados como se fossem strings.
  A lógica apresentada nesse template visa ilustrar a entrada e saída de dados de um bot.
  Cabe a você aprimorar a lógica das ações do seu bot.
  Bom jogo!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

typedef struct Carta
{
  char valor;
  char naipe[MAX_LINE];

} carta;

typedef struct Jogars
{
  char jogadores[99];

} jogars;
/**
 * Para "debugar", é possível enviar uma mensagem para a saída de erro padrão (stderr).
 * Essa mensagem não será enviada para o simulador, apenas para o terminal.
 */
void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

// APESAR DO CÓDIGO ESTAR EM UMA ÚNICA FUNÇÃO, É SEU OBJETIVO ESCREVER A LÓGICA
// DE FORMA ORGANIZADA, USANDO DIFERENTES FUNÇÕES E ARQUIVOS.

int main() {

  int njogadores = 0, vez, ncartas = 0, i;
  carta mao[99];
  carta mesa;
  char *token;
  jogars jogs[99];
  // Obs: As variáveis deste template foram definidas apenas para o código compilar e rodar.
  // Então, cabe a você usar as variáveis adequadas em função do que está lendo.
  char temp[MAX_LINE];   // string para leitura temporária de dados
  char my_id[MAX_ID_SIZE];  // identificador do seu bot

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  /*
  Antes da partida começar, o simulador irá enviar alguns dados para seu bot, a saber:
  - os bots que estão jogando, no formato: "PLAYERS <bot_1> <bot_2> ...";
  - o identificador de seu bot, no formato: "YOU <id>";
  - as cartas da sua mão, no formato: "HAND [ <c_1> <c_2> ... ]";
  - a carta que se encontra sobre a mesa, no formato "TABLE <c>".
  Um exemplo de dados iniciais é:
    PLAYERS b1 b2 b3
    YOU b1
    HAND [ 4♥ 7♦ 2♣ V♠ A♥ 3♦ 2♣ 9♠ ]
    TABLE 8♦
  Seu bot deve, então, ler todos esses dados no início do programa. Veja que o conjunto
  de cartas na mão do bot está entre []. Cabe a você tratar essa entrada.
  */

  // Lê uma linha até o '\n' com os identificadores dos jogadores.
  // Será necessário separar os identificadores para saber quem são, quantos bots estão
  // jogando e qual a ordem inicial de jogada deles.
  scanf("PLAYERS %[^\n]\n", temp);
  token = strtok(temp, " ");
  while( token != NULL ) {
      strcpy(jogs[njogadores].jogadores, token);
      njogadores++;
      token = strtok(NULL, " ");
  }
  // Caso queira imprimir uma mensagem para debugar, pode chamar 'debug()' passando uma string.
  // Por exemplo: debug(temp);
  debug(temp);

  // Lê o identificador do próprio bot. Isso é importante para testar quando é sua vez.
  scanf("YOU %s\n", my_id);

  // Lê as cartas iniciais que o bot tem na mão. Ex: "[ 4♥ 7♦ 2♣ J♠ A♥ 3♦ 2♣ 9♠ ]".
  // Os caracteres especiais (♥, ♦, ♣ e ♠) são caracteres ascii estendidos e precisam de
  // mais de um byte para armazená-los. Assim, é interesante guardá-los como strings.
  // Obs: lembre-se de tratar os colchetes.
  scanf("HAND [ %[^\n]\n", temp);
  token = strtok(temp, " ");
  while( strcmp(token, "]") != 0) {
      mao[ncartas].valor = token[0];
      for (i=0;i<strlen(token);i++){
          token[i]=token[i+1];
      }
      strcpy(mao[ncartas].naipe, token);
      ncartas++;
      token = strtok(NULL, " ");
  }

  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);
  mesa.valor = temp[0];
  for (i=0;i<strlen(temp);i++){
          temp[i]=temp[i+1];
  }
  strcpy(mesa.naipe, temp);
  // === PARTIDA ===

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char prior[MAX_LINE];
  int qnt = 0;
  carta comp;
  int boy = 0;
  int dado = 0;
  int j = 0;

  /*
  O `while(1) faz o bot entra num laço infinito, mas não se preocupe. O simulador do jogo irá
  "matar" o seu programa quando o jogo terminar.
  O jogo termina em duas ocasiões:
    1) quando um bot não tiver mais carta (GANHOU!)
    2) quando não tiver mais carta na pilha para comprar.
  Nesse último caso, ganha quem tiver menos cartas na mão. Em caso de mais de um bot ter o menor
  número de cartas na mão, todos eles são considerados os ganhadores.
  */
  while(1) {
    // A primeira coisa fazer é "esperar sua vez".
    // É preciso, então, de um laço enquanto a vez do seu bot não chega.
    do {
      /*
      Enquanto não chega a vez do seu bot, ele estará "escutando" todos os eventos
      do jogo. Estes eventos são repassados para todos os bots em uma linha no formato:
        <ação> <complemento1> [complemento2]
      
      Ou seja, <ação> <complemento1> estão sempre presentes na mensagem do evento, porém
      a presença de [complemento2] vai depender da ação e do complemento1.
      Por exemplo, se um bot descartar um 7 de paus, será gerado o seguinte evento:
        DISCARD 7♣
      A ação é DISCARD e o complemento é 7♣. Portanto, o próximo bot deverá descartar ou
      um 7 (de qualquer naipe) ou uma carta do naipe ♣. Guarde essa informação porque o
      próximo bot poderá ser o seu.
    
      Se a carta descartada for, por exemplo, A♣ (Ás = muda de cor), haverá um segundo
      complemento com o naipe a ser seguido pelos próximos jogadores. Por exemplo: no
      evento "DISCARD A♣ ♥", o próximo bot deverá então descartar alguma carta do naipe ♥.
      O valor da carta descartada pode também pedir uma ação do próximo jogador. Por
      exemplo, se for descartado o V (valete = compre 2), a primeira ação do próximo
      bot (pode ser o seu) deverá ser obrigatoriamente "BUY 2", sob pena do bot ser
      eliminado da partida.
      */

      strcpy(complement, "");

      scanf("%s ", action);
      if (strcmp(action, "TURN") != 0){
         boy = 0;
      }
      if (strcmp(action, "DISCARD") == 0)
      {
        scanf("%c%s", &mesa.valor, mesa.naipe);
        if (mesa.valor == 'V')
        {
          boy = 2;
        }
        else if (mesa.valor == 'C')
        {
          boy = 4;
        }
        else if (mesa.valor == 'A')
        {
          scanf(" %s", mesa.naipe);
        }
      }
      else
      {
        scanf("%s", complement);
      }
      // obs: um segundo scanf pode ser realizado par ler o 2º complemento.

      /*      
      Há um evento especial que não é gerado pelos outros bots, mas pelo simulador.
      Ele tem o formato: "TURN <id>".
      O simulador envia esta mensagem quando for a vez do bot de identificador <id>.
      Então, termine este laço interno quando for a vez do seu bot agir.
      */
    } while (strcmp(action, "TURN") || strcmp(complement, my_id));
    
    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");
    
    dado = 0;
    if (boy > 0)
    {
      printf("BUY %d\n", boy);
      for (i = 0; i < boy; i++)
      {
        scanf("%c%s", &mao[ncartas].valor, mao[ncartas].naipe);
        ncartas++;
      }
      boy = 0;
    }
    else
    {
      for (i = 0; i < ncartas; i++)
      {
        if ((mao[i].valor == 'V') || (mao[i].valor == 'C') || (mao[i].valor == 'R') || (mao[i].valor == 'A'))
        {
          if ((mao[i].valor == mesa.valor) || (strcmp(mao[i].naipe, mesa.naipe) == 0))
          {
            if (mao[i].valor == 'A')
            {
              printf("DISCARD %c%s %s\n", mao[i].valor, mao[i].naipe, mao[i].naipe);
            }
            else
            {
              printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            }
            ncartas--;
            mao[i].valor = mao[ncartas].valor;
            strcpy(mao[i].naipe, mao[ncartas].naipe);
            dado = 1;
          }
        }
      }
      if (dado == 0)
      {
        for (i = 0; i < ncartas; i++)
        {
          if (mao[i].valor == mesa.valor)
          {
            printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            ncartas--;
            mao[i].valor = mao[ncartas].valor;
            strcpy(mao[i].naipe, mao[ncartas].naipe);
            dado = 1;
          }
        }
        if (dado == 0)
        {
          for (i = 0; i < ncartas; i++)
          {
            if (strcmp(mao[i].naipe, mesa.naipe) == 0)
            {
              printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
              ncartas--;
              mao[i].valor = mao[ncartas].valor;
              strcpy(mao[i].naipe, mao[ncartas].naipe);
              dado = 1;
            }
          }
        }
      }
      if (dado == 0)
      {
        printf("BUY 1\n");
        scanf("%c%s", &mao[ncartas].valor, mao[ncartas].naipe);
        ncartas++;
      }
    }
  
    
  return 0;
}
