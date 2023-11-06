#include <coord.h>

/*
 * Fonctions get/set des attributs d'une coordonnee
 *=================================================
 */

extern 
int coord_sens_get( const coord_t c )
{
  return(c.sens) ;
}
extern 
err_t coord_sens_set( coord_t * const c , 
		      const sens_t sens )
{
  c->sens = sens ;
  return(CORRECT) ;
}

extern 
int coord_indice_get( const coord_t c )
{
  return(c.indice) ;
}
extern 
err_t coord_indice_set( coord_t * const c , 
			const int indice )
{
  c->indice = indice ;
  return(CORRECT);
}

extern 
off_t coord_position_get( const coord_t c )
{
  return(c.pos) ;
}
extern 
err_t coord_position_set( coord_t * const c , 
			  const off_t position )
{
  c->pos = position  ;
  return(CORRECT);
}

/* 
 * Ecriture/Lecture globale d'une coordonnee
 */

extern
err_t coord_set( coord_t * const coord , 
		 const sens_t sens,
		 const int indice,
		 const off_t position )
{
  int noerr = 0 ; 

  if( ( noerr = coord_sens_set(coord,sens) ) )
    return(noerr) ; 
  if( ( noerr = coord_indice_set(coord,indice) ) )
    return(noerr) ;
  if( ( noerr = coord_position_set(coord,position) ) )
    return(noerr) ;
  return(CORRECT) ;
}


extern
err_t coord_get( const coord_t coord , 
		 sens_t * sens,
		 int * indice,
		 off_t * position )
{
  (*sens)     = coord_sens_get(coord) ;
  (*indice)   = coord_indice_get(coord) ;
  (*position) = coord_position_get(coord) ;
  return(CORRECT) ; 
}

/* 
 * Affichages
 */

extern
void coord_fprintf( FILE * restrict stream, 
	       const coord_t coord )
{
  char string[STRING_LG_MAX] ;
  sens_sprintf( string , coord_sens_get(coord) ) ;
  fprintf( stream , "%s[%d](%lld)" , 
	   string , 
	   coord_indice_get(coord) ,
	   (long long int)coord_position_get(coord) );
}

extern
void coord_printf( const coord_t coord )
{
  coord_fprintf(stdout, coord ) ;
}

/*
 * Ecriture dans un fichier 
 */
extern
int coord_write( const int fd , /* Descriteur du fichier */
		 const coord_t coord )
{
  coord_t coord_w = coord ; 
  const size_t taille = sizeof(coord_t) ;
  ssize_t nb_ecrits = 0 ; 

  if( ( nb_ecrits= write( fd , &coord_w , taille ) != taille ) )
    {
      char mess[256] ;
      sprintf( mess , "coord_write: pb write : %lu octets ecrit(s) / %lu octets attendus\n" ,
	       nb_ecrits , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 
  return(CORRECT);
}

/*
 * Lecture dans un fichier 
 * Le fichier descripteur "fd" doit etre ouvert en lecture 
 * le parametre "coord" doit pointer sur une zone suffisante pour stocker une coord_t 
 */
extern
int coord_read( const int fd , /* Descriteur du fichier */
		coord_t * const coord )
{
  const size_t taille = sizeof(coord_t) ;
  ssize_t nb_lus = 0 ; 

  if( coord == NULL ) 
    {
      fprintf( stderr, "coord_read: coord inexistante\n") ; 
      return(ERREUR)  ;
    }

  if( ( nb_lus = read( fd , coord, taille ) != taille ) )
    {
      char mess[256] ;
      sprintf( mess , "coord_read: pb read : %lu octets lu(s) / %lu octets attendus\n" ,
	       nb_lus , taille );
      perror(mess) ; 
      return(ERREUR) ; 
    } 
  return(CORRECT);
}



/* 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */

/* Comparaison globale */

extern 
int coord_comparer( const coord_t * c1,
		    const coord_t * c2 )
{
     int cmp_s = c1->sens - c2->sens ;
     int cmp_i = c1->indice - c2->indice ;
     int cmp_pos = (int)(c1->pos - c2->pos) ;

     /*----------*/

     if( cmp_s )
	  return(cmp_s);
     else
     {
	  if( cmp_i )
	       return(cmp_i);
	  else
	       return(cmp_pos) ;
     }		    
}

/* Comparaison sur sens/colonne */

extern 
int coord_si_comparer( const coord_t * c1,
		       const coord_t * c2 )
{
     int cmp_s = c1->sens - c2->sens ;
     int cmp_i = c1->indice - c2->indice ;

     /*----------*/

     if( cmp_s )
	  return(cmp_s);
     else
       return(cmp_i);
}

/* Comparaison sur offset (position dans le fichier) */

extern 
int coord_pos_comparer( const coord_t * c1,
			const coord_t * c2 )
{
     int cmp_pos = (int)(c1->pos - c2->pos) ;

     /*----------*/

     return(cmp_pos);
}



/* 
 * Affectation des coordonnees d'une case 
 */

extern
err_t coord_copier( coord_t * const coord_cible,
		    const coord_t coord_source )
{
  int noerr = 0 ; 

  if( ( noerr = coord_sens_set( coord_cible , 
				 coord_sens_get(coord_source) ) ) )
    return(noerr) ;
  
  if( ( noerr = coord_indice_set( coord_cible , 
				  coord_indice_get(coord_source) ) ) )
    return(noerr) ;
  
  if( ( noerr = coord_position_set( coord_cible , 
				    coord_position_get(coord_source) ) ) )
    return(noerr) ;
  
  return(noerr) ;
}

/* 
 * Renvoie d'une coordonnee vide 
 */
extern
coord_t coord_vide() 
{
  coord_t coord ; 

  coord.sens   = -1 ;
  coord.indice = -1 ;
  coord.pos    = -1 ; 
  return(coord) ; 
}
