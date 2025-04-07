#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 50
#define TOTAL_TURNOS 4
#define MAX_MATERIAS 3

// structs
typedef enum {
    MANHA,
    TARDE,
    NOITE,
    MADRUGADA
} Turno;

typedef enum{
    ACAO_IR_AULA,
    ACAO_ESTUDAR,
    ACAO_DESCANSAR,
    ACAO_TRABALAHR,
    ACAO_SOCIALIZAR,
} ACAO;


typedef struct {
    char nome[MAX_NOME];
    int xp;
    int xpNecessario;
    int faltas;
    int max_faltas;
    bool horarios[TOTAL_TURNOS];
    bool concluida;
} Materia;

typedef struct{
    char nome[MAX_NOME];
    char descricao[100];
    bool especial;
    bool concluido;
} Evento;

typedef struct {
    char nome[MAX_NOME];
    int energia;
    int estresse;
    int moral;
    int semestre;
    Materia materias[MAX_MATERIAS];
    int NUM_MATERIAS;
} Personagem;


//funções
bool materiaJaExiste(Personagem *jogador, const char *nomeMateria){
    for(int i = 0; i <jogador ->NUM_MATERIAS; i++){
        if(strcmp(jogador->materias[i].nome, nomeMateria) == 0){
            return true;
        }
    }
    return false;
}



Personagem criarPersonagem(){
    Personagem jogador;
    int escolha_materia = 0, escolha_turno = 0, m = 0;
    char escolha_continue = 's';


    printf("Digite o nome do seu personagem: \n");
    fgets(jogador.nome, MAX_NOME, stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0';

    jogador.energia = 100;
    jogador.estresse = 0;
    jogador.moral = 0;
    jogador.semestre = 1;
    jogador.NUM_MATERIAS = 0;

    while(escolha_continue == 's' || escolha_continue == 'S'){

    while (escolha_materia < 1 || escolha_materia > 3){
        printf("Quais materias gostaria de fazer esse semestre?\n");
        printf("[1] Calculo I\n");
        printf("[2] Linguagem C\n");
        printf("[3] Física I\n");

        scanf("%d", &escolha_materia);

        if (escolha_materia < 1 || escolha_materia > 3){
            printf("Digito invalido, tente novamente \n");
        }

    }
    //chego

    switch(escolha_materia){
    case 1:{
        if(materiaJaExiste(&jogador, "Cálculo I")){
            printf("Essa matéria já foi adicionada\n");
        }else{
            Materia calculo_I;

           strcpy(calculo_I.nome, "Cálculo I");
           calculo_I.xp = 0;
           calculo_I.xpNecessario = 80;
           calculo_I.faltas = 0;
           calculo_I.max_faltas = 10;
           calculo_I.concluida = false;

           while (escolha_turno < 1 || escolha_turno > 3){
               printf("Em qual horario gostaria de fazer Cálculo I?\n");
               printf("[1] Manhã\n");
               printf("[2] Tarde\n");
               printf("[3] Noite\n");
               scanf("%d", &escolha_turno);

                if (escolha_turno < 1 || escolha_turno > 3){
                printf("Digito invalido, tente novamente \n");
            }
           }

           calculo_I.horarios[escolha_turno] = true;

           jogador.materias[m] = calculo_I;
           m += 1;
           jogador.NUM_MATERIAS += 1;
        }
       break;}

    case 2:{
        if(materiaJaExiste(&jogador, "Linguagem C")){
            printf("Essa matéria já foi adicionada\n");
        }else{
        Materia linguagem_c;

       strcpy(linguagem_c.nome, "Linguagem C");
       linguagem_c.xp = 0;
       linguagem_c.xpNecessario = 60;
       linguagem_c.faltas = 0;
       linguagem_c.max_faltas = 7;
       linguagem_c.concluida = false;

       while (escolha_turno < 1 || escolha_turno > 3){
           printf("Em qual horario gostaria de fazer linguagem_c?\n");
           printf("[1] Manhã\n");
           printf("[2] Tarde\n");
           printf("[3] Noite\n");
           scanf("%d", &escolha_turno);

            if (escolha_turno < 1 || escolha_turno > 3){
            printf("Digito invalido, tente novamente \n");
        }
       }

       linguagem_c.horarios[escolha_turno] = true;

       jogador.materias[m] = linguagem_c;
       m += 1;
       jogador.NUM_MATERIAS += 1;
        }
       break;}

    case 3:{
        if(materiaJaExiste(&jogador, "Física I")){
            printf("Essa matéria já foi adicionada\n");
        }else{
        Materia fisica_I;

       strcpy(fisica_I.nome, "Física I");
       fisica_I.xp = 0;
       fisica_I.xpNecessario = 100;
       fisica_I.faltas = 0;
       fisica_I.max_faltas = 12;
       fisica_I.concluida = false;

       while (escolha_turno < 1 || escolha_turno > 3){
           printf("Em qual horario gostaria de fazer Física I?\n");
           printf("[1] Manhã\n");
           printf("[2] Tarde\n");
           printf("[3] Noite\n");
           scanf("%d", &escolha_turno);

            if (escolha_turno < 1 || escolha_turno > 3){
            printf("Digito invalido, tente novamente \n");
        }
       }

       fisica_I.horarios[escolha_turno] = true;

       jogador.materias[m] = fisica_I;
       m += 1;
       jogador.NUM_MATERIAS += 1;
        }
       break;}

    }


    printf("Quer adicionar mais uma materia(s/n)?\n");
    scanf(" %c", &escolha_continue);

    escolha_materia = 0;
    escolha_turno = 0;


    }


    return jogador;
}





int main() {
    Personagem p = criarPersonagem();

    printf("\n--- Dados do Personagem ---\n");
    printf("Nome: %s\n", p.nome);
    printf("Energia: %d\n", p.energia);
    printf("Estresse: %d\n", p.estresse);
    printf("Moral: %d\n", p.moral);
    printf("Semestre: %d\n", p.semestre);
    printf("Matérias inscritas (%d):\n", p.NUM_MATERIAS);

    for (int i = 0; i < p.NUM_MATERIAS; i++) {
        printf("  - %s\n", p.materias[i].nome);
        printf("    XP: %d/%d\n", p.materias[i].xp, p.materias[i].xpNecessario);
        printf("    Faltas: %d/%d\n", p.materias[i].faltas, p.materias[i].max_faltas);
        printf("    Concluída: %s\n", p.materias[i].concluida ? "Sim" : "Não");

        printf("    Horários: ");
        for (int j = 0; j < TOTAL_TURNOS; j++) {
            if (p.materias[i].horarios[j]) {
                switch(j) {
                    case 1: printf("Manhã I "); break;
                    case 2: printf("Tarde I "); break;
                    case 3: printf("Noite I "); break;
                    default: printf("Turno %d ", j);
                }
            }
        }
        printf("\n");
    }

    return 0;
}




