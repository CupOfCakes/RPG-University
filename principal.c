#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

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
    ACAO_SOCIALIZAR,
} ACAO;

typedef struct {
    char nome[MAX_NOME];
    int xp;
    int xpNecessario;
    int frequencia;
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
    int moral;
    int semestre;
    Materia materias[MAX_MATERIAS];
    int NUM_MATERIAS;
} Personagem;


//funções auxiliares
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
           calculo_I.frequencia = 0;
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
       linguagem_c.frequencia = 0;
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
       fisica_I.frequencia = 0;
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


//ações
void irParaAula(Personagem *p, int turno){
    printf("Você decidiu ir a aula\n");

    bool teveAula = false;

    for(int i = 0; i < p->NUM_MATERIAS; i++){
        if(p->materias[i].horarios[turno]){
            Materia *m = &p->materias[i];
            teveAula = true;
            printf("Voce foi para a aula de %s\n", m->nome);

            //--evento sem xp
            int distracao = rand() % 100;

            if(distracao < 12){
                printf("Mas você não prestou atenção na aula, mais foco na proxima vez \n");
                continue;
            }

            //ganho de xp
            int xpGanho = 0;
            if(p->energia >= 70){
                xpGanho = 7 + rand() % 4;
            } else if(p->energia >= 40){
                xpGanho = 4 + rand() % 3;
            } else {
                xpGanho = 3;
            }

            m->xp += xpGanho;
            m->frequencia += 1;

            printf("Você ganhou %d de XP em %s.\n", xpGanho, m->nome);
        }
    }
    if(!teveAula){
        printf("Não tinha aula nesse turno... você foi até a faculdade à toa...\n");
    }else{
        p->energia -= 10;
    }
}


void estudar(Personagem *p){
    printf("Voce decidiu estudar\n");

    // sem materias
    if(p->NUM_MATERIAS == 0){
        printf("Você não tem materias cadastradas\n");
        return;
    }

    // escolha da materia
    int materiaIndex = -1;
    char entrada[10];

    printf("\nEscolha uma matéria para estudar:\n");

    for (int i = 0; i < p->NUM_MATERIAS; i++) {
        printf("[%d] %s\n", i, p->materias[i].nome);
    }

    printf("[a] Aleatório\n");

    printf("Sua escolha: ");
    scanf(" %s", entrada);


    if(strcmp(entrada, "a") == 0 || strcmp(entrada, "A") == 0 || materiaIndex < 0 || materiaIndex >= p->NUM_MATERIAS){
        materiaIndex = rand() % p->NUM_MATERIAS;

        if(materiaIndex < 0 || materiaIndex >= p->NUM_MATERIAS){
            printf("Voce digitou errado, então como punição a materia sera escolhida aleatoriamente\n");
        }
    }


    Materia *m = &p ->materias[materiaIndex];

    printf("Você decidiu estudar %s.\n", m -> nome);


    //EVENTO: dormir durante o estudo
    int chanceDormir = rand()%100;
    if(chanceDormir < 15){
        printf("Você dormiu enquanto estudava... pelo menos descansou um pouco\n");
        p->energia += 7;
        return;
    }

    //pouca energia
    if(p->energia <= 15){
        printf("Você tentou estudar, mas esta exausto demais...\n");
        p->energia -= 5;
        return;
    }

    // calculo do xp
    int inspiracao = rand()%100;
    bool superProdutivo = inspiracao < 10;


    int xpBase;
    if (p->energia >= 70) {
        xpBase = 10 + rand() % 4;
    } else if (p->energia >= 40) {
        xpBase = 6 + rand() % 4;
    } else {
        xpBase = 4 + rand() % 2;
    }

    if (superProdutivo) {
        printf("Você teve um momento de clareza e entendeu tudo de uma vez! (evento de inspiração!)\n");
        xpBase *= 1.4;
    }

    m->xp += xpBase;
    p->energia -= 10 + rand() % 6;

    printf("Você ganhou %d de XP em %s.\n", xpBase, m->nome);
}


void descansar(Personagem *p){
    printf("Você decidiu descansar\n");

    //EVENTO: sem sono
    int chanceSemSono = rand() % 100;

    if(chanceSemSono < 10){
        printf("Você tentou dormir, mas não conseguiu... Estude mais e encontre a cura da insona\n");
        return;
    }


    int sono = rand() % 100;
    int energiaGanha = 0;

    if(p->energia >= 95){
        printf("Você ja tinha bastante energia!!! ta com medo de um burnout?\n");
        energiaGanha = 2;
    }else{
        if(sono < 10){
            printf("Você estava com pouco sono, tirou um cochilo comum\n");
            energiaGanha = 10;
        } else if (p->energia <= 30) {
            printf("Você estava exausto, esse foi um descanso merecido\n");
            energiaGanha = 20;

        }else{
            printf("Voce descansou, sem nada demais\n");
            energiaGanha = 10;
        }
    }

    p->energia += energiaGanha;
    if(p->energia > 100) p->energia = 100;

    printf("Energia atual: %d\n", p->energia);
}

void socializar(Personagem *p){
    printf("Você escolheu socializar\n");

    int chance = rand() % 100;

    if(p->energia > 30){
    if(chance <= 10){
        printf("Você perdeu a noção e virou o bêbado inconveniente da festa...\n");
        printf("Precisaram te levar pra casa...\n");

        p->energia -= 5;
        p->moral -=10;
    }
    else if(chance >= 11 && chance <= 40){
        printf("Você até saiu de casa, mas passou a maior parte do tempo no canto, mexendo no celular...\n");
        printf("Ao menos tentou. Isso já é uma vitória.\n");

        p->energia -= 5;
        p->moral += 5;
    }
    else if(chance >= 41 && chance <= 70){
        printf("Você riu, falou besteira e até esqueceu dos problemas por um tempo.\n");
        printf("Foi um momento leve e divertido.\n");

        p->energia -= 10;
        p->moral += 10;
    }
    else if(chance >= 71 && chance <= 90){
        printf("Você conquistou geral com seu carisma e deixou todo mundo à vontade.\n");
        printf("Você não foi só mais um na multidão. Impressionante.\n");

        p->energia -= 15;
        p->moral += 20;
    }
    else{
        printf("VOCÊ. FOI. A. LUZ. DAQUELA. FESTA!\n");
        printf("Todos vão lembrar desse dia como 'aquele momento em que tudo foi perfeito'.\n");

        p->energia -= 20;
        p->moral += 30;
    }
    }else{
        printf("Você estava cansado demais para sair, mas fez mesmo assim\n");
        printf("Não foi tão compensador como você pensava");
        p->energia-= 5;
        p->moral += 2;
    }
}

//função de status
void mostrarStatus(Personagem *p){
    printf("=== STATUS DO(A) %S ===\n", p->nome);
    printf("%dº Semestre\n", p->semestre);
    printf("Energia: %d\n", p->energia);
    printf("Moral: %d\n", p->moral);

    printf("\nDesempenho nas matérias:\n");
    for (int i = 0; i < p->NUM_MATERIAS; i++) {
        Materia *m = &p->materias[i];
        printf("%s -> XP: %d | Frequência: %d%%\n", m->nome, m->xp, (m->frequencia/22)*100);
    }
    printf("=======================\n");

}

// função principal do dia a dia
void jogarSemestre(Personagem *p){
    int turno = 0;
    int diaAtual = 1;
    int diaMax = 30;
    ACAO escolha = -1;
    char escolhaStatus;

    //durante o semestre
    for(diaAtual; diaAtual <= diaMax; diaAtual++){
        printf("\n=== Dia %d ===\n", diaAtual);

        for (turno = 0; turno < TOTAL_TURNOS; turno++){

            escolha = -1;

            while (escolha < 0 || escolha > 4){
            printf("\nTurno %d\n", turno);
            printf("Escolha uma ação:\n");
            printf("[0] Ir à aula\n");
            printf("[1] Estudar\n");
            printf("[2] Dormir\n");
            printf("[3] Ir ao bar/festa\n");
            printf("[4] Ver Status\n");
            scanf("%d", (int*)&escolha);

            if (escolha < 0 || escolha > 4) {
                    printf("Ação inválida! Tente novamente");
                }
            }

            if(turno == 3 && escolha != ACAO_DESCANSAR){
                 p->energia -= 5;
                 printf("Você escolheu não descansar na madrugada... Pessima escolha");
            }

            if (escolha == 4) {
                mostrarStatus(p);
                escolha = -1;
                continue;
                printf("Escolha uma ação novamente sem ser os status: ");
                scanf("%d", (int*)&escolha);
            }


            switch (escolha) {
                case ACAO_IR_AULA:
                    if (diaAtual % 6 == 0 || diaAtual % 7 == 0){
                        if(diaAtual % 6 == 0){
                            printf("Hoje é sabado, não tem aula");
                            break;
                        }else{
                        printf("Hoje é domingo, não tem aula");
                        break;
                        }
                    }
                    irParaAula(p, turno);
                    break;

                case ACAO_ESTUDAR:
                    estudar(p);
                    break;

                case ACAO_DESCANSAR:
                    descansar(p);
                    break;

                case ACAO_SOCIALIZAR:
                    socializar(p);
                    break;
            }
        }
    }
    //final do semestre
    int aprovadas = 0;

    printf("\n--- Fim do Semestre---\n");

    for(int i = 0; i < p->NUM_MATERIAS; i++){
        Materia *m = &p -> materias[i];
        printf("\nMatérias: %s\n", m->nome);
        printf("XP: %d | Frequência: %d%%\n", m->xp, m->frequencia/22*100);

        bool passouXP = m->xp >= 60;
        bool passouFrequencia = (m->frequencia*100/22) >= 75;

        if (passouXP && passouFrequencia){
            printf("Resultado: Aprovado\n");
            aprovadas++;
        }
        else{
            printf("Resultado: Reprovado\n");
            if(!passouXP) printf("- Estudou pouco\n");
            if(!passouFrequencia) printf("- faltou demais nas aulas\n");
        }

    }

    printf("\nResumo: Você foi aprovado em %d de %d matérias.\n", aprovadas, p->NUM_MATERIAS);

    if(aprovadas == p->NUM_MATERIAS){
        printf("Parabéns! Você foi aprovado em tudo! 😎\n");
    } else if(aprovadas == 0){
        printf("Você... reprovou em tudo... você tem talento pra ser um fracassado!!!\n");
    } else {
        printf("Foi mais ou menos... mas já vi piores.\n");
    }
}


int main() {
    setlocale(LC_ALL,"");

    Personagem p = criarPersonagem();

    jogarSemestre(&p);

    return 0;
}


