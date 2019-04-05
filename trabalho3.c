/*
INSTITUTO FEDERAL DA BAHIA - IFBA
DISCIPLINA: LABORATORIO DE PROGRAMACAO
SEMESTRE: 2
DOCENTE: RENATO NOVAIS
ALUNO: MATHEUS ALVES RODRIGUES
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprime();
void aloca();
void iniciarEstrutura();
void alocarEstrutura();
void adicionarElemento();
void removerElemento();
void listarElementos();
void realocarMemoria();
void listarOrdenadoCada();
void listarOrdenadoGeral();
void liberar();
int printMenu();
int escolhaArq();
int verificaTipo();
int checaTamanho();

typedef struct posicao ListaPrincipal;
struct posicao{
  int *auxiliar;
  int cont;
  int tam;;
};

//------------------------------------------------------------
//FUNCOES GERENCIANDO ARQUIVOS
void cabecalho(){
    system("clear");
    printf("#######################################\n");
    printf("         ESTRUTURAS RAMIFICADAS\n");
    printf("         Armazenando em Arquivos\n");
    printf("########################################\n\n");
}

int printMenu(){
    int op;
    printf("(0) Sair\n");
    printf("(1) Inserir elemento\n");
    printf("(2) Excluir\n");
    printf("(3) Listar todas as estruturas\n");
    printf("(4) Listar ordenado (em cada estrutura auxiliar)\n");
    printf("(5) Listar ordenado (todos os numeros)\n");
    printf("(6) Aumentar tamanho da estrutura auxiliar\n");
    printf("\nDigite as opcao desejada: ");
    scanf("%d", &op);

    return op;
}

int escolhaArq(){
	int op;
	printf("Deseja criar de qual tipo?\n");
	printf("(0) binario\n");
	printf("(1) texto\n");
	scanf("%d", &op);

	return op;
}

int verificaTipo(){ //CHECA QUAL O TIPO DO ARQUIVO, BINARIO OU DE TEXTO
	FILE *checagem = fopen("checagem.txt", "r");
	int tipo;

	fopen("checagem.txt", "r");
	fscanf(checagem,"%d", &tipo);
	fclose(checagem);

	return tipo;
}

int checaTamanho(FILE *arq){ // CHECA TAMANHO DO ARQUIVO PARA VER SE TEM ALGO
		long tamanho;
		fseek(arq, 0, SEEK_END); // movimenta a posição corrente de leitura no arquivo para o seu fim
		tamanho = ftell(arq); // pega a posição corrente de leitura no arquivo
		fclose(arq);
		return tamanho;
	}

void iniciarEstrutura(ListaPrincipal *lp){
	int i;

	for(i = 0; i < 10;i++){
      lp[i].auxiliar = NULL;
    }

    for(i = 0; i < 10;i++){
      lp[i].cont = 0;
    }
}

void imprime(ListaPrincipal *lp){ //CHECA SE A PASSAGEM DE DADOS DO ARQUIVO PARA ESTRUTURA FUNCIONOU
	int i, j;

	printf("Tamanho:\n");
	for(i=0;i<10;i++){
		printf("%d\n", lp[i].tam);
	}

	printf("\nContador:\n");
	for(i=0;i<10;i++){
		printf("%d\n", lp[i].cont);
	}

	printf("\nDados:\n");
	for(i=0;i<10;i++){
		for(j=0;j<lp[i].cont;j++){
			printf("Estrutura %d - Auxiliar %d = %d\n",i+1, j+1, lp[i].auxiliar[j]);
		}
	}
}

void aloca(ListaPrincipal *lp){
	int i;

	for(i=0;i<10;i++){
		lp[i].auxiliar=(int*)malloc(lp[i].tam*sizeof(int));
	}
}

void alocarEstrutura(ListaPrincipal *lp){ //PASSA DADOS DO ARQUIVO PARA ESTRUTURA
	FILE *arq;
	FILE *indice;
	int i, j;

	indice = fopen("indice.txt", "r");
	for(i=0;i<10;i++){
		fscanf(indice,"%d %d",&lp[i].tam, &lp[i].cont);//
	}
	fclose(indice);

	aloca(lp);

	if(verificaTipo() == 0){ //CASO ARQUIVO BINARIO
		arq = fopen("arq.bin", "rb");
		for(i=0;i<10;i++){ //PEGANDO UMA DE CADA VEZ
			for(j=0;j<lp[i].cont;j++){
				fscanf(arq,"%d ",&lp[i].auxiliar[j]);
			}
		}
		fclose(arq);
	}
	else{ //CASO ARQUIVO DE TEXTO
		arq = fopen("arq.txt", "r");
		for(i=0;i<10;i++){ //PEGANDO UMA DE CADA VEZ
			for(j=0;j<lp[i].cont;j++){
				fscanf(arq,"%d ",&lp[i].auxiliar[j]);
			}
		}
		fclose(arq);
	}

}

int main(){
	int existe, i, j, opArq, op, tipo;
	FILE *arq, *checagem; //CHECAGEM GUARDA O TIPO DO ARQUIVO, SE = 0 <-BINARIO, SE !=0 <-TEXTO
    int sair = 0;
    ListaPrincipal lp[10];

	iniciarEstrutura(lp); //INICIALIZA A STRUCT

	if((checagem = fopen("checagem.txt", "r")) == NULL){ //ARQ NAO EXISTE
        cabecalho();
		printf("Arquivo nao existe\n");

		printf("Criando verificador.\n");
		opArq = escolhaArq();
		checagem = fopen("checagem.txt", "w");  //CRIA ARQ
		printf("Verificador criado com sucesso.\n");
		if(opArq == 0){
			existe = 0;
			fprintf(checagem, "%d", existe); //ARQ MOSTRA BINARIO
			if((fopen("arq.bin", "wb")) != NULL){ //CRIA BINARIO
				printf("Arquivo binario criado com sucesso.\n");
			}
			else{
				printf("Erro na criacao do arquivo binario.\n");
			}
		}
		else{
			existe = 1;
			fprintf(checagem, "%d", existe); //ARQ MOSTRA TEXTO
			if((fopen("arq.txt", "w")) != NULL){ //CRIA TEXTO
				printf("Arquivo de texto criado com sucesso.\n");
			}
			else{
				printf("Erro na criacao do arquivo de texto.\n");
			}
		}
		fclose(checagem);
	} //FECHA CONSTRUCAO DO ARQUIVO

	else{ //CASO ARQ EXISTA
		if(verificaTipo() == 0){ // VE SE EXISTE ALGO DENTRO DO ARQUIVO BINARIO
            cabecalho();
			printf("Arquivo Binario encontrado.\n");
			arq = fopen("arq.bin", "rb");

			if(checaTamanho(arq) == 0){
				printf("arquivo vazio\n");
			}
			else{
				arq = fopen("arq.bin", "rb");
				printf("Arquivo com algo\n");
				alocarEstrutura(lp);
			}
		}

		else{ // VE SE EXISTE ALGO DENTRO DO ARQUIVO DE TEXTO
			printf("Arquivo de Texto encontrado.\n");
			arq = fopen("arq.txt", "r");

			if(checaTamanho(arq) == 0){
				printf("arquivo vazio\n");
			}
			else{
				arq = fopen("arq.txt", "r");
				printf("Arquivo com algo\n");
				alocarEstrutura(lp);
			}
		}
	}

	while (!sair){
        op = printMenu();
        switch (op){
          case 0:{
                liberar(lp);
                sair =1;
                break;
            }
            case 1:{ //adicionarElemento
                adicionarElemento(lp);
                break;
            }
            case 2:{ //removerElemento
                removerElemento(lp);
                break;
            }
            case 3:{ //listar todos os elementos
                listarElementos(lp);
                break;
            }
            case 4:{ //listar elementos ordenados por estrutura
                listarOrdenadoCada(lp);
                break;
            }
            case 5:{ //listar todos os elementos ordenados
                listarOrdenadoGeral(lp);
                break;
            }
            case 6:{ //realocar memoria
                realocarMemoria(lp);
                break;
            }
            default:{
                printf("opcao invalida\n\n");
            }
        }
    }
    return 0;
}
// ------------------------------------------------------------------------------------------------
void liberar(ListaPrincipal *lp){ //SAIR
	int i, j;
	FILE *arq;
	ListaPrincipal est[10];

	FILE *indice = fopen("indice.txt", "w");
	for(i=0;i<10;i++){ //ARMAZENA O TAMANHO E CONTADOR DE CADA VETOR AUXILIAR
		fprintf(indice,"%d %d\n",lp[i].tam, lp[i].cont); //extra <-TENTATIVA
	}
	fclose(indice);
	printf("Indice salvo com sucesso.\n");

	if(verificaTipo() == 0){ //BINARIO
        arq = fopen("arq.bin", "wb");
		for(i=0;i<10;i++){
			for(j=0;j<lp[i].cont;j++){
				fprintf(arq,"%d\n",lp[i].auxiliar[j]);
			}
		}
		fclose(arq);
		printf("Auxiliar salva com sucesso.\n");

	}

	else{//TEXTO
		arq = fopen("arq.txt", "w");
		for(i=0;i<10;i++){
			for(j=0;j<lp[i].cont;j++){
				fprintf(arq,"%d\n",lp[i].auxiliar[j]);
			}
		}
		fclose(arq);
		printf("Auxiliar salva com sucesso.\n");

	}


  for(i = 0; i < 10; i++){
    free(lp[i].auxiliar); //LIBERA VETORES AUXILIARES
  }

  printf("Programa finalizado\n");
}

void adicionarElemento(ListaPrincipal *lp){ //INSERIR
  int pos, tam, elemento;

  printf("Informe a posicao de 1 a 10 a ser inserida:\n");
  scanf("%d", &pos);

  if(pos >= 1 && pos <= 10){
    pos = pos-1;

    if((lp[pos].auxiliar == NULL) || (lp[pos].tam == 0)){//
      printf("Informe o tamanho da estrutura auxiliar:\n");
      scanf("%d", &tam);

      lp[pos].auxiliar = (int*)malloc(tam*sizeof(int));

      lp[pos].tam = tam; //DEFINE O TAMANHO DO AUXILIAR
    }
    printf("Digite o valor:\n");
    scanf("%d", &elemento);

    lp[pos].auxiliar[lp[pos].cont] = elemento;

    if(lp[pos].cont == lp[pos].tam){ //AVISE SE CHEIA
      printf("A estrutura ja esta cheia\n");
    }
    else{
      lp[pos].cont = lp[pos].cont +1;//CASO NAO ESTEJA CHEIA, AUMENTA O CONTADOR
    }
  }
  else
    printf("Posicao nao encontrada\n\n");
}

void removerElemento(ListaPrincipal *lp){//REMOVER
  int pos, num, i, j, troca, local;

  printf("Informe a posicao da estrutura para remocao:\n");
  scanf("%d", &pos);

  if(pos >= 1 && pos <= 10){
    pos = pos-1;
    printf("Informe o numero a ser removido:\n");
    scanf("%d", &num);

    for(i = 0; i < lp[pos].tam; i++){
      if(lp[pos].auxiliar[i] == num){
        local = i;
        lp[pos].auxiliar[i] = 0;
        break;
      }
    }

    lp[pos].cont = lp[pos].cont - 1;

    printf("%d\n", local);

    for(i = local; i < lp[pos].tam - 1; i++){
        lp[pos].auxiliar[i] = lp[pos].auxiliar[i + 1];
    }
    lp[pos].auxiliar[i] = 0;
  }

  else
    printf("Posicao nao encontrada\n\n");
}

void listarElementos(ListaPrincipal *lp){//LISTA ELEMENTOS DE TODAS AS ESTRUTURAS
  int i, j, tam, est;

  for(i = 0; i < 10; i++){
    for(j = 0; j < lp[i].cont; j++){
        printf("Estrutura %d: Elemento %d = %d\n", i+1, j+1, lp[i].auxiliar[j]);
      }
  if(lp[i].tam != 0 && lp[i].cont != 0){
    printf("Tamanho da lp %d: %d\n", i+1, lp[i].tam);
    printf("Foram preenchidas %d posicao(oes)\n\n", lp[i].cont);
    }
  }
}

void listarOrdenadoCada(ListaPrincipal *lp){//LISTAR ELEMENTOS ORDENADOS PARA CADA AUXILIAR
  ListaPrincipal aux[10]; //STRUCT AUXILIAR
  int i, j, k, tam[10], troca;

  for(i = 0; i < 10;i++){ //<- NAO PRECISA
    tam[i] = lp[i].cont;
  }

  for(i = 0; i < 10;i++){
    aux[i].auxiliar = (int *) malloc (tam[i] * sizeof (int)); //ALOCA ESPACO NA AUXILIAR
  }

  for(i = 0; i < 10;i++){
    for(j = 0; j < tam[i]; j++){
      aux[i].auxiliar[j] = lp[i].auxiliar[j]; //BOTA ELEMENTOS NA VARIAVEL
    }
  }

  for(k = 0;k < 10; k++){ //INSERTION
    for(i = 0;i < tam[k] - 1; i++){
      for(j = i+1;j < tam[k];j++){
        if(aux[k].auxiliar[i] < aux[k].auxiliar[j]){
          troca = aux[k].auxiliar[i];
          aux[k].auxiliar[i] = aux[k].auxiliar[j];
          aux[k].auxiliar[j] = troca;
        }
      }
    }
  }

  for(i = 0; i < 10; i++){
    for(j = 0; j < tam[i]; j++){
        printf("Estrutura %d: Elemento %d = %d\n", i+1, j+1, aux[i].auxiliar[j]);
    }
  }
  printf("\n");
//free(aux);
}

void listarOrdenadoGeral(ListaPrincipal *lp){//LISTAR TODOS OS ELEMENTOS ORDENADOS
 int i, j, k, atual, *ordenar, contador=0, cont2=0;

 for(i=0; i<10; i++){
   contador = contador + lp[i].cont; //Encontrando total a ser alocado
 }

 if(contador>0)
  ordenar = (int*) malloc(contador*sizeof(int));//Alocando Valores

 for(i=0; i<10; i++){ //Passando os valores para vetorzao
  for(j=0; j<lp[i].cont; j++){
    if(lp[i].auxiliar != NULL){
      ordenar[cont2] = lp[i].auxiliar[j];
      cont2++;
    }
  }
}

   //Insertion
   for(j=1; j<cont2; j++){
     atual = ordenar[j];
     for(k=j-1; (k>=0) && (atual < ordenar[k]); k--){
       ordenar[k+1] = ordenar[k];
     }
     ordenar[k+1] = atual;
    }

  printf("\nElementos ordenados: ");
  for(i = 0; i < cont2; i++){
        printf(" %d ",ordenar[i]);
  }

printf("\n");
}

void realocarMemoria(ListaPrincipal *lp){//REALOCAR
  int pos, tam;

  printf("Escolha a posição da estrutura a ser aumentada:\n");
  scanf("%d", &pos);

  if((pos >= 1 && pos <= 10) && lp[pos].auxiliar != NULL){
    pos=pos-1;
    printf("Escolha quantas posicoes sera aumentada:\n");
    scanf("%d", &tam);
    if(tam > 0){
      lp[pos].auxiliar = (int*) realloc (lp[pos].auxiliar, tam*sizeof(int));
      lp[pos].tam += tam;
    }
    else
      printf("Nao eh possivel alocar valores negativos!!!\n");
  }
  else
    printf("Posicao inexistente\n");
}
