#CFLAGS = -DCEU_RUNTESTS -DCEU_DEBUG #-DCEU_DEBUG_TRAILS

all:
	ceu --cpp-args "-I ." $(CEUFILE)
	#gcc main.c $(CFLAGS) -lSDL2
	gcc -g -Os main.c $(CFLAGS) -lpthread -lm \
		-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net -lSDL2_gfx \
		-o $(basename $(CEUFILE)).exe

demo:
	ceu --cpp-args "-I . -DALL" samples/all.ceu
	#gcc main.c $(CFLAGS) -lSDL2
	gcc -g -Os main.c -DALL $(CFLAGS) -lpthread -lm \
		-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net -lSDL2_gfx \
		-o samples/all.exe

ui-scroll:
	ceu --cpp-args "-D __UI_SCROLL_CEU" ui-scroll.ceu
	gcc -g main.c $(CFLAGS) -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lm

ui-grid:
	ceu --cpp-args "-D __UI_GRID_CEU" ui-gridApp.ceu
	gcc -g main.c $(CFLAGS) -lSDL2 -lSDL2_gfx -lm

ui-texture:
	ceu --cpp-args "-D __UI_TEXTURE_CEU" ui-texture.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm

lui-number:
	ceu --cpp-args "-D __LUI_NUMBER_CEU" lui-number.ceu
	gcc main.c $(CFLAGS)  -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-number.exe    

lui-string:
	ceu --cpp-args "-D __LUI_STRING_CEU" lui-string.ceu
	gcc main2.c $(CFLAGS) -lm -llua5.1 -o lui-string.exe

lui-table:
	ceu --cpp-args "-D __LUI_TABLE_CEU" lui-table.ceu
	gcc main2.c $(CFLAGS) -lm -llua5.1 -o lui-table.exe

lui-quad:
	ceu --cpp-args "-D __LUI_QUAD_CEU" lui-quad.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-quad.exe

lui-img:
	ceu --cpp-args "-D __LUI_IMG_CEU" lui-img.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-img.exe

lui-text:
	ceu --cpp-args "-D __LUI_TEXT_CEU" lui-text.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-text.exe

lui-demo:
	ceu --cpp-args "-D __LUI_DEMO_CEU" lui-demo.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-demo.exe

lui-texture:
	ceu --cpp-args "-D __LUI_TEXTURE_CEU -D __LUI_SDL" lui-texture.ceu
	gcc main.c $(CFLAGS) -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lm -llua5.1 -o lui-texture.exe

lui-grid:
	ceu --cpp-args "-D __LUI_GRID_CEU -D __LUI_SDL" lui-gridApp.ceu
	gcc -g main.c $(CFLAGS) -lSDL2 -lSDL2_gfx -lm -llua5.1 -o lui-grid.exe

clean:
	find . -name "*.exe"  | xargs rm -f
	find . -name "_ceu_*" | xargs rm -f

.PHONY: all clean
