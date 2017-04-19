#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h> 

double *A;
int num_threads = 2;
int N = 33554432; //2^25
int ocurrencia = 0;
double buscar = 1;

double maximun_value;
double minimun_value;

pthread_mutex_t A_lock; 

//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}


void *find_max_min(void *aux){
	int id = *(int*)aux;
	int i;
	double my_min = A[0], my_max = A[0];
	int limite = N/num_threads;
	int base = id*limite;
	int fin = (id+1)*limite;
	//printf("%d %d %d\n",id,base,fin);
	for(i = base;i < fin; i++ ){
		if(A[i] > my_max){
			my_max = A[i];
		}else if(A[i] < my_min){
			my_min = A[i];
		}
	}
	pthread_mutex_lock(&A_lock);
	if (my_min < minimun_value) minimun_value = my_min;
	if (my_max > maximun_value) maximun_value = my_max;
	pthread_mutex_unlock(&A_lock);
	//printf("Soy el hilo %d y encontre: %d ocurrencias de %0lf\n",id,auxOcurrencia,auxBuscar);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		return 1;
	}
	num_threads = atoi(argv[1]);
	double timetick;
	int i;
	int ids[num_threads];
	for(i = 0; i < num_threads; i++){
		ids[i] = i;
	}
	A=(double*)malloc(sizeof(double)*N);
	for(i = 0; i < N; i++){
		A[i] = 5;
	}
	A[352] = 1.0;
	A[23554432] = 48612.0;
		
	maximun_value = A[0];
	minimun_value = A[0];

	pthread_t p_threads[num_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutex_init(&A_lock, NULL); 

	for(i=0; i< num_threads; i++){
		pthread_create(&p_threads[i], &attr, find_max_min, (void*) &ids[i]);
	}
	timetick = dwalltime();
	for(i=0; i< num_threads; i++){
		pthread_join(p_threads[i], NULL);
	}
	
	//printf("%d\n",ocurrencia);
	printf("Tiempo en segundos %f\n", dwalltime() - timetick);
	//printf("%0lf\n",minimun_value);
	//printf("%0lf\n",maximun_value);
	free(A);
	
	return 0;
}
