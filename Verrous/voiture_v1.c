#include <string.h>
#include <getopt.h>
#include <route.h>
**/*! Fonction de pause pour trace de niveau 3 */
void Pause()
{
  char s[2] ;
  printf("Tapez sur une touche pour continuer..." ); fflush(stdout) ;
  scanf( "%s" , s ) ;
}


/*!
 * \file voiture_v1.c
 * \brief Programme de déplacement d'une voiture sur une route sans dépassement 
 */

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <Fichier route> <marque voiture> <sens> <vitesse>\n" , nomprog ) ; 
  printf( "avec:\n" ) ; 
  printf( "\t<marque>  : un caractere\n" ) ; 
  printf( "\t<sens>    : O pour sens OUEST-->EST\n" ) ;
  printf( "\t            E pour sens EST-->OUEST\n" ) ;
  printf( "\t<vitesse> : L pour LENTE\n" ) ;
  printf( "\t            M pour MOYENNE\n" ) ;
  printf( "\t            R pour RAPIDE\n" ) ;
  printf( "options:\n" ) ; 
  printf( "\t--verbose=<niveau> : trace des actions (defaut = niveau 0)\n" ) ;
  printf( "\t                   niveau 0 : desactivee\n" ) ;
  printf( "\t                   niveau 1 : principale action\n" ) ;
  printf( "\t                   niveau 2 : actions sur les verrous\n" ) ;
  printf( "\t                   niveau 3 : pause apres actions sur les verrous\n" ) ; 
  printf( "\t--help             : affiche cette aide\n" ) ; 
}

static struct option longopts[] =
  {
    {"verbose", required_argument, NULL, (int)'v'},
    {"help", no_argument, NULL, (int)'h'},
    {0, 0, 0, 0}
  };

/*! Programme principal */
int
main( int argc , char * argv[] )
{
  int noerr = CORRECT ;     
  char mess[STRING_LG_MAX]; 

  /* --- Gestion des options --- */
  int opt ; 
  char nomprog[STRING_LG_MAX] ;
  int  verbose = 0 ;
  
  /* --- Route  --- */
  char fichier_route[STRING_LG_MAX] ;
  int fd_route = -1 ;

  /* --- Voiture  --- */

  voiture_t * voiture = NULL ;
  
  char marque = ' ' ;
  sens_t sens = -1 ;
  char sens_c = ' ' ;
  vitesse_t vitesse = -1 ;
  char vitesse_c = ' ' ;
  
  /*----------*/

  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "v:h", longopts, NULL)) != -1 )
    {
      switch(opt)
	{	  
	case 'v' :  /* --verbose */
	  verbose = atoi(optarg) ;
	  if( verbose > 3 )
	    {
	      printf( "Niveau de trace pour verbose incorrect : %d (doit etre < 4)\n" , verbose );
	      exit(0); 
	    }
	  break ; 

	case 'h': /* --help */
	  usage(nomprog) ;
	  exit(0);
	  break;

	case '?':
	  usage(nomprog) ;
	  exit(0);
	  break;

	default:
	  usage(nomprog) ;
	  exit(0);
	  break;
	}
    }
  argc -= optind ;
  argv += optind ;

  /* --- Parametres ---*/
  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */
  
  if( argc != 4 )
    {
      printf("%s : Nombre de parametres incorrect : %d (4 attendus)\n\n" , nomprog , argc ) ; 
      usage(nomprog) ;
      for( int i = 0 ; i<argc ; i++ )
	printf( "%s " , argv[i] ) ;
      printf("\n") ;
      
      exit(-1) ;
    }

  strcpy( fichier_route , argv[0] ) ;
  marque = argv[1][0] ;

  sens_c = argv[2][0] ;
  switch( sens_c )
    {
    case 'O' : sens = OUEST_EST ; break ;
    case 'E' : sens = EST_OUEST ; break ;
    default :
      fprintf( stderr , "%s : sens incorrect : %c (doit etre egal a O ou E)\n" , nomprog , sens_c ) ;
      exit(-1) ; 
    }
  
  vitesse_c = argv[3][0] ;
  switch( vitesse_c )
    {
    case 'R' : vitesse = RAPIDE ; break ;
    case 'M' : vitesse = MOYENNE ; break ;
    case 'L' : vitesse = LENTE ; break ;
    default :
      fprintf( stderr , "%s : vitesse incorrecte : %c (doit etre egale a R, M ou L)\n" , nomprog , vitesse_c ) ;
      exit(-1) ; 
    }
  
  srandom(getpid()) ;
  /*!
   * A FAIRE \\
   * Deplacement de la voiture sur la route \\
   * (voir exemple de déplacement ex_deplacement.c)
   */
   if( verbose ) 
    printf(" Initialisation route\n");
  if( (noerr = route_initialiser( fichier_route , longueur ) )) 
    {
      fprintf( stderr, "%s : erreur %d dans route_initialiser\n",
	       nomprog , noerr );
      exit(-1) ;
    }

  if( verbose ) printf(" Ouverture fichier route\n");
  if( ( fd_route = open( fichier_route , O_RDWR , 0644 )) == -1 )
    {
      fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fichier_route);
      exit(-1);
    }
  if( verbose ) printf(" Affichage route initialisee\n");
  if( (noerr = route_afficher(fd_route) )) 
    {
      fprintf( stderr, "%s : erreur %d dans route_afficher\n",
	       nomprog , noerr );
      exit(-1) ;
    }
    // Création des voitures
  voiture_t *voiture = voiture_new(NULL, marque, getpid(), sens, vitesse);
  voiture_printf(voiture);
  printf("\n");

  if (verbose)
    printf("Affichage route initiale\n");
  if ((noerr = route_afficher(fd_route)))
  {
    fprintf(stderr, "%s : erreur %d dans route_afficher\n",
            nomprog, noerr);
    exit(-1);
  }

  if (verbose)
    printf("Deplacement de la voiture\n");
  off_t new_pos = -1;
  off_t new_len = 0;
  booleen_t arrivee = FAUX;

  while (!arrivee)
  {
    if ((noerr = route_voiture_deplacement_calculer(fd_route,
                                                    voiture,
                                                    FAUX,
                                                    &new_pos,
                                                    &new_len,
                                                    &arrivee)))
    {
      fprintf(stderr, "%s / route_voiture_deplacement_calculer: sortie erreur %d\n",
              nomprog, noerr);
      exit(-1);
    }

    if ((noerr = route_voiture_deplacer(fd_route,
                                        voiture,
                                        new_pos,
                                        &arrivee)))
    {
      fprintf(stderr, "%s / route_voiture_deplacer: sortie erreur %d\n",
              nomprog, noerr);
      exit(-1);
    }

    if ((noerr = route_afficher(fd_route)))
    {
      fprintf(stderr, "%s : erreur %d dans route_afficher\n",
              nomprog, noerr);
      exit(-1);
    }

    sleep(1);
  }

  close(fd_route);
  unlink(fichier_route);

  printf("Voiture %c arrivee\n", voiture_marque_get(voiture));

  if (verbose)
    printf("Destruction de la voiture\n");
  voiture_destroy(&voiture);

  exit(0);
}
