
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pidA; //Creamos el pid para guardar el retorno del fork

    int tuberiaA[2];	//Creamos la variable para el pipe  
	  pipe(tuberiaA);  //Creamos el pipe
	  
    pidA = fork(); //Hacemos fork para crear el proceso hijo A

    
    if (pidA < 0){ //Ocurrio un error
        printf("Fallo el fork A");
        return 1;
    }
    

    
    
    else if (pidA == 0){ //Este es el proceso hijo A
        printf("Soy el proceso hijo A, mi PID es %d\n",getpid());
        int buffer[2]; //Variable para lectura
		    close(tuberiaA[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
        while(1){
      			read(tuberiaA[0],buffer,2*sizeof(int)); //Leemos datos del pipe, dos int cada vez
      			i++;
      			if (i == 10){ //Queremos leer 9 veces
      				  break;
            }
      			printf("Hijo A n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
            
		    }
	exit(0);
    }
    
    
    pid_t pidB;
    int tuberiaB[2];	//Creamos la variable para el pipe  
	pipe(tuberiaB);  //Creamos el pipe
    
    pidB = fork(); //Hacemos fork para crear el proceso hijo B
    if (pidB < 0){ //Ocurrio un error
		printf("Fallo el fork B");
		return 1;
    }
    
    
    
    else if (pidB == 0){ //Este es el proceso hijo B
        printf("Soy el proceso hijo B, mi PID es %d\n",getpid());
        int buffer[2]; //Variable para lectura
		    close(tuberiaB[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
        while(1){
      			read(tuberiaB[0],buffer,2*sizeof(int)); //Leemos datos del pipe, dos int cada vez
      			i++;
      			if (i == 10){ //Queremos leer 9 veces
      				  break;
            }
      			printf("Hijo B n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
            
		    }
	exit(0);
    }

    
    else{ //Proceso padre
        int buffer[100]={1,10,1,30,2,10,5,1,5,1,4,2,5,10,0,10,0,11};		
        close(tuberiaA[0]); //Cerramos el lado de lectura del pipeA
        close(tuberiaB[0]); //Cerramos el lado de lectura del pipeA
        write(tuberiaA[1],buffer,sizeof(int)*100); //Escribimos en el pipe los datos
        write(tuberiaB[1],buffer,sizeof(int)*100);
        wait(NULL); //Esperamos al hijo
        printf("Soy el padre, mis hijos eras  PID: %d,%d, yo soy el PID: %d\n",pidA,pidB,getpid());
        
    }   
    return 0;    
}
