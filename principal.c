#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 50
#define TOTAL_TURNOS 4
#define NUM_MATERIAS 2

typedef enum {
    MANHA,
    TARDE,
    NOITE,
    MADRUGADA
} Turno;

typedef struct {
    char nome[MAX_NOME];
    int xp;
    int xpNecessario;
    bool horarios[TOTAL_TURNOS];
} Materia;

typedef struct {
    char nome[MAX_NOME];
    Materia materias[NUM_MATERIAS];
} Personagem;

void jogarSemestre(Personagem *p) {
    const char* nomesTurno[] = {"Manhã", "Tarde", "Noite", "Madrugada"};

    for (int dia = 1; dia <= 5; dia++) { // Coloquei 5 dias só pra testar
        printf("\n--- Dia %d ---\n", dia);

        for (int turno = 0; turno < TOTAL_TURNOS; turno++) {
            printf("\nTurno: %s\n", nomesTurno[turno]);
            printf("O que você quer fazer?\n");

            bool temAula = false;
            for (int i = 0; i < NUM_MATERIAS; i++) {
                if (p->materias[i].horarios[turno]) {
                    printf("-> Aula de %s!\n", p->materias[i].nome);
                    temAula = true;
                }
            }

            printf("1. Ir à aula\n");
            printf("2. Estudar por conta\n");
            printf("3. Descansar\n");
            printf("4. Fazer algo aleatório\n");

            int escolha;
            scanf("%d", &escolha);
            getchar(); // limpa o \n do buffer

            switch (escolha) {
                case 1:
                    if (temAula) {
                        printf("Você foi pra aula como um bom aluno... +XP!\n");
                    } else {
                        printf("Tsc... não tinha aula agora, otário.\n");
                    }
                    break;
                case 2:
                    printf("Você estudou por conta. Isso sim é dedicação! +XP\n");
                    break;
                case 3:
                    printf("Descansar é importante, mas não dorme no ponto, hein?\n");
                    break;
                case 4:
                    printf("Você fez algo... suspeito. Espero que não se arrependa depois 😏\n");
                    break;
                default:
                    printf("Aprende a digitar, baka! Opção inválida.\n");
            }
        }
    }

    printf("\n--- Fim do semestre (teste) ---\n");
}

int main() {
    Personagem p;
    strcpy(p.nome, "Estudante Protagonista");

    strcpy(p.materias[0].nome, "Cálculo I");
    p.materias[0].xp = 0;
    p.materias[0].xpNecessario = 100;
    p.materias[0].horarios[MANHA] = true;

    strcpy(p.materias[1].nome, "Física I");
    p.materias[1].xp = 0;
    p.materias[1].xpNecessario = 100;
    p.materias[1].horarios[TARDE] = true;
    p.materias[1].horarios[MADRUGADA] = true; // Ousado!

    jogarSemestre(&p);

    return 0;
}


