#include "../include/auxiliar.h"
#include "../include/rooms.h"

int main(int argc, char* argv[]){

    if(argc < 4){
        printf("<program> #PERSONS #PROCESSES #MODE\n");
        printf("Values of #MODE:\n");
        printf("    a        - All different implementations, with the standard values\n");
        printf("    i #ITER  - Monte Carlo and SA implementation, using ITER iterations\n");
        printf("    t #TEMP  - SA implementation, with TEMP temperature\n");
        printf("    f #VALUE - SA implementation, with the decreasing function being T = VALUE*T\n");
        return 1;
    }

    int N = atoi(argv[1]);

    if(N%2 != 0){
        printf("The number of persons must not be an odd number.\n");
        return 1;
    }

    int processes = atoi(argv[2]);
    int iter = 100;
    double temp = 1, value = 0.999, exectime;
    int* ret = malloc(sizeof(int) * 2);
    int** D;

	srand(time(NULL));

    initD(N, &D);

    switch(argv[3][0]){
        case 'a':            
            for(int i = 0; i < 10; i++){
                clearCache();
                startTimer();
                rooms(N, &D, iter, &ret, processes);
                exectime = stopTimer();
                printf("MC,%d,%d,%lf\n", ret[0], ret[1], exectime);
            }

            for(int i = 0; i < 10; i++){
                clearCache();
                startTimer();
                roomsSA(N, &D, iter, temp, value, &ret, processes);
                exectime = stopTimer();
                printf("SA,%d,%d,%lf\n", ret[0], ret[1], exectime);
            }

            for(int i = 0; i < 10; i++){
                clearCache();
                startTimer();
                roomsGreedy(N, &D, &ret, processes);
                exectime = stopTimer();
                printf("Greedy,%d,,%lf\n", ret[0], exectime);
            }

            break;

        case 'i':
            if (argc == 5){
                iter = atoi(argv[4]);

                for(int i = 0; i < 10; i++){
                    clearCache();
                    startTimer();
                    rooms(N, &D, iter, &ret, processes);
                    exectime = stopTimer();
                    printf("MC,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
                
                for(int i = 0; i < 10; i++){
                    clearCache();
                    startTimer();
                    roomsSA(N, &D, iter, temp, value, &ret, processes);
                    exectime = stopTimer();
                    printf("SA,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
            }
            break;

        case 't':
            if (argc == 5){
                temp = strtod(argv[4], NULL);
                
                for(int i = 0; i < 10; i++){
                    clearCache();
                    startTimer();
                    roomsSA(N, &D, iter, temp, value, &ret, processes);
                    exectime = stopTimer();
                    printf("SA,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
            }
            break;

        case 'f':
            if (argc == 5){
                value = strtod(argv[4], NULL);
                
                for(int i = 0; i < 10; i++){
                    clearCache();
                    startTimer();
                    roomsSA(N, &D, iter, temp, value, &ret, processes);
                    exectime = stopTimer();
                    printf("SA,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
            }
            break;
        
        case 'p':
            for(int p = 1; p <= processes; p++)           
            {
                printf("\n%d Threads\n", p);
                for(int i = 0; i < 10; i++)
                {
                    clearCache();
                    startTimer();
                    rooms(N, &D, iter, &ret, p);
                    exectime = stopTimer();
                    printf("MC,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
                for(int i = 0; i < 10; i++)
                {
                    clearCache();
                    startTimer();
                    roomsSA(N, &D, iter, temp, value, &ret, p);
                    exectime = stopTimer();
                    printf("SA,%d,%d,%lf\n", ret[0], ret[1], exectime);
                }
                for(int i = 0; i < 10; i++)
                {
                    clearCache();
                    startTimer();
                    roomsGreedy(N, &D, &ret, p);
                    exectime = stopTimer();
                    printf("Greedy,%d,,%lf\n", ret[0], exectime);
                }
            }

            break;
            
        default:
            printf("Not a valid parameter.\n");
            break;
    }

    return 0;
}