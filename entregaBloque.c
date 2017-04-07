#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

//Dimension por defecto de las matrices

//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}


//Multiplicacion por bloques de matrices AxB y multiplica lo guarda en C y devuelve el promedio de A
double productoConPromedioPrimeraMatriz(double *A,double *B,double *C, int r,int N,int sizeMatrix, int sizeBlock ){
   int I,J,K,i,j,k;
	int despA, despB, despC,desp;
	double prom;

	prom = 0.0;

 for (i=0; i<sizeMatrix ;i++)
	  C[i]=0.0;
 
	for (I=0;I<N;I++){
		for (J=0;J<N;J++){
			despC = (I*N+J)*sizeBlock;
			for (K=0;K<N;K++){
				despA = (I*N+K)*sizeBlock;
				despB = (K*N+J)*sizeBlock;
				for (i=0;i<r;i++){
					for (j=0;j<r;j++){
						desp = despC + i*r+j;
						for (k=0;k<r;k++){
							C[desp] += A[despA + i*r+k]*B[despB + k*r+j]; 
						};
					};
				};
			};
			for (i=0;i<r;i++){
				for (j=0;j<r;j++){
					desp = despC + i*r+j;
					prom += A[desp];
				};
			};	
		}; 
	};
	return prom / sizeMatrix  ;
}

//Multiplicacion por bloque de matrices AxB y multiplica lo guarda en C y devuelve el promedio de B
double productoConPromedioSegundaMatriz(double *A,double *B,double *C, int r,int N,int sizeMatrix, int sizeBlock){
   int I,J,K,i,j,k;
	int despA, despB, despC,desp,save;
	double prom;


	save = 0;
	prom = 0.0;

 for (i=0; i<sizeMatrix ;i++)
	  C[i]=0.0;
 
	for (I=0;I<N;I++){
		for (J=0;J<N;J++){
			despC = (I*N+J)*sizeBlock;
			for (K=0;K<N;K++){
				despA = (I*N+K)*sizeBlock;
				despB = (K*N+J)*sizeBlock;
				for (i=0;i<r;i++){
					for(j=0;j<r;j++);
					for (j=0;j<r;j++){
						desp = despC + i*r+j;
						for (k=0;k<r;k++){
							C[desp] += A[despA + i*r+k]*B[despB + k*r+j]; 
						};
					};
				};
			};
			for (i=0;i<r;i++){
				for (j=0;j<r;j++){
					desp = despC + i*r+j;
					prom += B[desp];
				};
			};	
		}; 
	};
	return prom / sizeMatrix  ;
}


//Multiplicacion por bloque de matrices AxB y multiplica por un numero prom y lo guarda en C
void productoYPromedio(double *A,double *B,double *C, int r,int N,int sizeMatrix, int sizeBlock, double prom){
   int I,J,K,i,j,k;
	int despA, despB, despC,desp;
 for (i=0; i<sizeMatrix ;i++)
	  C[i]=0.0;
 
	for (I=0;I<N;I++){
		for (J=0;J<N;J++){
			despC = (I*N+J)*sizeBlock;
			for (K=0;K<N;K++){
				despA = (I*N+K)*sizeBlock;
				despB = (K*N+J)*sizeBlock;
				for (i=0;i<r;i++){
					for (j=0;j<r;j++){
						desp = despC + i*r+j;
						for (k=0;k<r;k++){
							C[desp] += A[despA + i*r+k]*B[despB + k*r+j] * prom; 
						};
					}
				};
			};
		};	
	}; 
}


//Suma por bloques A + B y lo guarda en C
void sumar(double *A,double *B,double *C, int r,int N,int sizeMatrix, int sizeBlock){
 int I,J,K,i,j,k;
 int despC,desp;
 for (i=0; i<sizeMatrix ;i++)
	  C[i]=0.0;
 
	for (I=0;I<N;I++){
		for (J=0;J<N;J++){
		despC = (I*N+J)*sizeBlock;
			for (i=0;i<r;i++){
				for (j=0;j<r;j++){
					desp = despC + i*r+j;
					C[desp] += A[desp]+B[desp] ;
					};
				}
			};
		};	
	} 



int main(int argc,char*argv[]){

if (argc < 3){
  printf("\n Falta un parametro ");
  printf("\n 1. Cantidad de bloques por dimension ");
  printf("\n 2. Dimension de cada bloque ");
  return 0;
}

 int N = atoi(argv[1]);
 int r = atoi(argv[2]);

 int n = N*r; //dimension de la matriz
 int sizeMatrix=n*n; //cantidad total de datos matriz
 int sizeBlock=r*r; //cantidad total de datos del bloque


	 double *A,*B,*C,*D,*E,*F,*R1,*R2;
	 double promD,promB;
	 int i,j,k;
	 double timetick;

 //Aloca memoria para las matrices
  A=(double*)malloc(sizeof(double)*sizeMatrix);
  B=(double*)malloc(sizeof(double)*sizeMatrix);
  C=(double*)malloc(sizeof(double)*sizeMatrix);
  D=(double*)malloc(sizeof(double)*sizeMatrix);
  E=(double*)malloc(sizeof(double)*sizeMatrix);
  F=(double*)malloc(sizeof(double)*sizeMatrix);
  R1=(double*)malloc(sizeof(double)*sizeMatrix);
  R2=(double*)malloc(sizeof(double)*sizeMatrix);

 //Inicializa las matrices A y B en 1, el resultado sera una matriz con todos sus valores en N
  for(i=0;i<sizeMatrix;i++){
	    A[i] = 1;
      B[i] = 2;
      C[i] = 3;
      D[i] = 4;
      E[i] = 2;
      F[i] = 3;
  }
//Realiza la multiplicacion
//i*N+j por fila
//i+N*j por columna

  timetick = dwalltime();
	//R1 = AxB
  promB = productoConPromedioSegundaMatriz(A,B,R1,r,N,sizeMatrix,sizeBlock);

  //R2 = DxE
 	promD = productoConPromedioPrimeraMatriz(D,E,R2,r,N,sizeMatrix,sizeBlock);

  //B = R1xC
 	productoYPromedio(R1,C,B,r,N,sizeMatrix,sizeBlock,promD);

	//D = R2xF
 	productoYPromedio(R2,F,D,r,N,sizeMatrix,sizeBlock,promB);



	
	//C = B + D
	sumar(B,D,C,r,N,sizeMatrix,sizeBlock);


 printf("Tiempo en segundos %f\n", dwalltime() - timetick);
 printf("Por Bloque\n");

//Imprime los promedios con las matrices resultantes
/*
	printf("%2lf\n",promB);
	printf("%2lf\n",promD);
	for(i=0;i<sizeMatrix;i++){
		printf("%2lf|",B[i]);	
	}
	printf("\n");
	for(i=0;i<sizeMatrix;i++){
		printf("%2lf|",D[i]);	
	}
	printf("\n");
	for(i=0;i<sizeMatrix;i++){
		printf("%2lf|",C[i]);	
	}
	printf("\n");
*/

N = n;

  for(i=0;i<N*N;i++){
	    A[i] = 1;
      B[i] = 2;
      C[i] = 3;
      D[i] = 4;
      E[i] = 2;
      F[i] = 3;
  }

double sumB, sumD;

 timetick = dwalltime();

//AxB
  sumB =  0.0;
  for(i=0;i<N;i++){
   for(j=0;j<N;j++){
    R1[i*N+j] = 0;
    sumB += B[i+N*j];
    for(k=0;k<N;k++){
      R1[i*N+j] += A[i*N+k] * B[k+N*j];  //A x Filas, B x columnas, R1 x filas
    }
   }
  }
  promB = sumB / (N*N);

  //DxE
  sumD =  0.0;
  for(i=0;i<N;i++){
   for(j=0;j<N;j++){
    R2[i*N+j] = 0;
    sumD += D[i+N*j];
    for(k=0;k<N;k++){
      R2[i*N+j] += D[i*N+k] * E[k+N*j];  //D x Filas, E x columnas, R2 x filas
    }
   }
  }
  promD = sumD / (N*N);

  //R1xC
    for(i=0;i<N;i++){
     for(j=0;j<N;j++){
      B[i*N+j] = 0;
      for(k=0;k<N;k++){
        B[i*N+j] += R1[i*N+k] * C[k+N*j];  //R1 x Filas, C x columnas
      }
     B[i*N+j] *= promD;
     }
    }

    //R2xF
      for(i=0;i<N;i++){
       for(j=0;j<N;j++){
        D[i*N+j] = 0;
        for(k=0;k<N;k++){
          D[i*N+j] += R2[i*N+k] * F[k+N*j];  //R2 x Filas, F x columnas
        }
       D[i*N+j] *= promB;
       }
      }

	
		//B+D
    for(i = 0; i < N*N; i++){
      C[i] = B[i] + D[i];
    }


 printf("Tiempo en segundos %f\n", dwalltime() - timetick);
 printf("Normal\n");


/*	

		for(i=0;i<N*N;i++){
			printf("%2lf|",B[i]);	
		}

		printf("\n");

		for(i=0;i<N*N;i++){
			printf("%2lf|",D[i]);	
		}
		printf("\n");

		for(i=0;i<N*N;i++){
			printf("%2lf|",C[i]);	
		}

		printf("\n");
*/

 free(A);
 free(B);
 free(C);
 free(D);
 free(E);
 free(F);
 return(0);
}
