#include "../include/rooms.h"

// Implementation in which a Monte Carlo method is used.
void rooms(int N, int*** D, int iter, int** ret, int processes){
    int N2 = N/2;
    int** retAux = malloc(sizeof(int*) * processes);
    for(int i = 0; i < processes; i++)
        retAux[i] = malloc(sizeof(int) * 2);

    #pragma omp parallel num_threads(processes)
    {
        int** room;
        int id, i, c, d, delta, aux;
        unsigned int myseed = rand();
        id = omp_get_thread_num();
        retAux[id][0] = 0;
        retAux[id][1] = 0;

        //First we initialize the rooms with random occupants
        randPerm(N, &room, myseed);

        //Next, we calculate the cost of this distribution
        for(i = 0; i < N2; i++)
            retAux[id][0] += (*D)[room[i][0]][room[i][1]];

        i = 0;

        /*After this, we'll try to see if it is possible to obtain a better distribution,
          by switching the occupants of different random places*/
        while(i < iter){
            (retAux[id][1])++;

            //Selecting the random occupant
            c = (rand_r(&myseed))%N2;

            //The occupant selected will switch with one in the next room
            if(c == N2-1)
                d = 0;
            else
                d = c+1;
        
            //Determining the difference between the old cost and the new one
            delta = ((*D)[room[c][0]][room[d][1]]+(*D)[room[d][0]][room[c][1]]) - ((*D)[room[c][0]][room[c][1]]+(*D)[room[d][0]][room[d][1]]);

            //If the difference is negative, then the switch will improve the cost, so it is accepted
            if(delta < 0){
                aux = room[c][1];
                room[c][1] = room[d][1];
                room[d][1] = aux;

                retAux[id][0] += delta;

                i = 0;
            }
            else
                i++;
        }
    }

    (*ret)[0] = retAux[0][0];
    (*ret)[1] = retAux[0][1];

    for(int i = 1; i < processes; i++){
        if(retAux[i][0] < (*ret)[0]){
            (*ret)[0] = retAux[i][0];
            (*ret)[1] = retAux[i][1];
        }
    }
}