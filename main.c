#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    int eBomba; // 0 para se não tem e 1 para ter
    int estaAberta; // 0 para sim e 1 para não
    int vizinhos ; // quantidade de bombas próximas
}Celula;

Celula jogo [10][10];
int l, c , tam = 10 ;

void inicializarJogo(){

    for (l = 0 ; l <tam;  l++){
        for(c = 0 ; c <tam ; c++){
            jogo[l][c].eBomba = 0 ;
            jogo[l][c].estaAberta = 0 ;
            jogo[l][c].vizinhos = 0;
        }
    }
}

//procedimento para sortear as bombas !!!
void sortearBombas(int n){
    srand(time(NULL));
    for(int i = 0 ; i <= n ; i ++){
         l = rand()% tam;
         c = rand()% tam;
         if(jogo[l][c].eBomba == 0){
             jogo[l][c].eBomba = 1 ;
         }
         else{
             i --;
         }
    }
}

int verificarCoordenadas(int l , int c){
    if(l >= 0 && l < tam && c >= 0 && c < tam ){
        return 1 ;
    }
    else
        return 0 ;
}

int BombasVizinhas(int l , int c){
    int quantidade ;

    if(verificarCoordenadas(l - 1 ,c ) && jogo[l-1][c].eBomba)
        quantidade ++ ;
    if(verificarCoordenadas(l +1 ,c ) && jogo[l+1][c].eBomba)
        quantidade ++ ;
    if(verificarCoordenadas(l ,c-1 ) && jogo[l][c-1].eBomba)
        quantidade ++ ;
    if(verificarCoordenadas(l ,c +1) && jogo[l][c+1].eBomba)
        quantidade ++ ;

    return quantidade ++ ;
}


int contarBombas(){
    for(l = 0 ; l <tam ; l++){
        for(c = 0 ; c < tam; c++){
            jogo[l][c].vizinhos = BombasVizinhas(l ,c);
        }
    }
}

//procedimento para imprimir o jogo

void imprimir(){
    printf("\n\n\t    ");
    for(l = 0 ; l < tam ; l ++){
        printf("  %d ", l); // indices colunas
    }
    printf("\n\t    -----------------------------------------\n");
    for(l = 0 ; l <tam ; l++){
        printf("\t%d   |", l); //indices das linhas
        for(c = 0 ; c < tam; c++){
            if(jogo[l][c].estaAberta){
                if(jogo[l][c].eBomba)
                    printf(" * ");
                else
                    printf(" %d ",jogo[l][c].vizinhos);
            }
            else {
                printf("   ");

            }
        printf("|");
        }
        printf("\n\t    -----------------------------------------\n");
    }
}

void abrirCelula(int linha ,int coluna){
    if(verificarCoordenadas(linha ,coluna)==1 && jogo[linha][coluna].estaAberta == 0){
        jogo[linha][coluna].estaAberta = 1;
        if(jogo[linha][coluna].vizinhos == 0){
            abrirCelula(linha-1,coluna);
            abrirCelula(linha+1, coluna);
            abrirCelula(linha,coluna-1);
            abrirCelula(linha, coluna+1);
        }
    }

}

int ganhou(){
    int quantidade = 0 ;
    for (l = 0 ; l <tam;  l++){
        for(c = 0 ; c <tam ; c++){
            if(jogo[l][c].estaAberta == 0 && jogo[l][c].eBomba ==0){
                quantidade++;
            }
        }
    }
    return quantidade;
}

void jogar(){
    int linha,coluna;

    do {
        imprimir();
        do {
            printf("\nDigite as coordenadas de linha e coluna : ");
            scanf("%d%d", &linha, &coluna);

            if (verificarCoordenadas(linha, coluna) == 0) {
                printf("\n\nCoordenada errada!!\n\n");
            }
        } while (verificarCoordenadas(linha, coluna) == 0 || jogo[linha][coluna].estaAberta == 1);

        abrirCelula(linha, coluna);
    }while(ganhou() != 0 && jogo[linha][coluna].eBomba == 0);

    if(jogo[linha][coluna].eBomba==1){
        printf("\n\nQue pena !!");
    }
    else
        printf("\n\t\tPARABÉNS!!!!\n");

    imprimir();
}

int main(void) {
    int opcao ;
    do {
        inicializarJogo();
        sortearBombas(10);
        contarBombas();
        printf("\n\t\t\t\t\t\tCAMPO MINADO\n");
        jogar();
        printf("\n\nDigite 1 para jogar novamente:");
        scanf("%d",&opcao);
    } while(opcao == 1);
    return 0 ;
}