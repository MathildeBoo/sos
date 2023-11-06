#ifndef _COMMUN_H_
#define _COMMUN_H_
/*! 
 * \file  commun.h
 * \brief Définitions des types de base 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*!
 * \def CORRECT 
 * \brief pas d'erreur
 * \def ERREUR 
 * \brief code erreur 
 * \def PAS_TROUVE
 * \brief recherche négative
 * \def TEMPS_LONG 
 * \brief Valeur d'un temps long 
 * \def TEMPS_MOYEN
 * \brief Valeur d'un temps moyen
 * \def TEMPS_COURT 
 * \brief Valeur d'un temps court
 * \def MESS_LONGUEUR
 * \brief Longueur d'un message d'erreur
 * \def STRING_LG_MAX 
 * \brief longueur maximum d'une chaine de caractères
*/

#define CORRECT 0	
#define ERREUR -1 
#define PAS_TROUVE -2 

#define TEMPS_LONG 10
#define TEMPS_MOYEN 5
#define TEMPS_COURT 1 

#define MESS_LONGUEUR 256
#define STRING_LG_MAX 512


/*! 
 * \typedef err_t
 * \brief type erreur 
 */
typedef int err_t ;

/*!
 * \enum booleen_s 
 * \brief Valeurs du type booleen_t
 * \typedef booleen_t
 * \brief type booleen 
 */
typedef enum booleen_s { FAUX=0 , VRAI=1 } booleen_t ;

/*!
 * \typedef case_t
 * \brief TDA case : cellule , une position de la route
 */
typedef char case_t ;

/*! 
 * \def CASE_VIDE
 * \brief Valeur d'une case vide 
 */
#define CASE_VIDE ' '

/*! 
 * Taille de l'entete d'un fichier route 
 * longueur : sizeof(int)
 */
#define TAILLE_ENTETE sizeof(int) 

/*!
 * \enum sens_s
 * \brief valeurs du type sens_t
 * \typedef sens_t
 * \brief type sens 
 */
typedef enum sens_s { OUEST_EST , EST_OUEST } sens_t ;

/*!
 * \enum vitesse_s
 * \brief valeurs du type vitesse_t
 * \typedef vitesse_t
 * \brief type vitesse 
 */
typedef enum vitesse_s { LENTE=1 , MOYENNE=2 , RAPIDE=3 } vitesse_t ;


/*!
 * \name Transformation d'un type e chaine de caractères
 * @{
 */

/*!
 * \fn err_t sens_sprintf( char * string , const sens_t sens )
 * \brief Transformation d'une variable de type sens en une chaine de caractères
 * \param[out] string : la chaine de caractères cible. Celle ci doit être réservée avant l'appel 
 * \param[in] sens : le sens à transformer en string
 */
extern err_t sens_sprintf( char * string , const sens_t sens ) ;

/*!
 * \fn err_t vitesse_sprintf( char * string , const vitesse_t vitesse )
 * \brief Transformation d'une variable de type vitesse en une chaine de caractères
 * \param[out] string : la chaine de caractères cible. Celle ci doit être réservée avant l'appel 
 * \param[in] vitesse : le vitesse à transformer en string
 */
extern err_t vitesse_sprintf( char * string , const vitesse_t vitesse ) ;

/*!
 * @}
 */

/*!
 * \name Tests
 * @{
 */

/*!
 * \fn booleen_t sens_correct( const sens_t sens )
 * \brief Vérifie si un sens à une valeur correcte
 * \return 
 * <ul>
 * <li> VRAI si valeur correcte
 * <li> FAUX sinon 
 * </ul>
 */
extern booleen_t sens_correct( const sens_t sens );

/*!
 * \fn booleen_t vitesse_correcte( const vitesse_t vitesse )
 * \brief Vérifie si une vitesse à une valeur correcte
 * \return 
 * <ul>
 * <li> VRAI si valeur correcte
 * <li> FAUX sinon 
 * </ul>
 */
extern booleen_t vitesse_correcte( const vitesse_t vitesse );

/*!
 * \fn booleen_t pos_correcte( const int longueur ,
 *			       const sens_t sens ,
 *			       const off_t position ) 
 * \brief Vérifie si une position/offset à une valeur correcte par rapport au sens de la voie
 * \param[in] longueur : longueur de la route
 * \param[in] sens : sens de la voie 
 * \param[in] position : position à vérifier
 * \return 
 * <ul>
 * <li> VRAI si valeur correcte 
 * <li> FAUX sinon 
 * </ul>
 */
extern booleen_t pos_correcte( const int longueur ,
			       const sens_t sens ,
			       const off_t position ) ;

/*!
 * @}
 */

/*! 
 * \name Conversions
 *@{
 */

/*!
 * \fn err_t si2pos( const int longueur,
 *                   const sens_t sens,
 *                   const int indice,
 *                   off_t * pos )  
 * \brief Conversion d'un couple (sens,indice) en une position dans le fichier
 * \param[in] longueur  : longueur de la route
 * \param[in] sens : sens de la voie 
 * \param[in] indice : indice/position dans la voie 
 * \param[out] pos : position/offset dans le fichier route 
 */
extern err_t si2pos( const int longueur ,
		     const sens_t sens,	
		     const int indice,	
		     off_t * pos ) ;

/*!
 * \fn err_t pos2si( const int longueur , 
 *                   const off_t pos , 
 *                   sens_t * sens,
 *                   int * indice )	
 * \brief Conversion d'une position dans le fichier en un couple (sens,indice)  
 * \param[in] longueur  : longueur de la route
 * \param[in] pos : position/offset dans le fichier route 
 * \param[out] sens : sens de la voie 
 * \param[out] indice : indice/position dans la voie 
 */
extern err_t pos2si( const int longueur,
		     const off_t pos,	
		     sens_t * sens,	
		     int * indice) ;

/*!
 *@}
 */

/*! 
 * \name Correspondances opposées dans les 2 voies 
 *@{
 */

/*! Indice dans la voie opposée */
extern int indice_oppose( const int longueur , const int indice  );
/*! voie opposée */
extern sens_t sens_oppose( const sens_t sens ) ;
/*! position dans la voie opposée */
extern off_t position_opposee( const int longueur , const off_t pos ) ;

/*!
 *@}
 */


/*!
 * \fn err_t startlen2flock( off_t * flock_start , 
 *                           off_t * flock_len ,
 *		             const off_t start  , 
 *                           const off_t len   ) 
 * \brief Conversion d'une zone (debut+portee) sur la route en une zone (start+len) dans un verrou de type struct flock. 
 * En effet, les portées négatives des verrous posés sont converties par le SE en des portées positives et en déplaçant le début du verrou 
 * \param[out] flock_start  : début de la zone pour le verrou
 * \param[out] flock_len : portée pour le verrou 
 * \param[in] start  : début initial de la zone 
 * \param[in] len : portée initiale de la zone 
 */

extern
err_t startlen2flock( off_t * flock_start , off_t * flock_len ,
		      const off_t start   , const off_t len   ) ;


#endif
