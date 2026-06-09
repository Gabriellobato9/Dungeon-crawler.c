#include <stdio.h>    // Entrada e saída padrão (usada para printf)
#include <stdlib.h>   // Funções padrão do sistema (como rand, srand e system)
#include <conio.h>    // Captura de teclas em tempo real do teclado (getch)
#include <windows.h>  // Funções exclusivas do Windows (Sleep para pausas)
#include <time.h>     // Usada para gerar números aleatórios baseados no relógio

// Definicao global da arma escolhida (1-Espada, 2-Arco, 3-Cajado)
int arma_escolhida = 0;

// ===========================================================
// FUNCOES DE RENDERIZACAO DOS MAPAS
// ===========================================================

void repeticao1(int intervalo1, int intervalo2, char mapa1[][10]) {
    for (intervalo1 = 0; intervalo1 < 10; intervalo1++) { // 1. Laço Externo (Linhas)
        for (intervalo2 = 0; intervalo2 < 10; intervalo2++) { // 2. Laço Interno (Colunas)
            printf(" %c", mapa1[intervalo1][intervalo2]);
        }
        printf("\n"); // 3. Quebra de linha
    }
}

void repeticao2(int intervalo1, int intervalo2, char mapa1[][15]) {
    for (intervalo1 = 0; intervalo1 < 15; intervalo1++) {
        for (intervalo2 = 0; intervalo2 < 15; intervalo2++) {
            printf(" %c", mapa1[intervalo1][intervalo2]);
        }
        printf("\n");
    }
}

void repeticao3(int intervalo1, int intervalo2, char mapa1[][25]) {
    for (intervalo1 = 0; intervalo1 < 25; intervalo1++) {
        for (intervalo2 = 0; intervalo2 < 25; intervalo2++) {
            printf(" %c", mapa1[intervalo1][intervalo2]);
        }
        printf("\n");
    }
}

// ===========================================================
// FUNCOES DE ATAQUE
// ===========================================================

void atacar_celula10(char mapa[][10], int y, int x, int rows, int cols, 
					int *m1x, int *m1y) {
    if (y < 0 || y >= rows || x < 0 || x >= cols) return;
    if (mapa[y][x] == 'k') { mapa[y][x] = ' '; }
    if (mapa[y][x] == 'X' || mapa[y][x] == 'Y') {
        mapa[y][x] = ' ';
        if (m1x && *m1x == x && m1y && *m1y == y) { *m1x = -1; *m1y = -1; }
    }
}

void atacar_celula15(char mapa[][15], int y, int x, int rows, int cols,
                     int *m1x, int *m1y, int *m2x, int *m2y) {
    if (y < 0 || y >= rows || x < 0 || x >= cols) return;
    if (mapa[y][x] == 'k') { mapa[y][x] = ' '; }
    if (mapa[y][x] == 'X' || mapa[y][x] == 'Y') {
        mapa[y][x] = ' ';
        if (m1x && *m1x == x && m1y && *m1y == y) { *m1x = -1; *m1y = -1; }
        if (m2x && *m2x == x && m2y && *m2y == y) { *m2x = -1; *m2y = -1; }
    }
}

// BUG 5 - Boss limitado a zona C (linhas 14-19) para nao teletransportar para fora do alcance
void atacar_celula25(char mapa[][25], int y, int x, int rows, int cols,
                     int *m1x, int *m1y, int *m2x, int *m2y,
                     int *bx, int *by, int *bvida) {
    if (y < 0 || y >= rows || x < 0 || x >= cols) return;
    if (mapa[y][x] == 'k') { mapa[y][x] = ' '; }
    if (mapa[y][x] == 'X') {
        mapa[y][x] = ' ';
        if (m1x && *m1x == x && m1y && *m1y == y) { *m1x = -1; *m1y = -1; }
    }
    if (mapa[y][x] == 'Y') {
        mapa[y][x] = ' ';
        if (m2x && *m2x == x && m2y && *m2y == y) { *m2x = -1; *m2y = -1; }
    }
    if (mapa[y][x] == 'Z' && bvida && *bvida > 0) {
        (*bvida)--;
        mapa[y][x] = ' ';
        if (*bvida > 0) {
            // Teletransporte limitado a Zona C (linhas 14-19)
            int nx = *bx, ny_b = *by;
            int tentativas = 0;
            do {
                nx = rand() % 23 + 1;
                ny_b = rand() % 6 + 14;
                tentativas++;
            } while (mapa[ny_b][nx] != ' ' && tentativas < 200);
            if (mapa[ny_b][nx] == ' ') {
                *bx = nx; *by = ny_b;
                mapa[*by][*bx] = 'Z';
            } else {
                // Fallback: boss fica na posicao original
                mapa[y][x] = 'Z';
                *bx = x; *by = y;
            }
        }
    }
}

// ===========================================================
// MAIN
// ===========================================================

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int Escolha = 0;
    int intervalo1 = 0, intervalo2 = 0;
    int r, c, i;

    printf("BEM VINDO AO DUNGEON CRAWLER!\n");
    system("pause");
    system("cls");

    while (Escolha != 3) {

        // ===================== MENU PRINCIPAL =====================
        printf("=============================\n");
        printf("| | 1- TUTORIAL           | |\n");
        printf("| | 2- INICIAR JOGO       | |\n");
        printf("| | 3- SAIR               | |\n");
        printf("=============================\n");

        char menu_tecla = getch();

        if (menu_tecla == '1') Escolha = 1;
        else if (menu_tecla == '2') Escolha = 2;
        else if (menu_tecla == '3') Escolha = 3;
        else {
            system("cls");
            printf("Tecla errada, tente novamente.\n\n");
            system("pause");
            system("cls");
            Escolha = 0;
            continue;
        }

        system("cls");

        // ===================== TUTORIAL =====================
        if (Escolha == 1) {
            printf("\n--- HISTORIA ---\n");
            printf("A vila 'ARGO' esta ameacada pelo Girotto das trevas que domina a masmorra!\n");
            printf("Voce e o escolhido para descer os tres andares e derrotar o mal.\n\n");
            printf("--- TUTORIAL DE SIMBOLOS ---\n");
            printf("^, v, <, > : Representam o jogador e a direcao para onde olha.\n");
            printf("* : Parede.\n");
            printf("@ : Chave para abrir as portas trancadas.\n");
            printf("D : Porta trancada.\n");
            printf("= : Porta aberta.\n");
            printf("L : Escada para o proximo andar.\n");
            printf("O : Botao interativo (use 'I' para ativar).\n");
            printf("# : Espinho perigoso (perde vida e reinicia a fase).\n");
            printf("k : Caixa de madeira (pode ser destruida com ataque).\n");
            printf("X : Monstro Nivel 1 (Movimento Aleatorio).\n");
            printf("Y : Monstro Nivel 2 (Perseguicao Simples).\n");
            printf("Z : Boss Final (Girotto das Trevas).\n");
            printf("N : NPC Mercador da Vila.\n\n");
            printf("CONTROLES:\n");
            printf(" W A S D - Movimentacao\n");
            printf(" I       - Interagir (NPC / Pegar Chaves / Abrir Portas / Ativar Botao)\n");
            printf(" O       - Executar Ataque com a Arma\n\n");
            printf("ARMAS:\n");
            printf(" 1 - Espada  : Ataca regiao 3x2 a frente\n");
            printf(" 2 - Arco    : Ataca 4 celulas em linha reta\n");
            printf(" 3 - Cajado  : Ataca as 8 celulas ao redor\n\n");
            system("pause");
            system("cls");
        }

        // ===================== INICIAR JOGO =====================
        else if (Escolha == 2) {

            int vid = 3;
            int fim = 0;
            arma_escolhida = 0;

            // ================= VILA (10x10) =================
            printf("BEM VINDO A VILA INICIAL!\n");
            printf("Fale com o NPC (N) pressionando 'I' para escolher a sua arma.\n");
            printf("Depois va ate a Escada (L) para entrar na masmorra.\n\n");
            system("pause");
            system("cls");

            char vila[10][10] = {
                {'*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ','N',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ','L','*'},
                {'*','*','*','*','*','*','*','*','*','*'}
            };

            int v_px = 4, v_py = 4;
            char v_simbolo = 'v';
            vila[v_py][v_px] = v_simbolo;
            repeticao1(intervalo1, intervalo2, vila);

            int na_vila = 1;
            while (na_vila) {
                char v_input = getch();
                int prox_x = v_px, prox_y = v_py;
                char novo_simbolo = v_simbolo;

                if (v_input == 'w' || v_input == 'W') { prox_y--; novo_simbolo = '^'; }
                else if (v_input == 's' || v_input == 'S') { prox_y++; novo_simbolo = 'v'; }
                else if (v_input == 'a' || v_input == 'A') { prox_x--; novo_simbolo = '<'; }
                else if (v_input == 'd' || v_input == 'D') { prox_x++; novo_simbolo = '>'; }
                else if (v_input == 'i' || v_input == 'I') {
                    if (vila[v_py-1][v_px] == 'N' || vila[v_py+1][v_px] == 'N' ||
                        vila[v_py][v_px-1] == 'N' || vila[v_py][v_px+1] == 'N') {
                        system("cls");
                        printf("NPC: Escolha sabiamente sua arma para a jornada:\n");
                        printf("1 - Espada   (Ataque 3x2 a frente)\n");
                        printf("2 - Arco     (Ataque em linha reta, 4 celulas)\n");
                        printf("3 - Cajado   (Ataque nas 8 celulas ao redor)\n");
                        printf("Escolha: ");
                        // BUG 1 - Validacao da escolha de arma no NPC
                        char npc_tecla = getch();
                        if (npc_tecla == '1') arma_escolhida = 1;
                        else if (npc_tecla == '2') arma_escolhida = 2;
                        else if (npc_tecla == '3') arma_escolhida = 3;
                        else {
                            system("cls");
                            printf("Tecla errada, tente novamente.\n\n");
                            system("pause");
                            system("cls");
                            arma_escolhida = 0;
                            na_vila = 0;
                            fim = -1;
                            break;
                        }
                        printf("\nNPC: Excelente escolha! Va ate a Escada (L) para entrar na masmorra.\n");
                        system("pause");
                    }
                }

                if (prox_x != v_px || prox_y != v_py) {
                    if (vila[prox_y][prox_x] == 'L') {
                        if (arma_escolhida == 0) {
                            system("cls");
                            printf("NPC: Voce nao pode entrar sem uma arma! Fale comigo primeiro.\n\n");
                            system("pause");
                        } else {
                            na_vila = 0;
                        }
                    } else if (vila[prox_y][prox_x] != '*' && vila[prox_y][prox_x] != 'N') {
                        vila[v_py][v_px] = ' ';
                        v_px = prox_x;
                        v_py = prox_y;
                    }
                    v_simbolo = novo_simbolo;
                    vila[v_py][v_px] = v_simbolo;
                }

                if (na_vila) {
                    system("cls");
                    repeticao1(intervalo1, intervalo2, vila);
                }
            }

            // Tecla errada no NPC: volta ao menu sem Game Over
            if (fim == -1 && arma_escolhida == 0) {
                fim = 0;
                arma_escolhida = 0;
                Escolha = 0;
                continue;
            }

            // ================= FASE 1 (10x10) =================
            system("cls");
            printf("BEM VINDO AO 1o ANDAR!\n");
            printf("Pegue a chave (@) com 'I', destrua caixas (k) com 'O' e abra a porta (D).\n");
            printf("A escada (L) aparece apos abrir a porta!\n\n");
            system("pause");
            system("cls");

            char mapa1[10][10] = {
                {'*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ','*','@','*'},
                {'*',' ','k',' ',' ',' ',' ','*',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ','k',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','D','*','*','*','*','*','*'}
            };

            int px = 1, py = 1;
            char p_simbolo = 'v';
            mapa1[py][px] = p_simbolo;
            printf("VIDAS: %d | CHAVES: 0\n", vid);
            repeticao1(intervalo1, intervalo2, mapa1);

            char input;
            int chave1 = 0;
            int fase1_ativa = 1;

            while (fase1_ativa) {
                input = getch();
                int movido = 0;
                int tent_x = px, tent_y = py;

                if (input == 'w' || input == 'W') { tent_y--; p_simbolo = '^'; movido = 1; }
                else if (input == 's' || input == 'S') { tent_y++; p_simbolo = 'v'; movido = 1; }
                else if (input == 'd' || input == 'D') { tent_x++; p_simbolo = '>'; movido = 1; }
                else if (input == 'a' || input == 'A') { tent_x--; p_simbolo = '<'; movido = 1; }

                // ATAQUE (tecla O)
                else if (input == 'o' || input == 'O') {
                    if (arma_escolhida == 1) {
                        if (p_simbolo == '^') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula10(mapa1, py-1, px+c, 10, 10, NULL, NULL);
                                atacar_celula10(mapa1, py-2, px+c, 10, 10, NULL, NULL);
                            }
                        } else if (p_simbolo == 'v') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula10(mapa1, py+1, px+c, 10, 10, NULL, NULL);
                                atacar_celula10(mapa1, py+2, px+c, 10, 10, NULL, NULL);
                            }
                        } else if (p_simbolo == '<') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula10(mapa1, py+r, px-1, 10, 10, NULL, NULL);
                                atacar_celula10(mapa1, py+r, px-2, 10, 10, NULL, NULL);
                            }
                        } else if (p_simbolo == '>') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula10(mapa1, py+r, px+1, 10, 10, NULL, NULL);
                                atacar_celula10(mapa1, py+r, px+2, 10, 10, NULL, NULL);
                            }
                        }
                    } else if (arma_escolhida == 2) {
                        for (i = 1; i <= 4; i++) {
                            if (p_simbolo == '^') atacar_celula10(mapa1, py-i, px, 10, 10, NULL, NULL);
                            else if (p_simbolo == 'v') atacar_celula10(mapa1, py+i, px, 10, 10, NULL, NULL);
                            else if (p_simbolo == '<') atacar_celula10(mapa1, py, px-i, 10, 10, NULL, NULL);
                            else if (p_simbolo == '>') atacar_celula10(mapa1, py, px+i, 10, 10, NULL, NULL);
                        }
                    } else if (arma_escolhida == 3) {
                        for (r = -1; r <= 1; r++)
                            for (c = -1; c <= 1; c++)
                                if (r != 0 || c != 0)
                                    atacar_celula10(mapa1, py+r, px+c, 10, 10, NULL, NULL);
                    }
                    system("cls");
                    mapa1[py][px] = p_simbolo;
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave1);
                    repeticao1(intervalo1, intervalo2, mapa1);
                }

                // INTERAGIR (tecla I)
                else if (input == 'i' || input == 'I') {
                    if (mapa1[py-1][px] == '@') { mapa1[py-1][px] = ' '; chave1++; }
                    else if (mapa1[py+1][px] == '@') { mapa1[py+1][px] = ' '; chave1++; }
                    else if (mapa1[py][px+1] == '@') { mapa1[py][px+1] = ' '; chave1++; }
                    else if (mapa1[py][px-1] == '@') { mapa1[py][px-1] = ' '; chave1++; }
                    else if (chave1 >= 1 &&
                             (mapa1[py-1][px] == 'D' || mapa1[py+1][px] == 'D' ||
                              mapa1[py][px+1] == 'D' || mapa1[py][px-1] == 'D')) {
                        if (mapa1[py-1][px] == 'D') mapa1[py-1][px] = 'L';
                        else if (mapa1[py+1][px] == 'D') mapa1[py+1][px] = 'L';
                        else if (mapa1[py][px+1] == 'D') mapa1[py][px+1] = 'L';
                        else if (mapa1[py][px-1] == 'D') mapa1[py][px-1] = 'L';
                        chave1--;
                    }
                    system("cls");
                    mapa1[py][px] = p_simbolo;
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave1);
                    repeticao1(intervalo1, intervalo2, mapa1);
                }

                // MOVIMENTO
                if (movido) {
                    char dest = mapa1[tent_y][tent_x];
                    if (dest == 'L') {
                        mapa1[py][px] = ' ';
                        fase1_ativa = 0;
                    } else if (dest == '#') {
                        vid--;
                        mapa1[py][px] = ' ';
                        px = 1; py = 1; p_simbolo = 'v';
                        mapa1[py][px] = p_simbolo;
                        system("cls");
                        printf("Voce pisou em espinhos! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase1_ativa = 0; fim = -1; }
                    } else if (dest != '*' && dest != 'D' && dest != '@' && dest != 'k') {
                        mapa1[py][px] = ' ';
                        px = tent_x; py = tent_y;
                    }
                    mapa1[py][px] = p_simbolo;
                    system("cls");
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave1);
                    repeticao1(intervalo1, intervalo2, mapa1);
                }
            }

            if (fim == -1) goto game_over;

            system("cls");
            printf("VOCE CONCLUIU O 1o ANDAR!\n\n");
            system("pause");
            system("cls");

            // ================= FASE 2 (15x15) =================
            // Mapa redesenhado com zonas horizontais claras:
            // Zona A (linhas 1-3): Chave 1 acessivel livremente
            // Parede + Porta1 (linha 4): precisa Chave 1
            // Zona B (linhas 5-8): Monstro X, Chave 2, Botao O
            // Parede + Porta2 (linha 9): precisa Chave 2
            // Zona C (linhas 10-13): Escada L
            printf("BEM VINDO AO 2o ANDAR!\n");
            printf("Pegue a Chave 1 (@) -> Abra a Porta 1 (D) -> Derrote o Monstro (X)\n");
            printf("Pegue a Chave 2 (@) -> Ative o Botao (O) com 'I' -> Abra a Porta 2 (D)\n");
            printf("Derrote o monstro antes de usar a Escada (L)!\n\n");
            system("pause");
            system("cls");

            char mapa2[15][15] = {
                {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ','k',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','D','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ','O',' ',' ',' ',' ','*'},
                {'*',' ','X',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','D','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ','L',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}
            };

            int p2x = 1, p2y = 1;
            char p2_simbolo = 'v';
            mapa2[p2y][p2x] = p2_simbolo;

            // Monstro X na Zona B
            int m2_1x = 2, m2_1y = 6;

            int botao_ativado2 = 0;
            int fase2_ativa = 1;
            int chave2 = 0;

            printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
            repeticao2(intervalo1, intervalo2, mapa2);

            while (fase2_ativa && vid > 0) {
                char input2 = getch();
                int movido2 = 0;
                int tent2x = p2x, tent2y = p2y;
                char novo_simbolo2 = p2_simbolo;

                if (input2 == 'w' || input2 == 'W') { tent2y--; novo_simbolo2 = '^'; movido2 = 1; }
                else if (input2 == 's' || input2 == 'S') { tent2y++; novo_simbolo2 = 'v'; movido2 = 1; }
                else if (input2 == 'a' || input2 == 'A') { tent2x--; novo_simbolo2 = '<'; movido2 = 1; }
                else if (input2 == 'd' || input2 == 'D') { tent2x++; novo_simbolo2 = '>'; movido2 = 1; }

                // ATAQUE (O)
                else if (input2 == 'o' || input2 == 'O') {
                    if (arma_escolhida == 1) {
                        if (p2_simbolo == '^') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula15(mapa2, p2y-1, p2x+c, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                                atacar_celula15(mapa2, p2y-2, p2x+c, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            }
                        } else if (p2_simbolo == 'v') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula15(mapa2, p2y+1, p2x+c, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                                atacar_celula15(mapa2, p2y+2, p2x+c, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            }
                        } else if (p2_simbolo == '<') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula15(mapa2, p2y+r, p2x-1, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                                atacar_celula15(mapa2, p2y+r, p2x-2, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            }
                        } else if (p2_simbolo == '>') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula15(mapa2, p2y+r, p2x+1, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                                atacar_celula15(mapa2, p2y+r, p2x+2, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            }
                        }
                    } else if (arma_escolhida == 2) {
                        for (i = 1; i <= 4; i++) {
                            if (p2_simbolo == '^') atacar_celula15(mapa2, p2y-i, p2x, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            else if (p2_simbolo == 'v') atacar_celula15(mapa2, p2y+i, p2x, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            else if (p2_simbolo == '<') atacar_celula15(mapa2, p2y, p2x-i, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                            else if (p2_simbolo == '>') atacar_celula15(mapa2, p2y, p2x+i, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                        }
                    } else if (arma_escolhida == 3) {
                        for (r = -1; r <= 1; r++)
                            for (c = -1; c <= 1; c++)
                                if (r != 0 || c != 0)
                                    atacar_celula15(mapa2, p2y+r, p2x+c, 15, 15, &m2_1x, &m2_1y, NULL, NULL);
                    }
                    system("cls");
                    mapa2[p2y][p2x] = p2_simbolo;
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
                    repeticao2(intervalo1, intervalo2, mapa2);
                }

                // INTERAGIR (I)
                else if (input2 == 'i' || input2 == 'I') {
                    if (mapa2[p2y-1][p2x] == '@') { mapa2[p2y-1][p2x] = ' '; chave2++; }
                    else if (mapa2[p2y+1][p2x] == '@') { mapa2[p2y+1][p2x] = ' '; chave2++; }
                    else if (mapa2[p2y][p2x-1] == '@') { mapa2[p2y][p2x-1] = ' '; chave2++; }
                    else if (mapa2[p2y][p2x+1] == '@') { mapa2[p2y][p2x+1] = ' '; chave2++; }
                    else if (chave2 >= 1 &&
                             (mapa2[p2y-1][p2x] == 'D' || mapa2[p2y+1][p2x] == 'D' ||
                              mapa2[p2y][p2x-1] == 'D' || mapa2[p2y][p2x+1] == 'D')) {
                        if (mapa2[p2y-1][p2x] == 'D') mapa2[p2y-1][p2x] = '=';
                        else if (mapa2[p2y+1][p2x] == 'D') mapa2[p2y+1][p2x] = '=';
                        else if (mapa2[p2y][p2x-1] == 'D') mapa2[p2y][p2x-1] = '=';
                        else if (mapa2[p2y][p2x+1] == 'D') mapa2[p2y][p2x+1] = '=';
                        chave2--;
                    }
                    // BUG 6 - Botao ativado por 'I' (adjacencia) e gera espinhos no mapa
                    else if (!botao_ativado2 &&
                             (mapa2[p2y-1][p2x] == 'O' || mapa2[p2y+1][p2x] == 'O' ||
                              mapa2[p2y][p2x-1] == 'O' || mapa2[p2y][p2x+1] == 'O')) {
                        botao_ativado2 = 1;
                        // Gera espinhos em varias regioes do mapa
                        mapa2[7][3] = '#'; mapa2[7][4] = '#'; mapa2[7][5] = '#';
                        mapa2[8][9] = '#'; mapa2[8][10] = '#'; mapa2[8][11] = '#';
                        mapa2[10][2] = '#'; mapa2[10][3] = '#';
                        mapa2[11][11] = '#'; mapa2[11][12] = '#';
                        system("cls");
                        printf("CUIDADO! O botao ativou armadilhas de espinhos pelo mapa!\n");
                        printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
                        mapa2[p2y][p2x] = p2_simbolo;
                        repeticao2(intervalo1, intervalo2, mapa2);
                        system("pause");
                    }
                    system("cls");
                    mapa2[p2y][p2x] = p2_simbolo;
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
                    repeticao2(intervalo1, intervalo2, mapa2);
                }

                // MOVIMENTO
                if (movido2) {
                    char dest2 = mapa2[tent2y][tent2x];
                    if (dest2 == '#') {
                        vid--;
                        mapa2[p2y][p2x] = ' ';
                        p2x = 1; p2y = 1; p2_simbolo = 'v';
                        mapa2[p2y][p2x] = p2_simbolo;
                        system("cls");
                        printf("Voce pisou em espinhos! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase2_ativa = 0; fim = -1; }
                    }
                    // BUG 3 - Escada so acessivel se o monstro estiver morto
                    else if (dest2 == 'L') {
                        if (m2_1x != -1) {
                            system("cls");
                            printf("Derrote os monstros para prosseguir!\n\n");
                            printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
                            mapa2[p2y][p2x] = p2_simbolo;
                            system("pause");
                            repeticao2(intervalo1, intervalo2, mapa2);
                        } else {
                            mapa2[p2y][p2x] = ' ';
                            fase2_ativa = 0;
                        }
                    } else if (dest2 == '=') {
                        mapa2[p2y][p2x] = ' ';
                        p2x = tent2x; p2y = tent2y;
                        p2_simbolo = novo_simbolo2;
                        mapa2[p2y][p2x] = p2_simbolo;
                    } else if (dest2 != '*' && dest2 != 'D' && dest2 != '@' &&
                               dest2 != 'k' && dest2 != 'X' && dest2 != 'O') {
                        mapa2[p2y][p2x] = ' ';
                        p2x = tent2x; p2y = tent2y;
                        p2_simbolo = novo_simbolo2;
                        mapa2[p2y][p2x] = p2_simbolo;
                    } else {
                        p2_simbolo = novo_simbolo2;
                        mapa2[p2y][p2x] = p2_simbolo;
                    }
                }

                // BUG 2 - IA Monstro Tipo 1 (X): detecta jogador em qualquer direcao
                if (m2_1x != -1 && m2_1y != -1) {
                    mapa2[m2_1y][m2_1x] = ' ';
                    int dir = rand() % 4;
                    int tmx = m2_1x, tmy = m2_1y;
                    if (dir == 0) tmy--;
                    else if (dir == 1) tmy++;
                    else if (dir == 2) tmx--;
                    else tmx++;

                    // BUG 2 - Permite mover para celula do jogador (qualquer simbolo de direcao)
                    if (tmx >= 0 && tmx < 15 && tmy >= 0 && tmy < 15) {
                        char cell_m = mapa2[tmy][tmx];
                        if (cell_m == ' ' || cell_m == '^' || cell_m == 'v' ||
                            cell_m == '<' || cell_m == '>') {
                            m2_1x = tmx; m2_1y = tmy;
                        }
                    }

                    if (m2_1x == p2x && m2_1y == p2y) {
                        vid--;
                        mapa2[p2y][p2x] = ' ';
                        p2x = 1; p2y = 1; p2_simbolo = 'v';
                        // Reposiciona monstro para nao sobrepor com jogador
                        m2_1x = 2; m2_1y = 6;
                        mapa2[p2y][p2x] = p2_simbolo;
                        system("cls");
                        printf("O Monstro X te pegou! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase2_ativa = 0; fim = -1; }
                    } else {
                        mapa2[m2_1y][m2_1x] = 'X';
                    }
                }

                if (fase2_ativa && vid > 0) {
                    system("cls");
                    printf("VIDAS: %d | CHAVES: %d\n", vid, chave2);
                    repeticao2(intervalo1, intervalo2, mapa2);
                }
            }

            if (fim == -1) goto game_over;

            system("cls");
            printf("VOCE CONCLUIU O 2o ANDAR!\n\n");
            system("pause");
            system("cls");

            // ================= FASE 3 (25x25) =================
            // Mapa com zonas horizontais claras:
            // Zona A (linhas 1-5):  Chave1 no canto direito. Monstro Y.
            // Parede + Porta1 (linha 6): precisa Chave1
            // Zona B (linhas 7-12): Monstro X. Chave2.
            // Parede + Porta2 (linha 13): precisa Chave2
            // Zona C (linhas 14-19): Chave3. Boss Z.
            // Parede + Porta3 (linha 20): precisa Chave3
            // Zona D (linhas 21-23): Saida (D->= quando boss morre)
            printf("BEM VINDO AO 3o ANDAR - O DESAFIO FINAL!\n");
            printf("Percurso: Chave1 -> Porta1 -> Monstros -> Chave2 -> Porta2\n");
            printf("       -> Chave3 -> Porta3 -> BOSS (Z) -> Saida!\n");
            printf("Derrote TODOS os inimigos e o Boss para poder sair!\n\n");
            system("pause");
            system("cls");

            char mapa3ret[25][25] = {
                {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','*'},
                {'*',' ','k',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ','Y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*','*','*','D','*','*','*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ','*'},
                {'*',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*','*','*','D','*','*','*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*','*','*','D','*','*','*','*','*','*','*','*','*','*','*','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
                {'*','*','*','*','*','*','*','*','*','*','*','*','D','*','*','*','*','*','*','*','*','*','*','*','*'}
            };

            char mapa3[25][25];
            for (intervalo1 = 0; intervalo1 < 25; intervalo1++)
                for (intervalo2 = 0; intervalo2 < 25; intervalo2++)
                    mapa3[intervalo1][intervalo2] = mapa3ret[intervalo1][intervalo2];

            int p3x = 1, p3y = 1;
            char p3_simbolo = 'v';

            int boss_x = 12, boss_y = 16;
            int boss_vida = 5;
            int boss_derrotado = 0;

            // Monstro Tipo 1 (X) - aleatorio - Zona B
            int mx3 = 3, my3 = 9;
            // Monstro Tipo 2 (Y) - perseguicao - Zona A
            int my3_x = 4, my3_y = 3;

            int fase3_ativa = 1;
            int chave3 = 0;

            mapa3[p3y][p3x] = p3_simbolo;
            mapa3[boss_y][boss_x] = 'Z';
            mapa3[my3][mx3] = 'X';
            mapa3[my3_y][my3_x] = 'Y';

            printf("VIDAS: %d | CHAVES: %d | BOSS: %d/5\n", vid, chave3, boss_vida);
            repeticao3(intervalo1, intervalo2, mapa3);

            while (fase3_ativa && vid > 0) {
                char input3 = getch();
                int movido3 = 0;
                int tent3x = p3x, tent3y = p3y;
                char novo_simbolo3 = p3_simbolo;

                if (input3 == 'w' || input3 == 'W') { tent3y--; novo_simbolo3 = '^'; movido3 = 1; }
                else if (input3 == 's' || input3 == 'S') { tent3y++; novo_simbolo3 = 'v'; movido3 = 1; }
                else if (input3 == 'a' || input3 == 'A') { tent3x--; novo_simbolo3 = '<'; movido3 = 1; }
                else if (input3 == 'd' || input3 == 'D') { tent3x++; novo_simbolo3 = '>'; movido3 = 1; }

                // ATAQUE (O)
                else if (input3 == 'o' || input3 == 'O') {
                    if (arma_escolhida == 1) {
                        if (p3_simbolo == '^') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula25(mapa3, p3y-1, p3x+c, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                                atacar_celula25(mapa3, p3y-2, p3x+c, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            }
                        } else if (p3_simbolo == 'v') {
                            for (c = -1; c <= 1; c++) {
                                atacar_celula25(mapa3, p3y+1, p3x+c, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                                atacar_celula25(mapa3, p3y+2, p3x+c, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            }
                        } else if (p3_simbolo == '<') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula25(mapa3, p3y+r, p3x-1, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                                atacar_celula25(mapa3, p3y+r, p3x-2, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            }
                        } else if (p3_simbolo == '>') {
                            for (r = -1; r <= 1; r++) {
                                atacar_celula25(mapa3, p3y+r, p3x+1, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                                atacar_celula25(mapa3, p3y+r, p3x+2, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            }
                        }
                    } else if (arma_escolhida == 2) {
                        for (i = 1; i <= 4; i++) {
                            if (p3_simbolo == '^') atacar_celula25(mapa3, p3y-i, p3x, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            else if (p3_simbolo == 'v') atacar_celula25(mapa3, p3y+i, p3x, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            else if (p3_simbolo == '<') atacar_celula25(mapa3, p3y, p3x-i, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                            else if (p3_simbolo == '>') atacar_celula25(mapa3, p3y, p3x+i, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                        }
                    } else if (arma_escolhida == 3) {
                        for (r = -1; r <= 1; r++)
                            for (c = -1; c <= 1; c++)
                                if (r != 0 || c != 0)
                                    atacar_celula25(mapa3, p3y+r, p3x+c, 25, 25, &mx3, &my3, &my3_x, &my3_y, &boss_x, &boss_y, &boss_vida);
                    }

                    // BUG 4 - Mensagem com temporizador de 3 segundos ao derrotar o boss
                    if (boss_vida <= 0 && !boss_derrotado) {
                        boss_derrotado = 1;
                        mapa3[24][12] = '='; // Abre a saida final
                        system("cls");
                        printf("================================================\n");
                        printf("  Parabens voce derrotou o Girotto das Trevas!  \n");
                        printf("================================================\n\n");
                        printf("A saida do dungeon foi aberta! Va ate ela para vencer!\n\n");
                        Sleep(3000); // Temporizador de 3 segundos
                    }

                    system("cls");
                    mapa3[p3y][p3x] = p3_simbolo;
                    printf("VIDAS: %d | CHAVES: %d | BOSS: %d/5\n", vid, chave3, boss_vida > 0 ? boss_vida : 0);
                    repeticao3(intervalo1, intervalo2, mapa3);
                }

                // INTERAGIR (I)
                else if (input3 == 'i' || input3 == 'I') {
                    if (mapa3[p3y-1][p3x] == '@') { mapa3[p3y-1][p3x] = ' '; chave3++; }
                    else if (mapa3[p3y+1][p3x] == '@') { mapa3[p3y+1][p3x] = ' '; chave3++; }
                    else if (mapa3[p3y][p3x-1] == '@') { mapa3[p3y][p3x-1] = ' '; chave3++; }
                    else if (mapa3[p3y][p3x+1] == '@') { mapa3[p3y][p3x+1] = ' '; chave3++; }
                    else if (chave3 >= 1 &&
                             (mapa3[p3y-1][p3x] == 'D' || mapa3[p3y+1][p3x] == 'D' ||
                              mapa3[p3y][p3x-1] == 'D' || mapa3[p3y][p3x+1] == 'D')) {
                        if (mapa3[p3y-1][p3x] == 'D') mapa3[p3y-1][p3x] = '=';
                        else if (mapa3[p3y+1][p3x] == 'D') mapa3[p3y+1][p3x] = '=';
                        else if (mapa3[p3y][p3x-1] == 'D') mapa3[p3y][p3x-1] = '=';
                        else if (mapa3[p3y][p3x+1] == 'D') mapa3[p3y][p3x+1] = '=';
                        chave3--;
                    }
                    system("cls");
                    mapa3[p3y][p3x] = p3_simbolo;
                    printf("VIDAS: %d | CHAVES: %d | BOSS: %d/5\n", vid, chave3, boss_vida > 0 ? boss_vida : 0);
                    repeticao3(intervalo1, intervalo2, mapa3);
                }

                // MOVIMENTO
                if (movido3) {
                    char dest3 = mapa3[tent3y][tent3x];
                    if (dest3 == '#') {
                        vid--;
                        mapa3[p3y][p3x] = ' ';
                        if (mx3 != -1 && my3 != -1) mapa3[my3][mx3] = ' ';
                        if (my3_x != -1 && my3_y != -1) mapa3[my3_y][my3_x] = ' ';
                        for (intervalo1 = 0; intervalo1 < 25; intervalo1++)
                            for (intervalo2 = 0; intervalo2 < 25; intervalo2++)
                                mapa3[intervalo1][intervalo2] = mapa3ret[intervalo1][intervalo2];
                        p3x = 1; p3y = 1; p3_simbolo = 'v';
                        mx3 = 3; my3 = 9;
                        my3_x = 4; my3_y = 3;
                        if (boss_vida > 0) { boss_x = 12; boss_y = 16; }
                        mapa3[p3y][p3x] = p3_simbolo;
                        mapa3[my3][mx3] = 'X';
                        mapa3[my3_y][my3_x] = 'Y';
                        if (boss_vida > 0) mapa3[boss_y][boss_x] = 'Z';
                        if (boss_derrotado) mapa3[24][12] = '=';
                        system("cls");
                        printf("Voce pisou em espinhos! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase3_ativa = 0; fim = -1; }
                    }
                    // BUG 3 - Saida so abre se Boss e todos monstros estiverem mortos
                    else if (dest3 == '=' && tent3y == 24) {
                        if (mx3 != -1 || my3_x != -1 || boss_vida > 0) {
                            system("cls");
                            printf("Derrote os monstros para prosseguir!\n\n");
                            printf("VIDAS: %d | CHAVES: %d | BOSS: %d/5\n", vid, chave3, boss_vida > 0 ? boss_vida : 0);
                            mapa3[p3y][p3x] = p3_simbolo;
                            system("pause");
                            repeticao3(intervalo1, intervalo2, mapa3);
                        } else {
                            mapa3[p3y][p3x] = ' ';
                            fase3_ativa = 0;
                            fim = 1;
                        }
                    } else if (dest3 == '=') {
                        mapa3[p3y][p3x] = ' ';
                        p3x = tent3x; p3y = tent3y;
                        p3_simbolo = novo_simbolo3;
                        mapa3[p3y][p3x] = p3_simbolo;
                    } else if (dest3 != '*' && dest3 != 'D' && dest3 != '@' &&
                               dest3 != 'k' && dest3 != 'Z' && dest3 != 'X' && dest3 != 'Y') {
                        mapa3[p3y][p3x] = ' ';
                        p3x = tent3x; p3y = tent3y;
                        p3_simbolo = novo_simbolo3;
                        mapa3[p3y][p3x] = p3_simbolo;
                    } else {
                        p3_simbolo = novo_simbolo3;
                        mapa3[p3y][p3x] = p3_simbolo;
                    }
                }

                // BUG 2 - IA Monstro Tipo 1 (X): movimento aleatorio, detecta jogador em qualquer direcao
                if (mx3 != -1 && my3 != -1) {
                    mapa3[my3][mx3] = ' ';
                    int dir3 = rand() % 4;
                    int tmx = mx3, tmy = my3;
                    if (dir3 == 0) tmy--;
                    else if (dir3 == 1) tmy++;
                    else if (dir3 == 2) tmx--;
                    else tmx++;

                    if (tmx >= 0 && tmx < 25 && tmy >= 0 && tmy < 25) {
                        char cell_x = mapa3[tmy][tmx];
                        if (cell_x == ' ' || cell_x == '=' || cell_x == '^' ||
                            cell_x == 'v' || cell_x == '<' || cell_x == '>') {
                            mx3 = tmx; my3 = tmy;
                        }
                    }

                    if (mx3 == p3x && my3 == p3y) {
                        vid--;
                        mapa3[p3y][p3x] = ' ';
                        p3x = 1; p3y = 1; p3_simbolo = 'v';
                        mx3 = 3; my3 = 9;
                        mapa3[p3y][p3x] = p3_simbolo;
                        system("cls");
                        printf("O Monstro X te pegou! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase3_ativa = 0; fim = -1; }
                    } else {
                        mapa3[my3][mx3] = 'X';
                    }
                }

                // BUG 2 - IA Monstro Tipo 2 (Y): perseguicao, detecta jogador em qualquer direcao
                if (my3_x != -1 && my3_y != -1) {
                    mapa3[my3_y][my3_x] = ' ';
                    int next_yx = my3_x, next_yy = my3_y;
                    if (my3_x < p3x) next_yx++;
                    else if (my3_x > p3x) next_yx--;
                    else if (my3_y < p3y) next_yy++;
                    else if (my3_y > p3y) next_yy--;

                    if (next_yx >= 0 && next_yx < 25 && next_yy >= 0 && next_yy < 25) {
                        char cell_y = mapa3[next_yy][next_yx];
                        if (cell_y == ' ' || cell_y == '=' || cell_y == '^' ||
                            cell_y == 'v' || cell_y == '<' || cell_y == '>') {
                            my3_x = next_yx; my3_y = next_yy;
                        }
                    }

                    if (my3_x == p3x && my3_y == p3y) {
                        vid--;
                        mapa3[p3y][p3x] = ' ';
                        p3x = 1; p3y = 1; p3_simbolo = 'v';
                        my3_x = 4; my3_y = 3;
                        mapa3[p3y][p3x] = p3_simbolo;
                        system("cls");
                        printf("O Monstro Y te alcancou! Vidas: %d\n", vid);
                        system("pause");
                        if (vid <= 0) { fase3_ativa = 0; fim = -1; }
                    } else {
                        mapa3[my3_y][my3_x] = 'Y';
                    }
                }

                if (fase3_ativa && vid > 0) {
                    system("cls");
                    printf("VIDAS: %d | CHAVES: %d | BOSS: %d/5\n", vid, chave3, boss_vida > 0 ? boss_vida : 0);
                    repeticao3(intervalo1, intervalo2, mapa3);
                }
            }

            // ===================== VITORIA =====================
            if (fim == 1) {
                system("cls");
                printf("========================================================\n");
                printf("    PARABENS! VOCE COMPLETOU O DUNGEON CRAWLER!         \n");
                printf("========================================================\n\n");
                printf("Com coragem e determinacao, voce desceu os tres andares,\n");
                printf("derrotou o Girotto das Trevas e libertou a vila de ARGO!\n");
                printf("A luz voltou a brilhar sobre as terras e o seu nome sera\n");
                printf("lembrado por todos como o heroi que salvou o CESUPA!\n\n");
                printf("  Creditos: Gabriel Saldanha e Gabriel Lobato\n\n");
                printf("========================================================\n\n");
                system("pause");
                Escolha = 3;
                continue;
            }

            // ===================== GAME OVER =====================
            game_over:
            if (fim == -1 || vid <= 0) {
                system("cls");
                printf("====================\n");
                printf("||   GAME OVER    ||\n");
                printf("====================\n\n");
                printf("Suas vidas terminaram! Voltando ao Menu Principal...\n\n");
                system("pause");
                system("cls");
                fim = 0;
                arma_escolhida = 0;
                Escolha = 0;
            }
        }
    }

    // ===================== SAIR =====================
    system("cls");
    printf("\nObrigado por jogar!\n");
    printf("Creditos: Gabriel Saldanha e Gabriel Lobato\n\n");
    return 0;
}
