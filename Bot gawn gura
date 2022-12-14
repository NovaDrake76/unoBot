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

void debug(char *message)
{
  fprintf(stderr, "%s\n", message);
}

int main()
{

  int njogadores = 0, vez, cardsInHand = 0, i;
  carta mao[99];
  carta mesa;
  char *token;
  jogars jogs[99];
  // Obs: As variáveis deste template foram definidas apenas para o código compilar e rodar.
  // Então, cabe a você usar as variáveis adequadas em função do que está lendo.
  char temp[MAX_LINE];     // string para leitura temporária de hasPlayeds
  char my_id[MAX_ID_SIZE]; // identificador do seu bot

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guarhasPlayed temporariamente"
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", temp);
  token = strtok(temp, " ");
  while (token != NULL)
  {
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
  while (strcmp(token, "]") != 0)
  {
    mao[cardsInHand].valor = token[0];
    for (i = 0; i < strlen(token); i++)
    {
      token[i] = token[i + 1];
    }
    strcpy(mao[cardsInHand].naipe, token);
    cardsInHand++;
    token = strtok(NULL, " ");
  }

  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);
  mesa.valor = temp[0];
  for (i = 0; i < strlen(temp); i++)
  {
    temp[i] = temp[i + 1];
  }
  strcpy(mesa.naipe, temp);
  // === PARTIDA ===

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char prior[MAX_LINE];
  int qnt = 0;
  carta comp;
  int cardsToBuy = 0;
  int hasPlayed = 0;
  int j = 0;

  while (1)
  {
    // A primeira coisa fazer é "esperar sua vez".
    // É preciso, então, de um laço enquanto a vez do seu bot não chega.
    do
    {

      strcpy(complement, "");

      scanf("%s ", action);
      if (strcmp(action, "TURN") != 0)
      {
        cardsToBuy = 0;
      }
      if (strcmp(action, "DISCARD") == 0)
      {
        scanf("%c%s", &mesa.valor, mesa.naipe);
        if (mesa.valor == 'V')
        {
          cardsToBuy = 2;
        }
        else if (mesa.valor == 'C')
        {
          cardsToBuy = 4;
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

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");

    // read all cards in hand
    // for (i = 0; i < cardsInHand; i++)
    // {
    //   debug(&mao[i].valor);
    // }

    hasPlayed = 0;
    // trata acao
    if (cardsToBuy == 2 || cardsToBuy == 4)
    {
      printf("BUY %d\n", cardsToBuy);
      for (i = 0; i < cardsToBuy; i++)
      {
        scanf("%s", temp);
        mao[cardsInHand].valor = temp[0];
        for (j = 0; j < strlen(temp); j++)
        {
          temp[j] = temp[j + 1];
        }
        strcpy(mao[cardsInHand].naipe, temp);

        cardsInHand++;
      }
      hasPlayed = 1;
      cardsToBuy = 0;
    }
    else
    {

      for (i = 0; i < cardsInHand; i++)
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

            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);

            hasPlayed = 1;
          }
        }
        if (hasPlayed == 1)
        {
          break;
        }
      }

      // verificar valor
      if (hasPlayed == 0)
      {

        for (i = 0; i < cardsInHand; i++)
        {
          if (mao[i].valor == mesa.valor)
          {
            printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);
            hasPlayed = 1;
          }

          if (hasPlayed == 1)
          {
            break;
          }
        }
      }

      // verificar naipe
      if (hasPlayed == 0)
      {
        for (i = 0; i < cardsInHand; i++)
        {
          if (strcmp(mao[i].naipe, mesa.naipe) == 0)
          {
            printf("DISCARD %c%s\n", mao[i].valor, mao[i].naipe);
            cardsInHand--;
            mesa.valor = mao[i].valor;
            strcpy(mesa.naipe, mao[i].naipe);
            mao[i].valor = mao[cardsInHand].valor;
            strcpy(mao[i].naipe, mao[cardsInHand].naipe);
            hasPlayed = 1;
          }

          if (hasPlayed == 1)
          {
            break;
          }
        }
      }

      // se não tiver feito nada, compra
      if (hasPlayed == 0)
      {

        printf("BUY 1\n");
        scanf("%s", temp);
        mao[cardsInHand].valor = temp[0];
        for (i = 0; i < strlen(temp); i++)
        {
          temp[i] = temp[i + 1];
        }
        strcpy(mao[cardsInHand].naipe, temp);

        cardsInHand++;
        cardsToBuy = 0;
      }
    }
  }
  return 0;
}
