// EggCatcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Player.h"
#include "Chicken.h"
#include "Eggs.h"
#include "EggSpecial.h"
#include "EggLife.h"
#include "Bomb.h"
#include "HealthObject.h"
#include "TextObject.h"

TTF_Font* font_score;
TTF_Font* font_menu;


bool Init()
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("--------------------------------------------------EGG CATCHER--------------------------------------------", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
            {
                success = false;
            }
        }

        g_sound = Mix_LoadMUS("sound//sound.mp3");
        if (g_sound == NULL)
        {
            success = false;
        }

        Mix_Chunk* chicken_sound = Mix_LoadWAV("sound//chicken.wav");
        Mix_PlayChannel(-1, chicken_sound, 0);

        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_score = TTF_OpenFont("font//PublicPixel-z84yD.ttf", 18);
        if (font_score == NULL)
        {
            success = false;
        }
    }

    return success;
}

BaseObject g_background;
bool LoadBackGround()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false)
        return false;
    return true;
}

BaseObject g_level_up;
bool LoadLevelUp()
{
	bool ret = g_level_up.LoadImg("img//levelup.png", g_screen);
	if (ret == false) return false;
	return true;
}

BaseObject g_menu_end;
std::string finalScore;
std::string outputScore;
bool Gameover()
{

    bool ret2 = g_menu_end.LoadImg("img//gameover-0.png", g_screen);
    if (ret2 == false)
        return false;
    const int num_item_menu_end = 3;
    SDL_Rect pos_arr_end[num_item_menu_end];

    pos_arr_end[0].x = 280;
    pos_arr_end[0].y = 180;

    pos_arr_end[1].x = 280;
    pos_arr_end[1].y = 250;

    pos_arr_end[2].x = 280;
    pos_arr_end[2].y = 110;

    TextObject text_menu_end[num_item_menu_end];

    text_menu_end[0].setText("> Play Again");
    text_menu_end[0].setColor(TextObject::WHITE_TEXT);
    text_menu_end[0].LoadFromRenderText(font_score, g_screen);
    text_menu_end[0].RenderText(g_screen, 280, 180);


    text_menu_end[1].setText("> Exit");
    text_menu_end[1].setColor(TextObject::WHITE_TEXT);
	text_menu_end[1].LoadFromRenderText(font_score, g_screen);
    text_menu_end[1].RenderText(g_screen, 280, 250);

    outputScore = "> ";
    outputScore += finalScore;
    text_menu_end[1].setText(outputScore);
    text_menu_end[1].setColor(TextObject::WHITE_TEXT);
    text_menu_end[1].LoadFromRenderText(font_score, g_screen);
    text_menu_end[1].RenderText(g_screen, 280, 110);

    return true;
}
const int num_item_menu = 3;
BaseObject g_menu_;
TextObject text_menu[num_item_menu];
SDL_Rect pos_arr[num_item_menu];

void restart()
{
    // Menu start

    bool ret1 = g_menu_.LoadImg("img//menu.png", g_screen);
    if (ret1 == false)
        return ;
    bool success = true;

    if (TTF_Init() == -1)
    {
        success = false;
    }
    font_menu = TTF_OpenFont("font//PublicPixel-z84yD.ttf", 40);
    if (font_menu == NULL)
    {
        success = false;
    }



    pos_arr[0].x = 280;
    pos_arr[0].y = 200;

    pos_arr[1].x = 280;
    pos_arr[1].y = 250;

    pos_arr[2].x = 280;
    pos_arr[2].y = 150;



    text_menu[0].setText("> Play");
    text_menu[0].setColor(TextObject::WHITE_TEXT);
    text_menu[0].LoadFromRenderText(font_score, g_screen);


    text_menu[1].setText("> Exit");
    text_menu[1].setColor(TextObject::WHITE_TEXT);
    text_menu[1].LoadFromRenderText(font_score, g_screen);

    text_menu[2].setText("> Instruction");
    text_menu[2].setColor(TextObject::WHITE_TEXT);
    text_menu[2].LoadFromRenderText(font_score, g_screen);
}

void close()
{
    g_background.Free();


    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_FreeMusic(g_sound);
    g_sound = NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    if (Init() == false)
        return -1;

    Mix_PlayMusic(g_sound, -1);

    SDL_Event m_event;
    restart();
    Player *basket;
    basket  = new Player();
    HealthObject health_object;
    Chicken chicken;
    Eggs* eggs = new Eggs[NUM_OBSTACLE];
    EggSpecial* eggspecials = new EggSpecial[NUM_OBSTACLE];
		EggLife* egglifes = new EggLife[NUM_OBSTACLE*2];

    Bomb* bombs = new Bomb[NUM_BOMB];

    int mode = 0;

    while (true)
    {
        if (mode == 0)
        {
            while (SDL_PollEvent(&m_event))
            {
                switch (m_event.type)
                {
                case SDL_QUIT:
                    return 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    int xm = m_event.button.x;
                    int ym = m_event.button.y;

                    if (xm >=280 && xm <= 450 && ym >=250 && ym <= 300)
                    {
                        close();
                    }

                    if (xm >= 280 && xm <= 450 && ym >= 180 && ym <= 230)
                    {
                        mode = 1;
                    }
                    break;
                }
                }
            }

            g_menu_.Render(g_screen);
			text_menu[0].RenderText(g_screen, pos_arr[0].x, pos_arr[0].y);
            text_menu[1].RenderText(g_screen,  pos_arr[1].x, pos_arr[1].y);
            text_menu[2].RenderText(g_screen,  pos_arr[2].x, pos_arr[2].y);
            SDL_RenderPresent(g_screen);
        }

        else if (mode == 1)
        {

            if (LoadBackGround() == false)
                return -1;
            basket->SetRect(400, 450);
            bool ret = basket->LoadImg("img//basket2.png", g_screen);
            if (ret == false)
                return false;
            if (Gameover() == false)
                return -1;

            health_object.Init(g_screen);

            chicken.Init(g_screen);

            for (int t = 0; t < NUM_OBSTACLE; t++)
            {
                Eggs* egg =  (eggs + t);
                ret = egg->LoadImg("img//egg2.png", g_screen);
                if (ret == false)
                {
                    return 0;
                }
                int x_pos = 0;
                if (t % 3 == 0)
                {
                    x_pos = x1;
                }
                else if (t % 3 == 1)
                {
                    x_pos = x2;
                }
                else if (t % 3 == 2)
                {
                    x_pos = x3;
                }
                egg->SetRect(x_pos, 110 + (t * 100));
                egg->set_y_val(2);
            }

            for (int k = 0; k < 1; k++)
            {
                EggSpecial* eggspecial = (eggspecials + k);

                ret = eggspecial->LoadImg("img//eggspecial.png", g_screen);
                if (ret == false)
                {
                    return 0;
                }

                int x_pos_options[] = {x1, x2, x3};
                int x_pos_index = rand() % 3;
                int x_pos = x_pos_options[x_pos_index];

                eggspecial->SetRect(x_pos, 100 + (k * 50));
                eggspecial->set_y_val(4);

            }

			for (int u = 0; u < 1; u++)
						{
							EggLife* egglife = (egglifes + u);

							ret = egglife->LoadImg("img//life.png", g_screen);
							if (ret == false)
							{
								return 0;
							}

							int x_pos_options[] = {x1, x2, x3};
							int x_pos_index = rand() % 3;
							int x_pos = x_pos_options[x_pos_index];

							egglife->SetRect(x_pos, 100 + (u * 50));
							egglife->set_y_val(4);

						}

            int y_val = 3;
            for (int i = 0; i<NUM_BOMB; i++)
            {
                Bomb* bomb = (bombs + i);
                ret = bomb->LoadImg("img//bomb2 (2).png", g_screen);
                if (ret == false)
                    return 0;
                int x_pos = 0;
                if (i % 3 == 0)
                {
                    x_pos = x1;
                }
                else if (i % 3 == 1)
                {
                    x_pos = x2;
                }
                else if (i % 3 == 2)
                {
                    x_pos = x3;
                }
                bomb->SetRect(x_pos, 100 + (i * 100));
                bomb->set_y_val(y_val);
            }
            TextObject score_text;
            score_text.setColor(TextObject::RED_TEXT);
            UINT score = 0;
            unsigned int num_die_ = 0;
            while (mode == 1)
            {
                while (SDL_PollEvent(&m_event))
                {
                    switch (m_event.type)
						{
                    case SDL_QUIT:
                        return 0;
                        break;
                    case SDL_KEYDOWN:
                    {
                        basket->HandleInputAction(m_event);
                        break;
                    }
                    }
                }

                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);

                g_background.Render(g_screen);
                basket->HandleMove();
                basket->Render(g_screen);
                health_object.Show(g_screen);
                chicken.Show(g_screen);
											Uint32 time_val = SDL_GetTicks()/1000;

                for (int tt=0; tt < NUM_OBSTACLE; tt++)
                {
                    Eggs* egg = (eggs + tt);
                    if (egg)
                    {
                        egg->HandleMove();
                        egg->Render(g_screen);
                    }
                    SDL_Delay(1);
					if (time_val == 20) 
								{
									egg->set_y_val(3);
								}
								if (time_val == 50) 
								{
									egg->set_y_val(4);
								}
                    bool is_col_1 = SDLCommonFunc::CheckCollision(basket->GetRect(), egg->GetRect());
                    if (is_col_1)
                    {
                        Mix_Chunk* ding_sound = Mix_LoadWAV("sound//Ding.wav");
                        Mix_PlayChannel(-1, ding_sound, 0);
                        int x_pos = 0;
                        if (tt % 3 == 0)
                        {
                            x_pos = x1;
                        }
                        else if (tt % 3 == 1)
                        {
                            x_pos = x2;
                        }
                        else if (tt % 3 == 2)
                        {
                            x_pos = x3;
                        }
                        egg->SetRect(x_pos, 110);
                        egg->set_y_val(2);

                        score++ ;
                    }
                }

                int egg_special_x_pos[3] = {x1, x2, x3};
                static bool is_egg_special_dropped = false;
                for (int kk=0; kk < NUM_OBSTACLE; kk++)
                {
                    EggSpecial* eggspecial = (eggspecials + kk);
                    if (eggspecial)
                    {
                        if (score % 17 == 0 && score > 0)
                        {
                            if (!is_egg_special_dropped)
                            {
                                int rand_index = rand() % 3;
                                eggspecial->SetRect(egg_special_x_pos[rand_index], 110);
                                eggspecial->set_y_val(4);
                                is_egg_special_dropped = true;
                            }
                        }
                        else{
                            is_egg_special_dropped = false;
                        }

                        if (score >= 17)
                        {
                            eggspecial->HandleMove();
                            eggspecial->Render(g_screen);
							bool is_col_2 = SDLCommonFunc::CheckCollision(basket->GetRect(), eggspecial->GetRect());
                            if (is_col_2)
                            {
                                Mix_Chunk* ding_sound = Mix_LoadWAV("sound//Ding.wav");
                                Mix_PlayChannel(-1, ding_sound, 0);

                                eggspecial->SetRect(-100, -100);
                                eggspecial->set_y_val(0);
                                score ++;
                            }
							if (eggspecial->GetRect()->y > SCREEN_HEIGHT) {
							mode=2;
						}
                        }

                        SDL_Delay(1);

                    }
                }

				 int egg_life_x_pos[3] = {x1, x2, x3};
                static bool is_egg_life_dropped = false;
                for (int uu=0; uu < NUM_OBSTACLE; uu++)
                {
                    EggLife* egglife = (egglifes + uu);
                    if (egglife)
                    {
                        if (score % 14 == 0 && score > 0)
                        {
                            if (!is_egg_life_dropped)
                            {
                                int rand_index = rand() % 3;
                                egglife->SetRect(egg_life_x_pos[rand_index], 110);
                                egglife->set_y_val(4);
                                is_egg_life_dropped = true;
                            }
                        }
                        else{
                            is_egg_life_dropped = false;
                        }

                        if (score >= 14)
                        {
                            egglife->HandleMove();
                            egglife->Render(g_screen);
							bool is_col_3 = SDLCommonFunc::CheckCollision(basket->GetRect(), egglife->GetRect());
                            if (is_col_3)
                            {
                                Mix_Chunk* pop_sound = Mix_LoadWAV("sound//pop.wav");
                                Mix_PlayChannel(-1, pop_sound, 0);

                                egglife->SetRect(-100, -100);
                                egglife->set_y_val(0);
								health_object.Increase();
										health_object.Render(g_screen);
										num_die_ --;

                                score ++;
                            }
							
                        }

                        SDL_Delay(1);

                    }
                }

                for (int ii = 0; ii < NUM_BOMB; ii++)
                {
                    Bomb* bomb = (bombs+ii);
                    if (bomb)
                    {
                        bomb->HandleMove();
                        bomb->Render(g_screen);
                    }
                    SDL_Delay(1);
                    if (score % 10 == 0 && score > 0)
                    {
                        int y_val = (score / 10) + 3;
                        bomb->set_y_val(y_val);
                    }
                    bool is_col_4 = SDLCommonFunc::CheckCollision(basket->GetRect(), bomb->GetRect());
                    if (is_col_4)
                    {
                        Mix_Chunk* wrong_sound = Mix_LoadWAV("sound//wrong.wav");
                        Mix_PlayChannel(-1, wrong_sound, 0);
                        int x_pos = 0;
                        if (ii % 3 == 0)
                        {
                            x_pos = x1;
                        }
                        else if (ii % 3 == 1)
                        {
                            x_pos = x2;
                        }
                        else if (ii % 3 == 2)
                        {
                            x_pos = x3;
                        }
                        bomb->SetRect(x_pos, 110 );
                        num_die_ ++;
                        if (num_die_ < 3)
                        {
                            health_object.Decrease();
                            health_object.Render(g_screen);
                        }
                        if (num_die_ == 3)
                        {
                            mode = 2;
                        }
                    }
                }

				bool level_up = false;
							if (score % 10 == 0 && score > 0 && !level_up) 
							{
								level_up = true;
								SDL_SetRenderDrawBlendMode(g_screen, SDL_BLENDMODE_BLEND);
								SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 128);
								SDL_Rect screen_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
								SDL_RenderFillRect(g_screen, &screen_rect);

								if (LoadLevelUp() == false) return -1;
								g_level_up.SetRect(150,200);
								g_level_up.Render(g_screen);

								SDL_RenderPresent(g_screen);
								Mix_Chunk* levelup_sound = Mix_LoadWAV("sound//levelup.wav");
								Mix_PlayChannel(-1, levelup_sound, 0);
							}


                std::string score_val = std::to_string(score);
                std::string str_score("Score: ");
                str_score += score_val;
                finalScore = str_score;
                score_text.setText(str_score);
                score_text.LoadFromRenderText(font_score, g_screen);
                score_text.RenderText(g_screen, SCREEN_WIDTH / 2 - 30, 10);

                SDL_RenderPresent(g_screen);

            }
        }
        else if (mode == 2)
        {
            Mix_Chunk* gameover_sound = Mix_LoadWAV("sound//game-over.wav");
            Mix_PlayChannel(-1, gameover_sound, 0);
			g_menu_end.Render(g_screen);
            Gameover();
            SDL_RenderPresent(g_screen);
            SDL_Delay(5000);

            while (mode == 2)
            {
                while (SDL_PollEvent(&m_event))
                {
                    switch (m_event.type)
                    {
                    case SDL_QUIT:
                        return 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        int xm = m_event.button.x;
                        int ym = m_event.button.y;

                        if (xm >=280 && xm <= 450 && ym >=250 && ym <= 300)
                        {
                            close();
                        }
                        if (xm >= 280 && xm <= 450 && ym >= 180 && ym <= 230)
                            mode = 1;
                        break;
                    }
                    }
                }
            }
        }
    }

    close();
    return 0;
}