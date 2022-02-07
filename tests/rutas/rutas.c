//gcc rutas.c -o rutas -Wall $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags)
//./rutas

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_primitives.h>


#define WIDTH   640
#define HEIGHT  480

/* Collide
*
*
*
*/
bool collide(float ax1,float ax2,float ay1,float ay2,float bx1,float bx2,float by1,float by2);

int main(void){

    /*************************************************************************/
    if (!al_init()) { 
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) { 
        fprintf(stderr, "failed to initialize keyboard!\n");
        return -1;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();


    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
    if (!disp) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        fprintf(stderr, "failed to create fort!\n");
        return -1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    /************************************************************************

    ALLEGRO_BITMAP* image = ...;
    if(!image)
    {
       printf("couldn't load image\n");
       return 1;
    }
        ************************************************************************/
    if(!al_init_primitives_addon())
    {
        printf("couldn't initialize primitives addon\n");
        return 1;
    }

    /************************************************************************/

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    
    // Posicion PERSONAJE y bool para finalizar el analisis de mov
    int x = 0, y = 0, done = false;

    /*************************************************************************/

    //inicializamos la semilla para RND
    srand(time(NULL));

    //Igual al de los OBs, igual a un bloque del "grid"  
    #define F_SIZE 20
    //Numero de ROUTES
    #define ROUTES_N    3 
    //Igual al de la rana, igual a un bloque del "grid"  
    #define ROUTE_SIZE  20 
    //Numero de OB creados para una ROUTE, por ahora fijo despues capas varie; DEBE SER >1!, para que funcione
    #define NUM         10
    //Tipos de obstaculos
    enum OBSTACLE_TYPE {
        MOTORCICLE = 0,
        CAR,
        TRUCK,
        OB_N
    };
    /*OBJ obstaculo
    *   Posicion (x,y)
    *   Tamaño
    *   Tipo
    */
    typedef struct OBSTACLE
    {
        float x, y;
        float size;
        int type;
        bool running;
    } OBSTACLE;
    /*OBJ Arreglo de OB
    *   Frame despues del anterior para aparecer
    *   OB
    */
    typedef struct OB_ARR
    {
        int frame;
        OBSTACLE ob;
    } OB_ARR;

    /*OBJ ruta
    *   Numero de ruta
    *   Velocidad Permitida
    *   Arreglo de elementos OB_ARR, (lista de autos en la ruta)
    */
    typedef struct ROUTES
    {
        int n;
        float v;
        OB_ARR* array;
    } ROUTES;

    //Inicializacion de las rutas
    ROUTES rt[ROUTES_N];
    //Var auxiliar del arreglo de OB
    OB_ARR  r_arr[ROUTES_N][NUM];
    //Inicializacion de cada ruta por separado
    for(int i = 0; i < ROUTES_N; i++)
    {
        //Cargo Numero de ruta
        rt[i].n = i+1;
        //Cargo Velocidad Permitida pixels/frame
        rt[i].v = 1*(i+1);//FALTA DECIDIR COMO DARLE LOS V, POR UN MACRO ARRAY?? V[]={10,20,30}??
        for(int j = 0; j < NUM; j++){
            //Cargo Frame, entre 5 y los frames necesarios para estar a 1/4 de la pantalla entre auto y auto
            r_arr[i][j].frame = rand()%((WIDTH/(int)(rt[i].v))/3)+5;
            //Cargo Tipo, numero rnd entre 1 y OB_N
            r_arr[i][j].ob.type  = rand()%OB_N+1;
            //Cargo Tamaño
            r_arr[i][j].ob.size  = 15*(r_arr[i][j].ob.type);// STANDAR_SIZE*type
            //Cargo Posiciion inicial, en el comienzo de la ruta en la que se encuentra 
            r_arr[i][j].ob.x  = -r_arr[i][j].ob.size;
            r_arr[i][j].ob.y  = 100+50*i;// POS_RUTA + MAIN_SIZE*Ruta_i
            //Bloquea el movimeinto
            r_arr[i][j].ob.running  = false;
        }
        //Cargo Arreglo de elementos OB_ARR
        rt[i].array = r_arr[i];
        //REINICIALIZAMOS los #1 OBs de cada ROUTE para permitir su movimiento
        rt[i].array[0].ob.running = true;

    }
    /*for(int i = 0; i < ROUTES_N; i++){
        for(int j = 0; j < NUM; j++){
        printf("%d\n",rt[i].n);
        printf("%f\n",rt[i].v);
        printf("%d\n",rt[i].array[j].frame);
        printf("%f\n",rt[i].array[j].ob.x);
        printf("%f\n",rt[i].array[j].ob.y);
        printf("%d\n",rt[i].array[j].ob.type);
        printf("%f\n",rt[i].array[j].ob.size);
        printf("%d\n",rt[i].array[j].ob.running);
        printf("\n\n\n");
        }
    }
    */


    /*  FALTA:
    *   inicializar los obstaculos en cada ruta
    *   hacer avanzar a los objetos y que frenen cuando terminen
    *   analisis de choque **IMP**
    */

    /******************************* MAIN LOOP ********************************/

    bool redraw = true;
    //Contador de frames y contador de terminados
    int c_frame[ROUTES_N],c_run[ROUTES_N];
    //Inicializacion de todos los elementos en 0
    memset(c_frame,0,sizeof(c_frame));
    memset(c_run,0,sizeof(c_run));

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
            //Avanza el contador de frames de las N ROUTES
            for(int i = 0; i < ROUTES_N; i++)
            c_frame[i] +=1;
            
        }
        
        else if(done)
        break;

        switch(event.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    if(key[ALLEGRO_KEY_UP])
                        y-=2;
                    if(key[ALLEGRO_KEY_DOWN])
                        y+=2;
                    if(key[ALLEGRO_KEY_LEFT])
                        x-=2;
                    if(key[ALLEGRO_KEY_RIGHT])
                        x+=2;

                    if(key[ALLEGRO_KEY_ESCAPE])
                        done = true;

                    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                        key[i] &= KEY_SEEN;

                    //Avance OB (Luego dibujamos en su posicion actual)
                    for(int i = 0; i < ROUTES_N; i++){
                        for(int j = 0; j < NUM; j++){
                            //Si esta corriendo...
                            if(rt[i].array[j].ob.running){
                                //Si llego...
                                if(rt[i].array[j].ob.x >= (WIDTH + 0.5*(rt[i].array[j].ob.size)))
                                    //Para de correr
                                    rt[i].array[j].ob.running = false;
                                //Si no...
                                else
                                    //Avanza
                                    rt[i].array[j].ob.x += rt[i].v;
                                /*printf("%f\n",rt[i].array[j].ob.x);
                                printf("%f\n",rt[i].array[j].ob.y);*/
                            }
                            //Si NO esta corriendo...
                            else{
                                //Si esta en el INICIO Y suficiente distancia con el ANTEIROR...
                                if((rt[i].array[j].ob.x == -rt[i].array[j].ob.size) && (rt[i].array[j].frame <= (rt[i].array[(NUM+j-1)%NUM].ob.x)/rt[i].v)){
                                    //Permite de correr
                                    rt[i].array[j].ob.running = true;
                                    //Devuelve al inicio al PROXIMO (HAY QUE TENER CUIDADO QUE NUM SE SUF GRANDE)
                                    rt[i].array[(j+1)%NUM].ob.x = -rt[i].array[(j+1)%NUM].ob.size;
                                }
                                //Si no...
                                else
                                //NADA
                                ;

                            }
                        }
                    }
                    /*for(int i = 0; i < ROUTES_N; i++){
                        for(int j = 0; j < NUM; j++){
                        printf("%d\n",rt[i].n);
                        printf("%d\n",rt[i].array[j].ob.running);
                        printf("\n");
                        }
                    }*/

                    //Deteccion de choque
                    for(int i = 0; i < ROUTES_N; i++){
                        for(int j = 0; j < NUM; j++){
                            //Si esta corrriendo Y choca...
                            if(rt[i].array[j].ob.running == true && collide(x, x+F_SIZE, y, y+F_SIZE, rt[i].array[j].ob.x, rt[i].array[j].ob.x+rt[i].array[j].ob.size, rt[i].array[j].ob.y, rt[i].array[j].ob.y+rt[i].array[j].ob.size)){
                                //Devuelve al PESONAJE al inicio
                                x = 0;
                                y = 0;
                            }
                        }
                    }

                    redraw = true;
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    key[event.keyboard.keycode] &= KEY_RELEASED;
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done = true;
                    break;
            }

        if(redraw)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //Dibujamos el PERSONAJE/FROG
            al_draw_filled_rectangle(x-F_SIZE/2,y-F_SIZE/2,x+F_SIZE/2,y+F_SIZE/2,al_map_rgb(255,0,0));
            //Dibujamos los OBs para cada ROUTE
            for(int i = 0; i < ROUTES_N; i++){
                for(int j = 0; j < NUM; j++){
                    int x_obs = (rt[i].array[j]).ob.x;
                    int y_obs = (rt[i].array[j]).ob.y;
                    int s_obs = (rt[i].array[j]).ob.size;
                    //Si no recorrio toda la ruta...
                    if( x_obs <= (WIDTH+s_obs)){
                        al_draw_filled_rectangle(x_obs-s_obs/2, y_obs-s_obs/2, x_obs+s_obs/2, y_obs+s_obs/2, al_map_rgb(0,0,255-25*j));
                    }
                    //Si ya no hay mas OB en la ruta que deban avanzar...
                    //else
                    //Paso a la prox ROUTE
                    //break;
                    
                }
            }

            redraw = false;
                
            
            al_flip_display();
        }
    }            
    /*************************************************************************/
    
    //al_destroy_bitmap(mysha);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
//NO ESTA BIEN TODAVIA!!!!!
bool collide(float ax1,float ax2,float ay1,float ay2,float bx1,float bx2,float by1,float by2){
  /*  //Se tocan por el #1 cuadrante
    if(bx1 < ax2 && by2 > ay1)    return true;


    //Se tocan por el #2 cuadrante
    if(bx2 > ax1 && by2 > ay1)    return true;
    //Se tocan por el #3 cuadrante
    if(bx2 > ax1 && by1 < ay2)    return true;
    //Se tocan por el #4 cuadrante
    if(bx1 < ax2 && by1 < ay2)    return true;
  */
    //No se tocan
    return false;
}