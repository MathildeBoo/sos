#include <commun.h> 

extern
err_t sens_sprintf( char * string , const sens_t sens )
{
  switch(sens)
    {
    case OUEST_EST :
      strcpy( string , "OUEST_EST" ) ;
      break ;
    case EST_OUEST :
      strcpy( string , "EST_OUEST" ) ;
      break ;
    default :
      strcpy( string , "?" ) ;
      break ;      
    }
  return(CORRECT) ; 
}

extern
booleen_t sens_correct( const sens_t sens )
{
  switch(sens)
    {
    case OUEST_EST : return(VRAI) ;
    case EST_OUEST : return(VRAI) ;
    default        : return(FAUX) ;
    }
}


extern
err_t vitesse_sprintf( char * string , const vitesse_t vitesse )
{
  switch(vitesse)
    {
    case LENTE :
      strcpy( string , "LENTE" ) ;
      break ;
    case MOYENNE :
      strcpy( string , "MOYENNE" ) ;
      break ;
    case RAPIDE :
      strcpy( string , "RAPIDE" ) ;
      break ;
    default :
      strcpy( string , "?" ) ;
      break ;      
    }
  return(CORRECT) ; 
}

extern
booleen_t vitesse_correcte( const vitesse_t vitesse )
{
  switch(vitesse)
    {
    case LENTE   : return(VRAI) ;
    case MOYENNE : return(VRAI) ;
    case RAPIDE  : return(VRAI) ;
    default      : return(FAUX) ;
    }
}


extern
booleen_t pos_correcte( const int longueur ,
			const sens_t sens ,
			const off_t position )
{
  const off_t depl_sens = ( sens == OUEST_EST ? 0 : 1 ) * sizeof(case_t) * longueur ; 
  const off_t pos_max = TAILLE_ENTETE + depl_sens + sizeof(case_t) * longueur - 1 ;
  const off_t pos_min = TAILLE_ENTETE + depl_sens ;

  if( (position <= pos_max) && (position >= pos_min) )
    return(VRAI) ;
  else
    return(FAUX) ;
}


/*
 * Conversion d'un couple (sens,indice) en une position dans le fichier
 */

extern
err_t si2pos( const int longueur ,
	      const sens_t sens,	
	      const int indice,	
	      off_t * pos )	
{
  int deplacement = 0 ;
  
  /*--------------------*/
 
  /*
   * Calcul position fichier
   */
  
  switch(sens)
    {
    case OUEST_EST : deplacement = 0        ; break ;
    case EST_OUEST : deplacement = longueur ; break ;
    default :
      fprintf( stderr , "route_si2pos : sens incorrect (%d) \n" , sens ) ;
      return(ERREUR); 
    }

  (*pos) = TAILLE_ENTETE + deplacement * sizeof(case_t) + indice * sizeof(case_t) ;

  
  return(CORRECT);
}


/*
 * Conversion d'une position dans le fichier en un couple (sens,indice)  
 */
extern
err_t pos2si( const int longueur,	/* Longueur de la route */
	      const off_t pos,		/* Position dans le fichier route */
	      sens_t * sens,		/* sens de la voie */
	      int * indice)		/* indice dans la voie */

{
  int pos_w = pos - TAILLE_ENTETE ;
  
  /*--------------------*/

  (*sens) = ( pos_w / longueur ? EST_OUEST : OUEST_EST ) ; 
  (*indice) = (int)(pos_w - ( ((*sens) == OUEST_EST ? 0 : 1) * longueur ) ) ;

  return(CORRECT) ;
}

/* 
 * Correspondances opposées dans les 2 voies 
 */

extern
int indice_oppose( const int longueur , const int indice  )
{
  return( longueur - 1 - indice ) ; 
}

extern
sens_t sens_oppose( const sens_t sens )
{
  return( (sens == OUEST_EST ? EST_OUEST : OUEST_EST) ) ;
}

extern
off_t position_opposee( const int longueur , const off_t pos )
{
  return( (2 * TAILLE_ENTETE) + (2 * longueur) - pos - 1 ) ;
}

/*
 * Conversion debut + portee calcules sur la route 
 * en start + len dans un verrou de type struct flock 
 */

extern
err_t startlen2flock( off_t * flock_start , off_t * flock_len ,
		      const off_t start   , const off_t len   )
{
  
  if( len < 0 )
    {
      (*flock_start) = start + len + 1 ;
      (*flock_len)   = len * -1 ; 
    }
  else
    {
      (*flock_start) = start ;
      (*flock_len)   = len ; 
    }
  
  return(CORRECT) ;
}
