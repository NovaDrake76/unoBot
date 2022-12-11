#include <stdio.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

/**
 * Para "debugar", é possível enviar uma mensagem para a saída de erro padrão (stderr).
 * Essa mensagem não será enviada para o simulador, apenas para o terminal.
 */
void debug(char *message)
{
  fprintf(stderr, "%s\n", message);
}

// APESAR DO CÓDIGO ESTAR EM UMA ÚNICA FUNÇÃO, É SEU OBJETIVO ESCREVER A LÓGICA
// DE FORMA ORGANIZADA, USANDO DIFERENTES FUNÇÕES E ARQUIVOS.

typedef struct Carta
{
  char valor;
  char naipe[MAX_LINE];

} carta;

int main()
{

  int njogadores = 0;
  int vez;
  int ncartas = 7;
  carta mao[99];
  carta mesa;
  int i = 0;
  // Obs: As variáveis deste template foram definidas apenas para o código compilar e rodar.
  // Então, cabe a você usar as variáveis adequadas em função do que está lendo.
  char temp[MAX_LINE];
  char tempois;            // string para leitura temporária de dados
  char my_id[MAX_ID_SIZE]; // identificador do seu bot

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", temp);

  // Caso queira imprimir uma mensagem para debugar, pode chamar 'debug()' passando uma string.
  // Por exemplo: debug(temp);
  debug(temp);

  // Lê o identificador do próprio bot. Isso é importante para testar quando é sua vez.
  scanf("YOU %s", my_id);

  scanf("HAND [ %c%s", &mao[0].valor, mao[0].naipe);
  for (i = 1; i < ncartas; i++)
  {
    scanf("%c%s", &mao[i].valor, mao[i].naipe);
  }

  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %c%s", &mesa.valor, mesa.naipe);

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

  while (1)
  {

    do
    {
      strcpy(complement, "");
      boy = 0;

      scanf("%s", action);
      j = strcmp(action, "DISCARD");
      if (j == 0)
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
          scanf("%s", mesa.naipe);
        }
      }
      else
      {
        scanf("%s", complement);
        j = strcmp(complement, my_id);
      }

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
          j = strcmp(mao[i].naipe, mesa.naipe);
          if ((mao[i].valor == mesa.valor) || (j = 0))
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
            j = strcmp(mao[i].naipe, mesa.naipe);
            if (j == 0)
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
  }

  return 0;
}
