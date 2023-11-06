#include <getopt.h>
#include <route.h>
#include <signal.h>

/* Met une voiture immobile sur la route */

void Pause()
{
  char s[2] ;
  printf("Tapez sur une touche pour continuer..." ); fflush(stdout) ;
  scanf( "%s" , s ) ;
}

booleen_t Fin ;

static
void hand_arret( int sig )
{
     /* Arret de la voiture  */     
     printf(  "Arret voiture test\n");
     Fin = VRAI ;
}

/*!
 * \file voiture_test.c
 * \brief Programme mettant une voiture immobile sur la roue pour faire des tests de depassement 
 */

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <Fichier route> <marque voiture> <sens> <indice>\n" , nomprog ) ; 
  printf( "avec:\n" ) ; 
  printf( "\t<marque>  : un caractere\n" ) ; 
  printf( "\t<sens>    : O pour sens OUEST-->EST\n" ) ;
  printf( "\t            E pour sens EST-->OUEST\n" ) ;
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
  int indice = - 1; 
  
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

  if(  sscanf( argv[3] , "%d" , &indice ) != 1 )
    {
      fprintf( stderr , "%s : indice incorrect (%s)\n" , nomprog , argv[3] ) ;
      exit(-1) ; 
    }

  /*  Capture signaux d'arret */
  signal( SIGINT  , hand_arret ) ;
  signal( SIGQUIT , hand_arret ) ;
  
  /* 
   * Ouverture fichier route
   */

  if( verbose > 1 ) printf(" Ouverture fichier route\n");
  if( ( fd_route = open( fichier_route , O_RDWR , 0644 )) == -1 )
    {
      fprintf( stderr, "%s : Pb open sur %s\n", nomprog , fichier_route);
      exit(-1);
    }
 
  /*
   * Creation de la voiture : la vitesse est arbitraire (on nes'en sert pas) 
   */
  voiture = voiture_new( NULL , marque , getpid() , sens  , LENTE )  ;

  if( verbose ) { voiture_printf(voiture) ; printf("\n") ; }

  /*
   * Positionnement de la voiture 
   */
  off_t start = -1 ;
  off_t len = VOITURE_TAILLE ;
  
  if( ( noerr = route_si2pos( fd_route, sens , indice , &start ) ) )
    {
      fprintf( stderr, "%s : erreur %d dans recherche position voiture\n",
	       nomprog , noerr );
      exit(-1) ;
    }
  booleen_t ok = FAUX ;  
  if( ( noerr = route_voiture_positionner( fd_route, voiture , indice , &ok ) ) )
    {
      fprintf( stderr, "%s : erreur %d dans route_voiture_positionner\n",
	       nomprog , noerr );
      exit(-1) ;
    }
      
  if( ok )
    {
      printf( "Demarrage voiture %c position=%lld portee=%lld\n",
	      marque , (long long int)start , (long long int)len ) ;
    }
  else
    {
      printf( "Probleme sur demarrage de la voiture %c (position=%lld portee=%lld), obstacle sans verrou sur la voie\n" ,
	      marque , (long long int)start , (long long int)len ) ;
      exit(1) ; 
    }	
  /* ---------- */

  Fin = FAUX ; 
  while( !Fin )
    pause() ;

#ifdef _DEBUG_
  printf( "Effacement voiture \n");
#endif
  
  if( (noerr = route_voiture_effacer( fd_route, voiture ) ) )
    return(noerr) ;
  
  close(fd_route); 
  
  if( verbose > 1 ) printf("Destruction voiture %c\n" , marque ) ;
  voiture_destroy( &voiture ) ;

  exit(0);
}
