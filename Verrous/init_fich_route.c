#include <route.h>
/*! 
 * \file init_fich_route.c
 * \brief Programme d'initialisation d'un fichier route
 */

/*! Programme principal */
int
main( int nb_arg , char * tab_arg[] )
{
     int no_err = 0 ;
     char fich_route[256] ;
     char nomprog[128] ;
     int longueur = 0 ;

     /*----------*/

     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <nom fichier route> <longueur route>\n",
		   tab_arg[0] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_route , tab_arg[1] );
     sscanf( tab_arg[2] , "%d" , &longueur );


#ifdef _DEBUG_
     printf( "%s --> Initialisation de %s[%d]\n",
	     nomprog , fich_route, longueur) ;
#endif
     /*
      * Creation route 
      */

     if( (no_err = route_initialiser( fich_route,longueur)) )
     {
	  fprintf( stderr, "%s : erreur %d dans route_initialiser : impossible de creer %s[%d]\n",
		   nomprog , no_err , fich_route , longueur );
	  exit(no_err) ;
     }

 
#ifdef _DEBUG_
     {
	  int fd_route ;

	  /* Ouverture fichier aire de jeu */
	  if( ( fd_route = open( fich_route , O_RDWR , 0644 )) == -1 )
	  {
	       fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fich_route);
	       exit(-1);
	  }

	  /* Affichage aire de jeu */
	  if( (no_err = route_afficher(fd_route) )) 
	  {
	       fprintf( stderr, "%s : erreur %d dans route_afficher\n",
			nomprog , no_err );
	       exit(no_err) ;
	  }

	  /* Fermeture fichier aire de jeu */
	  close(fd_route); 
     }

     printf( "%s --> Initialisation de %s[%d] Reussie\n",
	     nomprog , fich_route, longueur ) ;
#endif

     exit(0);

}
