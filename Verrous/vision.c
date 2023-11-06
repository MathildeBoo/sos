#include <getopt.h>
#include <route.h>

#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

/*!
 * \file vision.c
 * \brief Programme de visualisation de la route 
 */

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <Fichier route>\n" , nomprog ) ; 
  printf( "options:\n" ) ; 
  printf( "\t--verbose : trace des principales actions (defaut = desactive)\n" ) ; 
  printf( "\t--help    : affiche cette aide\n" ) ; 
}

static struct option longopts[] =
  {
    {"verbose", no_argument, NULL, (int)'v'},
    {"help", no_argument, NULL, (int)'h'},
    {0, 0, 0, 0}
  };

/*! Programme principal */
int
main( int argc , char * argv[] )
{
  int noerr = CORRECT ;     

  /* --- Gestion des options --- */
  int opt ; 
  char nomprog[STRING_LG_MAX] ;
  booleen_t  verbose = FAUX ;

  /* --- Gestion du fichier --- */
  char fichier_route[STRING_LG_MAX] ;

  
  
  /* --- Variables de travail --- */
  
  /*----------*/

  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 )
    {
      switch(opt)
	{	  
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

  strcpy( fichier_route , argv[0] ) ;

  
  exit(0);

}
