/*  Programa: Versao simplificada para aprendizado do jogo Portal. */
#include <raylib.h>
#include <stdio.h>

#define LARGURA 1200
#define ALTURA 600
#define A_MAPA 30
#define L_MAPA 60
#define MAX_OPTIONS 3

typedef struct//Estrutura do jogador - complementar variaveis
{
    int fase;
    int vidas;
    int alavancas;
} Jogador;

int desenhaMenu(int screenWidth, int screenheight);//Mostra o Menu Inicial
void jogo(Jogador *player, int screenWidth, int screenHeight);//Executa o jogo passando um ponteiro para a struct Jogador
void desenharCabecalho(Jogador *player);

int main()
{
    SetTargetFPS(20);
    int screenWidth = 1200;
    int screenHeight = 660;

    InitWindow(screenWidth, screenHeight, "Jogo Educativo - Portal");//Inicializa a janela do Raylib com largura, altura e titulo

    int opcao_menu = desenhaMenu(screenHeight, screenWidth);//Mostra o Menu Inicial e salva a opcao do usuario

    while (!WindowShouldClose())//Loop do menu
    {
        if (opcao_menu == 0)//Opcao Novo Jogo
        {
        //FAZER AQUI: CARREGAMENTO DE NIVEL

            Jogador player = {1, 3, 2};//Inicializa a struct Jogador
            jogo(&player, screenWidth, screenHeight);//Passa o endereço da struct para a funcao jogo
        }
        else
            if (opcao_menu == 1)//Opcao Carregar Jogo Salvo
            {
            //FAZER AQUI: CARREGAMENTO DE JOGO SALVO
            }
            else//Opcao Sair do jogo
            {
            printf("saiu");
            }
    }
    //FAZER AQUI: TELA DE GAME OVER OU DE VITORIA
    CloseWindow();

    return 0;
}

int desenhaMenu(int screenWidth, int screenheight)//Mostra o Menu Inicial
{
    int selectedOption = 0;//Opcao selecionada pelo usuario inicializada em 0
    while(!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();//Inicia o processo de desenho na tela

        ClearBackground(WHITE);//Desenha o fundo da tela

        DrawText("Menu Inicial", screenWidth/2 - MeasureText("Menu Inicial", 40)/2, 100, 40, DARKGRAY);//Desenha "menu"

        const char* options[MAX_OPTIONS] = {"Novo Jogo", "Carregar Jogo Salvo", "Sair do Jogo"};//Array de ponteiros para armazenar as strings do menu

        for (int i = 0; i < MAX_OPTIONS; i++)//Desenhar opcoes
        {
            if (i == selectedOption)
                DrawText(TextFormat("-> %s", options[i]), screenWidth/2 - MeasureText(options[i], 20)/1, 220 + 40 * i, 40, MAROON);//Desenha as opcoes destacando a selecionada
                else
                    DrawText(options[i], screenWidth/2 - MeasureText(options[i], 20)/1, 220 + 40 * i, 40, DARKGRAY);//Desenha as opcoes não selecionadas
        }

        EndDrawing();//Finaliza o processo de desenho na tela

        if (IsKeyPressed(KEY_UP))//Verificar entrada do usuario
        {
            selectedOption--;//Decrementa a opcao selecionada

            if (selectedOption < 0)//Se a opcao for menor que 0, volta para a ultima opcao
                selectedOption = MAX_OPTIONS - 1;
        } else
            if (IsKeyPressed(KEY_DOWN))//Verificar entrada do usuario
            {
                selectedOption++;//Incrementa a opcao selecionada
                if (selectedOption >= MAX_OPTIONS)//Se a opcao for maior ou igual ao numero maximo de opcoes, volta para a primeira opcao
                    selectedOption = 0;
            }
    }

    return selectedOption;
}

void jogo(Jogador *player, int screenWidth, int screenHeight)
{
    char texto[50];
    const int headerHeight = 60;//Altura do cabecalho

    char mapa[A_MAPA][L_MAPA]= {
'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W',
'W','J',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ','H','M',' ',' ',' ',' ','M','W','A',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W','W','W','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','H',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','H',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W','H','W','W','W','W',' ',' ','H',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ','M','W',' ',' ','H',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','H','H','H','H','H','H','H','H','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','H',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','H',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W','M',' ',' ',' ','W',' ',' ','H','A',' ',' ',' ','W','M',' ',' ',' ',' ','M','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ','W',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W','W','W','W','H','W','H','W','W','W','W','W','W','W','W','W','W','W','W','H','W','W','H','W','W','W','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ','W','A','W',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ','W',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H','H','H','H','H','H','H','H','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ','M',' ',' ','W',' ',' ','W',' ',' ','A','W',' ',' ',' ',' ',' ',' ',' ','H',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ','M',' ',' ','W',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','W',' ',' ',' ','W',' ',' ',' ','M',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ','M',' ',' ','W',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ','H',' ',' ','M','W',' ',' ',' ',' ',' ',' ',' ','W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','H','W',
'W',' ',' ',' ',' ','W',' ',' ','W','W','W','W','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W','H','H','H',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','M','M','M','M','M','M','M','M','M',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',
'W',' ',' ','H',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','M','M','M','M','M','M','M','M','M',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',
'W','A',' ','H',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ','M','M','M','M','M','M','M','M','M',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ','W','S',' ',' ',' ',' ',' ',' ','W',
'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'};

    Texture2D playerTexture = LoadTexture("player_up.png");//Carrega a imagem do jogador

    int playerX = 0;
    int playerY = headerHeight;//Posicao inicial do jogador abaixo do cabecalho
    int playerSpeed = 20;

    bool exitGame = false;

    while (!exitGame)//Loop do jogo - Condicoes de saida do jogo
    {
        if (IsKeyDown(KEY_D) && playerX + playerTexture.width < screenWidth)
            playerX += playerSpeed;

        if (IsKeyDown(KEY_A) && playerX > 0)
            playerX -= playerSpeed;

        if (IsKeyDown(KEY_W) && playerY > headerHeight)
            playerY -= playerSpeed;

        if (IsKeyDown(KEY_S) && playerY + playerTexture.height < screenHeight)
            playerY += playerSpeed;

        BeginDrawing();

        ClearBackground(WHITE);

        desenharCabecalho(player);

        for (int i = 0; i < A_MAPA; i++)//Desenha as paredes
            for (int j = 0; j < L_MAPA; j++)
                if (mapa[i][j] == 'W')
                    DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, BLACK);//Ajusta a posicao vertical das paredes para abaixo do cabecalho
                else
                    if (mapa[i][j] == 'J')
                        DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, ORANGE);
                    else
                        if (mapa[i][j] == 'M')
                            DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, RED);
                        else
                            if (mapa[i][j] == 'A')
                                DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, GREEN);
                            else
                                if (mapa[i][j] == 'H')
                                    DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, BROWN);
                            else
                                if (mapa[i][j] == 'S')
                                    DrawRectangle(j * 20, i * 20 + headerHeight, 20, 20, BLUE);

        DrawTexture(playerTexture, playerX, playerY, WHITE);//Desenha o jogador

        EndDrawing();

        if (player->vidas < 1)//Condicao de Game Over
            exitGame = true;
    }
    UnloadTexture(playerTexture);//Exclui a imagem da memoria
}

void desenharCabecalho(Jogador *player)
{
    char texto[50];
    sprintf(texto, "Fase: %d   Vidas: %d   Alavancas: %d", player->fase, player->vidas, player->alavancas);
    DrawRectangle(0, 0, LARGURA, 60, PURPLE);
    DrawText(texto, 30, 10, 40, WHITE);
}
