#ifndef _COORD_H_
#define _COORD_H_

#include <commun.h> 
/*! 
 * \file  coord.h
 * \brief Définitions des primitives de gestion d'une coordonnee 
 */


/*!
 * \struct coord_s
 * \brief Attributs d'une coordonnée
 * \typedef coord_t
 * \brief Type d'une coordonnée
 */

typedef struct coord_s
{
     sens_t sens ;	/*!< sens de la voie          */
     int indice  ;	/*!< indice case dans la voie */
     off_t pos ;	/*!< position dans le fichier */
} coord_t ;

/*
 * Definitions des constantes 
 */

/*!
 * \def COORD_VIDE
 * \brief Valeur d'initialisation d'une coordonnée
 */
#define COORD_VIDE coord_vide() 

/*! Retourne Valeur d'initialisation d'une coordonnée */
extern coord_t coord_vide() ;

/*!
 * \name Fonctions get/set des attributs d'une coordonnee
 * @{
 */
/*! Lecture du sens */
extern int coord_sens_get( const coord_t c ) ;
/*! Ecriture du sens */
extern err_t coord_sens_set( coord_t * const c , const sens_t sens );

/*! Lecture de l'indice */
extern int coord_indice_get( const coord_t c );
/*! Ecriture de l'indice */
extern err_t coord_indice_set( coord_t * const c ,  const int indice ) ;

/*! Lecture de la position dans le fichier */
extern off_t coord_position_get( const coord_t c ) ;
/*! Ecriture de la position dans le fichier */
extern err_t coord_position_set( coord_t * const c , const off_t position ) ;

/*! Lecture globale d'une coordonnée : les attributs sont lus dans 3 paramètres */
extern err_t coord_set( coord_t * const coord , 
			const sens_t sens,
			const int indice,
			const off_t position ) ;

/*! Ecriture globale d'une coordonnée : les 3 attributs sont donnés en une fois */
extern err_t coord_get( const coord_t coord , 
			sens_t * sens,
			int * indice,
			off_t * position ) ;

/*!
 * @}
 */

/*! 
 * \name Affichages
 * @{
 */

/*! Affichage sur un canal de sortie */
extern void coord_fprintf( FILE * restrict stream, const coord_t coord ) ;
/*! Affichage sur la sortie standard */
extern void coord_printf( const coord_t coord ) ;

/*!
 * @}
 */

/*!
 * \fn int coord_write( const int fd , 
 *		        const coord_t coord ) ;
 * \brief Ecriture d'une coordonnnee dans un fichier 
 * \param[in] fd : descripteur d'un fichier ouvert en écriture
 * \param[out] coord : coordonnée à écrire
 */
extern int coord_write( const int fd ,          
			const coord_t coord ) ; 

/*!
 * \fn int coord_read( const int fd , 
 *		       coord_t * const coord ) ;
 * \brief Lecture d'une coordonnee depuis un fichier 
 * \param[in] fd : descripteur d'un fichier ouvert en lecture
 * \param[out] coord : pointeurr sur une zone suffisante pour stocker une coord_t 
 */
extern
int coord_read( const int fd , 
		coord_t * const coord ) ;

/* 
 * Comparaison de 2 coordonnees 
 * retour < 0 si c1 < c2 
 *        = 0 si c1 = c2 
 *        > 0 si c1 > c2 
 */

/*! Comparaison globale */
extern int coord_comparer( const coord_t * c1,
			   const coord_t * c2 ) ;

/*! Comparaison sur sens/case */
extern int coord_xy_comparer( const coord_t * c1,
			      const coord_t * c2 ) ;

/*! Comparaison sur offset (position dans le fichier) */
extern int coord_pos_comparer( const coord_t * c1,
			       const coord_t * c2 ) ;

/*! Affectation des coordonnees d'une case */
extern err_t coord_copier( coord_t * const coord_cible,	
			   const coord_t coord_source ) ; 

#endif
