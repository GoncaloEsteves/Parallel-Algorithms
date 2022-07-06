#include "../include/poisson.h"
#include "../include/auxiliar.h"

int main(int argc, char* argv[]){

    if(argc != 3){
        printf("<app> <implementation> <size>\n");
        return 0;
    }

    double** U;
    double** W;
    int N = atoi(argv[2]);
    int iter;
    double time;

    switch (argv[1][0]){
        case 'j':
            for(int i = 0; i < 5; i++){
                clearCache();

                initMatrixesJac(N, &U, &W);
               
                startTimer();
                iter = poissonJac(N, &U, &W);
                time = stopTimer();
               
                printf("%d, %2f\n", iter, time);
            }
            //printMatrix(N, &U);
            break;

        case 'g':            
            for(int i = 0; i < 5; i++){
                clearCache();

                initMatrixes(N, &W);
                
                startTimer();
                iter = poissonGS(N, &W);
                time = stopTimer();
                
                printf("%d, %2f\n", iter, time);
            }
            //printMatrix(N, &W);
            break;

        case 's':
            switch (argv[1][1]){        
                case 'G':            
                    for(int i = 0; i < 5; i++){
                        clearCache();

                        initMatrixes(N, &W);
                
                        startTimer();
                        iter = poissonGSRBSeq(N, &W);
                        time = stopTimer();
                
                        printf("%d, %2f\n", iter, time);
                    }

                    //printMatrix(N, &W);
                    break;
        
                case 's':
                    for(int i = 0; i < 5; i++){
                        clearCache();

                        initMatrixes(N, &W);
                
                        startTimer();
                        iter = poissonSORRBSeq(N, &W);
                        time = stopTimer();
                
                        printf("%d, %2f\n", iter, time);
                    }

                    //printMatrix(N, &W);
                    break;
    
                default:
                    break;
            }
            break;

        case 'p':
            switch (argv[1][1]){        
                case 'G':            
                    for(int i = 0; i < 5; i++){
                        clearCache();

                        initMatrixes(N, &W);
                
                        startTimer();
                        iter = poissonGSRBPar(N, &W);
                        time = stopTimer();
                
                        printf("%d, %2f\n", iter, time);
                    }

                    //printMatrix(N, &W);
                    break;
        

                case 's':
                    for(int i = 0; i < 5; i++){
                        clearCache();

                        initMatrixes(N, &W);
                
                        startTimer();
                        iter = poissonSORRBPar(N, &W);
                        time = stopTimer();
                
                        printf("%d, %2f\n", iter, time);
                    }

                    //printMatrix(N, &W);
                    break;
    
                default:
                    break;
            }
            break;

        default:
            break;
    }
    

    return 1;
}