if( test $# -ne 3 -a $# -ne 4 )
then
    
    echo "$0 : Nombre de parametres incorrect $# (2 attendus)"
    echo "Usage: $0 <fichier route> <nb voitures> <type voiture> [<sens> (E/O)]"
    exit 1
fi 

OptionSens=X
if( test $# -eq 4 )
then
    echo " <sens> = $4"
    if( test $4 = "E" -o $4 = "O" )
    then
	OptionSens=$4
    else
	echo "$0 : parametre sens incorrect $4 (E ou O)"
	exit 1
    fi
fi

fich_route=$1
nb_voitures=$2
type_voiture=$3

if( ! test -e   $fich_route )
then
    echo "Fichier route $fich_route inconnu"
    exit 1
fi

if( test $3 != "v1" -a $3 != "v2" )
then
    echo "Type de voiture $3 inconnu(v1 ou v2)"
    exit 1
fi

tab_marques=( A B C D E F G H I J K L M N O P Q R S T U V W X Y Z )
i_marques=0 
tab_sens=( O E )
i_sens=0 
tab_vitesses=( L M R )
i_vitesses=0 

i_voitures=0
marque='A'
sens='O'
vitesse='L'
while( test $i_voitures -lt $nb_voitures )
do
    marque=${tab_marques[$i_marques]}
    i_marques=`expr \( $i_marques + 1 \) % 26`

    if( test $OptionSens != "X" )
    then
	sens=$OptionSens
    else	
	sens=${tab_sens[$i_sens]}
	i_sens=`expr $RANDOM % 2`
    fi

    vitesse=${tab_vitesses[$i_vitesses]}
    i_vitesses=`expr $RANDOM % 3`
             
    echo "lancement $i_voitures: voiture $marque $sens $vitesse"
    ./voiture_$3 --verbose=1 $fich_route $marque $sens $vitesse &
    
    i_voitures=`expr $i_voitures + 1`
done 

