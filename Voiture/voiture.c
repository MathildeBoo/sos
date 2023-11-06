/*
 * Realisation des primitives du TDA voiture  
 */

#include <voiture.h>


/*
 *=============================================================
 * Fonctions de gestion d'une voiture 
 *=============================================================
 */

/*
 * Valeur voiture vide 
 */

extern 
voiture_t voiture_vide() 
{
  voiture_t voiture ;
 
  voiture.corps  = NULL ;
  voiture.marque = '?' ;
  voiture.pid    = -1 ; 
  voiture.sens   = -1 ;
  
  return(voiture) ; 
}

/*
 * Creation d'une voiture 
 */
extern 
voiture_t * voiture_new( const coords_t * const coords,
			 const case_t marque,
			 const pid_t pid ,
			 const sens_t sens ,
			 const vitesse_t vitesse ) 
{
  voiture_t * voiture ;

  if( ( voiture = malloc( sizeof(voiture_t) ) ) == NULL )
    {
      fprintf( stderr , "voiture_new: debordement memoire (%lu octets demandes)\n" , 
	       sizeof(voiture_t) ); 
      return(NULL) ; 
    }

  (*voiture) = VOITURE_VIDE ; 

  if( voiture_set( voiture, coords, marque, pid , sens , vitesse ) == -1 )
      return(NULL) ;

  return(voiture) ; 
}

extern 
int voiture_destroy( voiture_t ** voiture ) 
{
  int noerr = 0  ;
  
  if(( noerr = coords_destroy( &((*voiture)->corps) ) ) )
    return(noerr) ; 

  free((*voiture)) ; 
  (*voiture) = NULL ;

  return(CORRECT) ; 
}


/*
 * Methodes  get/set 
 */


/*
 * Lecture/Ecriture du corps du voiture 
 */

extern 
coords_t * voiture_corps_get( const voiture_t * const voiture ) 
{ 
  return( voiture->corps ) ; 
}

extern 
err_t voiture_corps_set( voiture_t * const voiture ,    /* Voiture */
		      const coords_t * const coords)  /* Tableau de VOITURE_TAILLE coords composant le corps du voiture */
{ 
     int noerr = 0 ; 

     /*----------*/

     /* La liste des anciennes coordonnees est ecrasee */
     if( ( noerr = coords_copier( &(voiture->corps) ,
				  coords ) ) )
       return(noerr) ; 

     return(CORRECT);
}

extern 
coord_t voiture_debut_get( const voiture_t * const voiture ) 
{ 
  return( coords_coord_get(voiture->corps,0) ) ; 
}

extern 
coord_t voiture_fin_get( const voiture_t * const voiture ) 
{ 
  return( coords_coord_get(voiture->corps , VOITURE_TAILLE-1 ) ) ; 
}

/*
 * Lecture/Ecriture du signe distinctif du voiture 
 */

extern 
case_t voiture_marque_get( const voiture_t * const voiture ) 
{ 
     return(voiture->marque) ; 
}
extern 
err_t voiture_marque_set( voiture_t * const voiture , 
		       const case_t m) 
{ 
    voiture->marque = m ;
    return(CORRECT); 
}


/*
 * Lecture/Ecriture du pid du processus qui execute la voiture 
 */

extern 
pid_t voiture_pid_get( const voiture_t * const voiture ) 
{ 
     return(voiture->pid) ; 
}
extern 
err_t voiture_pid_set( voiture_t * const voiture , 
		    const pid_t pid) 
{ 
  voiture->pid = pid ;
  return(CORRECT) ; 
}

/*
 * Lecture/Ecriture du sens de la voiture 
 */

extern 
sens_t voiture_sens_get( const voiture_t * const voiture ) 
{ 
     return(voiture->sens) ; 
}
extern 
err_t voiture_sens_set( voiture_t * const voiture , 
			const sens_t sens) 
{ 
  voiture->sens = sens ;
  return(CORRECT) ; 
}

/*
 * Lecture/Ecriture de la vitesse de la voiture 
 */

extern 
vitesse_t voiture_vitesse_get( const voiture_t * const voiture ) 
{ 
     return(voiture->vitesse) ; 
}
extern 
err_t voiture_vitesse_set( voiture_t * const voiture , 
			const vitesse_t vitesse) 
{ 
  voiture->vitesse = vitesse ;
  return(CORRECT) ; 
}

/*
 * Lecture de la voie sur laquelle est la voiture 
 */

extern 
sens_t voiture_voie_get( const voiture_t * const voiture ) 
{ 
  return(coord_sens_get(coords_coord_get(voiture->corps,0))) ; 
}



/* 
 * Ecriture des caracteristiques completes d'une voiture 
 * la voiture doit etre cree
 */
extern
err_t voiture_set( voiture_t * voiture,
		   const coords_t * const coords,
		   const case_t marque,
		   const pid_t pid ,
		   const sens_t sens ,
		   const vitesse_t vitesse )
{
  int noerr = 0 ; 
  
  /*----------*/

  if( voiture == VOITURE_NULL ) 
    {
      fprintf( stderr , "voiture_set: affectation d'une voiture inexistant\n") ; 
      return(ERREUR) ;
    }

  if( ( noerr = voiture_corps_set( voiture , coords) ) )
    return(noerr) ;
     
  if( ( noerr = voiture_marque_set( voiture ,  marque ) ) )
    return(noerr) ; 

  if( ( noerr = voiture_pid_set( voiture , pid ) ) )
    return(noerr) ;

  if( ( noerr = voiture_sens_set( voiture , sens ) ) )
    return(noerr) ;

  if( ( noerr = voiture_vitesse_set( voiture , vitesse ) ) )
    return(noerr) ;

  return(CORRECT);
}


/*
 * Affecte une voiture à une position
 */
extern 
err_t voiture_positionner( voiture_t * const voiture ,    /* Voiture */
			   const int longueur ,
			   const sens_t sens,
			   const int depart )  /* Position de depart de la fin de la voiture 
							    Le corps de la voiture sera affecté avant cette position 
							    sur TAILLE_VOITURE cases */
{ 
     int noerr = 0 ; 
     int i = 0 ;
     coord_t coord = COORD_VIDE ;
     off_t position = - 1;
     
     /*----------*/

     /*
      * Assertions 
      */
     
     if( voiture == VOITURE_NULL )
       {
	 fprintf( stderr , "voiture_positionner: voiture inexistante\n" ) ;
	 return(ERREUR);
       }

     /*----------*/

     if( voiture->corps == NULL )
       {
	 coord_t coord_init = COORD_VIDE ;
	 
	 /* Creation du corps de la voiture */
	 voiture->corps = coords_new() ;
	 for( i=0 ; i<VOITURE_TAILLE ; i++ )
	   if( (noerr = coords_coord_add( voiture->corps , coord_init ) ) )
	     return(noerr) ; 
       }

     /* Mise à jour du corps de la voiture */
     int pas = ( voiture_sens_get(voiture) == sens ? 1 : -1 ) ;
     int depart_w = depart ;
     for( i=VOITURE_TAILLE-1 ; i>=0 ; i-- )
       {
	 si2pos( longueur , sens , depart_w , &position ) ;
	 
	 if( (noerr = coord_set( &coord , sens , depart_w , position ) ) )
	   return(noerr) ;

	 if( ( noerr = coords_coord_set( voiture->corps , i , coord ) ) )
	   return(noerr) ;
	 
	 depart_w = depart_w + pas ; 
       }

     return(CORRECT);
}

/*
 * Copie d'une voiture 
 * "voiture_cible" est cree ; s'i existait deja alors il est efface puis re-cree
 */

extern 
err_t voiture_copier( voiture_t ** voiture_cible , const voiture_t * const voiture_source ) 
{ 
  int noerr = 0 ; 

  /*----------*/

  if( (*voiture_cible) != VOITURE_NULL ) 
    {
      if( ( noerr = voiture_destroy( voiture_cible ) ) )
	return(noerr) ; 
    }

  if( ( (*voiture_cible) = voiture_new( voiture_corps_get(voiture_source) ,
					voiture_marque_get(voiture_source) ,
					voiture_pid_get(voiture_source) ,
					voiture_sens_get(voiture_source) ,
					voiture_vitesse_get(voiture_source) ) ) == VOITURE_NULL )
    return(ERREUR) ; 

  return(CORRECT) ; 
}



/* 
 * Affichage de toutes les caracteristiques d'une voiture dans un canal de sortie
 */

extern
void voiture_fprintf( FILE * restrict stream , const voiture_t * const voiture )
{
  char s_sens[STRING_LG_MAX] ;
  char s_vitesse[STRING_LG_MAX] ;
  
  /*--------------------*/
  
  if( voiture == VOITURE_NULL ) 
    {
      fprintf( stream , "(voiture inexistant)\n");
      return ;
    }
  
  /* Affichage position corps du voiture */
  sens_sprintf( s_sens , voiture->sens ) ;
  vitesse_sprintf( s_vitesse , voiture->vitesse ) ;
  fprintf( stream , "{ %c /%s/%s/ (%d) ",
	   voiture->marque ,
	   s_vitesse,
	   s_sens , 
	   voiture->pid );
  coords_fprintf( stream , voiture->corps);
  fprintf( stream , " }" );
}

/*! 
 * Affichage de toutes les caracteristiques d'une voiture sur la sortie standard 
 */

extern
void voiture_printf( const voiture_t * const voiture )
{
  voiture_fprintf( stdout , voiture ) ;
}

/*
 * Ecriture dans un fichier 
 */
extern
err_t voiture_write( const int fd , /* Descriteur du fichier */
		     const voiture_t * const voiture )
{
  size_t taille = 0 ;
  ssize_t nb_ecrits = 0 ; 
  case_t marque = CASE_VIDE ;
  pid_t pid = -1 ;
  sens_t sens = -1 ;
  vitesse_t vitesse = -1 ;

  /* Ecriture du corps */
  if( coords_write( fd , 
		    voiture_corps_get(voiture) ) == -1 )
    {
      fprintf( stderr , "voiture_write: pb sauvegarde du corps\n" );
      return(ERREUR) ; 
    } 

  /* Ecriture de la marque */
  taille = sizeof(case_t) ;
  marque = voiture_marque_get(voiture) ;
  if( ( nb_ecrits = write( fd , 
			   &marque , 
			   taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_write: pb sauvegarde de la marque : %lu octet(s) ecrit(s) / %lu octet(s) attendu(s)\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 
  
  /* Ecriture du pid */
  taille = sizeof(pid_t) ; 
  pid = voiture_pid_get(voiture) ; 
  if( ( nb_ecrits = write( fd , 
			  &pid ,  
			  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_write: pb sauvegarde du pid  : %lu octet(s) ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    }

  /* Ecriture du sens */
  taille = sizeof(sens_t) ; 
  sens = voiture_sens_get(voiture) ; 
  if( ( nb_ecrits = write( fd , 
			  &sens ,  
			  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_write: pb sauvegarde du sens : %lu octet(s) ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    }

  /* Ecriture de la vitesse */
  taille = sizeof(vitesse_t) ; 
  vitesse = voiture_vitesse_get(voiture) ; 
  if( ( nb_ecrits = write( fd , 
			  &vitesse ,  
			  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_write: pb sauvegarde de la vitesse : %lu octet(s) ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 
 
  return(CORRECT);
}

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture
 * la voiture "voiture" est cree 
 */
extern
err_t voiture_read( const int fd , /* Descriteur du fichier */
		    voiture_t ** voiture )
{
  size_t taille = 0 ;
  ssize_t nb_lus = 0 ; 
  int noerr = 0 ; 
  coords_t * corps = NULL ; 
  case_t marque = CASE_VIDE ; 
  pid_t pid = -1 ;
  sens_t sens = -1 ;
  vitesse_t vitesse = -1 ;

  if( (*voiture) != VOITURE_NULL ) 
    {
      if( ( noerr = voiture_destroy( voiture ) ) )
	return(noerr);
    }
 
  /* Lecture du corps */
  if( coords_read( fd , &corps ) == -1 )
    {
      fprintf( stderr , "voiture_read: pb read sur le corps\n" );
      return(ERREUR) ; 
    } 

  /* Lecture de la marque */
  taille = sizeof(case_t) ; 
  if( ( nb_lus = read( fd , &marque , taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_read: pb read sur la marque : %lu octet(s) lu(s) / %lu octet(s) attendu(s)\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 
  
  /* Lecture du pid */
  taille = sizeof(pid_t) ; 
  if( ( nb_lus = read( fd , &pid ,  taille ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_read: pb read sur le pid  : %lu octet(s) lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    }

  /* Lecture du sens */
  taille = sizeof(sens_t) ; 
  if( ( nb_lus = read( fd , &sens ,  sizeof(sens_t) ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_read: pb read sur le sens  : %lu octet(s) lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    }

   /* Lecture du vitesse */
  taille = sizeof(vitesse_t) ; 
  if( ( nb_lus = read( fd , &vitesse ,  sizeof(vitesse_t) ) ) != taille ) 
    {
      char mess[256] ;
      sprintf( mess , "voiture_read: pb read sur la vitesse  : %lu octet(s) lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 

  /* Creation du voiture */
  if( ( (*voiture) = voiture_new( corps , marque, pid , sens , vitesse ) ) == NULL )
      return(ERREUR) ;

  
  /* Destruction variables de travail */
  if( ( noerr = coords_destroy( &corps ) ) )
    return(noerr) ; 

  return(CORRECT);
}


/*
 * Tests
 */

extern
booleen_t voiture_demarree( const voiture_t * const voiture )
{
  /* Une voiture n'a pas demarre si elle n'a pas encore de coordonnées */
  if( voiture->corps == NULL )
    return(FAUX) ;
  else
    return(VRAI) ; 
}

extern
int voiture_comparer( const voiture_t * v1 , const voiture_t * v2 )
{
  int cmp = 0 ;

  /* Sur la marque */
  cmp = voiture_marque_get(v1) - voiture_marque_get(v2) ;
  if( cmp ) return(cmp) ;

  /* Sur le pid */
  cmp = voiture_pid_get(v1) - voiture_pid_get(v2) ;
  if( cmp ) return(cmp) ;

  /* Sur le sens */
  cmp = voiture_sens_get(v1) - voiture_sens_get(v2) ;
  if( cmp ) return(cmp) ;

  /* Sur la vitesse */
  cmp = voiture_vitesse_get(v1) - voiture_vitesse_get(v2) ;
  if( cmp ) return(cmp) ;

  /* Sur les coordonnées */
  int i = 0 ;
  coord_t coord_v1 = COORD_VIDE ;
  coord_t coord_v2 = COORD_VIDE ;
  for( i=0 ; i < VOITURE_TAILLE ; i++ )
    {
      coord_v1 = coords_coord_get( voiture_corps_get(v1) , i ) ;
      coord_v2 = coords_coord_get( voiture_corps_get(v2) , i ) ;
      if( ( cmp = coord_comparer(  &coord_v1 , &coord_v2 ) ) )
	return(cmp) ;
      
    }

  return(0) ;
}

extern
int voiture_comparer_cb( const void * v1 , const void * v2 )
{
  return( voiture_comparer( v1 , v2 ) ) ; 
}


extern
booleen_t voiture_sortie_route( const int longueur,
				const voiture_t * const voiture )
{
  int tete = -1 ;
  
  /*----------*/

  tete = coord_indice_get(voiture_debut_get(voiture)) ;
  if( (tete > longueur-1) || (tete < 0) )
    return(VRAI) ;
  else    
    return(FAUX);
}
