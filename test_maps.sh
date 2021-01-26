#! /bin/bash

# MAP INVALIDES
nb_invalid_map=`ls ./cub/invalid_map | wc -w`
rm -rf err.log
for filename in ./cub/invalid_map/*.cub; do
	./Cub3D "$filename" "--save" 1> /dev/null 2>> err.log
done
found_invalid_map=`cat err.log | wc -l`
if [ $found_invalid_map == $nb_invalid_map ]
then
	printf "\033[32mLes $nb_invalid_map maps invalides sont ok.\033[0m\n"
else
	printf "\033[31m$($nb_invalid_map-$found_valid_map) n'ont pas été trouvées.\033[0m\n"
fi

# MAP VALIDES
rm -rf err.log
nb_valid_map=`ls ./cub/valid_map | wc -w`
for filename in ./cub/valid_map/*.cub; do
	./Cub3D "$filename" "--save" 1> /dev/null 2>> err.log
done
found_valid_map=`cat err.log | wc -l`
if [ $found_valid_map == 0 ]
then
	printf "\033[32mLes $nb_valid_map maps valides sont ok.\033[0m\n"
else
	printf "\033[31m$found_valid_map en trop on ete trouvées.\033[0m\n"
fi
rm -rf err.log
