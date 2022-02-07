#define CARS_N 
#define LANE_N

long frames;

typedef struct CAR
{
    int x;              //Poscion del auto (se usa para velocidad tambien).
    int lane;           //Carril del auto.
    //int type
    bool used;          //Marca disponibilidad en el array.
}CAR;

bool lanes[5];          //Array de carriles.

CAR cars[CARS_N];       //Array de autos.

void cars_init()
{
    for(int i = 0; i < CARS_N; i++)
        cars[i].used = false;           //Inicio array de autos desocupando.
}

void lanes_init()
{
    for(int i = 0; i < LANE_N; i++)
        lanes[i] = false;               //Inicio array de carriles desocupando.
}

void cars_update()
{
    int new_quota =                 //2 a 5 autos cada 120 frames.
        (frames % 120)
        ? 0
        : between(2, 5)
    ;

    int temp_quota = new_quota;     //Para guardar cuantos autos salen en la cuota.

    lanes_init();                   //Vacio el array de carriles para usarlo cada vez.

    for(int i = 0; i < CARS_N; i++)
    {
        //Spawneo de autos.
        if(!cars[i].used)           //Lugar libre?
        {
            if(new_quota > 0)       //Hay autos para salir.
            {
                cars[i].lane = between(1, 5);           //Asigno carril.

                if(lanes[cars[i].lane - 1] == false)
                    lanes[cars[i].lane - 1] = true;     //Marco el carril ocupado.
                else
                {
                    while(lanes[cars[i].lane - 1] == true)      //Verifico que no se repitan autos del mismo bache en los carriles.
                    {
                        cars[i].lane = between(1, 5);

                        if(lanes[cars[i].lane - 1] == false)
                        {
                            lanes[cars[i].lane - 1] = true;
                            break;
                        }
                    }
                }

                //Las posiciones iniciales son tales que se dinujan afuera de la pantalla inicialmente.
                if(cars[i].lane == between(1, 5))
                    cars[i].x = BUFFER_W;           //Empiezan los autos en la derecha en algunos carriles aleatorios.

                else
                    cars[i].x = 0 - CAR_W;          //En el resto empiezan desde la izquierda
                
                //cars[i].type
                cars[i].used = true;            //Marco el lugar ocupado.

                new_quota--;
            }
            continue;
        }
        if (cars[i].x == BUFFER_W)              //Si empiezan en la derecha avnazan hacia la izquierda.
        {
            if(cars[i].lane % 2 != 0)       //Avanzan mas rapido en los carriles impares.
                cars[i].x--;
            else                            //Avanzan mas lento en los carriles pares.
            {
                if(frames % 2)
                    cars[i].x--;
            }
        }
        else                                    //Si empiezan desde la izquierda avanzan hacia la dereha.
        {
            if(cars[i].lane % 2 != 0)       
                cars[i].x++;
            else
            {
                if(frames % 2)
                    cars[i].x++;
            }
        }
        if((cars[i].x <= BUFER_W - (CAR_W + 1) || (cars[i].x >= (BUFER_W + 1))      //Libero el espacio en el array cuando los autos salesn de la pantalla + 1.       
            cars[i].used = false;
            continue;
    }
}

void cars_draw()
{
    for(int i = 0; i < CARS_N; i++)
    {
        if(!cars[i].used)
            continue;

        al_draw_bitmap("car_spritesheet.png", cars[i].x, BUFFER_H/14 + 8 + cars[i].lane, 0);    //Dibujo los autos en sus carriles.
    }
}
