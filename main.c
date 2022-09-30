#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define SIZE 512
 
int main( int argc, char **argv )
{
  pid_t pid1;
  int p1[2], readbytes1;
  char buffer1[SIZE];
 
  pipe( p1 );
 
  if ( (pid1=fork()) == 0 )
  { // hijo
	  
    close( p1[1] ); /* cerramos el lado de escritura del pipe */
 
    while( (readbytes1=read( p1[0], buffer1, SIZE )) > 0)
      write( 1, buffer1, readbytes1 );
 
    close( p1[0] );
    exit(0);
  }
  
  
  pid_t pid2;
  int p2[2], readbytes2;
  char buffer2[SIZE];
 
  pipe( p2 );
 
  if ( (pid2=fork()) == 0 )
  { // hijo
	  
    close( p2[1] ); /* cerramos el lado de escritura del pipe */
	printf("aaa\n");
    while( (readbytes2=read( p2[0], buffer2, SIZE )) > 0)
      write( 1, buffer2, readbytes2 );
    close( p2[0] );
    exit(0);
  }
   
  
  
  

  else
  { // padre
	  while(1){ /*aca colocar el criterio de parada, ya que el padre estara constantemente enviando intrucciones a los hijos*/
		close( p1[0] ); /* cerramos el lado de lectura del pipe 1 */
		close( p2[0] ); /* cerramos el lado de lectura del pipe 2 */
		
		strcpy( buffer1, "Esto llega a traves de la tuberia 1\n" );  /*esto se envia al proceso hijo 1*/
		strcpy( buffer2, "Esto llega a traves de la tuberia 2\n" );	/*esto se envia al proceso hijo 2*/
		
		write( p1[1], buffer1, strlen( buffer1 ) );
		write( p2[1], buffer2, strlen( buffer2 ) );
	 

  }
  		close( p1[1] ); /*aca se cierran los pipes*/
		close( p2[1] );
}
  waitpid( pid1, NULL, 0 );
  waitpid( pid2, NULL, 0 );
  exit( 0 );
}
