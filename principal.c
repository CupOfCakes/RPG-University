#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

#define MAX_NOME 50
#define TOTAL_TURNOS 4
#define MAX_MATERIAS 3
#define NUM_ROMANCES 3

// structs
typedef enum {
    MANHA,
    TARDE,
    NOITE,
    MADRUGADA
} Turno;

const char* nomesTurnos[]= {
    "manha",
    "tarde",
    "noite",
    "madrugada"
};

typedef enum{
    ACAO_IR_AULA,
    ACAO_ESTUDAR,
    ACAO_DESCANSAR,
    ACAO_SOCIALIZAR,
} ACAO;

typedef struct{
    char nome[MAX_NOME];
    int xp;
    int xpNecessario;
    int frequencia;
    bool horarios[TOTAL_TURNOS];
    bool concluida;
} Materia;

typedef enum{
    BEBADO,
    MACHUCADO,
    DOENTE,
    BANIDO_DO_BAR,
    NUM_STATUS
} Status;

const char *nomeStatus[NUM_STATUS] = {
    "Bêbado",
    "Machucado",
    "Doente",
    "Banido do bar"
};

typedef struct{
    char nome[MAX_NOME];
    char descricao[100];
    int afinidade;
    bool namorando;
    bool desbloqueado;
}NPC;

NPC romances[NUM_ROMANCES] = {
    {"Alex", "Um estudante misterioso que adora poesia.", 0, false, false},
    {"Júlia", "Uma atleta que frequenta o bar aos fins de semana.", 0, false, false},
    {"Rafa", "Gamer e tímido(a), só socializa depois de umas cervejas.", 0, false, false}
};

typedef struct {
    char nome[MAX_NOME];
    int energia;
    int moral;
    int semestre;
    Materia materias[MAX_MATERIAS];
    int NUM_MATERIAS;
    bool situacao[NUM_STATUS];
    int dias_banido;
    int dias_doente;
} Personagem;


//funções auxiliares
void mostrarStatus(Personagem *p);

bool materiaJaExiste(Personagem *jogador, const char *nomeMateria){
    for(int i = 0; i <jogador ->NUM_MATERIAS; i++){
        if(strcmp(jogador->materias[i].nome, nomeMateria) == 0){
            return true;
        }
    }
    return false;
}

void criarMateria(Personagem *p, const char *nomeMateria, int xpNecessario){
    if(materiaJaExiste(p, nomeMateria)){
            printf("Essa matéria já foi adicionada\n");
            return;
            }

    Materia nova;

   strcpy(nova.nome, nomeMateria);
   nova.xp = 0;
   nova.xpNecessario = xpNecessario;
   nova.frequencia = 0;
   nova.concluida = false;

   for(int i = 0; i < TOTAL_TURNOS; i++){
    nova.horarios[i] = false;
   }

   int escolha_turno = -1;

   while (escolha_turno < 1 || escolha_turno > 3){
       printf("Em qual horario gostaria de fazer %s?\n", nomeMateria);
       printf("[1] Manhã\n");
       printf("[2] Tarde\n");
       printf("[3] Noite\n");
       scanf("%d", &escolha_turno);

       escolha_turno -= 1;

        if (escolha_turno < 0 || escolha_turno > 2){
        printf("Digito invalido, tente novamente \n");
    }
   }

   nova.horarios[escolha_turno] = true;

   p->materias[p->NUM_MATERIAS] = nova;
   p->NUM_MATERIAS ++;

}

void pressionarTeclaeLimpar(){
    int c;

    printf("Pressione Enter para continuar...");
    getchar();
    while ((c = getchar()) != '\n' && c != EOF); // limpa o buffer

    system("cls");
}

int escolherAcao(int turno, Personagem *p){
    int escolha = -1;

    while (escolha < 0 || escolha > 4 ){
    printf("\nTurno %s\n", nomesTurnos[turno]);
    printf("Escolha uma ação:\n");
    printf("[0] Ir à aula\n");
    printf("[1] Estudar\n");
    printf("[2] Dormir\n");
    printf("[3] Ir ao bar/festa\n");
    printf("[4] Ver Status\n");
    scanf("%d", (int*)&escolha);

    if (escolha < 0 || escolha > 4){
            printf("Ação inválida! Tente novamente\n");
        }
    }

    if (escolha == 4) {
        mostrarStatus(p);
        escolha = -1;
        while (escolha < 0 || escolha > 4){
            printf("Escolha uma ação novamente sem ser os status: ");
            scanf("%d", (int*)&escolha);
        }

    if(turno == 3 && escolha != ACAO_DESCANSAR){
         p->energia -= 15;
         printf("Você escolheu não descansar na madrugada... Pessima escolha\n");
    }
    }
    return escolha;
}

//funções de criar personagem
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
    jogador.dias_banido = 0;

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

    switch(escolha_materia){
    case 1:
        criarMateria(&jogador, "Calculo I", 80);
        break;

    case 2:
        criarMateria(&jogador, "Linguagem C", 60);
        break;

    case 3:
        criarMateria(&jogador, "Física I", 80);
        break;
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
    printf("\x1b[36mVocê decidiu ir a aula\x1b[0m\n");

    bool teveAula = false;
    int chanceSemPresenca = rand()%100;

    for(int i = 0; i < p->NUM_MATERIAS; i++){
        Materia *m = &p->materias[i];

        if(m->horarios[turno]){
            if(p->situacao[BEBADO]){
                int chanceProfBom = rand() % 3;

                if(chanceProfBom == 0){
                    printf("Você foi à aula bêbado, mas teve sorte: o professor estava de bom humor e não te expulsou.\n");
                    printf("Mas você não entendeu nada da aula.\n");
                    p->energia -= 12;
                    m->frequencia += 1;
                }else if(chanceProfBom == 1){
                    printf("Você foi à aula bêbado e o professor te expulsou da sala na frente de todo mundo.\n");
                    p->energia -= 12;
                    p->moral -= 5;
                }else{
                    printf("Você tentou ir pra aula... mas acabou desmaiando na cama antes de sair de casa.\n");
                }
                return;
            }

            if(p->situacao[DOENTE]){
                printf("Você estava doente e mal conseguiu prestar atenção...\n");
                m->xp += 3; // valor reduzido
                p->energia -= 12;
                return;
            }


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

            //EVENTO:aula sem presença
            if(chanceSemPresenca < 5){
                printf("Voce foi a aula, mas esqueceu de assinar a presença");
            }else{
                m->frequencia += 1;
            }

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
    printf("\x1b[36mVoce decidiu estudar\x1b[0m\n");

    // sem materias
    if(p->NUM_MATERIAS == 0){
        printf("Você não tem materias cadastradas\n");
        return;
    }



    // escolha da materia
    int materiaIndex = -1;
    char entrada[10];
    bool entradaValida = true;

    printf("\nEscolha uma matéria para estudar:\n");

    for (int i = 0; i < p->NUM_MATERIAS; i++) {
        printf("[%d] %s\n", i, p->materias[i].nome);
    }

    printf("[a] Aleatório\n");

    printf("Sua escolha: ");
    scanf("%s", entrada);


    if (strcmp(entrada, "a") == 0 || strcmp(entrada, "A") == 0) {
    materiaIndex = rand() % p->NUM_MATERIAS;
    printf("Matéria aleatória escolhida!\n");
    } else {
    // Tenta verificar se é um número real
    entradaValida = true;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            entradaValida = false;
            break;
        }
    }

    if (entradaValida) {
        materiaIndex = atoi(entrada);
        if (materiaIndex < 0 || materiaIndex >= p->NUM_MATERIAS) {
            entradaValida = false;  // fora do intervalo
        }
    } else {
        materiaIndex = -1; // resetar só por segurança
    }

    if (!entradaValida) {
        printf("Você digitou errado, então como punição a matéria será escolhida aleatoriamente... Tsc, preste mais atenção da próxima vez!\n");
        materiaIndex = rand() % p->NUM_MATERIAS;
    }
    }



    Materia *m = &p ->materias[materiaIndex];

    printf("Você decidiu estudar %s.\n", m -> nome);

    if(p->situacao[BEBADO] || p->situacao[MACHUCADO] || p->situacao[DOENTE]){
        printf("Você não esta em condições de estudar, mas tentou");
        p->energia -=5;
        m->xp += 2 + rand()%8;
        return;
    }


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
    printf("\x1b[36mVocê decidiu dormir\x1b[0m\n");

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
    printf("\x1b[36mVocê escolheu ir ao bar\x1b[0m\n");

    if(p->situacao[BANIDO_DO_BAR]){
        printf("Você ainda está banido do bar por %d dia(s).\n", p->dias_banido);
        return;
    }

    int escolha = -1, acoes = 0, bebidas = 0;
    bool sair = false;

    while (!sair){

        if(acoes < 5){
            pressionarTeclaeLimpar();
        }

        printf("\nVocê está no bar! O que deseja fazer?\n");
        printf("[0] Conversar com colegas\n");
        printf("[1] Jogar sinuca\n");
        printf("[2] Beber cerveja\n");
        printf("[3] Ir embora\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        int chance = rand() % 100, chanceRaro = rand() % 100;

        if(chanceRaro < 9){
            int evento = rand() % 3;
            int finalEvento= rand()% 2;

            printf("\n\x1b[35mEVENTOS ESPECIAIS\x1b[0m\n");

            switch(evento){
            case 0:
                printf("\nVocê esbarrou em alguém que não gostou nada disso... Uma briga começou!\n");
                p->energia -= 20;
                if(finalEvento == 1){
                    printf("Magicamente você conseguiu vencer");
                    p->moral += 25;
                }else{
                    printf("Foi lindo");
                    printf("Você tomou uma surra fenomenal");
                    p->moral -= 40;
                    p->situacao[MACHUCADO] = true;
                    sair = true;
                }
                break;
            case 1:
                printf("\nVocê trocou olhares com uma pessoa, tomou uma dose de coragem e foi ate ela(e)\n");
                p->energia -= 5;
                if(finalEvento == 1){
                    printf("Você foi até a pessoa com confiança e...\n");
                    printf("bingo! Conversa vai, conversa vem, vocês acabaram trocando contatos. Nada mal!\n");

                    //desbloquear personagem
                    int bloqueados[NUM_ROMANCES];
                    int num_bloqueados = 0;

                    // Preenche a lista com os que ainda estão bloqueados
                    for (int i = 0; i < NUM_ROMANCES; i++) {
                        if (!romances[i].desbloqueado) {
                            bloqueados[num_bloqueados++] = i;
                        }
                    }

                    // se não houver mais personagens bloqueados, nada acontece
                    if (num_bloqueados == 0) {
                        printf("Você tomou um fora, pelo menos tentou...\n");
                    } else {
                        // Escolhe aleatoriamente um entre os bloqueados
                        int escolhido = bloqueados[rand() % num_bloqueados];

                        romances[escolhido].desbloqueado = true;
                        printf("Você conheceu %s! %s\n", romances[escolhido].nome, romances[escolhido].descricao);
                    }

                    p->moral += 15;
                }else{
                    printf("Você flertou com a pessoa errada... \n");
                    printf("era o par do segurança. Antes que percebesse, estava sendo educadamente escoltado pra fora.\n");
                    printf("Pelas suas ações você foi expulso do bar por 3 dias\n");
                    p->moral -= 15;
                    sair = true;
                    p->situacao[BANIDO_DO_BAR] = true;
                    p->dias_banido = 3;
                }
                break;
            case 2:
                printf("\nUma competição de karaokê começa do nada! Alguém te desafia no meio do bar.\n");
                p->energia -= 10;
                if(finalEvento == 1){
                    printf("ocê soltou a voz como um astro do pop! Todos aplaudiram.\n");
                    printf(" Você ganhou uma rodada grátis de bebida!\n");
                    p->moral += 15;
                    bebidas++;
                }else{
                    printf("Você desafinou tanto que o barman pediu para que você descesse\n");
                    p->moral -= 25;
                }
                break;
            case 3:{
                int prof = rand()% p->NUM_MATERIAS;
                printf("\nEntre a multidão barulhenta, você vê uma figura familiar... é seu professor de %s!\n", p->materias[prof].nome);
                p->energia -= 5;
                if(finalEvento == 1){
                    printf("Vocês acabam conversando e ele é mais legal do que você esperava.\n");
                    printf("Você ganhou um poquinho de xp na materia dele!\n");
                    p->materias[prof].xp += 15;
                }else{
                    printf("Ele finge que não te viu... Mas você sabe que ele te viu\n");
                    p->materias[prof].xp -= 10;
                }
                break;
            }
            }
            acoes++;
            pressionarTeclaeLimpar();
            continue;
        }



        switch(escolha){
            case 0:
                 if(chance >= 80){
                    printf("Você encontrou seus melhores amigos! A conversa fluiu e te reanimou.\n");
                    p->energia += 10;
                 } else if(chance >= 50){
                    printf("Você encontrou conhecidos e bateu um papo... nada demais.\n");
                    p->energia += 2;
                 } else {
                    printf("Você tentou conversar, mas acabou se sentindo deslocado.\n");
                    p->energia -= 5;
                 }
                 acoes++;
                 break;
            case 1:
                if(chance >= 85){
                    printf("Você venceu a partida! Sua moral subiu e você se sente confiante.\n");
                    p->moral += 1;
                    p->energia += 5;
                } else if(chance >= 40){
                    printf("Foi uma boa partida de sinuca, mesmo sem ganhar. Você relaxou um pouco.\n");
                    p->energia += 2;
                } else {
                    printf("Você perdeu feio e ainda rasgou o feltro da mesa... que vergonha!\n");
                    p->moral -= 1;
                    p->energia -= 5;
                }
                acoes++;
                break;
            case 2:
                bebidas++;
                if(bebidas == 1){
                    printf("Uma bebidinha não mata ninguem\n");
                    p->energia -= 2;
                } else if(bebidas == 2){
                    printf("Uma bebidinha não mata ninguem... mas foi mais de uma\n");
                    p->energia -= 4;
                } else if (bebidas == 3){
                    printf("Serio que você quis beber tanto?\n");
                    printf("PARABENS!!! VOCE BEBEU DEMAIS\n");
                    p->energia -= 10;
                    p->moral -= 15;
                    p->situacao[BEBADO] = true;
                } else{
                    printf("Eu não tenho mais o que te falar");
                }
                acoes++;
                break;
            case 3:
                printf("Você decide ir embora do bar.\n");
                sair = true;
                break;
            default:
                printf("Opção inválida, tente novamente\n");
                break;
        }


        if(acoes >= 5 && !sair && !p->situacao[BEBADO]){
            printf("\nVocê ficou tempo demais no bar e foi cordialmente convidado a sair\n");
            sair = true;
        }

        if(p->situacao[BEBADO] && acoes >= 5){
            sair = true;
            int evento = rand() % 4;

            switch(evento) {
                case 0:
                    printf("Você desmaiou no bar. Acordou com o dono do bar te abanando com um cardápio.\n");
                    p->energia = 0;
                    p->moral -= 5;
                    break;
                case 1:
                    printf("Você acordou em um banco de praça com uma pizza meio comida do seu lado. Onde você arranjou isso?!\n");
                    p->energia = 5;
                    p->moral -= 10;
                    break;
                case 2:
                    printf("Você acordou em casa... como você chegou aqui?.\n");
                    p->moral -= 3;
                    break;
                case 3:
                    printf("Você acordou em um quarto estranho numa cama com outra pessoa, por sorte conseguiu sair antes dela acordar. Quem é essa pessoa?!\n");
                    p->moral -= 2;
                    break;
            }
        }

        }

}


//função de status
void mostrarStatus(Personagem *p){
    bool temStatus = false;

    printf("\n\x1b[36m=== STATUS DO(A) %s === \x1b[0m\n", p->nome);

    //status do personagem
    printf("%dº Semestre\n", p->semestre);
    printf("Energia: %d\n", p->energia);
    printf("Moral: %d\n", p->moral);

    //situação ativas
    printf("\nSituação atual:\n");
    for(int i = 0; i< NUM_STATUS; i++){
        if (p->situacao[i]) {
            if (i == BANIDO_DO_BAR) {
                printf("- %s (dias restantes: %d)\n", nomeStatus[i], p->dias_banido);
            } else {
                printf("- %s\n", nomeStatus[i]);
            }
            temStatus = true;
        }
    }

    if (!temStatus) {
        printf("Nenhum status ativo no momento. Tá se achando agora, né?\n");
    }

    //status da materia
    printf("\nDesempenho nas matérias:\n");
    for (int i = 0; i < p->NUM_MATERIAS; i++) {
        Materia *m = &p->materias[i];
        printf("%s -> XP: %d | Frequência: %d%%\n", m->nome, m->xp, m->frequencia*100/22);
    }
    printf("\x1b[36m=======================\n\x1b[0m");

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

        //ban bar
        if(p->situacao[BANIDO_DO_BAR]){
            p->dias_banido--;
            if(p->dias_banido <= 0){
                p->situacao[BANIDO_DO_BAR] = false;
            }
        }

        //doença
        int chanceDoente = rand() % 100;

        if(!p->situacao[DOENTE] && chanceDoente <= 7){
            printf("Você acordou se sentindo mal, parece que você pegou um resfriado");
            p->situacao[DOENTE] = true;
            p->dias_doente = 2;
        }else{
            p->dias_doente--;
            if(p->dias_doente <= 0){
                printf("Você acordou se sentindo melhor, parece que seu resfriado se foi");
                p->situacao[DOENTE] = false;
            }
        }

        //turnos do dia
        for (turno = 0; turno < TOTAL_TURNOS; turno++){
            printf("\n=== Dia %d ===\n", diaAtual);

            //perde um turno se estiver bebado no dia anterior
            if(turno == 0 && p->situacao[BEBADO]){
                printf("Você acordou com uma forte ressaca e não conseguiu fazer nada pela manhã");
                p->situacao[BEBADO] = false;
                pressionarTeclaeLimpar;
                continue;
            }

            //recupera machucados
            if(turno == 0 && p->situacao[MACHUCADO]){
                printf("Você se sente melhor dos machucados");
                p->situacao[MACHUCADO] = false;
                pressionarTeclaeLimpar;
            }

            escolha = escolherAcao(turno, p);

            if (p->situacao[DOENTE] && rand() % 100 < 20) {
                printf("Você tentou sair, mas passou mal no caminho e voltou pra casa...\n");
                pressionarTeclaeLimpar();
                continue;
            }


            switch (escolha) {
                case ACAO_IR_AULA:
                    if ((diaAtual + 1) % 7 == 0 || diaAtual % 7 == 0){
                        if((diaAtual + 1) % 7 == 0){
                            printf("Hoje é sabado, não tem aula\n");
                            break;
                        }else{
                        printf("Hoje é domingo, não tem aula\n");
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
                case 7:
                    continue;
                    break;
            }
        //penalidade machucado
        if(p->situacao[MACHUCADO] && escolha != ACAO_DESCANSAR){
            printf("Voce estava machucado então se esforçou mais na ação");
            p->energia -=5;
        }

        pressionarTeclaeLimpar();
        }
        // final do dia

    }
    //final do semestre
    int aprovadas = 0;

    printf("\\x1b[31mn--- Fim do Semestre---\\x1b[0mn");

    for(int i = 0; i < p->NUM_MATERIAS; i++){
        Materia *m = &p -> materias[i];
        printf("\nMatérias: %s\n", m->nome);
        printf("XP: %d | Frequência: %d%%\n", m->xp, m->frequencia*100/22);

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
    setlocale(LC_ALL, "Portuguese");

    //Titulo
    printf("=== RPG DE ESTUDANTE ===\n");

    Personagem p = criarPersonagem();

    system("cls");

    jogarSemestre(&p);

    pressionarTeclaeLimpar();

    return 0;
}


