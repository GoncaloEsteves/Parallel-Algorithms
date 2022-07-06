#include "../include/rooms.h"

// Implementation in which a Greedy method is used.
void roomsGreedy(int N, int*** D, int** ret, int processes){
    int* retAux = malloc(sizeof(int) * processes);

    #pragma omp parallel num_threads(processes)
    {
        int** room = malloc(sizeof(int*) * (N/2));
        int* allocated = malloc(sizeof(int) * N);
        int id, i, j, toAllocate, min, aux;
        id = omp_get_thread_num();
        retAux[id] = 0;

        //Initialization of the rooms, making all of them empty
        for(i = 0; i < N/2; i++){
            room[i] = malloc(sizeof(int) * 2);

            room[i][0] = -1;
            room[i][1] = -1;
        }

        //No one is allocated to a room initially
        for(i = 0; i < N; i++)
            allocated[i] = 0;

        min = 11;
        i = 0;

        //Deciding which will be the first person to allocate
        toAllocate = rand()%N;

        //This cycle will run until all of the rooms are fill
        while(i < (N/2)){
            aux = -1;

            //Determining which is the best available option to put in a room with the chosen person (defined in "toAllocate")
            for(j = 0; j < N; j++){
                if(toAllocate != j && !(allocated[j]) && (*D)[toAllocate][j] < min){
                    min = (*D)[toAllocate][j];
                    aux = j;
                }
            }

            if(aux != -1){
                //Putting both persons into the next room available
                room[i][0] = toAllocate;
                room[i][1] = aux;

                //Updating the cost
                retAux[id] += min;

                //Marking both of them as allocated
                allocated[toAllocate] = 1;
                allocated[aux] = 1;

                j = 0;
                //Determining which will be the next person to get allocated
                while(j < N){
                    toAllocate = (toAllocate+1)%N;

                    if(!(allocated[toAllocate]))
                        j = N;
                    else
                        j++;
                }

                min = 11;
                i++;
            }

            else
                break;
        }
    }

    (*ret)[0] = retAux[0];
    (*ret)[1] = 0;

    for(int i = 1; i < processes; i++){
        if(retAux[i] < (*ret)[0]){
            (*ret)[0] = retAux[i];
        }
    }
}