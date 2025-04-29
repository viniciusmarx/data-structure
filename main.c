#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TURMAS 10

struct aluno{
  int codigo;
  char nome[50];
  struct aluno* prox;
  struct aluno* ant;
}; typedef struct aluno ALUNO;

struct grupo{
  int codigo_grupo;
  int codigo_turma;
  ALUNO* inicio_alunos;
  struct grupo* prox;
  struct grupo* ant;
}; typedef struct grupo GRUPO;

struct turma{
  int codigo;
  struct aluno* inicio_alunos;
  struct grupo* inicio_grupos;
}; typedef struct turma TURMA;

TURMA* turmas = NULL;
int total_turmas = 0;

void criar_turma(int codigo){
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo){
      printf("Erro: Ja existe uma turma com o codigo %d\n", codigo);
      return;
    }
  }

  TURMA* nova_turma = (TURMA*)realloc(turmas, (total_turmas + 1) * sizeof(TURMA));
  if(nova_turma == NULL){
    printf("Erro: Nao foi possivel alocar memoria para nova turma\n");
    return;
  }
  turmas = nova_turma;
  turmas[total_turmas].codigo = codigo;
  turmas[total_turmas].inicio_alunos = NULL;
  turmas[total_turmas].inicio_grupos = NULL;
  total_turmas++;
  return;
}

void remover_alunos(ALUNO* inicio){
  ALUNO* aux;

  while(inicio != NULL){
    aux = inicio;
    inicio = inicio->prox;
    free(aux);
  }
}

void remover_grupos(GRUPO* inicio){
  GRUPO* aux;

  while(inicio != NULL){
    aux = inicio;
    inicio = inicio->prox;
    free(aux);
  }
}

void remover_turma(int codigo){
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo){
      remover_alunos(turmas[i].inicio_alunos);
      remover_grupos(turmas[i].inicio_grupos);

      for(int j=i; j<total_turmas-1; j++){
        turmas[j] = turmas[j+1];
      }
      total_turmas--;
      TURMA* temp = (TURMA*)realloc(turmas, total_turmas * sizeof(TURMA));
      if(temp == NULL && total_turmas > 0){
        printf("Erro: Nao foi possivel realocar memoria\n");
        return;
      }
      turmas = temp;

      printf("Turma de codigo %d removida\n", codigo);
      return;
    }
  }

  printf("Erro: Nao foi possivel encontrar uma turma com o codigo %d\n", codigo);
  return;
}

void consultar_turmas(){
  int turma_encontrada = 0;

  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo != 0){
      turma_encontrada = 1;
      printf("Turma Codigo: %d\n", turmas[i].codigo);
    }
  }

  if(!turma_encontrada){
    printf("Nenhuma turma cadastrada\n");
  }
}

void incluir_aluno(int codigo_turma, int codigo_aluno, char* nome){

  for(int i=0; i<total_turmas; i++){

    if(turmas[i].codigo == codigo_turma){

      ALUNO* novo_aluno = (ALUNO*)malloc(sizeof(ALUNO));

      if(!novo_aluno){
        printf("Erro ao alocar memoria para o aluno\n");
        return;
      }

      novo_aluno->codigo = codigo_aluno;
      strcpy(novo_aluno->nome, nome);
      novo_aluno->prox = NULL;
      novo_aluno->ant = NULL;

      if(turmas[i].inicio_alunos == NULL){
        turmas[i].inicio_alunos = novo_aluno;
      } else{
          ALUNO* alunos = turmas[i].inicio_alunos;

          while(alunos->prox != NULL){
            alunos = alunos->prox;
          }
          alunos->prox = novo_aluno;
          novo_aluno->ant = alunos;
      }

      printf("Aluno %s (codigo: %d) adicionado a turma %d\n", nome, codigo_aluno, codigo_turma);
      return;
    }
  }

  printf("Erro: Turma com codigo %d nao encontrada\n", codigo_turma);
  return;
}

void remover_aluno_turma(TURMA* turma, int codigo_aluno){
  ALUNO* alunos = turma->inicio_alunos;

  while(alunos != NULL){
    if(alunos->codigo == codigo_aluno){

      if(alunos->ant != NULL){
        alunos->ant->prox = alunos->prox;
      } else{
        turma->inicio_alunos = alunos->prox;
      }

      if(alunos->prox != NULL){
        alunos->prox->ant = alunos->ant;
      } 

      free(alunos);
      return;
    }
    alunos = alunos->prox;
  }
}

void remover_aluno_grupo(TURMA* turma, int codigo_aluno){
  GRUPO* grupos = turma->inicio_grupos;

  while(grupos != NULL){
    ALUNO* aluno_grupo = grupos->inicio_alunos;

    while(aluno_grupo != NULL){
      if(aluno_grupo->codigo == codigo_aluno){

        if(aluno_grupo->ant != NULL){
          aluno_grupo->ant->prox = aluno_grupo->prox;
        } else{
          grupos->inicio_alunos = aluno_grupo->prox;
        }

        if(aluno_grupo->prox != NULL){
          aluno_grupo->prox->ant = aluno_grupo->ant;
        } 

        free(aluno_grupo);
        break;;
      }
      aluno_grupo = aluno_grupo->prox;
    }
    grupos = grupos->prox;
  }
}

void remover_aluno(int codigo_turma, int codigo_aluno){

  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      remover_aluno_grupo(&turmas[i], codigo_aluno);

      remover_aluno_turma(&turmas[i], codigo_aluno);

      printf("Aluno de codigo %d removido da turma %d", codigo_aluno, codigo_turma);
      return;
    }
  }

  printf("Erro: Turma com codigo %d nao encontrada\n", codigo_turma);
}

void consultar_alunos(int codigo_turma){

  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      ALUNO* aluno_atual = turmas[i].inicio_alunos;

      if(aluno_atual == NULL){
        printf("Nenhum aluno cadastrado na turma %d\n", codigo_turma);
        return;
      }

      while(aluno_atual != NULL){
        printf("Codigo: %d, Nome: %s\n", aluno_atual->codigo, aluno_atual->nome);
        aluno_atual = aluno_atual->prox;
      }
      return;
    }
  }
  printf("Erro: Turma com codigo %d nao encontrada\n", codigo_turma);
}

void criar_grupo(int codigo_turma, int codigo_grupo){

  TURMA* turma = NULL;
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  for(GRUPO* g = turma->inicio_grupos; g!=NULL; g = g->prox){
    if(g->codigo_grupo == codigo_grupo){
      printf("Grupo com codigo %d ja existe na turma %d\n", codigo_grupo, codigo_turma);
      return;
    }
  }

  GRUPO* novo_grupo = (GRUPO*)malloc(sizeof(GRUPO));
  if(!novo_grupo){
    printf("Erro ao alocar memoria para o grupo\n");
    return;
  }

  novo_grupo->codigo_grupo = codigo_grupo;
  novo_grupo->codigo_turma = codigo_turma;
  novo_grupo->inicio_alunos = NULL;
  novo_grupo->prox = NULL;
  novo_grupo->ant = NULL;

  if(turma->inicio_grupos == NULL){
    turma->inicio_grupos = novo_grupo;
  } else{
    GRUPO* ultimo = turma->inicio_grupos;
    while(ultimo->prox != NULL){
      ultimo = ultimo->prox;
    }
    ultimo->prox = novo_grupo;
    novo_grupo->ant = ultimo;
  }

  printf("Grupo com codigo %d criado na turma %d\n", codigo_grupo, codigo_turma);
  return;
}

void remover_alunos_grupo(GRUPO* grupo){

  ALUNO* aluno_atual = grupo->inicio_alunos;
  while(aluno_atual != NULL){
    ALUNO* aluno_remover = aluno_atual;
    aluno_atual = aluno_atual->prox;

    free(aluno_remover);
  }

  grupo->inicio_alunos = NULL;
}

void remover_grupo(int codigo_turma, int codigo_grupo){

  TURMA* turma = NULL;
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  GRUPO* grupo = turma->inicio_grupos;
  while(grupo != NULL){
    if(grupo->codigo_grupo == codigo_grupo){
      remover_alunos_grupo(grupo);

      if(grupo->ant != NULL){
        grupo->ant->prox = grupo->prox;
      } else{
        turma->inicio_grupos = grupo->prox;
      }

      if(grupo->prox != NULL){
        grupo->prox->ant = grupo->ant;
      } 

      free(grupo);
      printf("Grupo com codigo %d removido da turma %d\n", codigo_grupo, codigo_turma);
      return;
    }
    grupo = grupo->prox;
  }

  printf("Grupo com codigo %d nao encontrado na turma %d\n", codigo_grupo, codigo_turma);
}

void consultar_grupos(int codigo_turma){

  TURMA* turma = NULL;
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  printf("Grupos da turma %d: \n", codigo_turma);
  GRUPO* grupo = turma->inicio_grupos;
  if(!grupo){
    printf("Nenhum grupo cadastrado\n");
    return;
  }

  while(grupo != NULL){
    printf("Grupo codigo %d\n", grupo->codigo_grupo);
    grupo = grupo->prox;
  }
}

void incluir_aluno_grupo(int codigo_turma, int codigo_grupo, int codigo_aluno){

  TURMA* turma = NULL;

  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  GRUPO* grupo = NULL;
  for(GRUPO* g = turma->inicio_grupos; g!=NULL; g = g->prox){
    if(g->codigo_grupo == codigo_grupo){
      grupo = g;
      break;
    }
  }
  if(!grupo){
    printf("Grupo com codigo %d nao encontrado\n", codigo_grupo);
    return;
  }

  for(GRUPO* g = turma->inicio_grupos; g!=NULL; g = g->prox){
    for(ALUNO* a = g->inicio_alunos; a!=NULL; a = a->prox){
      if(a->codigo == codigo_aluno){
        printf("Aluno com codigo %d ja esta em um grupo da turma %d\n", codigo_aluno, codigo_turma);
        return;
      }
    }
  }

  ALUNO* aluno = NULL;
  for(ALUNO* a = turma->inicio_alunos; a!=NULL; a = a->prox){
    if(a->codigo == codigo_aluno){
      aluno = a;
      break;
    }
  }
  if(!aluno){
    printf("Aluno com codigo %d nao encontrado na turma %d\n", codigo_aluno, codigo_turma);
    return;
  }

  ALUNO* novo_aluno_grupo = (ALUNO*)malloc(sizeof(ALUNO));
  if(!novo_aluno_grupo){
    printf("Erro ao alocar memoria para o aluno no grupo\n");
    return;
  }

  novo_aluno_grupo->codigo = aluno->codigo;
  strcpy(novo_aluno_grupo->nome, aluno->nome);
  novo_aluno_grupo->prox = NULL;
  novo_aluno_grupo->ant = NULL;

  if(grupo->inicio_alunos == NULL){
    grupo->inicio_alunos = novo_aluno_grupo;
  } else{
    ALUNO* ultimo = grupo->inicio_alunos;
    while(ultimo->prox != NULL){
      ultimo = ultimo->prox;
    }
    ultimo->prox = novo_aluno_grupo;
    novo_aluno_grupo->ant = ultimo;
  }

  printf("Aluno com codigo %d adicionado ao grupo %d da turma %d\n", codigo_aluno, codigo_grupo, codigo_turma);
  return;
}

void remover_aluno_do_grupo(int codigo_turma, int codigo_grupo, int codigo_aluno){

  TURMA* turma = NULL;
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  GRUPO* grupo = NULL;
  for(GRUPO* g = turma->inicio_grupos; g!=NULL; g = g->prox){
    if(g->codigo_grupo == codigo_grupo){
      grupo = g;
      break;
    }
  }
  if(!grupo){
    printf("Grupo com codigo %d nao encontrado\n", codigo_grupo);
    return;
  }

  ALUNO* aluno = NULL;
  for(ALUNO* a = grupo->inicio_alunos; a!=NULL; a = a->prox){
    if(a->codigo == codigo_aluno){
      aluno = a;
      break;
    }
  }
  if(!aluno){
    printf("Aluno com codigo %d nao encontrado no grupo %d\n", codigo_aluno, codigo_grupo);
    return;
  }

  if(aluno->ant != NULL){
    aluno->ant->prox = aluno->prox;
  } else{
    grupo->inicio_alunos = aluno->prox;
  }

  if(aluno->prox != NULL){
    aluno->prox->ant = aluno->ant;
  } 

  free(aluno);

  printf("Aluno com codigo %d removido do grupo %d da turma %d\n", codigo_aluno, codigo_grupo, codigo_turma);
}

void consultar_alunos_grupos(int codigo_turma){

  TURMA* turma = NULL;

  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  GRUPO* grupo_atual = turma->inicio_grupos;
  if(!grupo_atual){
    printf("A turma %d nao possui grupos cadastrados\n", codigo_turma);
    return;
  }

  printf("Grupos da turma %d:\n", codigo_turma);
  while(grupo_atual != NULL){
    printf(" Grupo %d:\n", grupo_atual->codigo_grupo);

    ALUNO* aluno_atual = grupo_atual->inicio_alunos;
    if(!aluno_atual){
      printf("   (Nenhum aluno neste grupo)\n");
    } else{
      while(aluno_atual != NULL){
        printf("   Aluno %d: %s\n", aluno_atual->codigo, aluno_atual->nome);
        aluno_atual = aluno_atual->prox;
      }
    }
    grupo_atual = grupo_atual->prox;
  }
}

void listar_alunos_sem_grupo(int codigo_turma){

  TURMA* turma = NULL;
  for(int i=0; i<total_turmas; i++){
    if(turmas[i].codigo == codigo_turma){
      turma = &turmas[i];
      break;
    }
  }
  if(!turma){
    printf("Turma com codigo %d nao encontrada\n", codigo_turma);
    return;
  }

  ALUNO* aluno_atual = turma->inicio_alunos;
  if(aluno_atual == NULL){
    printf("Turma %d nao tem alunos", codigo_turma);
    return;
  }

  int encontrou = 0;
  printf("Alunos sem grupo na turma %d\n", codigo_turma);

  while(aluno_atual != NULL){
    int tem_grupo = 0;

    GRUPO* grupo_atual = turma->inicio_grupos;
    while(grupo_atual != NULL){
      ALUNO* aluno_grupo = grupo_atual->inicio_alunos;
      while(aluno_grupo != NULL){
        if(aluno_grupo->codigo == aluno_atual->codigo){
          tem_grupo = 1;
          break;
        }
        aluno_grupo = aluno_grupo->prox;
      }
      if(tem_grupo) break;
      grupo_atual = grupo_atual->prox;
    }
    if(!tem_grupo){
      printf("  Aluno %d: %s\n", aluno_atual->codigo, aluno_atual->nome);
      encontrou = 1;
    }
    aluno_atual = aluno_atual->prox;
  }
  if(!encontrou) printf(" Todos os alunos estao em grupos\n");
}

void listar_alunos_varias_turmas(){

  int encontrado = 0;

  for(int i=0; i<total_turmas; i++){
    ALUNO* aluno_turma_i = turmas[i].inicio_alunos;

    while(aluno_turma_i != NULL){
      int contador = 0;

      for(int j=0; j<total_turmas; j++){
        if(i == j) continue;

        ALUNO* aluno_turma_j = turmas[j].inicio_alunos;
        while(aluno_turma_j != NULL){
          if(aluno_turma_j->codigo == aluno_turma_i->codigo){
            contador++;
            break;
          }
          aluno_turma_j = aluno_turma_j->prox;
        }
      }
      if(contador > 0){
        printf("Aluno %s (codigo %d) esta em mais de uma turma\n", aluno_turma_i->nome, aluno_turma_i->codigo);
        encontrado = 1;
      }

      aluno_turma_i = aluno_turma_i->prox;
    }
  }

  if(!encontrado){
    printf("Nenhum aluno esta em mais de uma turma\n");
  }
}

void apenas_uma_turma(){

  for(int i=0; i<total_turmas; i++){
    TURMA* turma = &turmas[i];

    for(ALUNO* aluno = turma->inicio_alunos; aluno!=NULL; aluno = aluno->prox){
      int contagem_turmas = 0;

      for(int j=0; j<total_turmas; j++){
        TURMA* outra_turma = &turmas[j];

        for(ALUNO* aluno_check = outra_turma->inicio_alunos; aluno_check!=NULL; aluno_check = aluno_check->prox){
          if(aluno_check->codigo == aluno->codigo){
            contagem_turmas++;
            break;
          }
        }
      }

      if(contagem_turmas == 1){
        printf("Aluno: %s, codigo: %d\n", aluno->nome, aluno->codigo);
      }
    }
  }
}

int main(){

  int opcao = 0;
  int codigo_aluno, codigo_turma, codigo_grupo;
  char nome_aluno[50];

  criar_turma(10);
  criar_turma(20);
  criar_turma(30);
  incluir_aluno(10, 1, "gio macaco");
  incluir_aluno(10, 2, "vini marx");
  incluir_aluno(10, 3, "samuel brustolas");
  incluir_aluno(10, 4, "timothee chalamet");
  incluir_aluno(20, 5, "charlie TPOBAW");
  incluir_aluno(20, 6, "william lee");
  incluir_aluno(20, 7, "Ada Lovelace");
  incluir_aluno(20, 8, "tralaleros tralala");
  incluir_aluno(20, 9, "bombardilo crocodilo");
  incluir_aluno(20, 10, "tumtumtumtum sahur");
  criar_grupo(10, 100);
  criar_grupo(20, 200);
  incluir_aluno_grupo(10, 100, 1);
  incluir_aluno_grupo(10, 100, 2);
  incluir_aluno_grupo(10, 100, 3);
  incluir_aluno_grupo(10, 100, 4);
  incluir_aluno_grupo(20, 200, 5);
  incluir_aluno_grupo(20, 200, 6);
  incluir_aluno_grupo(20, 200, 7);

  while(opcao != -1){
    printf("\n");
    printf("1 incluir nova turma\n");
    printf("2 remover uma turma\n");
    printf("3 consultar todas as turmas\n");
    printf("4 incluir aluno\n");
    printf("5 remover aluno\n");
    printf("6 consultar alunos\n");
    printf("7 incluir novo grupo\n");
    printf("8 remover grupo\n");
    printf("9 consultar todos os grupos de uma turma\n");
    printf("10 incluir aluno no grupo de uma turma\n");
    printf("11 remover aluno do grupo de uma turma\n");
    printf("12 consultar alunos dos grupos de uma turma\n");
    printf("13 alunos sem grupo\n");
    printf("14 alunos em mais de uma turma\n");
    printf("15 alunos em apenas uma turma\n");
    printf("-1 para sair\n");
    printf("Escolha uma opcao:");
    scanf("%d", &opcao);

    switch (opcao){
      case 1:
        printf("Digite o codigo da nova turma:");
        scanf("%d", &codigo_turma);
        criar_turma(codigo_turma);
        break;

      case 2:
        consultar_turmas();
        printf("Digite o codigo da turma a ser excluida:\n");
        scanf("%d", &codigo_turma);
        remover_turma(codigo_turma);
        break;

      case 3:
        consultar_turmas();
        break;
    
      case 4:
        consultar_turmas();
        printf("Digite o codigo da turma para incluir o aluno:\n");
        scanf("%d", &codigo_turma);
        printf("Digite o codigo do aluno:\n");
        scanf("%d", &codigo_aluno);
        fflush(stdin);
        printf("Digite o nome do aluno:\n");
        fgets(nome_aluno, 50, stdin);
        incluir_aluno(codigo_turma, codigo_aluno, nome_aluno);
        break;

      case 5:
        consultar_turmas();
        printf("Digite o codigo da turma para remover o aluno:\n");
        scanf("%d", &codigo_turma);
        consultar_alunos(codigo_turma);
        printf("Digite o codigo do aluno:\n");
        scanf("%d", &codigo_aluno);
        remover_aluno(codigo_turma, codigo_aluno);
        break;

      case 6:
        consultar_turmas();
        printf("Digite o codigo da turma:\n");
        scanf("%d", &codigo_turma);
        consultar_alunos(codigo_turma);
        break;

      case 7:
        consultar_turmas();
        printf("Digite o codigo da turma\n");
        scanf("%d", &codigo_turma);
        printf("Digite o codigo do novo grupo\n");
        scanf("%d", &codigo_grupo);
        criar_grupo(codigo_turma, codigo_grupo);
        break;

      case 8:
        consultar_turmas();
        printf("Digite o codigo da turma\n");
        scanf("%d", &codigo_turma);
        consultar_grupos(codigo_turma);
        printf("Digite o codigo do grupo a ser excluido\n");
        scanf("%d", &codigo_grupo);
        remover_grupo(codigo_turma, codigo_grupo);
        break;

      case 9:
        consultar_turmas();
        printf("Digite a turma\n");
        scanf("%d", &codigo_turma);
        consultar_grupos(codigo_turma);
        break;

      case 10:
        consultar_turmas();
        printf("Digite o codigo da turma\n");
        scanf("%d", &codigo_turma);
        consultar_grupos(codigo_turma);
        printf("Digite o codigo do grupo\n");
        scanf("%d", &codigo_grupo);
        printf("Digite o codigo do aluno\n");
        scanf("%d", &codigo_aluno);
        incluir_aluno_grupo(codigo_turma, codigo_grupo, codigo_aluno);
        break;

      case 11:
        consultar_turmas();
        printf("Digite o codigo da turma\n");
        scanf("%d", &codigo_turma);
        consultar_alunos_grupos(codigo_turma);
        printf("Digite o codigo do grupo\n");
        scanf("%d", &codigo_grupo);
        printf("Digite o codigo do aluno\n");
        scanf("%d", &codigo_aluno);
        remover_aluno_do_grupo(codigo_turma, codigo_grupo, codigo_aluno);
        break;

      case 12:
        consultar_turmas();
        printf("Digite a turma\n");
        scanf("%d", &codigo_turma);
        consultar_alunos_grupos(codigo_turma);
        break;

      case 13:
        consultar_turmas();
        printf("Digite a turma\n");
        scanf("%d", &codigo_turma);
        listar_alunos_sem_grupo(codigo_turma);
        break;

      case 14:
        listar_alunos_varias_turmas();
        break;

      case 15:
        apenas_uma_turma();
        break;

      default:
        printf("Opcao invalida\n");
        break;
    }
  }

  return 0;
}