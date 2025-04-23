//
// Created by MSI GF63 on 4/7/2025.
//

#include "Game.h"

Game::Game(){
    gameplay_window = nullptr;
    gameplay_renderer = nullptr;
    isRunning = true;
    backgroundTexture = nullptr;
    playerTexture = nullptr;
    bulletTexture = nullptr;
    enemyTexture = nullptr;
    entityTexture = nullptr;
    bossTexture = nullptr;
    bossLazeTexture = nullptr;
    heartTexture == nullptr;
    victoryTexture = nullptr;
    defeatTexture = nullptr;
  }

Game::~Game(){
    Clean();
}

void Game::Run(bool& gameRunning)
{
    if (!InitWindowRenderer())
    {
        cout << "Failed to create window or renderer" << endl;
    }
    else
    {
        // Nạp tất cả các ảnh
        backgroundTexture = LoadGameTexture(gameplay_renderer, "assets/Game/background.png");
        playerTexture = LoadGameTexture(gameplay_renderer, "assets/Game/jinxup.png");
        bulletTexture = LoadGameTexture(gameplay_renderer, "assets/Game/bullet.png");
        enemyTexture = LoadGameTexture(gameplay_renderer, "assets/Game/ghost.png");
        entityTexture = LoadGameTexture(gameplay_renderer, "assets/Game/dog.png");
        bossTexture = LoadGameTexture(gameplay_renderer, "assets/Game/boss.png");
        bossLazeTexture = LoadGameTexture(gameplay_renderer, "assets/Game/bossBullet.png");
        heartTexture = LoadGameTexture(gameplay_renderer, "assets/Game/heart.png");
        victoryTexture = LoadGameTexture(gameplay_renderer, "assets/Game/victory.png");
        defeatTexture = LoadGameTexture(gameplay_renderer, "assets/Game/defeat.png");

        // Fonts
        font = TTF_OpenFont("assets/Fonts/slkscr.ttf", 48);
        SDL_Color textColorHealth = { 0, 255, 0 };
        SDL_Texture* healthTexture = renderText("Health: ",gameplay_renderer, font, textColorHealth);
        SDL_Rect textRect1 = {500, 20, 0, 0}; // Ban dau dat w va h la 0
        SDL_QueryTexture(healthTexture, nullptr, nullptr, &textRect1.w, &textRect1.h); // Lay kich thuoc w va h cua texture

        //Music
        LoadAudio();
        PlayMusic();
        // Khởi tạo tất cả nhân vật, vật thể trong game
        Player player(Globals::SCREEN_GAME_WIDTH / 2, Globals::SCREEN_GAME_HEIGHT / 2);
        vector <Health> Hearts ={
            Health(700,15),
            Health(775,15),
            Health(850,15),
        };
        vector <Bullet> Bullets;
        vector <Enemy> Enemies;
        vector <pair<Boss,int>> Bosses;
        vector <BossLaze> BossLazes;
        vector <Entity> entities = {
            Entity(0,10),
            Entity(0,190),
            Entity(0,360),
            Entity(0,550),
            Entity(0,730)
        };
        int Points = 0;

        SDL_Event e;
        while(isRunning && Points < 1000)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    pair<int, int> gunPos = player.gunPosition();
                    Bullet bullet(gunPos.first, gunPos.second);
                    Bullets.push_back(bullet);
                    PlaySound(shootSound);
                }

            }
            // Handle nhan vat
            const Uint8* CurrentKeyState = SDL_GetKeyboardState(nullptr);
            player.move(CurrentKeyState);
            player.limit(Globals::SCREEN_GAME_WIDTH, Globals::SCREEN_GAME_HEIGHT);

            // Đạn di chuyển
            for (int i = 0; i < Bullets.size(); i++)
            {
                Bullets[i].move(); //  đạn di chuyển sau mỗi lần gọi
                if (Bullets[i].bulletLimit(Globals::SCREEN_GAME_WIDTH))
                {
                    Bullets.erase(Bullets.begin() + i);
                }
            }

            //Spawn kẻ địch ở vị trí ngẫu nhiên bên phải màn hình
            if (SDL_GetTicks() - lastSpawnTime > spawnDelay) {
                spawnEnemy(Enemies);
                lastSpawnTime = SDL_GetTicks();
            }

            // Handle địch

            for (size_t i = 0; i < Enemies.size();i++)
            {
                Enemies[i].move();
                if (Enemies[i].isOutside())
                {
                    isRunning = false; //Địch đi vào được ngoài cùng bên trái thì thua
                    Mix_FreeMusic(bgMusic);
                    PlaySound(defeatSound);
                    SDL_Rect defeatRect {Globals::SCREEN_GAME_WIDTH/2 - 200,Globals::SCREEN_GAME_HEIGHT/2 - 200,500,500};
                    SDL_RenderCopy(gameplay_renderer, defeatTexture, nullptr, &defeatRect);
                    SDL_RenderPresent(gameplay_renderer);
                    SDL_Delay(4000);
                    break;
                }
                SDL_Rect enemyRect = Enemies[i].getRect();
                SDL_Rect playerRect = player.getRect();
                if (SDL_HasIntersection(&enemyRect,&playerRect))
                {
                    Hearts.erase(Hearts.begin() + 0);
                    Enemies.erase(Enemies.begin() + i);
                    PlaySound(playerHitSound);
                    if (Hearts.size() == 0)
                    {
                        Mix_FreeMusic(bgMusic);
                        isRunning = false;
                        SDL_Rect defeatRect {Globals::SCREEN_GAME_WIDTH/2 - 200,Globals::SCREEN_GAME_HEIGHT/2 - 200,500,500};
                        SDL_RenderCopy(gameplay_renderer, defeatTexture, nullptr, &defeatRect);
                        SDL_RenderPresent(gameplay_renderer);
                        PlaySound(defeatSound);
                        SDL_Delay(4000);
                        break;
                    }
                }

                for (size_t j = 0; j < entities.size(); j++)
                {
                    SDL_Rect entityRect = entities[j].getRect();
                    if (SDL_HasIntersection(&enemyRect, &entityRect))
                    {
                        Enemies.erase(Enemies.begin() + i);
                        entities.erase(entities.begin() + j);
                        if (entities.size() == 0)
                        {
                            isRunning = false; // Nếu player mất hết người thân thì thua
                            Mix_FreeMusic(bgMusic);
                            SDL_Rect defeatRect {Globals::SCREEN_GAME_WIDTH/2 - 200,Globals::SCREEN_GAME_HEIGHT/2 - 200,500,500};
                            SDL_RenderCopy(gameplay_renderer, defeatTexture, nullptr, &defeatRect);
                            SDL_RenderPresent(gameplay_renderer);
                            PlaySound(defeatSound);
                            SDL_Delay(4000);
                            break;
                        }
                    }

                }

                // Kiểm tra va chạm giữa địch và đạn
                for (size_t j = 0; j < Bullets.size(); ++j) {
                    SDL_Rect bulletRect = Bullets[j].getRect(); // Store the returned value in a local variable
                    if (SDL_HasIntersection(&enemyRect, &bulletRect)) {
                        Bullets.erase(Bullets.begin() + j);
                        Enemies.erase(Enemies.begin() + i);
                        PlaySound(enemyHitSound);
                        Points++;
                        break;
                    }
                }
            }

            // Xu ly boss
            if (SDL_GetTicks() > Globals::timeBoss)
            {
                if (SDL_GetTicks() - lastSpawnTimeBoss > spawnDelayBoss) {
                    spawnBoss(Bosses);
                    lastSpawnTimeBoss = SDL_GetTicks();
                }

                for (int i = 0; i < Bosses.size();i++)
                {

                    SDL_Rect bossRect = Bosses[i].first.getRect();
                    for (int j =  0; j < Bullets.size(); j++)
                    {
                        SDL_Rect bulletRect = Bullets[j].getRect();
                        if (SDL_HasIntersection(&bossRect, &bulletRect))
                        {
                            Bullets.erase(Bullets.begin() + j);
                            Bosses[i].second++;
                            PlaySound(enemyHitSound);
                            if (Bosses[i].second == 3)
                            {
                                Bosses.erase(Bosses.begin() + i);
                                Points += 20;
                                break;
                            }

                        }
                    }
                }
                if (SDL_GetTicks() - lastShotTime > shotDelay) {
                    spawnBossLaze(BossLazes, Bosses);
                    lastShotTime = SDL_GetTicks();
                }
                for (int i = 0; i < BossLazes.size(); i++)
                {
                    BossLazes[i].move();
                    if (BossLazes[i].getRect().x < 0)
                    {
                        BossLazes.erase(BossLazes.begin() + i);
                    }
                    SDL_Rect bosslazeRect = BossLazes[i].getRect();
                    SDL_Rect playerRect = player.getRect();
                    if (SDL_HasIntersection(&playerRect, &bosslazeRect))
                    {
                        PlaySound(playerHitSound);
                        Hearts.erase(Hearts.begin() + 0);
                        BossLazes.erase(BossLazes.begin() + i);
                        if (Hearts.size() == 0)
                        {
                            isRunning = false;
                            Mix_FreeMusic(bgMusic);
                            SDL_Rect defeatRect {Globals::SCREEN_GAME_WIDTH/2 - 200,Globals::SCREEN_GAME_HEIGHT/2 - 200,500,500};
                            SDL_RenderCopy(gameplay_renderer, defeatTexture, nullptr, &defeatRect);
                            SDL_RenderPresent(gameplay_renderer);
                            PlaySound(defeatSound);
                            SDL_Delay(4000);
                            break;
                        }
                    }
                }

            }
            string scoreText = "Points: " + to_string(Points);
            SDL_Color textScoreColor = { 255, 255, 255 };
            SDL_Texture* textScore = renderText(scoreText.c_str(), gameplay_renderer, font, textScoreColor);
            SDL_Rect textRect2 = {1200, 10, 0, 0};
            SDL_QueryTexture(textScore, nullptr, nullptr, &textRect2.w, &textRect2.h);

            //Render tat ca
            SDL_RenderClear(gameplay_renderer);
            SDL_RenderCopy(gameplay_renderer, backgroundTexture, nullptr, nullptr);
            player.update(gameplay_renderer, playerTexture);
            for (int i = 0; i < Bullets.size(); i++)
            {
                Bullets[i].update(gameplay_renderer, bulletTexture);
            }
            for (auto& enem : Enemies)
            {
                enem.render(gameplay_renderer, enemyTexture);
            }
            for (auto& ent : entities)
            {
                ent.render(gameplay_renderer, entityTexture);
            }
            for (auto& health : Hearts)
            {
                health.Render(gameplay_renderer, heartTexture);
            }
            if (SDL_GetTicks() > Globals::timeBoss)
            {
                for (auto& x : Bosses)
                {
                    x.first.render(gameplay_renderer, bossTexture);
                }
                for (auto& enemybull : BossLazes)
                {
                    enemybull.render(gameplay_renderer, bossLazeTexture);
                }
            }
            SDL_RenderCopy(gameplay_renderer, healthTexture, nullptr, &textRect1);
            SDL_RenderCopy(gameplay_renderer, textScore, nullptr, &textRect2);
            SDL_RenderPresent(gameplay_renderer);
            SDL_Delay(10);
        }
        // check Game over
        if (Points == 1000 || Points > 1000)
        {
            Mix_FreeMusic(bgMusic);
            SDL_Rect victoryRect {Globals::SCREEN_GAME_WIDTH/2 - 200,Globals::SCREEN_GAME_HEIGHT/2 - 200,500,500};
            SDL_RenderCopy(gameplay_renderer, victoryTexture, nullptr, &victoryRect);
            SDL_RenderPresent(gameplay_renderer);
            PlaySound(victorySound);
            SDL_Delay(4000);
        }
    }
    gameRunning = false;
}

bool Game::InitWindowRenderer(){
    gameplay_window = SDL_CreateWindow("Gameplay",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::SCREEN_GAME_WIDTH, Globals::SCREEN_GAME_HEIGHT, SDL_WINDOW_SHOWN);
    if (gameplay_window == nullptr)
    {
        cout << "Can not create window. Erorr: " << SDL_GetError() << endl;
        return false;

    }
    gameplay_renderer = SDL_CreateRenderer(gameplay_window, - 1, SDL_RENDERER_ACCELERATED);
    if (gameplay_renderer == nullptr)
    {
        cout << "Can not create renderer. Error: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(gameplay_renderer, 0, 0, 0, 255); // Set mau ve cho renderer
    SDL_RenderSetLogicalSize(gameplay_renderer, Globals::SCREEN_GAME_WIDTH, Globals::SCREEN_GAME_HEIGHT);
    return true;
}

SDL_Texture* Game::LoadGameTexture(SDL_Renderer* p_renderer, const char* p_filePath)
{
    SDL_Texture* newtext = IMG_LoadTexture(p_renderer, p_filePath);
    if (newtext == nullptr)
    {
        cout << "Could not load texture. Error: " << IMG_GetError() << endl;
    }
    return newtext;
}

TTF_Font* loadFont(const char* filePath, int size)
{
    TTF_Font* gFont = TTF_OpenFont(filePath, size);
    if (gFont == nullptr)
    {
        cout << "Failed to load font. Error: " << TTF_GetError() << endl;
    }
    return gFont;
}

SDL_Texture* Game::renderText(const char* text, SDL_Renderer* p_renderer, TTF_Font* font, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == nullptr)
    {
        cout << "Failed to create text surface. Error: " << TTF_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(p_renderer, textSurface);
    if (textTexture == nullptr)
    {
        cout << "Failed to create text texture. Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        return nullptr;
    }
    SDL_FreeSurface(textSurface);
    return textTexture;
}

void Game::LoadAudio()
{
    bgMusic = Mix_LoadMUS("assets/Music/Sucker.mp3");
    shootSound = Mix_LoadWAV("assets/Music/shoot.wav");
    enemyHitSound = Mix_LoadWAV("assets/Music/dead.wav");
    playerHitSound = Mix_LoadWAV("assets/Music/jinxoof.wav");
    defeatSound = Mix_LoadWAV("assets/Music/defeat.wav");
    victorySound = Mix_LoadWAV("assets/Music/victory.wav");

    if (!bgMusic || !shootSound || !enemyHitSound || !playerHitSound || !defeatSound || !victorySound)
    {
        cout << "Failed to load audio. Error: " << Mix_GetError() << endl;
    }
}

void Game::PlayMusic() {
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(bgMusic, -1); // -1 = lặp vô hạn
    }
}
void Game::PlaySound(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0); // -1 = kênh bất kỳ
}



void Game::Clean()
{
    SDL_DestroyWindow(gameplay_window);
    SDL_DestroyRenderer(gameplay_renderer);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(entityTexture);
    SDL_DestroyTexture(bossTexture);
    SDL_DestroyTexture(bossLazeTexture);
    TTF_CloseFont(font);
    Mix_FreeChunk(shootSound);
    Mix_FreeChunk(enemyHitSound);
    Mix_FreeChunk(playerHitSound);
    Mix_FreeChunk(defeatSound);
    Mix_FreeChunk(victorySound);
}

