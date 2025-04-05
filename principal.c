#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_MATERIAS 10
#define MAX_EVENTOS 5
#define MAX_NOME 50

// Enums pros ambientes
typedef enum {
    CASA,
    FACULDADE,
    ESTAGIO,
    BIBLIOTECA,
    BARZINHO
} Ambiente;

// Enum de ações
typedef enum {
    ACAO_ESTUDAR,
    ACAO_IR_AULA,
    ACAO_TRABALHAR,
    ACAO_DESCANSAR,
    ACAO_SOCIALIZAR,
    ACAO_EVENTO
} Acao;

// Struct de uma matéria
typedef struct {
    char nome[MAX_NOME];
    int xp;
    int xp_necessario;
    int faltas;
    int max_faltas;
    bool concluida;
} Materia;

// Struct do personagem
typedef struct {
    char nome[MAX_NOME];
    int energia;
    int estresse;
    int moral;
    int semestre;
    Materia materias[MAX_MATERIAS];
    int num_materias;
} Personagem;

// Struct de evento
typedef struct {
    char nome[MAX_NOME];
    char descricao[100];
    bool especial;
    bool concluido;
} Evento;

Personagem criarPersonagem(){
    Personagem p;

    printf("Digite o nome do seu estudante sofredor: ");
    fgets(p.nome, MAX_NOME, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    p.energia = 100;
    p.estresse = 0;
    p.moral = 100;
    p.semestre = 1;
    p.num_materias = 3;

    // Matéria 1 - Cálculo
    strcpy(p.materias[0].nome, "Cálculo I");
    p.materias[0].xp = 0;
    p.materias[0].xp_necessario = 100;
    p.materias[0].faltas = 0;
    p.materias[0].max_faltas = 3;
    p.materias[0].concluida = false;

    // Matéria 2 - Programação
    strcpy(p.materias[1].nome, "Programação I");
    p.materias[1].xp = 0;
    p.materias[1].xp_necessario = 80;
    p.materias[1].faltas = 0;
    p.materias[1].max_faltas = 3;
    p.materias[1].concluida = false;

    // Matéria 3 - Física
    strcpy(p.materias[2].nome, "Física I");
    p.materias[2].xp = 0;
    p.materias[2].xp_necessario = 90;
    p.materias[2].faltas = 0;
    p.materias[2].max_faltas = 3;
    p.materias[2].concluida = false;

    return p;
}


int main(){
    Personagem jogador = criarPersonagem();

    printf("\nBem-vindo, %s!\n", jogador.nome);
    printf("Você está começando seu primeiro semestre...\n");

    return 0;
}


