/**
 * @file 	ranking.c
 * @authors	AGRIPPINO, ALVAREZ, CASTRO, HEIR
 *
 * @brief 	Source del modulo ranking.
 * 			Funciones de interaccion con el ranking de jugadores.
 * 			Permite trabajar con el txt correspondiente fácilmente,
 *
 * @copyright Copyright (c) 2022 ~ Ingeniería Electrónica ~ ITBA
 *
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "ranking.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

// Largo maximo de una linea del txt
#define MAX_LEN 100

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Lee el archivo de ranking y recarga arrays internos.
 *
 */
static void recargarRanking(void);

/**
 * @brief Reordena arrays internos con informacion de ranking, quedando el de mayor puntaje primero, por orden alfabetico.
 *
 */
static void ordenarRanking(void);

/**
 * @brief Escribe los arrays internos al txt de ranking
 *
 */
static void writeRanking(void);

/**
 * @brief Crea txt de ranking si no existe
 *
 */
static void createRankingFile(void);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Nombre del archivo de ranking
static char *strRanking = "ranking.txt";
// Nombre del archivo temporal
static char *strTemp = "temp.txt";

// Handler del archivo de ranking
FILE *handlerRanking = NULL;
// Handler del archivo temporal
FILE *handlerTemp = NULL;

// Punteros a nombres
static char **names = NULL;
// Puntero a scores
static unsigned long long *scores = NULL;

// String temporal
static char tempStr[MAX_LEN];

// Contador de lineas del txt
static uint lineNumber = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void iniciarRanking(void)
{
    lineNumber = 0;

    createRankingFile();

    if ((handlerRanking = fopen(strRanking, "r")) == NULL)
    {
        printf("Error opening ranking.txt");
    }

    recargarRanking();

    fclose(handlerRanking);
}

void actualizarRanking(char *name, unsigned long long score)
{
    int i;
    bool player_exists;

    // Veo si el jugador esta en el ranking
    for (i = 0, player_exists = false; i < lineNumber && !player_exists; i++)
    {
        if (!lineNumber)
            break;

        // Si el nombre coincide...
        if (strcmp(names[i], name) == 0)
        {
            // Actualiza el score
            scores[i] = score;
            player_exists = true;
        }
    }

    // Si el jugador no existe en el ranking, lo agrego al final
    if (!player_exists)
    {
        // Reservo memoria para un puntero
        names = (char **)realloc(names, sizeof(char *) * (lineNumber + 1));
        // Reservo memoria para el nombre
        names[lineNumber] = (char *)calloc(strlen(name), sizeof(char));
        // Asigno nombre
        strcpy(names[lineNumber], name);

        // Reservo memoria para un score
        scores = (unsigned long long *)realloc(scores, sizeof(unsigned long long) * (lineNumber + 1));
        // Asigno score
        scores[lineNumber] = score;

        lineNumber++;
    }

    ordenarRanking();
}

void desiniciarRanking(void)
{
    // Escribe al archivo
    writeRanking();

    // Liberacion de memoria
    int i;
    for (i = 0; i < lineNumber; i++)
        free(names[i]);

    free(names);
}

bool verificarJugadorRanking(char *name)
{
    int i;
    bool exists;

    // Ranking vacio
    if (!lineNumber)
        return false;

    for (i = 0, exists = false; i < lineNumber && !exists; i++)
    {
        // Si el nombre coincide...
        if (strcmp(names[i], name) == 0)
            exists = true;
    }

    return exists;
}

unsigned long long getJugadorRankingPuntos(char *name)
{
    int i;
    bool exists;
    unsigned long long score;

    for (i = 0, exists = false; i < lineNumber && !exists; i++)
    {
        // Si el nombre coincide...
        if (strcmp(names[i], name) == 0)
        {
            // Carga el score
            score = scores[i];
            exists = true;
        }
    }

    if (!exists)
        score = 0;

    return score;
}

uint getRankingLineas(void)
{
    return lineNumber;
}

char **getRankingNombres(void)
{
    return names;
}

unsigned long long *getRankingPuntos(void)
{
    return scores;
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void recargarRanking(void)
{
    lineNumber = 0;

    while (fgets(tempStr, MAX_LEN, handlerRanking) != NULL)
    {
        // Remove the trailing newline character
        if (strchr(tempStr, '\n'))
            tempStr[strlen(tempStr) - 1] = '\0';

        // Puntero al nombre
        char *tempPtr = strtok(tempStr, " ");
        // Reservo memoria para un puntero
        names = (char **)realloc(names, sizeof(char *) * (lineNumber + 1));
        // Reservo memoria para el nombre
        names[lineNumber] = (char *)calloc(strlen(tempPtr), sizeof(char));
        // Copia nombre
        strcpy(names[lineNumber], tempPtr);

        // Puntero al score
        tempPtr = strtok(NULL, " ");
        // Reservo memoria para un score
        scores = (unsigned long long *)realloc(scores, sizeof(unsigned long long) * (lineNumber + 1));
        // Copia score
        scores[lineNumber] = strtoul(tempPtr, NULL, 10);

        lineNumber++;
    }
}

static void ordenarRanking(void)
{
    int i, j;
    unsigned long long tempScore;

    for (i = 0; i < (lineNumber - 1); i++)
    {
        for (j = 0; j < (lineNumber - i - 1); j++)
        {
            // Si el primer score es menor, o si es igual al siguiente pero predomina orden alfabetico...
            if ((scores[j] < scores[j + 1]) || ((scores[j] == scores[j + 1]) && (strcmp(names[j], names[j + 1]) > 0)))
            {
                // Backup del menor
                strcpy(tempStr, names[j]);
                tempScore = scores[j];

                // El mayor se pone en la posicion del menor
                strcpy(names[j], names[j + 1]);
                scores[j] = scores[j + 1];

                // El backup se pone en la posicion del mayor
                strcpy(names[j + 1], tempStr);
                scores[j + 1] = tempScore;
            }
        }
    }
}

static void writeRanking(void)
{
    int i;

    // Crea archivo temporal
    if ((handlerTemp = fopen(strTemp, "w")) == NULL)
    {
        printf("Error opening temp.txt");
    }

    if (lineNumber)
    {
        // Copia lo nuevo en temp.txt
        for (i = 0; i < lineNumber; i++)
        {
            fprintf(handlerTemp, "%s %lld\n", names[i], scores[i]);
        }
    }

    remove(strRanking);
    rename(strTemp, strRanking);

    fclose(handlerTemp);
}

static void createRankingFile(void)
{
    // crea el archivo, si no lo estaba
    FILE *pFile;
    if ((pFile = fopen(strRanking, "a")) == NULL)
    {
        printf("Error creando %s", strRanking);
    }
    fclose(pFile);
}
