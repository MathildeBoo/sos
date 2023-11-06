#include <getopt.h>
#include <route.h>

/*!
 * \file ex_deplacement.c
 * \brief Exemples de déplacement de voitures sur une route 
 * <ul>
 * <li> les voitures se déplacent les unes après les autres, séquentiellement
 * <li> les voitures ne se doublent pas, elles restent sur la même voie
 * <li> les voitures avancent "à l'aveugle" sans se soucier s'il y a une autre voiture devant
 * </ul>
 * C'est un exemple d'utilisation des fonctions de déplacement et d'arrêt de la gestion de la route quand il y a eu une collision
 */

/*! Nom du fichier route par défaut */
#define FICHIER_TEST "../Fichiers/exemple_route_v1.bin"
/*! Longueur de la route par défaut */
#define LONGUEUR 20 

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <nb voitures>\n" , nomprog ) ; 
  printf( "options:\n" ) ; 
  printf( "\t--verbose : trace des principales actions (defaut = desactive)\n" ) ; 
  printf( "\t--help    : affiche cette aide\n" ) ; 
  printf( "\t--fichier  <fichier route> : fichier dans lequel vont se déplacer les voitures (defaut %s)\n" , FICHIER_TEST ) ;
  printf( "\t--longueur <entier> : Longueur de la route (defaut %d)\n" , LONGUEUR );
}

static struct option longopts[] =
  {
    {"verbose", no_argument, NULL, (int)'v'},
    {"help", no_argument, NULL, (int)'h'},
    {"fichier", required_argument, NULL, (int)'f'},
    {"longueur", required_argument, NULL, (int)'l'},
    {0, 0, 0, 0}
  };

/*! 
 * \brief Programme principal <br>
 * usage: ex_depassement [options] <code>nb voitures</code> <br>
 * options:
 * <ul>
 * <li> --verbose : trace des principales actions (par defaut desactivée)
 * <li> --help    : affiche cette aide
 * <li> --fichier  <code>fichier route</code> : fichier dans lequel vont se déplacer les voitures (par defaut FICHIER_TEST)
 * <li> --longueur <code>entier</code> : Longueur de la route (par defaut LONGUEUR)
 * </ul>
 */
int
main( int argc , char * argv[] )
{
  int noerr = CORRECT ;     


  /* --- Gestion des options --- */
  int opt ; 
  char nomprog[STRING_LG_MAX] ;
  booleen_t  verbose = FAUX ;

  char fichier_route[STRING_LG_MAX] ;
  strcpy( fichier_route , FICHIER_TEST ) ;
  
  int longueur = LONGUEUR ;
  
  /*----------*/
  
  int fd_route ;
  int v = 0 ;
  int nb_voitures = 0 ; 
  
  /*----------*/

  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vhf:l:", longopts, NULL)) != -1 )
    {
      switch(opt)
	{	  
	case 'f':  /* --fichier d'initialisation */
	  strcpy(fichier_route,optarg) ;
	  break;

	case 'l': /* --longueur de la route */
	  longueur = atoi(optarg) ;
	  break ;

	case 'v' :  /* --verbose */
	  verbose = VRAI ;
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
  
  if( argc != 1 )
    {
      printf("%s : Nombre de parametres incorrect : %d (1 attendus)\n\n" , nomprog , argc ) ; 
      usage(nomprog) ; 
      exit(-1) ;
    }

  nb_voitures = atoi(argv[0] ) ; 
  
  srandom(getpid()) ;
  
  /* 
   * Ouverture fichier route
   */
 
  if( verbose ) printf(" Initialisation route\n");
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
  
  const sens_t tab_sens[2] = { OUEST_EST, EST_OUEST } ;
  const vitesse_t tab_vitesses[3] = { LENTE , MOYENNE , RAPIDE } ;
  voiture_t ** voiture = malloc( sizeof(voiture_t *) * nb_voitures ) ;
  for( v=0 ; v<nb_voitures ; v++ )
    {
      voiture[v] = voiture_new( NULL , 'A'+v , getpid() , tab_sens[random()%2]  , tab_vitesses[random()%3] )  ;  
      voiture_printf(voiture[v]) ; printf("\n") ;
    }
  
  if( verbose ) printf( "Affichage route initiale\n");  
  if( (noerr = route_afficher(fd_route) )) 
    {
      fprintf( stderr, "%s : erreur %d dans route_afficher\n",
	       nomprog , noerr );
      exit(-1) ;
    }

  

  if( verbose ) printf("Deplacement des voitures\n") ;
  off_t new_pos = -1 ;
  off_t new_len = 0 ; 
  int nb_arrivees = 0 ;
  booleen_t collision = FAUX ;
  booleen_t ok = FAUX ;
  booleen_t arrivee = FAUX ;

  while( (nb_arrivees < nb_voitures) && (!collision)  )
    {      
      for( v=0 ; (v<nb_voitures) && (!collision) ; v++ )
	{
	  if( route_collision( fd_route ) )
	    {
	      printf( "!!! COLLISION !!!\n");
	      collision=VRAI ;
	      break ;
	    }
	  
	  if( ! voiture_demarree( voiture[v] ) )
	    {
	      if( verbose )
		{
		  printf( "Demarrage voiture %c " , voiture_marque_get(voiture[v]) ) ;
		  fflush(stdout) ;
		}
	      
	      if( ( noerr = route_voiture_demarrer( fd_route,
						    voiture[v] ,
						    &ok ) ) )
		{
		  fprintf( stderr, "%s : erreur %d dans route_afficher\n",
			   nomprog , noerr );
		  exit(-1) ;
		}
	      
	      if( verbose )
		{
		  if(ok) printf( "OK\n") ; else printf( "non\n") ;
		}

	      if( (noerr = route_afficher(fd_route) )) 
		{
		  fprintf( stderr, "%s : erreur %d dans route_afficher\n",
			   nomprog , noerr );
		  exit(-1) ;
		}

	      continue ;
	    }

	  if( route_voiture_arrivee( fd_route, voiture[v] ) )	    
	      continue ;

	  if( (noerr = route_voiture_deplacement_calculer( fd_route ,
							   voiture[v] ,
							   FAUX ,
							   &new_pos ,
							   &new_len ,
							   &ok) ) )    
	    {
	      fprintf( stderr, "%s / route_voiture_deplacement_calculer: sortie erreur %d\n",
		       nomprog , noerr );
	      exit(-1) ;
	    }
	  
	  if( (noerr = route_voiture_deplacer( fd_route ,
					       voiture[v] ,
					       new_pos  ,
					       &arrivee ) ) )
	    {
	      fprintf( stderr, "%s / route_voiture_deplacer: sortie erreur %d\n",
		       nomprog , noerr );
	      exit(-1) ;
	    }
	  
	  if( arrivee )
	    {
	      nb_arrivees++ ;
	      printf( "Voiture %c arrivee\n" , voiture_marque_get(voiture[v]) ) ;
	      if( (noerr = route_voiture_effacer( fd_route,
						  voiture[v] ) ) )
		return(noerr) ;
	    }
		  
	  if( (noerr = route_afficher(fd_route) )) 
	    {
	      fprintf( stderr, "%s : erreur %d dans route_afficher\n",
		       nomprog , noerr );
	      exit(-1) ;
	    }	  
	  sleep(1) ;
	}
    }

  close(fd_route); 
  unlink(fichier_route) ;
  
  if( verbose ) printf ("nb arrivees = %d ; collision = %s\n" , nb_arrivees , (collision ? "VRAI" : "FAUX" ) ) ;
  
  if( verbose ) { printf("Destruction des voitures ") ; fflush(stdout); }
  for( v=0 ; v<nb_voitures ; v++ )
    voiture_destroy( &voiture[v] ) ;
  if( verbose ) printf("OK\n");

  

	 
  exit(0);

}
