#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h> 

double *A;
int num_threads = 2;
int N = 33554432; //2^25
int ocurrencia = 0;
double buscar = 1;

pthread_mutex_t sumando; 

//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}


void *calculate_prod(void *aux){
	int id = *(int*)aux;
	int i, auxOcurrencia = 0;
	double auxBuscar = buscar;
	int limite = N/num_threads;
	int base = id*limite;
	int fin = (id+1)*limite;
	//printf("%d %d %d\n",id,base,fin);
	for(i = base;i < fin; i++ ){
		if(A[i] == auxBuscar) auxOcurrencia++;		
	}
	pthread_mutex_lock(&sumando);
	ocurrencia += auxOcurrencia;
	pthread_mutex_unlock(&sumando);
	//printf("Soy el hilo %d y encontre: %d ocurrencias de %0lf\n",id,auxOcurrencia,auxBuscar);
}

int main(int argc, char *argv[]){
	if(argc != 3){
		return 1;
	}
	buscar = atoi(argv[1]);
	num_threads = atoi(argv[2]);
	double timetick;
	int i;
	int ids[num_threads];
	for(i = 0; i < num_threads; i++){
		ids[i] = i;
	}
	A=(double*)malloc(sizeof(double)*N);
	for(i = 0; i < N; i++){
		A[i] = i;
	}
	A[1] = 3.0;
	A[352] = 3.0;
	A[23554432] = 3.0;
	
	pthread_t p_threads[num_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutex_init(&sumando, NULL); 

	for(i=0; i< num_threads; i++){
		pthread_create(&p_threads[i], &attr, calculate_prod, (void*) &ids[i]);
	}
	timetick = dwalltime();
	for(i=0; i< num_threads; i++){
		pthread_join(p_threads[i], NULL);
	}
	
	//printf("%d\n",ocurrencia);
	 printf("Tiempo en segundos %f\n", dwalltime() - timetick);
	free(A);
	
	return 0;
}
