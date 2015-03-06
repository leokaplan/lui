#ifndef _UI_TEXTURE_CEU
#define _UI_TEXTURE_CEU
#include "ui-texture.ceu"
#include "lui.ceu"

class LUITexture with
    interface UI;
    var   _SDL_Renderer[] ren       = null;
    var char* varname;
    function (_SDL_Rect* r)=>void go;
    function (_SDL_Rect* bg, bool redim??)=>void go_bg;
do
    
    var _SDL_Texture[] tex;
    
    LUI_getstring(type,_G[@varname].type,nil);
    
    if not strcmp(type,"text") then
        _TTF_Init();
        finalize 
        with
            _TTF_Quit();
        end

        var _TTF_Font[] font;
        var int fontsize =  [[ _G[@varname].font_size or 20 ]];
        LUI_getstring(fontpath,_G[@varname].font, "Deutsch.ttf" ); 
        finalize
            font = _TTF_OpenFont( fontpath ,fontsize);
        with
            _TTF_CloseFont(font);
        end
        _assert(font != null);


        finalize
            tex = _SDL_text2texture(ren, font,_LUI_Color([[ _G[@varname].fg_clr or "black" ]], _LUI_Color([[ _G[@varname].bg_clr or "white"]]) );
        with
            _SDL_DestroyTexture(tex);
        end
    
    end
    if not strcmp(type,"img") then
        LUI_getstring(path,_G[@varname].src,nil);
        finalize
            tex = _IMG_LoadTexture(ren,path);
        with
            _SDL_DestroyTexture(tex);
        end
    end


    var UITexture ui with
        this.ren = ren;
        this.tex = tex;
        this.align_x = _LUI_Halign([[_G[@varname].horizontal_align or "left" ]]);
        this.align_y = _LUI_Valign([[_G[@varname].vertical_align or "top" ]]);
    end;
end


#ifdef __LUI_TEXTURE_CEU

#include "c.ceu"
#include "sdl-colors.ceu"

input void SDL_QUIT;

var int win_w;
var int win_h;
var _SDL_Window[] win;
    finalize
        win = _SDL_CreateWindow("UI - Texture",
                            500, 1300, 800, 480, _SDL_WINDOW_SHOWN);
    with
        _SDL_DestroyWindow(win);
    end

_SDL_GetWindowSize(win, &win_w, &win_h);
var _SDL_Rect win_r;
    win_r.x = 0;
    win_r.y = 0;
    win_r.w = win_w;
    win_r.h = win_h;

var _SDL_Renderer[] ren;
    finalize
        ren = _SDL_CreateRenderer(win, -1, 0);
    with
        _SDL_DestroyRenderer(ren);
    end


var _SDL_Rect r1, r2;

par/or do
    await SDL_QUIT;
with
    every SDL_REDRAW do
        _SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00, 0xFF);
        _SDL_RenderFillRect(ren, &win_r);
        _SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF, 0xFF);
        _SDL_RenderFillRect(ren, &r2);
        _circleRGBA(ren, win_r.w/2, win_r.h/2, 2, 0xFF,0xFF,0xFF,0xFF);
    end
with

    var LUITexture ui_txt with
        this.ren = ren;
        this.varname = "txt";
    end;

    var _SDL_Rect r_txt;
        r_txt.x = 0;
        r_txt.y = 0;
    ui_txt.go(&r_txt);

    await 1s;
/*
    ui_txt.align_bg_x = _UI_ALIGN_RIGHT;
    ui_txt.align_bg_y = _UI_ALIGN_BOTTOM;
    ui_txt.go_bg(&win_r, false);
*/
    var UITexture ui1 with
        this.ren = ren;
        this.varname = "img1";
    end;

    var UITexture ui2 with
        this.ren = ren;
        this.varname = "img2";
    end;
/*
    par do
        r1.x = 10;
        r1.y = 10;
        r1.w = 150;
        r1.h = 150;

        r2.x = 200;
        r2.y = 100;
        r2.w = 100;
        r2.h = 100;

        loop do
            native _rand();
            loop i in 500 do
                r1.x = r1.x + 1;
                r1.w = r1.w + _rand() % 3 - 1;
                if r1.w < 5 then r1.w = 5; end
                r1.h = r1.h + _rand() % 3 - 1;
                if r1.h < 5 then r1.h = 5; end
                ui1.go_bg(&r1, false);
                await 10ms;
            end

            loop i in 300 do
                r1.y = r1.y + 1;
                r1.w = r1.w + _rand() % 3 - 1;
                if r1.w < 5 then r1.w = 5; end
                r1.h = r1.h + _rand() % 3 - 1;
                if r1.h < 5 then r1.h = 5; end
                ui1.go_bg(&r1, false);
                await 10ms;
            end

            loop i in 500 do
                r1.x = r1.x - 1;
                r1.w = r1.w + _rand() % 3 - 1;
                if r1.w < 5 then r1.w = 5; end
                r1.h = r1.h + _rand() % 3 - 1;
                if r1.h < 5 then r1.h = 5; end
                ui1.go_bg(&r1, false);
                await 10ms;
            end

            loop i in 300 do
                r1.y = r1.y - 1;
                r1.w = r1.w + _rand() % 3 - 1;
                if r1.w < 5 then r1.w = 5; end
                r1.h = r1.h + _rand() % 3 - 1;
                if r1.h < 5 then r1.h = 5; end
                ui1.go_bg(&r1, false);
                await 10ms;
            end
        end
    with
        loop do
            ui2.align_x = _UI_ALIGN_CENTER;
            ui2.align_y = _UI_ALIGN_MIDDLE;
            loop i in 3 do
                loop j in 3 do
                    ui1.align_bg_x = i;
                    ui1.align_bg_y = j;
                    ui1.go_bg(&r1, false);

                    ui2.align_bg_x = i;
                    ui2.align_bg_y = j;
                    ui2.go_bg(&r2, false);

                    await 1s;
                end
            end

            var _SDL_Rect r;
                r.x = win_r.w / 2;
                r.y = win_r.h / 2;

            loop i in 3 do
                loop j in 3 do
                    ui2.align_x = i;
                    ui2.align_y = j;
                    ui2.go(&r);
                    await 1s;
                end
            end
        end
    with
        every ui1.ok_clicked do
            _printf("clicked 1\n");
        end
    with
        every ui2.ok_clicked do
            _printf("clicked 2\n");
        end
    end
*/
with
    every SDL_REDRAW do
        _SDL_RenderPresent(ren);
    end
end

escape 0;

#endif
#endif
