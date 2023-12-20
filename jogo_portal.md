# Jogo-Portal
Projeto inspirado no jogo "portal" da cadeira de algoritmos e programação
#include "raylib.h"
#include <string.h>

#define LARGURA 1200
#define ALTURA 600

// DECLARACAO DAS FUNCOES
void move_personagem(int *x, int *y);

int main(void) {
    int x = 300, y = 300;

    InitWindow(LARGURA, ALTURA, "jogo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        move_personagem(&x, &y);

        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(x, y, 20, 20, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void move_personagem(int *x, int *y) {
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed('D')) { // direita
        (*x) += 20;
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed('A')) { // esquerda
        (*x) -= 20;
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed('W')) { // cima
        (*y) -= 20;
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed('S')) { // baixo
        (*y) += 20;
    }

    if (*x < 0 || *x >= LARGURA || *y < 0 || *y >= ALTURA) {
        return;
    }
}
