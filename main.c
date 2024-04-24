#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define LIN 3
#define COL 3

//funcoes
void iniciarJogo();
void impJogo();
char verificaWin();
int lugarVazio(int i, int j);
int bot();
int jogoBot();
int jogo();
void load(char *texto);
int carregar();
//variaveis globais
int linha,coluna;
char matriz[LIN][COL];
char jogador=1;S
char computador = 'O';
char vaidevagar[]=("......");
int jogada=0;

int main()
{
    //variaveis
    int menu=-1, corrige=0;
    char r;
    printf("\t\t\n\nA carregar a capoeira.");
    carregar();  
    do
    {  
//construcao de tabuleiro
        iniciarJogo();
        system("cls");    
// menu do jogo
        printf("O Jogo do Galo v1.0\n");
        printf("Escolha uma das opcoes: \n");
        printf("1 - Solo\n");
        printf("2 - Duo\n");
        printf("3 - Sair\n");
        scanf(" %d",&menu);
// bug corrigido so trabalha com numeros do menu!!!
        while (menu !=1 && menu !=2 && menu != 3) 
        {
            scanf(" %d",&menu);
            fflush(stdin);
        }        
        system("cls");
        switch(menu)
        {   
            case 1:
            {
                //inicio do jogo com bot
                //Loading screen
                printf("Galo VS Galo do Futuro\n");
                printf("Loading.");
                carregar();
                while (1)
                {
                    system("cls");
                    impJogo();
                    jogoBot();
                    system("cls");
                    impJogo();
                    // verifica a win
                    if (verificaWin())
                    {
                        printf("\nParabens es agora o Mestre do Galo\n");
                        break;
                    }
                    //Caso de empate
                    if (jogada == 9)
                    {
                        printf("\nEmpate!\n"); 
                        break;
                    }
                    
                }
                break;

            }
            case 2: 
            {   
                //inicio do jogo com humanos
                //Loading screen
                printf("Galo VS Galo\n");
                printf("Loading.");
                carregar();  
                while (1)
                {
                //imprimir tabuleiro
                    
                    system("cls");
                    impJogo();
                    jogo();
                    impJogo(); 
              
                    //verifica win
                    if (verificaWin())
                    {
                        printf("\nParabens es agora o Mestre do Galo\n");
                        break; 
                    }   
                //Caso de empate
                    if (jogada == 9)
                    {
                        printf("\nEmpate!\n"); 
                        break;
                    }  
                }
                   
            }        
            case 3:
                break;  
        }
            printf("Loading.");//so para eu nao me cansar sozinho dos loading; :p
            carregar();
            system("cls");
            printf("\nDesejar continuar? Y/N: "); //para fazer loop e voltar ao menu
            r=getchar();
        while (r!='y' && r!='Y' && r!='n' && r!='N')
        {
            printf("\n Y/N : ");
            r=getchar();
            fflush(stdin);
            system("cls");
        }  
        if (r=='Y' && r=='y') //jogadas voltarem a zero
            jogada=0;
           
    }while(r !='N' && r!='n'); //para sair precisa clicar n ou N
        return 0;
    return 0;
}
void iniciarJogo() 
{
    //funcao para iniciar o jogo
     for(int i = 0; i < LIN; i++) {
        for(int j = 0; j < COL; j++) 
        {
            matriz[i][j] = ' ';
        }
    }
}
void impJogo ()
{
    //funcao para imprimir o jogo
    printf("\tJogo do Galo\n");
    printf("\n\t  0   1    2");
    printf("\n\t----+----+----\n");
    for(int i=0;i<LIN;i++)
    {
        printf("\t%d| %c |  %c | %c |",i,matriz[i][0],matriz[i][1],matriz[i][2]);
        printf("\n\t----+----+----\n");   
    }
}
char verificaWin()
{
    //funcao para verificacao de vitoria
    int i,j;
    // verifica a win diagonal
        if ( matriz[0][0]==matriz[1][1]  && matriz[0][0]==matriz[2][2] || matriz[2][0] == matriz[1][1] && matriz[2][0] == matriz[0][2])
        {
            if (matriz[1][1]!=' ')
                return 1;
        }
        //verifica win horizontal
        for ( i=0; i<LIN;i++)    
        {
            if (matriz[i][0]==matriz[i][1] && matriz[i][0]==matriz[i][2])
            {    
                if (matriz[i][0]!= ' ')
                    return 1;
            }
        }
        //verifica win vertical
        for ( i=0; i<LIN;i++) 
        { 
            if (matriz[0][i]==matriz[1][i] && matriz[0][i]==matriz[2][i] ) 
            {
                if (matriz[0][i]!= ' ')
                    return 1;
            }
        }
    return 0;
}
int lugarVazio(int i, int j)
//funcao para saber se existe lugar vazio
{
    if (matriz[i][j]==' ')
    {
        if (jogador==1)
        {
            matriz[i][j]= 'X';
            jogador=2;
        }
        else
        {
            matriz[i][j]= 'O';
            jogador=1;
        }
        jogada++;
        return 1; //1 se estiver vazia
    }
    return 0; //0 se estiver ocupada
    
}
int bot()
{
    //funcao para bot
    int i,j;
    srand(time(NULL));
    do 
    {
        i = rand() %LIN;//%3 de 0 ate 2
        j = rand() %COL;
    }
    while(!lugarVazio(i,j));
    return 1; //retorna para indicar que o bot fez jogada
    
}   
int jogo()
{
//vez do jogador
//controlo de entrada para nao ler letras"tinha um bug manhoso que lia 
//sempre a primeira jogada com letras, nas proximass jogadas ja nao deixava 
    printf("Jogador %d ",jogador);
    printf("Escolha a linha : ");
    
    while(scanf("%d",&linha)!=1)
    {
        fflush(stdin);
    }
 //limpar buffer
//verifica se a linha entra
    while ( linha != 0 && linha != 1 && linha !=2)
    {
        printf("erro, escolha outra linha :");
        scanf("%d",&linha);
        fflush(stdin); //limpar buffer
    }   

    printf("Escolha a coluna : ");
    scanf("%d",&coluna);
    fflush(stdin);  //limpar buffer

//verifica se a coluna entra    
    while ( coluna != 0 && coluna != 1 && coluna !=2)
    { 
        printf("erro, escolha outra coluna :");
        scanf("%d",&coluna);
        fflush(stdin);  //limpar buffer
    }
//verifica se a jogada eh valida para implementar as coordanadas
    int jogadaValida = lugarVazio(linha, coluna);
    if (!jogadaValida)
    {
        printf("Essa posicao ja esta ocupada! Tente novamente.\n");
    }

    return jogadaValida;
}
int jogoBot()
{   
    //jogo do bot 
    printf("Jogador %d ",jogador);
    if (jogador==1)
    {
        printf("Escolha a linha : ");
    
        while(scanf("%d",&linha)!=1)
        {
            fflush(stdin); //limpar buffer
        }
        //verifica se a linha entra
        while ( linha != 0 && linha != 1 && linha !=2)
        {
            printf("erro, escolha outra linha :");
            scanf("%d",&linha);
            fflush(stdin); //limpar buffer
        }

        printf("Escolha a coluna : ");
        scanf("%d",&coluna);
        fflush(stdin);  //limpar buffer

            //verifica se a coluna entra    
        while ( coluna != 0 && coluna != 1 && coluna !=2)
        { 
            printf("erro, escolha outra coluna :");
            scanf("%d",&coluna);
            fflush(stdin);  //limpar buffer
        }
        lugarVazio(linha, coluna);
    }
    else
    {   //loop para garantir que o botou faz uma jogada valida
        int botJogou = 0;
        do
        {
            botJogou = bot();
        } while (!botJogou);

        //verifica win
        if ( verificaWin())
        {
            printf("\nO botzinho fiambrou o galo!");
            sleep(1);
        }   
    }
}
void load(char *texto)
{
    //funcao para passar texto modo "vassoura":::::
    
    int i = 0;
    while (texto[i] != '\0')
    {
        putchar(texto[i]); // a letra que ele vai buscar 
        fflush(stdout); // Força a impressão imediata do caractere
        usleep(750000); // Atraso de 750 milissegundos (ajuste conforme desejado)
        i++;
    }   
}
int carregar()
{
    //funcao do loading
    do
        load(vaidevagar);
    while (usleep(50)); 
    return 0;
}