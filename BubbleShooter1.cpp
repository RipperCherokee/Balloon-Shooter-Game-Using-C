#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void draw_screen();
void show_score(int chance, int success, int score, int level, int color);
void draw_shaft(int x, int y, int c);
void draw_baloon(int x, int y, int c);
void game();

int point;

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    setcolor(1);
    outtextxy(100, 100, "Press S to Play the game");

    if (getch() == 's' || getch() == 'S')
    {
        game();
    }
    else
    {
        outtextxy(100, 200, "Wrong Key. Please Enter The Right Key");
        if (getch() == 's' || getch() == 'S')
        {
            game();
        }
    }

    getch();
    closegraph();
    return 0;  
}

void draw_screen()
{
    setfillstyle(1, 2);
    bar(0, 0, 150, 20);
    outtextxy(30, 5, "Score Board");
    setfillstyle(1, 3);
    bar(0, 20, 150, 250);
    setcolor(1);
    outtextxy(30, 40, "Total Chance");
    outtextxy(30, 80, "Success");
    outtextxy(30, 120, "  Score");
    outtextxy(30, 160, "  Level");
    setcolor(15);
    setfillstyle(1, 2);
    bar(0, 255, 150, 275);
    outtextxy(30, 260, "Control key");
    setfillstyle(1, 3);
    bar(0, 275, 150, 479);

    setcolor(1);
    outtextxy(30, 290, "UP");
    setcolor(4);
    for (int i = 0; i <= 5; i++)
        line(100 - i, 285 + i, 100 + i, 285 + i);
    line(100, 290, 100, 300);

    setcolor(1);
    outtextxy(30, 330, "DOWN");
    setcolor(4);
    for (int i = 0; i <= 5; i++)
        line(95 + i, 330 + i, 105 - i, 330 + i);
    line(100, 320, 100, 330);

    setcolor(1);
    outtextxy(30, 370, "Shoot");
    setcolor(4);
    outtextxy(100, 370, "Enter");

    setcolor(1);
    outtextxy(30, 410, "Exit");
    setcolor(4);
    outtextxy(100, 410, "Esc");
    setfillstyle(1, 1);
    bar(151, 0, 639, 479);
}

void show_score(int chance, int success, int score, int level, int color)
{
    setcolor(2);
    char str[3];
    gcvt(chance, 3, str);
    outtextxy(70, 60, str);
    gcvt(success, 3, str);
    outtextxy(70, 100, str);
    gcvt(score, 3, str);
    outtextxy(70, 140, str);
    gcvt(level, 3, str);
    outtextxy(70, 180, str);
}

void draw_shaft(int x, int y, int c)
{
    setcolor(c);
    rectangle(x - 1, y - 1, x - 30, y + 1);
    line(x, y, x - 30, y);
    line(x, y, x - 6, y - 4);
    line(x, y, x - 6, y + 4);
}

void draw_baloon(int x, int y, int c)
{
    setcolor(c);
    setfillstyle(1, c);
    sector(x, y, 0, 180, 10, 10);
    for (int i = 0; i <= 12; i++)
        line(x - 10 + i, y + i, x + 10 - i, y + i);
}

void game()
{
    int gd = 0, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    draw_screen();
    int chance = 0, success = 0, score = 0, level = 1;
    int shaft_x = 185, shaft_y = 200, shaft_color = 4;
    int baloon_x = 400, baloon_y = 400, baloon_color = 15;
    int balloon_count = 0, total_balloons = 10;
    show_score(chance, success, score, level, 0);
    draw_shaft(shaft_x, shaft_y, shaft_color);
    draw_baloon(baloon_x, baloon_y, baloon_color);

    while (balloon_count < total_balloons)
    {
        int chance_end = 0;

        while (!chance_end)
        {
            while (!kbhit())
            {
                delay(20); 
                baloon_color = 1;
                draw_baloon(baloon_x, baloon_y, baloon_color);
                baloon_y--;
                baloon_color = 15;
                draw_baloon(baloon_x, baloon_y, baloon_color);
                if (baloon_y < 0)
                {
                    chance_end = 1;
                    break;
                }
            }

            if (!chance_end)
            {
                char ch = getch();
                switch (ch)
                {
                case 72: 
                    shaft_color = 1;
                    draw_shaft(shaft_x, shaft_y, shaft_color);
                    shaft_y -= 5;
                    shaft_color = 4;
                    draw_shaft(shaft_x, shaft_y, shaft_color);
                    break;
                case 80: 
                    shaft_color = 1;
                    draw_shaft(shaft_x, shaft_y, shaft_color);
                    shaft_y += 5;
                    shaft_color = 4;
                    draw_shaft(shaft_x, shaft_y, shaft_color);
                    break;
                case 13:
                    do
                    {
                        delay(20);
                        baloon_color = 1;
                        draw_baloon(baloon_x, baloon_y, baloon_color);
                        baloon_y--;
                        baloon_color = 15;
                        draw_baloon(baloon_x, baloon_y, baloon_color);
                        shaft_color = 1;
                        draw_shaft(shaft_x, shaft_y, shaft_color);
                        shaft_x += 5;
                        shaft_color = 4;
                        draw_shaft(shaft_x, shaft_y, shaft_color);

                        if (shaft_x > baloon_x - 10 && shaft_x < baloon_x + 10 && shaft_y > baloon_y - 10 && shaft_y < baloon_y + 10)
                        {
                            baloon_color = 1;
                            draw_baloon(baloon_x, baloon_y, baloon_color);
                            shaft_color = 1;
                            draw_shaft(shaft_x, shaft_y, shaft_color);
                            show_score(chance, success, score, level, 3);
                            success++;
                            score += 10;
                            point = score;
                            show_score(chance, success, score, level, 1);
                            chance_end = 1;
                            shaft_x = 185;
                            shaft_y = 200;
                        }

                    } while (!chance_end && baloon_y > 0);

                    break;
                case 27:
                    closegraph();
                    return;
                default:
                    break;
                }
            }
        }
        balloon_count++;
        chance++;
        show_score(chance, success, score, level, 0);
        if (balloon_count < total_balloons)
        {
            shaft_x = 185;
            shaft_y = 200;

            do
            {
                baloon_x = rand() % 600;
            } while (baloon_x < 300);

            baloon_y = 400;
        }
    }
    outtextxy(200, 200, "Game Over");
    getch();
    closegraph();
}

