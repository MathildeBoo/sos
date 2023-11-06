#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <route.h>

/* 
 * Affichage d'une case/cellule de la route 
 */

static
void route_case_printf( case_t cellule )
{
  printf( "%c" , cellule );
}

/* 
 * Methodes set/get
 */

/* Longueur de la route */
extern 
err_t route_longueur_fget( const int fd_route , int * longueur )
{
  char mess[MESS_LONGUEUR] ;
  (*longueur) = -1 ;
  
  /* 
   * Mise de la position courante au debut du fichier
   */
  
  if( lseek( fd_route, (off_t)0, SEEK_SET) == -1 )
    {
      sprintf( mess , "route_longueur_get : Pb lseek debut fichier fd=%d\n",
	       fd_route );
      perror(mess);
      return(ERREUR) ;
    }

  /* 
   * Lecture longueur de la route
   */
     
  if( read( fd_route , longueur , sizeof(int)) == -1 )
    {
      perror("route_longueur_get : Pb read sur lecture longueur");
      return(ERREUR) ;
    }
  
  return(CORRECT) ; 
}

extern 
err_t route_longueur_set( const int fd_route ,
			  const int longueur )
{

  char mess[MESS_LONGUEUR] ;
  int lg = longueur ;
  
  /* 
   * Mise de la position courante au debut du fichier
   */
  
  if( lseek(fd_route, (off_t)0, SEEK_SET) == -1 )
    {
      sprintf( mess , "route_longueur_get : Pb lseek debut fichier fd=%d\n",
	       fd_route );
      perror(mess);
      return(ERREUR) ;
    }

  /* 
   * Ecriture longueur de la route
   */
     
  if( write( fd_route , &lg , sizeof(int)) == -1 )
    {
      perror("route_longueur_get : Pb read sur lecture longueur");
      return(ERREUR) ;
    }
  
  return(CORRECT) ; 
}


/* 
 * Lecture d'une case de la route 
 */ 

/* A partir de coordonnees */
extern 
err_t route_coord_fget( const int fd_route,		/* descripteur du fichier route */
			const coord_t coord ,	/* coordonnees de la case a lire */
			case_t * contenu ) /* contenu de la case lue */
{

  /*--------------------*/

  if( lseek( fd_route, coord.pos , SEEK_SET) == -1 )
    {
      fprintf(stderr , "route_case_get : Pb lseek (dans fichier fd=%d) sur case " ,
	      fd_route );
      coord_fprintf( stderr , coord );
      fprintf(stderr, "\n");
      perror("Pb lseek") ;
      return(ERREUR) ;
    }
     
  if( read( fd_route , contenu , sizeof(case_t) ) == -1 )
    {
      fprintf( stderr , "route_case_get : Pb read sur lecture de la case " );
      coord_fprintf( stderr , coord );
      perror("Pb read");
      return(ERREUR) ;
    }

  return(CORRECT);
}

/* A partir d'une position dans le fichier */
extern 
err_t route_pos_fget( const int fd_route,		/* descripteur du fichier route */
		      const off_t pos  ,	/* offset dans le fichier */
		      case_t * contenu )  /* contenu de la case lue */
{
  
  /*--------------------*/
  
  if( lseek( fd_route, pos , SEEK_SET) == -1 )
    {
      fprintf(stderr , "route_pos_fget : Pb lseek (dans fichier fd=%d) sur case position %lld\n" ,
	      fd_route , (long long int)pos );
      perror("Pb lseek") ;
      return(ERREUR) ;
    }
     
  if( read( fd_route , contenu , sizeof(case_t) ) == -1 )
    {
      fprintf( stderr , "route_pos_fget : Pb lecture (dans fichier fd=%d) de la case position %lld\n" ,
	       fd_route , (long long int)pos );
      perror("Pb read");
      return(ERREUR) ;
    }
  
  return(CORRECT);
}

/* A partir du sens et d'un indice de case */
extern 
err_t route_si_fget( const int fd_route,		/* descripteur du fichier route */
		     const sens_t sens  ,	/* sens de la voie */
		     const int indice  ,	/* indice de la case dans la voie */
		     case_t * contenu )  /* contenu de la case lue */
{
  err_t noerr = CORRECT ; 
  off_t pos = -1 ;
  
  /*--------------------*/

  if( (noerr = route_si2pos( fd_route, sens, indice,
			     &pos ) ) )
    return(noerr) ;
  
  if( lseek( fd_route, pos , SEEK_SET) == -1 )
    {
      fprintf(stderr , "route_si_fget : Pb lseek (dans fichier fd=%d) sur case position %lld\n" ,
	      fd_route , (long long int)pos );
      perror("Pb lseek") ;
      return(ERREUR) ;
    }
     
  if( read( fd_route , contenu , sizeof(case_t) ) == -1 )
    {
      fprintf( stderr , "route_si_fget : Pb lecture (dans fichier fd=%d) de la case position %lld\n" ,
	       fd_route , (long long int)pos );
      perror("Pb read");
      return(ERREUR) ;
    }
  
  return(CORRECT);
}


/* 
 * Ecriture d'une case de la route 
 */

/* A partir d'une coordonnée */
extern
err_t  route_coord_set( const int fd_route,
			const coord_t coord,
			const case_t contenu )
{
  case_t m = contenu ;
  char mess[MESS_LONGUEUR] ;

  /*----------*/

  if( lseek( fd_route, coord.pos, SEEK_SET ) == -1 )
    {
      sprintf( mess , "route_coord_set : erreur dans deplacement a la position %lld dans le fichier route (fd=%d)\n",
	       (long long int)coord.pos , fd_route );
      perror(mess);
      return(ERREUR) ;
    }

  if( write(fd_route, &m, sizeof(case_t)) == -1 )
    {
      fprintf( stderr , "route_coord_set : Pb sur ecriture fichier route (fd=%d) sur la case position %lld\n" ,
	       fd_route , (long long int)coord.pos );
      perror("Pb write");
      return(ERREUR) ;
    }

  return(CORRECT) ;
}

/* A partir d'une position dans le fichier */
extern 
err_t route_pos_set( const int fd_route,
		     const off_t pos  ,	
		     const case_t contenu )
{
  case_t c = contenu ;
  
  /*--------------------*/
  
  if( lseek( fd_route, pos , SEEK_SET) == -1 )
    {
      fprintf(stderr , "route_pos_set : Pb lseek (dans fichier fd=%d) sur case position %lld\n" ,
	      fd_route , (long long int)pos );
      perror("Pb lseek") ;
      return(ERREUR) ;
    }
     
  if( write( fd_route , &c , sizeof(case_t) ) == -1 )
    {
      fprintf( stderr , "route_pos_set : Pb sur ecriture (dans fichier fd=%d) sur case position %lld\n" ,
	       fd_route , (long long int)pos );
      perror("Pb write");
      return(ERREUR) ;
    }
  
  return(CORRECT);
}

/* A partir du sens et d'un indice de case */
extern 
err_t route_si_set( const int fd_route,	
		    const sens_t sens  ,
		    const int indice  ,	
		    const case_t contenu ) 
{
  err_t noerr = CORRECT ; 
  off_t pos = -1 ;
  case_t c = contenu ;
  
  /*--------------------*/

  if( (noerr = route_si2pos( fd_route, sens, indice,
			     &pos ) ) )
    return(noerr) ;
  
  if( lseek( fd_route, pos , SEEK_SET) == -1 )
    {
      char c_sens[STRING_LG_MAX] ;
      sens_sprintf( c_sens , sens ) ; 
      fprintf(stderr , "route_si_set : Pb lseek (dans fichier fd=%d) sur case position [%s,%d]\n" ,
	      fd_route , c_sens , indice );
      perror("Pb lseek") ;
      return(ERREUR) ;
    }
     
  if( write( fd_route , &c , sizeof(case_t) ) == -1 )
    {
      char c_sens[STRING_LG_MAX] ;
      sens_sprintf( c_sens , sens ) ; 
      fprintf(stderr , "route_si_set : Pb ecriture (dans fichier fd=%d) sur case position [%s,%d]\n" ,
	      fd_route , c_sens , indice );
      perror("Pb write");
      return(ERREUR) ;
    }
  
  return(CORRECT);
}

/*
 * Conversion d'une coordonnée [sens,indice] en une position dans le fichier
 */

extern
err_t route_si2pos( const int fd_route,	
		    const sens_t sens,	
		    const int indice,	
		    off_t * pos )	
{
  err_t noerr = CORRECT ; 
  int longueur = -1 ;

  /*--------------------*/
  
  /*
   * Lecture de la longueur de la route
   */
  
  if( (noerr = route_longueur_fget( fd_route , &longueur ) ) )
    return(noerr) ; 

  /*
   * Calcul position fichier
   */
  
  if( (noerr = si2pos( longueur , sens , indice , pos ) ) )
    return(noerr) ;
  
  return(CORRECT);
}


/*
 * Conversion d'une position dans le fichier en une coordonnée [sens,indice]  
 */
extern
err_t route_pos2si( const int fd_route,	/* Descripteur fichier route */
		    const off_t pos,	/* Position dans le fichier route */
		    sens_t * sens,		/* sens de la voie */
		    int * indice)		/* indice dans la voie */

{
  err_t noerr = CORRECT ; 
  int longueur = -1 ;     

  /*--------------------*/

  /*
   * Initialisation des resultats
   */
  
  (*sens) = -1 ;
  (*indice) = -1 ;
  
  /*
   * Lecture de la longueur de la route
   */
  
  if( (noerr = route_longueur_fget( fd_route , &longueur )) )
    return(noerr) ; 
  
  if( ( noerr = pos2si( longueur , pos , sens , indice ) ) )
    return(noerr) ;
  
  return(CORRECT) ;
}


/* 
 * Initialisation des fichiers de la route
 */

extern 
err_t route_initialiser( const char * const fich_route ,
			 const int longueur )
{
  char mess[MESS_LONGUEUR] ;
  int i ;
  case_t c = CASE_VIDE ;
  int fd_route = -1 ; 
  
  /*----------*/

  /* 
   * Ouverture fichier route
   */
  if( ( fd_route = open( fich_route , O_WRONLY | O_CREAT , 0666)) == -1 )
    {
      sprintf( mess, "Pb open sur %s\n", fich_route);
      perror(mess);
      return(ERREUR);
    }

  /* 
   * Ecriture de la longueur
   */
     
  if( write( fd_route , &longueur , sizeof(int)) == -1 )
    {
      sprintf( mess , "route_initialiser : erreur sur ecriture de la longueur=%i\n", longueur );
      perror(mess);
      return(ERREUR) ;
    }
   
  /* 
   * Ecriture de la voie Ouest --> Est
   */

  for( i=0 ; i<longueur ; i++ )
    {	
      if( write( fd_route , &c , sizeof(case_t)) == -1 )
	{
	  sprintf( mess , "route_initialiser : erreur sur ecriture %s[%i] Ouest --> Est\n",fich_route,i);
	  perror(mess);
	  return(ERREUR) ;
	}       
    }

  /* 
   * Ecriture de la voie Est --> Ouest
   */

  for( i=0 ; i<longueur ; i++ )
    {	
      if( write( fd_route , &c , sizeof(case_t)) == -1 )
	{
	  sprintf( mess , "route_initialiser : erreur sur ecriture %s[%i] Ouest --> Est\n",fich_route,i);
	  perror(mess);
	  return(ERREUR) ;
	}       
    }

  /*
   * Fermeture fichier route
   */
  close(fd_route);
     
  return(CORRECT);
}

/* 
 * Affichage de la route
 */

extern 
err_t route_afficher( const int fd_route )
{     
  case_t cellule = CASE_VIDE ;
  int longueur; 
  char mess[MESS_LONGUEUR];
  int i ;
  case_t * voie = NULL ;
     
  /*----------*/

  if( fd_route == -1 )
    {
      fprintf( stderr , "route_afficher: descripteur fichier route non ouvert\n");
      return(ERREUR) ;
    }

  /* 
   * Positionnment debut fichier  
   */
     
  if( lseek( fd_route, (off_t)0, SEEK_SET) == -1 )
    {
      sprintf( mess , "route_afficher : Pb lseek debut fichier fd=%d\n",
	       fd_route );
      perror(mess);
      return(ERREUR) ;
    }
     
  /* 
   * Lecture de la longueur de la route 
   */
     
  if( read( fd_route , &longueur , sizeof(int)) == -1 )
    {
      sprintf( mess , "route_afficher : erreur sur lecture de la longueur\n");
      perror(mess);
      return(ERREUR) ;
    }

  for( i=0 ; i<longueur ; i++ ) (i/100 ? fprintf( stdout , "%1d" , (i/100)%10 ) : fprintf( stdout , " " ) ) ; fprintf(stdout , "\n");
  for( i=0 ; i<longueur ; i++ ) (i/10 ? fprintf( stdout , "%1d" , (i/10)%10 ) : fprintf( stdout , " " ) ) ; fprintf(stdout , "\n");
  for( i=0 ; i<longueur ; i++ ) fprintf( stdout , "%1d" , i%10 ); fprintf(stdout , "\n");
  for( i=0 ; i<longueur ; i++ ) fprintf( stdout , "-" )     ; fprintf(stdout , "\n");
     
  /* 
   * Affichage voie Ouest-Est
   */

  for( i=0 ; i<longueur; i++ )
    {
      if( read( fd_route , &cellule, sizeof(case_t)) == -1 )
	{
	  sprintf( mess , "route_afficher : erreur sur lecture case[%i] sens Ouest-Est\n", i );
	  perror(mess);
	  return(ERREUR) ;
	}
      route_case_printf( cellule );
    }
  fprintf(stdout , "\n");
     
  /* 
   * Ligne du milieu 
   */     
  for( i=0 ; i<longueur ; i++ ) ( i % 2 ? fprintf( stdout , "-" ) : fprintf( stdout , " " ) ) ; fprintf(stdout , "\n");


  /* 
   * Affichage voie Est-Ouest dans le sens contraire
   */
  if( (voie = malloc( sizeof(case_t) * longueur ) ) == NULL )
    {
      fprintf( stderr , "route_afficher : debordement memoire lors de la creation de la voie Est-Ouest (%lu octets demandes)\n" ,
	       sizeof(case_t) * longueur ) ; 
      return(ERREUR) ; 
    }
  for( i=0 ; i<longueur; i++ )
    {
      if( read( fd_route , &voie[i] , sizeof(case_t)) == -1 )
	{
	  sprintf( mess , "route_afficher : erreur sur lecture case[%i] sens Est-Ouest\n", i );
	  perror(mess);
	  return(ERREUR) ;
	}
    }
     
  for( i=longueur-1 ; i>=0 ; i-- )
    {
      route_case_printf( voie[i] );
    }	  
  fprintf(stdout , "\n");

  free( voie ) ;
     
  /* Affichage derniere ligne */
  for( i=0 ; i<longueur ; i++ ) fprintf( stdout , "-" )     ; fprintf(stdout , "\n");

  return(CORRECT);
}


/*
 * Demarrage d'une voiture sur une voie de la route
 * La voiture doit être instanciee avec 
 * - le sens de la voie sur laquelle elle veut demarrer 
 * - sa marque 
 */

extern
err_t route_voiture_demarrer( const int fd_route,		/* Fichier route */
			      voiture_t * voiture ,		/* Voiture */
			      booleen_t * ok )
{
  int noerr = CORRECT ;

  if( ( noerr = route_voiture_positionner( fd_route ,
					   voiture ,
					   0,
					   ok ) ) )
    return(noerr) ;
  
  return(CORRECT) ; 
}

/*
 * Positionnement d'une voiture sur une voie de la route
 * La voiture doit être instanciee avec 
 * - le sens de la voie sur laquelle elle veut demarrer 
 * - sa marque 
 */

extern
err_t route_voiture_positionner( const int fd_route,		/* Fichier route */
				 voiture_t * voiture ,		/* Voiture */
				 const int depart ,		/* Indice de depart sur la voie */
				 booleen_t * ok )
{
  int noerr = CORRECT ;

  int longueur = -1 ; /* Longueur de la route */
  sens_t sens = -1 ;
  case_t marque = CASE_VIDE ;
     
  int i ;

  case_t case_route ;

  /*--------------------*/

  (*ok) = FAUX ;
     
  /* 
   * Assertions
   */

  if( (noerr = route_longueur_fget(fd_route, &longueur) ) )
    {
      fprintf( stderr , "route_voiture_demarrer: pb lecture longueur de la route\n" );
      return(noerr) ;
    }

  if( longueur < VOITURE_TAILLE )
    {
      fprintf( stderr , "route_voiture_demarrer: Route trop courte pour y deposer une voiture\n" );
      fprintf( stderr , "                        taille voiture (%d) > longueur route (%d)\n" ,
	       VOITURE_TAILLE , longueur );
      return(noerr) ;
    }

  if( voiture == NULL )
    {
      fprintf( stderr , "route_voiture_demarrer: voiture inexistante\n" );
      return(ERREUR) ; 
    }
     
  sens = voiture_sens_get( voiture ) ;
  if( ! sens_correct(sens) )
    {
      fprintf( stderr , "route_voiture_demarrer: sens de la voiture incorrect (%d)\n" ,
	       sens );
      return(ERREUR) ; 
    }

  marque = voiture_marque_get(voiture) ;
  if( marque == CASE_VIDE  )
    {
      fprintf( stderr , "route_voiture_demarrer: marque de la voiture incorrecte (equivalente a une case vide)\n" );
      return(ERREUR) ; 
    }
     
  /*
   * Verification si il y a assez de place au depart de la voie pour cette voiture
   */
     
  for( i=0 ; i<VOITURE_TAILLE ; i++ )
    {
      route_si_fget( fd_route , sens , depart+i , &case_route ) ;
      if( case_route != CASE_VIDE )
	{
	  (*ok) = FAUX ; 
	  return(CORRECT) ;
	}
    }

  /*
   * Mise à jour de la coordonnee de la voiture
   */

  if( (noerr = voiture_positionner( voiture , longueur , sens , depart ) ) )
    return(noerr) ;
 
  /*
   * Ecriture de la voiture au debut de la voie dans le fichier
   */

  for( i=0 ; i<VOITURE_TAILLE ; i++ )
    {
      if( (noerr = route_si_set( fd_route , sens , depart+i , marque ) ) )
	return(noerr);
    }
     
  /* 
   * Gestion retour 
   */
  (*ok) = VRAI ; 
  return(CORRECT);

}

extern
err_t route_voiture_deplacement_calculer( const int fd_route,
					  const voiture_t * const voiture,
					  const booleen_t depassement , 
					  off_t * position_deplacement ,
					  off_t * portee_deplacement ,
					  booleen_t * sortie ) 
{
  err_t noerr = CORRECT ;
  off_t fin         = -1 ;
  vitesse_t vitesse = -1 ;
  off_t deplacement = -1 ; 
  int longueur = -1 ;
  sens_t sens = -1 ;
  int indice = -1 ;    
  sens_t sens_voiture = -1 ;
  sens_t sens_voie    = -1 ;

  
  /* Initialisation du resultat */
  (*position_deplacement) = -1 ;
  (*portee_deplacement) = VOITURE_TAILLE ;
  (*sortie) = FAUX ; 

  /* Assertions */
  if( voiture == NULL )
    {
      fprintf( stderr , "route_deplacement_calculer: voiture inexistante\n" ) ;
      return(ERREUR) ;
    }

  vitesse = voiture_vitesse_get(voiture) ;
  switch(vitesse)
    {
    case LENTE   : deplacement = VOITURE_TAILLE + 1 ; break ;
    case MOYENNE : deplacement = VOITURE_TAILLE + 2 ; break ;
    case RAPIDE  : deplacement = VOITURE_TAILLE + 3 ; break ;
    default :
      {
	fprintf( stderr , "route_deplacement_calculer: vitesse de la voiture incorrecte (%d)\n" , vitesse ) ;
	return(ERREUR) ;
      }
    }
  
  /* Calcul deplacement */
  fin = coord_position_get(voiture_fin_get(voiture)) ;
  /* 
   * Le deplacement est positif si il est dans le meme sens que la voiture,
   *  negatif sinon 
   */

  sens_voiture = voiture_sens_get(voiture) ;  
  sens_voie = voiture_voie_get(voiture) ;

  if( (noerr = route_longueur_fget( fd_route , &longueur ) ) )
    return(noerr) ;
  
  if( depassement )
    {
      sens_voie = sens_oppose(sens_voie) ;
      fin = position_opposee( longueur , fin ) ;
    }
  
  if( sens_voiture != sens_voie )
    {
      deplacement = deplacement * -1 ;
      (*portee_deplacement) = -VOITURE_TAILLE ; 
    }
  
  deplacement = fin + deplacement ;
 
  if( ! pos_correcte( longueur , sens_voie , deplacement ) )
    {
       (*position_deplacement) = -1 ;
       (*portee_deplacement) = 0 ;
       (*sortie) = VRAI ; 
       return(CORRECT) ; 
    }

  if( (noerr = pos2si( longueur , deplacement , &sens  , &indice ) ) )
    return(noerr) ;
  
 
  if( indice < 0 )
    {
      if( ( noerr = si2pos( longueur , sens  , 0 , &deplacement ) ) )
	return(noerr) ;
    }
  
  if( indice >= longueur )
    {
      if( ( noerr = si2pos( longueur , sens  , longueur-1 , &deplacement ) ) )
	return(noerr) ;
    }

  /* Resultat */
  if( ( noerr = pos2si( longueur , deplacement , &sens  , &indice ) ) )
	return(noerr) ;

  
  
  if( (indice < VOITURE_TAILLE-1) && (sens_voiture != sens_voie) )
    (*portee_deplacement) = -indice-1 ;

  if( (indice+VOITURE_TAILLE > longueur) && (sens_voiture == sens_voie) )
    (*portee_deplacement) = longueur-indice ;
     
  (*position_deplacement) = deplacement ;
  
  return(CORRECT) ; 
}

/* 
 * Dans ses nouvelles coordonnées, la voiture peut depasser la portion de route 
 * mais dans ce cas elle n'est pas écrite dans le fichier route
 */

extern
err_t route_voiture_deplacer( const int fd_route,
			      voiture_t * voiture,
			      const off_t depart_pos ,
			      booleen_t * arrivee )
{
  err_t noerr = CORRECT ; 
  int longueur = -1 ;
  sens_t depart_sens = -1 ;
  int depart_indice = -1 ; 

  /* ---------- */
  /*
   * Initialisation resultat 
   */
  (*arrivee) = FAUX ;
  
  /*
   * Assertions
   */

  if( voiture == VOITURE_NULL )
    {
      fprintf( stderr , "route_voiture_deplacer: voiture inexistante\n");
      return(ERREUR) ; 
    }

  if( fd_route == -1 )
    {
      fprintf( stderr , "route_voiture_deplacer: mauvais descripteur de fichier route\n");
      return(ERREUR) ; 
    }

  if( (noerr = route_longueur_fget( fd_route , &longueur ) ) )
    return(noerr) ;

  /* 
   * Deplacement dans le fichier 
   */

  /* Effacement anciennes positions */
  if( (noerr = route_voiture_effacer( fd_route,
				      voiture ) ) )
    return(noerr) ; 

  /* Mise à jour des nouvelles coordonnées de la voiture */
  if( (noerr = pos2si( longueur , depart_pos , &depart_sens, &depart_indice ) ) )
	return(noerr) ;
  
  if( (noerr = voiture_positionner( voiture , 
				    longueur ,
				    depart_sens,
				    depart_indice ) ) )
    return(noerr) ;
  
  /* 
   * Ecriture de la voiture à ses nouvelles positions
   */

  if( voiture_sortie_route( longueur , voiture ) )
    {
      /* On n'écrit pas juste une partie de la voiture */
      (*arrivee) = VRAI ;
    }
  else
    {
      /* Ecriture de la totalite de la voiture */
      if( (noerr = route_voiture_set( fd_route, voiture ) ) )
	return(noerr) ;
    }
      
  /* Gestion retour */
  return(CORRECT) ;
}


/*
 * Ecriture d'une voiture sur la route
 */

extern
err_t route_voiture_set( const int fd_route,
			 const voiture_t * const voiture )
{
  int i = 0 ;
  int noerr = CORRECT ;
  case_t marque = CASE_VIDE ;
  int longueur = -1 ;
  int indice = -1 ;
  
  /*----------*/

  if( voiture == VOITURE_NULL )
    {
      fprintf( stderr , "route_voiture_set: voiture inexistante\n" ) ;
      return(ERREUR) ;      
    }

  marque = voiture_marque_get(voiture) ;
  
  if( (noerr = route_longueur_fget(fd_route , &longueur ) ) )
    return(noerr) ;
  
  for( i=0 ; i<VOITURE_TAILLE ; i++ )
    {
      indice = coord_indice_get(coords_coord_get( voiture_corps_get(voiture) , i ) );
      if( (indice >= 0 ) && (indice < longueur) )
	{
	  if( (noerr = route_coord_set( fd_route,
					coords_coord_get( voiture_corps_get(voiture) , i ),
					marque ) ) )
	    return(noerr);
	}
    }
  return(CORRECT);
}


/*
 * Effacement d'une voiture de la route
 */

extern
err_t route_voiture_effacer( const int fd_route,
			     const voiture_t * const voiture )
{
  int i = 0 ;
  int noerr = CORRECT ;
  int longueur = - 1 ;
  int indice = -1 ;
  
  /*----------*/


  if( voiture == VOITURE_NULL )
    {
      fprintf( stderr , "route_voiture_effacer: voiture inexistante\n" ) ;
      return(ERREUR) ;      
    }

  if( voiture_corps_get(voiture) == NULL )
    {
      /* pas de coordonnées, rien à effacer */
      return(CORRECT) ;
    }
  
  if( (noerr = route_longueur_fget(fd_route , &longueur ) ) )
    return(noerr) ;

  
  for( i=0 ; i<VOITURE_TAILLE ; i++ )
    {
      indice = coord_indice_get(coords_coord_get( voiture_corps_get(voiture) , i ));
      if( (indice >= 0) && (indice < longueur) )
	{
	  if( (noerr = route_coord_set( fd_route,
					coords_coord_get( voiture_corps_get(voiture) , i ),
					CASE_VIDE ) ) )
	    return(noerr);
	}
    }
  return(CORRECT);
}


/*
 * Tests
 */


extern
booleen_t route_voiture_arrivee( const int fd_route,
				 const voiture_t * const voiture )
{
  err_t noerr = CORRECT ; 
  int longueur = -1 ;

  /*----------*/
 
  if( ( noerr = route_longueur_fget( fd_route , &longueur ) ) )
    return(noerr) ;
  
  return( voiture_sortie_route( longueur , voiture ) );
}

extern
booleen_t route_collision( const int fd_route)
{
  char mess[STRING_LG_MAX] ;
  
  int longueur = -1 ;
  int i = 0 ;
  sens_t sens = -1 ; 
  
  case_t cellule = CASE_VIDE ;
  
  case_t voiture_marque = CASE_VIDE ;
  case_t voiture_longueur = -1 ;
  
  /*----------*/

  if( fd_route == -1 )
    {
      fprintf( stderr , "route_collision: descripteur fichier route non ouvert\n");
      return(ERREUR) ;
    }

  /* 
   * Positionnement debut fichier  
   */
  
  if( lseek( fd_route, (off_t)0, SEEK_SET) == -1 )
    {
      sprintf( mess , "route_collion: Pb lseek debut fichier fd=%d\n",
	       fd_route );
      perror(mess);
      return(ERREUR) ;
    }
     
  /* 
   * Lecture de la longueur de la route 
   */
  
  if( read( fd_route , &longueur , sizeof(int)) == -1 )
    {
      sprintf( mess , "route_collision : erreur sur lecture de la longueur\n");
      perror(mess);
      return(ERREUR) ;
    }

  /* 1ere lecture */
  if( read( fd_route , &cellule, sizeof(case_t)) == -1 )
    {
      sprintf( mess , "route_collision : erreur sur lecture case[%i] sens Ouest-Est\n", i );
      perror(mess);
      return(ERREUR) ;
    }
  
  /* Initialisation fichier route */
  sens = 0 ;

  /*
   * Boucle fichier route 
   */
  while( sens < 2 )
    {      
      /* Initialisation voie */
      i=0 ;
      /*
       * Boucle voie 
       */
      while( (sens < 2) &&
	     (i <longueur) )
	{

	  /* 
	   * Boucle cases vides 
	   */
	  
	  while( (sens < 2) &&
		 (i < longueur) &&
		 (cellule == CASE_VIDE) )
	    {
	      /* Lecture suivante */
	      if( read( fd_route , &cellule, sizeof(case_t)) == -1 )
		{
		  sprintf( mess , "route_collision : erreur sur lecture case[%i] sens Ouest-Est\n", i );
		  perror(mess);
		  return(ERREUR) ;
		}
	      i++;
	    }

	  /* Initialisation voiture */
	  voiture_marque = cellule ;
	  voiture_longueur = 0 ;

	  /*
	   * Boucle voiture
	   */
	  while( (sens < 2) &&
		 (i < longueur) &&
		 (voiture_marque == cellule) )
	    {
	      /* Lecture suivante */
	      if( read( fd_route , &cellule, sizeof(case_t)) == -1 )
		{
		  sprintf( mess , "route_collision : erreur sur lecture case[%i] sens Ouest-Est\n", i );
		  perror(mess);
		  return(ERREUR) ;
		}
	      voiture_longueur++ ; 
	      i++;
	    }
	  
	  /* Fin voiture */
	  if( (voiture_longueur != 0) && (voiture_longueur != VOITURE_TAILLE) )
	    {
	      printf( "detection collision voiture %c tronquee a %d\n" ,
		      voiture_marque , voiture_longueur ) ;
	      /* Une voiture a été tronquée */
	      return(VRAI) ;
	    }
	}
      
      /* Fin voie : passage a la voie suivante */
      sens++ ;
    }
  /* Fin fichier route */
  
      
  return(FAUX) ; 
  
}


extern
err_t route_voiture_collision( booleen_t * collision ,
			      const int fd_route,
				   const voiture_t * const voiture )
{
  char mess[STRING_LG_MAX] ;

  int i = 0 ;
  case_t cellule = CASE_VIDE ;
  case_t marque = CASE_VIDE ;
  off_t pos = -1 ;
  coords_t * corps = NULL ; 
  
  /*----------*/
  
  (*collision) = FAUX ; 
  
  if( route_voiture_arrivee( fd_route, voiture ) )    
    return(CORRECT) ;


  /* 
   * Verificiation de toutes les positions du corps de la voirure dans le fichier 
   */

  corps = voiture_corps_get(voiture) ;
  marque = voiture_marque_get(voiture) ; 
  for( i=0 ; i<VOITURE_TAILLE ; i++ )
    {
      pos = coord_position_get(coords_coord_get( corps , i )) ;

      /* Deplacement a la position sur la route */
      if( lseek( fd_route, pos , SEEK_SET) == -1 )
	{
	  sprintf( mess , "route_voiture_collion: Pb lseek a la position =%lld\n",
		   (long long int)pos );
	  perror(mess);
	  return(ERREUR) ;
	}
  
      /* Lecture case sur la route */
      if( read( fd_route , &cellule, sizeof(case_t)) == -1 )
	{
	  sprintf( mess , "route_voiture_collision : erreur sur lecture position %lld \n", (long long int)pos );
	  perror(mess);
	  return(ERREUR) ;
	}
  
      /* Verif s'il s'agit bien de la voiture */
      if( cellule != marque )
	{
	  (*collision) = VRAI ;
#ifdef _DEBUG_
	  printf( "route_collision_voiture: voiture %c tronquee a %d\n" , marque , i ) ;
#endif
	  return(CORRECT) ;
	}
    }
  
  return(CORRECT) ; 
  
}




/* Rabattement de la voiture sur la voie opposee */

extern
err_t route_voiture_rabattement_calculer( const int fd_route,
					  const voiture_t * const voiture,
					  off_t * position_rabattement ) 
{
  err_t noerr = CORRECT ;


  int longueur = -1 ;

  /* Initialisation du resultat */
  (*position_rabattement) = -1 ;

  /* Assertions */
  if( voiture == NULL )
    {
      fprintf( stderr , "route_voiture_rabattement_calculer: voiture inexistante\n" ) ;
      return(ERREUR) ;
    }

  /* NB : Pas de deplacement pour la voiture */


  /* On passe la voiture aux memes coordonnees mais dans la voie opposee */
  if( (noerr = route_longueur_fget( fd_route , &longueur ) ) )
    return(noerr) ;

  (*position_rabattement) = position_opposee( longueur , coord_position_get( voiture_fin_get(voiture) ) ) ;

  return(CORRECT) ; 
}
