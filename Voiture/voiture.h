#ifndef _VOITURE_H_
#define _VOITURE_H_

#include <coords.h>

/*! 
 * \file  voiture.h
 * \brief Définitions des primitives de gestion d'une voiture
 */

/*
 *=============================================================
 * Constantes du TDA voiture
 *=============================================================
 */

/*!
 * \def VOITURE_TAILLE 
 * \brief Taille du coprs d'une voiture
 * \def VOITURE_NULL 
 * \brief Valeur d'initilisation d'une pointe sur une voiture 
 * \def VOITURE_VIDE 
 * \brief Valeur d'une voiture vide
 */
#define VOITURE_TAILLE  3
#define VOITURE_NULL NULL 
#define VOITURE_VIDE voiture_vide()



/*!
 * \struct voiture_s
 * \brief Attributs d'une voiture
 * \typedef voiture_t
 * \brief Type d'une voiture
 */
typedef struct voiture_s
{
  coords_t   * corps ;     /*!< Liste des TAILLE_VOITURE coordonnees du corps de la voiture */
  case_t       marque ;    /*!< 1 caractere identifiant la voiture */
  pid_t        pid ;       /*!< PID du processus voiture */
  sens_t       sens ;	   /*!< voie sur laquelle circule la voiture */
  vitesse_t    vitesse ;   /*!< vitesse de la voiture */
} voiture_t ;


/*
 *=============================================================
 * Primitives du TDA voiture 
 *=============================================================
 */

/*!
 * Valeur voiture vide 
 */

extern voiture_t voiture_vide() ;

/*
 * Methodes creation/destruction 
 */
/*! Creation d'une voiture */
extern voiture_t * voiture_new(const coords_t * const coords,
			       const case_t marque,
			       const pid_t pid ,
			       const sens_t sens ,
			       const vitesse_t vitesse )  ;
/*! Destruction d'une voiture */
extern int voiture_destroy( voiture_t ** voiture )  ;

/*!
 * \name Methodes  get/set 
 * @{
 */

/*! Accès aux coordonnées du corps d'une voiture */
extern coords_t * voiture_corps_get( const voiture_t * const voiture )  ;
/*! Affectation des coordonnées du corps d'une voiture */
extern err_t voiture_corps_set( voiture_t * const voiture ,    
			      const coords_t * const coords) ; 

/*! Accès à la position de début du corps d'une voiture */
extern coord_t voiture_debut_get( const voiture_t * const voiture ) ;
/*! Accès à la position de fin du corps d'une voiture*/
extern coord_t voiture_fin_get( const voiture_t * const voiture )  ;

/*! Accès à la marque d'identification d'une voiture */
extern case_t voiture_marque_get( const voiture_t * const voiture )  ;
/*! Affectation de la marque d'identification d'une voiture */
extern err_t voiture_marque_set( voiture_t * const voiture , 
			       const case_t m)  ;

/*! Accès au pid du processus d'une voiture */
extern pid_t voiture_pid_get( const voiture_t * const voiture )  ;
/*! Affectation du pid du processus d'une voiture */
extern err_t voiture_pid_set( voiture_t * const voiture , const pid_t pid) ;

/*! Accès au sens de la voie sur laquelle est la voiture */
extern sens_t voiture_sens_get( const voiture_t * const voiture ) ;
/*! Affectation du sens de la voie sur laquelle est la voiture */
extern err_t voiture_sens_set( voiture_t * const voiture , const sens_t sens) ;

/*! Accès à la vitesse de la voiture */
extern vitesse_t voiture_vitesse_get( const voiture_t * const voiture ) ;
/*! Affectation de la vitesse de la voiture */
extern err_t voiture_vitesse_set( voiture_t * const voiture , const vitesse_t vitesse) ;

/*! Acces a la voie sur laquelle circule la voiture */
extern sens_t voiture_voie_get( const voiture_t * const voiture ) ;

/*! Affectation globale des attributs d'une voiture */
extern err_t voiture_set( voiture_t * voiture,
			  const coords_t * const coords,
			  const case_t marque,
			  const pid_t pid ,
			  const sens_t sens ,
			  const vitesse_t vitesse  );
/*!
 * @}
 */

/*!
 * \fn err_t voiture_positionner( voiture_t * const voiture , 
 *                                const int longueur ,
 *                                const sens_t sens ,
 *                                const int depart ) 
 * \brief Affecte les coordonnées d'une voiture à partir d'une position
 * \param[in,out] voiture : voiture à positionner. Les coordonnées de la voiture seront affectées depuis la coordonnée de fin de la voiture et sur VOITURE_TAILLE coordonnées. 
 * La coordonnée de fin sera affectée par  la position (sens,depart) puis les suivantes en incrémentant l'indice de départ.
 * \param[in] longueur : longueur de la route 
 * \param[in] sens : voie sur laquelle on veut positionner la voiture
 * \param[in] depart : indice de la voie à partir duquel il faut positonner la voiture
 */
extern err_t voiture_positionner( voiture_t * const voiture , 
				  const int longueur ,
				  const sens_t sens,
				  const int depart ) ;
					

/*!
 * Copie d'une voiture 
 * "voiture_cible" est cree ; s'i existait deja alors il est efface puis re-cree
 */
extern err_t voiture_copier( voiture_t ** voiture_cible , const voiture_t * const voiture_source ) ;

/*! 
 * \name Affichages de toutes les caracteristiques d'une voiture 
 * @{
 */

/*! sur la sortie standard (raccourci de voiture_fprintf( stdout , voiture ) */

extern void voiture_printf( const voiture_t * const voiture ) ;

/*! dans un canal de sortie */

extern void voiture_fprintf( FILE * restrict stream , const voiture_t * const voiture ) ; ;

/*!
 * @} 
 */

/*!
 * \fn err_t voiture_write( const int fd , 
 *			 const voiture_t * const voiture ) 
 * \brief Sauvegarde d'une voiture dans un fichier 
 * \param[in] fd : descripter d'un fichier qui doit être ouvert en écriture
 * \param[in] voiture : voiture à sauvegarder. 
 */
extern err_t voiture_write( const int fd , 
			    const voiture_t * const voiture ) ;

/*!
 * \fn err_t voiture_read( const int fd , 
 *			   voiture_t ** voiture ) 
 * \brief Chargement d'une voiture depuis un fichier  
 * \param[in] fd : descripteur de fichier qui doit être ouvert en lecture 
 * \param[out] voiture : voiture à charger ; celle-ci est créée par la fonction 
  */
extern err_t voiture_read( const int fd , 
			   voiture_t ** voiture ) ;
/*!
 * \fn booleen_t voiture_demarree( const voiture_t * const voiture )
 * \brief Teste si une voiture à déjà été mise sur la route. <br>NB: une voiture non démarrée n'a pas de coordonnées
 * \param[in] voiture : la voiture à tester
 * \return 
 * - VRAI si la voiture à démarré (si elle possède des coordonnées
 * - FAUX sinon 
 */
extern booleen_t voiture_demarree( const voiture_t * const voiture ) ;

/*!
 * \fn booleen_t booleen_t voiture_sortie_route( const int longueur,
 *				                 const voiture_t * const voiture )
 * \brief Teste si une voiture est arrivée au bout d'une route 
 * \param[in] longueur : longueur de la route
 * \param[in] voiture : la voiture à tester
 * \return 
 * - VRAI si la voiture est arrivée
 * - FAUX sinon 
 */
extern booleen_t voiture_sortie_route( const int longueur,
				       const voiture_t * const voiture ) ;
/*!
 * \name Comparaisons
 * @{
 */

/*! Comparasion de 2 voitures */
extern int voiture_comparer( const voiture_t * v1 , const voiture_t * v2 ) ;
/*! Fonctin générique de voiture_comparer */
extern int voiture_comparer_cb( const void * v1 , const void * v2 ) ;

/*!
 *@}
 */


#endif


