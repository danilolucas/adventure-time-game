#include <allegro.h>

void init();
void deinit();
void reset();
void buffer();
void move();
void gravity();
void colisao(int, int, int, int);
void movementAnimation();
void fisica();
void descida();

BITMAP *BackGround;
BITMAP *Buffer;
BITMAP *finn;

bool jump=false;
bool jumpval=true;
int atualPos;

struct player{
    int x;
    int y;
    int val;
    int direc;
    int direction;
    int pixelY;
    int pixelX;
    int pos;
    BITMAP *image;
};

player player1;

int main(){

    init();

	reset();

    //Timers
	install_int(buffer, 10);
	install_int(move, 5);
	install_int(gravity, 3);
	install_int(fisica, 1);
	install_int(movementAnimation, 180);

	while (!key[KEY_ESC]){
		/* put your code here */
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

void reset(){
     Buffer=create_bitmap(1280, 720);
     player1.image=load_bitmap("animation/finnwalk.bmp", NULL);     

     player1.x=20;
     player1.y=330;
     
     player1.direction=0;
     
     player1.pixelY=0;
     player1.pixelX=0;
     player1.pos=1;
     player1.direc=2;

     BackGround = load_bitmap("texture/map1.bmp", NULL);
}

void buffer(){
     draw_sprite(Buffer, BackGround, 0, 0);
     masked_blit(player1.image, Buffer, player1.pixelX, player1.pixelY, player1.x, player1.y, player1.image->w/4, player1.image->h/3);
     draw_sprite(screen, Buffer, 0, 0);
     clear_bitmap(Buffer);
}

void move(){  
    if(key[KEY_RIGHT]){
        player1.x++;
        player1.pos=1;
        player1.direction=1;
    }
    else        
        if(key[KEY_LEFT]){
            player1.x--;
            player1.pos=2;
            player1.direction=2;
        }
        else{
            player1.direction=0;
        }
        
    if(key[KEY_UP]){
        jump=true;
    }    
}

void gravity(){  //aplicas double jump
    player1.y++;     
    if(jump==true){
        if(jumpval==true){
            player1.y-=2;
            if(player1.y<atualPos-100)
                jumpval=false; 
            player1.direction=3;
            player1.direc=1;
        }
        else{
            player1.direction=3;
            player1.direc=2;
            jump=false;
        }
    }
}

void fisica(){
     //fisica das paredes principais
    if(player1.x<=0)
        player1.x++;
    if(player1.x>=767)
        player1.x--;
    //queda no buraco
    if(player1.y>=800){
        player1.x=20;
        player1.y=328;
    }
    
    //fisica dos objetos...
    colisao(334, 600, 0, 55);
    descida();  
    colisao(367, 600, 0, 310);  
    colisao(430, 600, 435, 800);
}

void movementAnimation(){
    if(player1.direction==0){
        if(player1.pos==1){
            player1.pixelX+=32;
            player1.pixelY=100;
            if(player1.pixelX>=64){
                player1.pixelX=0;
            }
        }
        else
            if(player1.pos==2){
                player1.pixelX+=32;
                player1.pixelY=100;
                if(player1.pixelX>=128){
                    player1.pixelX=64;
                }       
            }
    }
    else
        if(player1.direction==1){
            player1.pixelX+=32;
            player1.pixelY=0;
            if(player1.pixelX>=128){
                player1.pixelX=0;
            }
        }
        else
            if(player1.direction==2){
                player1.pixelX+=32;
                player1.pixelY=50;
                if(player1.pixelX>=128){
                    player1.pixelX=0;
                }            
            }
            else
                if(player1.direction==3){
                    player1.pixelX=32;             
                }
}

void colisao(int t, int h, int l, int w){
     //colisao UP
     if(player1.direc==1){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.y++;
     }
     //colisao DOWN
     if(player1.direc==2){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else{
             player1.y--;
             jumpval=true;
             atualPos=player1.y;
         }
     }
     //colisao RIGHT
     if(player1.direc==3){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.x--;                          
     }
     //colisao LEFT
     if(player1.direc==4){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.x++;  
     }     
}

void descida(){
    colisao(336, 600, 0, 60);
    colisao(339, 600, 0, 65);
    colisao(342, 600, 0, 70);
    colisao(345, 600, 0, 75);
    colisao(348, 600, 0, 80);
    colisao(351, 600, 0, 85);
    colisao(354, 600, 0, 90);
    colisao(357, 600, 0, 95);
    colisao(360, 600, 0, 100);
    colisao(363, 600, 0, 105);
    colisao(366, 600, 0, 110);
    colisao(369, 600, 0, 115);
    colisao(372, 600, 0, 120);
    colisao(375, 600, 0, 125);
}
