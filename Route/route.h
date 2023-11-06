#ifndef _ROUTE_H_
#define _ROUTE_H_

#include <voiture.h>

/*! 
 * \file  route.h
 * \brief Définitions des primitives de gestion du fichier route 
 */

/*!
 * Structure d'un fichier route<br>
 * <ul>
 * <li> sizeof(int)             : longueur de la route </li>
 * <li> sizeof(char) * longueur : contenu de la voie Ouest-Est </li>
 * <li> sizeof(char) * longueur : contenu de la voie Est-Ouest </li> 
 * </ul>
 */

/*
 *==================================================
 * Methodes set/get
 *==================================================
 */

/*! Lecture de la longueur de la route */
extern err_t route_longueur_fget( const int fd_route , int * longueur );
/*! Ecriture de la longueur de la route */
extern err_t route_longueur_set( const int fd_route , const int longueur ) ;

/*!
 * \name Lecture d'une case de la route 
 * @{
 */ 

/*! 
 * \fn err_t route_coord_fget( const int fd,
 *                             const coord_t coord,
 *                             case_t * contenu )
 * \brief Lecture à partir d'une coordonnée
 * \param[in] fd : descripteur du fichier route 
 * \param[in] coord : coordonnees de la case a lire 
 * \param[out] contenu : contenu de la case
 */
extern err_t route_coord_fget( const int fd,
                               const coord_t coord ,        
                               case_t * contenu ) ;        

/*! 
 * \fn err_t route_pos_fget( const int fd_route,
 *                           const off_t pos , 
 *                           case_t * contenu )
 * \brief Lecture à partir d'une position dans le fichier
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] pos : offset dans le fichier
 * \param[out] contenu : contenu de la case
 */
extern 
err_t route_pos_fget( const int fd_route,
                      const off_t pos  ,
                      case_t * contenu ) ;

/*! 
 * \fn err_t route_si_fget( const int fd_route,
 *                          const sens_t sens ,
 *                          const int indice ,
 *                          case_t * contenu ) 
 * \brief Lecture à partir du sens et d'un indice de case
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] sens : sens de la voie
 * \param[in] indice : indice de la case dans la voie
 * \param[out] contenu : contenu de la case
 */
extern 
err_t route_si_fget( const int fd_route ,
                     const sens_t sens  ,
                     const int indice   ,
                     case_t * contenu   ) ;

/*!
 *@}
 */

/*! 
 * \name Ecriture d'une case de la route 
 * @{
 */

/*! 
 * \fn err_t route_coord_set( const int fd,
 *                            const coord_t coord , 
 *                            const case_t contenu )
 * \brief Ecriture à partir d'une coordonnée
 * \param[in] fd : descripteur du fichier route 
 * \param[in] coord : coordonnees de la case dans laquell on écrit 
 * \param[in] contenu : contenu à écrire 
 */
extern err_t route_coord_set( const int fd,
                              const coord_t coord ,
                              const case_t contenu ) ;
/*! 
 * \fn err_t err_t route_pos_set( const int fd_route , 
 *                                const off_t pos , 
 *                                const case_t contenu )
 * \brief Ecriture à partir d'une position dans le fichier
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] pos : offset dans le fichier
 * \param[in] contenu : contenu à écrire 
 */
extern err_t route_pos_set( const int fd_route,
                            const off_t pos  ,        
                            const case_t contenu ) ;

/*! 
 * \fn err_t route_si_set( const int fd_route ,
 *                         const sens_t sens,
 *                         const int indice, 
 *                         const case_t contenu ) 
 * \brief Ecriture à partir du sens et d'un indice de case
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] sens : sens de la voie
 * \param[in] indice : indice de la case dans la voie
 * \param[in] contenu : contenu à écrire 
 */
extern err_t route_si_set( const int fd_route,        
                           const sens_t sens  ,
                           const int indice  ,        
                           const case_t contenu ) ;
/*!
 * @}
 */

/*!
 * \name Conversions
 * @{
 */

/*! 
 * \fn err_t route_si2pos( const int fd_route,
 *                         const sens_t sens ,
 *                         const int indice ,
 *                         off_t * pos )
 * \brief Convertion d'une coordonnée [sens,indice] en une position dans le fichier
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] sens : sens de la voie
 * \param[in] indice : indice de la case dans la voie
 * \param[out] pos : position dans le fichier route
 */
extern err_t route_si2pos( const int fd_route,        
                           const sens_t sens,        
                           const int indice,        
                           off_t * pos ) ;

/*! 
 * \fn err_t route_pos2si( const int fd_route , 
 *                         const off_t pos , 
 *                         sens_t * sens ,
 *                         int * indice )
 * \brief Conversion d'une position dans le fichier en une coordonnée [sens,indice]  
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] pos : position dans le fichier route
 * \param[out] sens : sens de la voie
 * \param[out] indice : indice de la case dans la voie
 */

extern err_t route_pos2si( const int fd_route,        
                           const off_t pos,        
                           sens_t * sens,        
                           int * indice ) ;        
 /*!
 * @}
 */
 
/*
 *==================================================
 * Primitives du TDA route 
 *==================================================
 */

/*! 
 * \fn err_t route_afficher( const int fd_route )
 * \brief Affichage de la route 
 * \param[in] fd_route : Descripteur fichier route 
 */
extern err_t route_afficher( const int fd_route ); 

/*!
 * \fn err_t route_initialiser( const char * const fich_route ,
 *                                const int longueur ) 
 * \brief Initialisation d'un fichier route 
 * \param[in] fich_route : nom du fichier représentant la route
 * \param[in] longueur : longueur de la portion de route 
 */
extern err_t route_initialiser( const char * const fich_route ,
                                const int longueur ) ;

/*! 
 * \fn err_t route_voiture_demarrer( const int fd_route,
 *                                   voiture_t * voiture ,
 *                                   booleen_t * ok ) 
 * \brief Démarrage d'une voiture sur une voie de la route<br>
 * La voiture doit être instanciée avec 
 * <ul>
 * <li> le sens de la voie sur laquelle elle veut demarrer 
 * <li> sa marque 
 * </ul>
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in,out] voiture : voiture à positonner en début de voie
 * <ul>
 * <li>attributs[in] : sens , marque 
 * <li>attributs[out] : corps 
 * <li>attributs non utilisés : pid
 * </ul>
 * \param[out] ok : indique si la voiture a pu être positionnée ou non 
*/
extern
err_t route_voiture_demarrer( const int fd_route,        
                              voiture_t * voiture ,
                              booleen_t * ok ) ;

/*! 
 * \fn err_t route_voiture_positionner( const int fd_route,
 *                                   voiture_t * voiture ,
 *                                   const int depart ,
 *                                   booleen_t * ok ) 
 * \brief Démarrage d'une voiture sur une voie de la route<br>
 * La voiture doit être instanciée avec 
 * <ul>
 * <li> le sens de la voie sur laquelle elle veut demarrer 
 * <li> sa marque 
 * </ul>
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in,out] voiture : voiture à positonner en début de voie
 * <ul>
 * <li>attributs[in] : sens , marque 
 * <li>attributs[out] : corps 
 * <li>attributs non utilisés : pid
 * </ul>
 * \param[in] depart : indice de départ sur la voie choisie
 * \param[out] ok : indique si la voiture a pu être positionnée ou non 
 */

extern
err_t route_voiture_positionner( const int fd_route,	
				 voiture_t * voiture ,	
				 const int depart ,	
				 booleen_t * ok ) ; 
/*!
 * \fn err_t route_voiture_deplacement_calculer( const int fd_route,
 *                                               const voiture_t * const voiture,
 *                                               const booleen_t depassement ,
 *                                               off_t * position_deplacement ,
 *                                               off_t * portee_deplacement ,
 *                                               booleen_t * sortie )
 * \brief calcul du déplacement d'une voiture selon sa vitesse 
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] voiture : voiture à déplacer
 * \param[in] depassement : indique si la voiture fait un depassment (change de voie)
 * \param[out] position_deplacement : future position de fin de la voiture 
 * \param[out] portee_deplacement : future portée du déplacement depuis position_deplacement. Celle ci est comprise dans l'intervalle [-VOITURE_TAILLE .. +VOITURE_TAILLE]
 * \param[out] sortie : indique si la voiture est sortie de la route 
 */
extern err_t route_voiture_deplacement_calculer( const int fd_route,                 
                                                 const voiture_t * const voiture,
                                                 const booleen_t depassement , 
                                                 off_t * position_deplacement ,
                                                 off_t * portee_deplacement ,
                                                 booleen_t * sortie ) ;


/*!
 * \fn err_t route_voiture_deplacer( const int fd_route,
 *                              voiture_t * voiture,
 *                              const off_t depart ,
 *                              booleen_t * arrivee ) 
 * \brief Déplacement d'une voiture sur la route et mise à jour éventuelle de ses coordonnées
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in,out] voiture : voiture à déplacer
 * \param[in] depart : position dans le fichier à partir de laquelle il faut déplacer la voiture
 * \param[out] arrivee : indique si la voiture est arrivee à la fin de la route. Dans ce cas
 * <ul>
 * <li> la voiture peut avoir des coordonnées en dehors de la route
 * <li> la voiture n'est pas reporté sur le fichier route
 * </ul>
 */
extern err_t route_voiture_deplacer( const int fd_route,
                                     voiture_t * voiture,
                                     const off_t depart ,
                                     booleen_t * arrivee ) ;

/*!
 * \fn err_t route_voiture_set( const int fd_route,
 *                         const voiture_t * const voiture )
 * \brief Ecriture d'une voiture sur la route
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] voiture : voiture à écrire dans le fichier route 
 */

extern
err_t route_voiture_set( const int fd_route,
                         const voiture_t * const voiture ) ;

/*!
 * \fn err_t err_t route_voiture_effacer( const int fd_route,
 *                             const voiture_t * const voiture ) 
 * \brief Effacement d'une voiture sur dans le fichier route
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] voiture : voiture à effacer
 */
extern
err_t route_voiture_effacer( const int fd_route,
                             const voiture_t * const voiture ) ;

/*!
 * \fn err_t route_voiture_rabattement_calculer( const int fd_route,
 *					  const voiture_t * const voiture,
 *					  off_t * position_rabattement ) ;
 *     
 * \brief Calcul des positions d'unevoiture quand elle veut se rabattre sur la voie opposée
 * \param[in] fd_route : descripteur du fichier route 
 * \param[in] voiture : voiture à faire rabattre
 * \param[out] position_rabattement : nouvelle position de la tête de la voiture après le rabattement
 */
extern
err_t route_voiture_rabattement_calculer( const int fd_route,
					  const voiture_t * const voiture,
					  off_t * position_rabattement ) ;
/*!
 * \name Tests
 * @{
 */

/*! Teste si une voiture est arrivée à la fin de la portion de route : cette fonction n'utilise pas la zone critique du fichier */
extern
booleen_t route_voiture_arrivee( const int fd_route,
                                 const voiture_t * const voiture ) ;

/*! Teste si il y a une collision sur la route : cette fonction lit dans la zone critique du fichier */
extern
booleen_t route_collision( const int fd_route) ;

/*! Teste si il y a collisionpour une voiture */
extern
err_t route_voiture_collision( booleen_t * collision ,
			       const int fd_route,
			       const voiture_t * const voiture ) ; 
/*!
 * @}
 */

#endif

