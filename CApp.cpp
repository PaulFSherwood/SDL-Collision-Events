//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;

    Running = true;
}
//==============================================================================
//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if(CArea::AreaControl.OnLoad("./maps/1.area") == false) {
        return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if(Player.OnLoad("yoshi.png", 64, 64, 8) == false) {
        return false;
    }

    if(Player2.OnLoad("yoshi.png", 64, 64, 8) == false) {
        return false;
    }

    Player2.X = 100;

    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Player2);

    CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    return true;
}
//==============================================================================
//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}
//==============================================================================
//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            Player.MoveLeft = true;
            break;
        }

        case SDLK_a: {
            Player.MoveLeft = true;
            break;
        }

        case SDLK_d: {
            Player.MoveRight = true;
            break;
        }
        case SDLK_w: {
            Player.Jump();
            break;
        }

        case SDLK_RIGHT: {
            Player.MoveRight = true;
            break;
        }

        case SDLK_SPACE: {
            Player.Jump();
            break;
        }

        default: {
        }
    }
}
//==============================================================================
//==============================================================================
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            Player.MoveLeft = false;
            break;
        }

        case SDLK_RIGHT: {
            Player.MoveRight = false;
            break;
        }

        case SDLK_a: {
            Player.MoveLeft = false;
            break;
        }

        case SDLK_d: {
            Player.MoveRight = false;
            break;
        }

        default: {
        }
    }
}
//==============================================================================
//==============================================================================
void CApp::OnExit() {
    Running = false;
}

//==============================================================================
//==============================================================================
void CApp::OnLoop() {
    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }

    //Collision Events
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

        if(EntityA == NULL || EntityB == NULL) continue;

        if(EntityA->OnCollision(EntityB)) {
            EntityB->OnCollision(EntityA);
        }
    }

    CEntityCol::EntityColList.clear();

    CFPS::FPSControl.OnLoop();

    char Buffer[255];
    sprintf(Buffer, "FPS: %d", CFPS::FPSControl.GetFPS());
    SDL_WM_SetCaption(Buffer, Buffer);
}
//==============================================================================
//==============================================================================
void CApp::OnRender() {
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WWIDTH;
    Rect.h = WHEIGHT;

    SDL_FillRect(Surf_Display, &Rect, 0);

    CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnRender(Surf_Display);
    }

    SDL_Flip(Surf_Display);
}

//==============================================================================
//==============================================================================
void CApp::OnCleanup() {
    CArea::AreaControl.OnCleanup();

    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnCleanup();
    }

    CEntity::EntityList.clear();

    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}
//==============================================================================
//==============================================================================
int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}
//==============================================================================
//==============================================================================
