//BERNARDO SOARES DINIZ LARA & MIGUEL FERREIRA PINTO


#include <stdio.h>
#include <math.h>

// insere os valores do arquivo na matriz atravez de recursividade
int leia(FILE *arquivo, int matriz[20][20])
{
    int numero1, numero2, numero3 = 0;
    int resultado = fscanf(arquivo, "%d,%d,%d", &numero1, &numero2, &numero3);

    if (resultado == 3)
    {
        matriz[numero1][numero2] = numero3;
        leia(arquivo, matriz);
    }

    return 0;
}

// funcao que printa uma matriz
void print_matriz(int m, int n, int matriz[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d, ", matriz[i][j]);
        }
        printf("\n");
    }
}

// limpa o lixo de memoria presente na matriz iniciando com -1
void iniciar_matriz(int matriz[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matriz[i][j] = -1;
        }
    }
}
// limpa o lixo de memoria presente na vetor iniciando com -1
void preenechevetor(int vetor[])
{
    for (int i = 0; i < 20; i++)
    {
        vetor[i] = -1;
    }
}

// checa se o destino ja foi visitado
int existe_novetor(int vetor[], int valor)
{
    for (int i = 0; i <= 19; i++)
    {
        if (vetor[i] == valor)
        {
            return 1;
        }
    }
    return 0;
}

// analiza qual o proximo destino que ainda nao foi visitado com o menor valor possivel
int menor_possivel(int vetor[], int anterior, int matriz[20][20])
{
    int menor_indice;
    int menor_valor = 2147483647;
    for (int i = 0; i < 20; i++)
    {
        int existe = existe_novetor(vetor, i);
        if (existe == 0 && matriz[anterior][i] < menor_valor && matriz[anterior][i] != -1)
        {
            menor_valor = matriz[anterior][i];
            menor_indice = i;
        }
    }
    return menor_indice;
}

// insere dentro do vetor a rota com o menor valor possivel
void analiza_menor(int inicio, int final, int vetor_rota[], int matriz[20][20])
{
    preenechevetor(vetor_rota); //limpa o vetor antes de iniciar as opercoes da funcao
    vetor_rota[0] = inicio;
    vetor_rota[19] = final;
    for (int i = 1; i < 19; i++)
    {
        vetor_rota[i] = menor_possivel(vetor_rota, vetor_rota[i - 1], matriz);
    }
}

// printa o vetor
void print_vetor(int tamanho, int vetor[])
{
    printf("\n");
    for (int i = 0; i < tamanho - 1; i++)
    {
        printf("%d,", vetor[i]);
    }
    printf("%d \n", vetor[tamanho - 1]);
}

// funcao que faz o ponderamento dos custos e preenche a matriz ponderada
void pondera_matriz(int transito[20][20], int criminalidade[20][20], int distancia[20][20], int matriz_ponderada[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (transito[i][j] > -1 && criminalidade[i][j] > -1 && distancia[i][j] > -1)
            {
                matriz_ponderada[i][j] = (transito[i][j] * 2) + (criminalidade[i][j] * criminalidade[i][j]) + (distancia[i][j] * 2);
            }
            else
            {
                matriz_ponderada[i][j] = -1;
            }
        }
    }
}

// funcao que calcula o custo da viagem
int calcula_custo(int vetor[], int matriz[20][20])
{
    int custo = 0;
    for (int i = 0; i < 19; i++)
    {
        if (matriz[vetor[i]][vetor[i + 1]] == -1 && custo > 0)
        {
            custo = custo * (matriz[vetor[i] - 1][vetor[i + 1] - 1]);
        }
        else
        {
            custo = custo + (matriz[vetor[i]][vetor[i + 1]]);
        }
    }
    return custo;
}

void copia_vetor(int vetor[], int vetor_aux[])
{
    for (int l = 0; l < 20; l++)
    {
        vetor_aux[l] = vetor[l];
    }
}
int main()
{
    FILE *arquivo;

    int transito[20][20];
    int criminalidade[20][20];
    int distancia[20][20];
    int matriz_ponderada[20][20];
// VETORES PARA CALCULAR AS ROTAS DE MENOR CUSTO UTILIZANDO UM PONTO DE PARTIDA E DE CHEAGADA
   /* int rota_transito[20];
    int rota_criminalidade[20];
    int rota_distancia[20];
    int rota_ponderada[20];*/
    int rota[20];
    int vetor_aux[20];

 //limpando o lixo de memoria   
    iniciar_matriz(transito);
    iniciar_matriz(criminalidade);
    iniciar_matriz(distancia);
 //Utiliza recursividade para ler o arquivo   
    arquivo = fopen("transito.txt", "r");
    if (arquivo == NULL)
    {
        printf("ERRO AO LER ARQUIVO Transito\n");
    }
    leia(arquivo, transito);// lê e preenche a matriz

    int resposta = fclose(arquivo); // fecha o arquivo
    if (resposta == -1)
    {
        printf("Ocorreu um erro ao fechar transito!\n");
    }

    arquivo = fopen("criminalidade.txt", "r");
    if (arquivo == NULL)
    {
        printf("ERRO AO LER ARQUIVO Criminalida\n");
    }

    leia(arquivo, criminalidade);// lê e preenche a matriz

    resposta = fclose(arquivo); // fecha o arquivo

    if (resposta == -1)
    {
        printf("Ocorreu um erro ao fechar criminalidade!\n");
    }
    arquivo = fopen("distancia.txt", "r");

    if (arquivo == NULL)
    {
        printf("ERRO AO LER ARQUIVO Distancia \n");
    }
    leia(arquivo, distancia);// lê e preenche a matriz

    resposta = fclose(arquivo); // fecha o arquivo

    if (resposta == -1)
    {
        printf("Ocorreu um erro ao fechar distancia! \n");
    }

    pondera_matriz(transito, criminalidade, distancia, matriz_ponderada);

    printf("Matriz transito\n");
    print_matriz(20, 20, transito);

    printf("Matriz criminalidade\n");
    print_matriz(20, 20, criminalidade);

    printf("Matriz distancia\n");
   print_matriz(20, 20, distancia);

    printf("Matriz ponderada\n");
    print_matriz(20, 20, matriz_ponderada);
    printf("\n");
    
    //CALCULAR AS ROTAS DE MENOR CUSTO UTILIZANDO UM PONTO DE PARTIDA E DE CHEAGADA
    /*printf("Rota distancia");                        //                INSERIR                INSERIR
    analiza_menor(2, 19, rota_distancia, distancia); // analiza_menor("PONTO DE PARTIDA", "PONTO DE CHEGADA", rota_distancia, distancia);
    print_vetor(20, rota_distancia);
    printf("O custo e %d", calcula_custo(rota_distancia, distancia));
    printf("\n");

    printf("Rota criminalidade");
    analiza_menor(2, 19, rota_criminalidade, criminalidade); // analiza_menor("PONTO DE PARTIDA", "PONTO DE CHEGADA", rota_distancia, distancia);
    print_vetor(20, rota_criminalidade);
    printf("O custo e %d", calcula_custo(rota_criminalidade, criminalidade));
    printf("\n");

    printf("Rota transito");
    analiza_menor(2, 19, rota_transito, transito); // analiza_menor("PONTO DE PARTIDA", "PONTO DE CHEGADA", rota_distancia, distancia);
    print_vetor(20, rota_transito);
    printf("O custo e %d", calcula_custo(rota_transito, transito));
    printf("\n");

    printf("Rota ponderada");
    analiza_menor(9, 16, rota_ponderada, matriz_ponderada); // analiza_menor("PONTO DE PARTIDA", "PONTO DE CHEGADA", rota_distancia, distancia);
    print_vetor(20, rota_ponderada);
    printf("O custo e %d", calcula_custo(rota_ponderada, matriz_ponderada));
    printf("\n");*/
     

//CALCULAR A ROTA DE MENOR CUSTO QUE PASSA EM TODOS OS PONTO
    int aux = 2147483647;                //maior numero que as variaveis do tipo int podem receber
    int valor = 0;
    for (int i = 0; i < 20; i++)         //percorre todos os numeros que podem assumir a posicao de inicio
    {
        for (int j = 0; j < 20; j++)     //percorre todos os numeros que podem assumir a posicao final
        {
            if (i != j)
            {
                analiza_menor(i, j, rota, matriz_ponderada);     //analiza a melhor rota pra cada posibilidade
                valor = calcula_custo(rota, matriz_ponderada);  //calcula o custo da rota
                if (valor < aux)                                 //analisa se o valor de custo é menor que o valor ja armazenado
                {
                    aux = valor;                                 //se valor for menor ele é amazenado para futuras comparações 
                    copia_vetor(rota,vetor_aux);                 //amazena o vetor que representa a melhor rota
                }
            }
        }
    }
    printf("Rota de menor custo: ");
    print_vetor(20,vetor_aux);                                          //depois de ter feito todas as comparações possiveis printa a melhor rota
    printf("O custo e %d", calcula_custo(vetor_aux, matriz_ponderada)); //calcula custo da melhor rota
    printf("\n");
}