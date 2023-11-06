#ifndef _COORDS_H_
#define _COORDS_H_

/*! 
 * \file  coords.h
 * \brief Définitions des primitives de gestion d'une liste de coordonnées
 */
#include <coord.h>


/*!
 * \struct coords_s
 * \brief Attributs d'une liste de coordonnées
 * \typedef coords_t
 * \brief Type d'une liste de coordonnées
 */
typedef struct coords_s
{
  int nb ;		/*!< Nombre de coordonnées dans la liste */
  coord_t * coords ;	/*!< Tableau de coordonnées */
} coords_t ;

/*
 * Methodes set/get
 */


/*! Acces au nombre de coords dans la liste */
extern int coords_nb_get( const coords_t * const l );
/*! Acces a une coord dans la liste */
extern coord_t coords_coord_get( const coords_t * const l  , const int ind_coord );
/*! 
 * Affectation d'une coord dans une liste de coords 
 * La position du coord doit exister
 * L'ancienne valeur du coord est ecrasee  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern err_t coords_coord_set( coords_t * const liste_coords , 
			       const int ind_coord , 
			       const coord_t coord )  ;

/* 
 * Primitives 
 */

/*!
 * Creation d'une liste de coords
 */
extern coords_t * coords_new() ;

/*!
 *  Destruction d'une liste de coords 
 */
extern int coords_destroy( coords_t ** liste_coords ) ;

/*!
 * \name Affichage d'une liste de coords 
 *@{
 */
/*! Affichage sur la sortie standard */
extern void coords_printf( const coords_t * const liste_coords );
/*! Affichage dans un canal de sortie */ 
extern void coords_fprintf( FILE * restrict stream , const coords_t * const liste_coords ) ;
/*!
 *@}
 */

/*! 
 * Copie d'une liste de coordonnees
 */
extern err_t coords_copier( coords_t ** coords_cible,
			    const coords_t * const coords_source ) ;
/*!
 * Ajout d'une coord dans une liste de coords 
 * L'affectation se fait par copie  
 * NB : affectation par copie OK car pas de pointeur dans coord_t
 */
extern err_t coords_coord_add( coords_t * const liste_coords , 
			       const coord_t coord ) ;

/*! 
 * Deletion d'une coord dans une liste de coords 
 */
extern err_t coords_coord_del( coords_t * const liste_coords , 
			       const int ind_coord )  ;

/*!
 * \name Methodes sauvegarde/restauration
 * @{
 */

/*!
 * Chargement d'une liste de coords a partir d'un fichier 
 * Le descripteur "fd" doit correspondre a un fichier ouvert en lecture
 * la liste "liste_coords" est creee 
 */
extern 
err_t coords_read(  const int fd ,  /* descripteur fichier de restauration */
		    coords_t ** liste_coords ) ; /* structure liste coords a charger */

/*!
 * Ecriture du contenu d'une liste de coords dans un fichier
 * Le descripteur doit coorespondre a un fichier ouvert en ecriture
 */
extern 
err_t coords_write(  const int fd ,  /* descripteur fichier de restauration */
		     const coords_t * const liste_coords ) ; /* structure liste coords a charger */

/*!
 * @}*/

/*
 * \name Methode de recherche d'un element 
 */

/*!
 * Recherche d'une coord dans une liste de coords 
 * Valeur retournee : indice du premier coord trouve dans la liste si il existe  
 *                    -1 sinon 
 */

extern 
int coords_coord_seek( const coords_t * const liste_coords,
		       const coord_t * coord ,
		       int (*comparer) (const coord_t * , const coord_t * ) ) ;

/*!
 * \fn int coords_comparer( const coords_t * l1,
 *		            const coords_t * l2 )
 * \brief Comparaison de 2 listes de coords l1 et l2
 * \param[in] l1 : liste 1 à comparer
 * \param[in] l2 : liste 2à comparer
 * \return
 * <ul>
 * <li> < 0 si l1 <  l2
 * <li>   0 si l1 == l2
 * <li> > 0 si l1 >  l2
 * </ul>
 */

extern 
int coords_comparer( const coords_t * l1,
		     const coords_t * l2 ) ;


#endif


