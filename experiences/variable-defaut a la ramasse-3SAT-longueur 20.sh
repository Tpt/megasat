#!/bin/bash

rm -f variable.dat
echo "argument -moms -dlis -moms-wl -dlis-wl -wl" >> variable.dat

# une boucle for:
# la variable entree parcourt toutes les valeurs que renvoie la commande
# seq 25 40
# on pourrait aussi faire  "for entree in `ls exemples/`" pour parcourir
# tous les noms de fichier contenus dans le sous-repertoire exemples/.
# au passage, la syntaxe `bla` est utilisee pour designer "la valeur
# renvoyee par l'execution de la commande bla"

nbVar=$1
max=$2
pas=$3


heuristiques[0]="-malin"
heuristiques[1]="-rand"
heuristiques[2]="-moms"
heuristiques[3]="-dlis"
heuristiques[4]=""
wl[0]="-wl"
wl[1]=""

rm -f temp_var.cnf

while [ "$nbVar" -le "$max" ]; do
    it=0
    total00="0.0"
    total10="0.0"
    total20="0.0"
    total30="0.0"
    total40="0.0"
    total01="0.0"
    total11="0.0"
    total21="0.0"
    total31="0.0"
    total41="0.0"
    while [ "$it" -le 99 ] ; do
        echo "Nombre de variable " $nbVar
        
        ./../gen/gen $nbVar "20" "3" "3" "temp_var.cnf"
        #echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps00.txt ./../resol "temp_var.cnf" ${heuristiques[0]} ${wl[0]}
        #echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps10.txt ./../resol "temp_var.cnf" ${heuristiques[1]} ${wl[0]}
        echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps20.txt ./../resol "temp_var.cnf" ${heuristiques[2]} ${wl[0]}
        echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps30.txt ./../resol "temp_var.cnf" ${heuristiques[3]} ${wl[0]}
        #echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps40.txt ./../resol "temp_var.cnf" ${heuristiques[4]} ${wl[0]}
        #echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps01.txt ./../resol "temp_var.cnf" ${heuristiques[0]} ${wl[1]}
        #echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps11.txt ./../resol "temp_var.cnf" ${heuristiques[1]} ${wl[1]}
        echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps21.txt ./../resol "temp_var.cnf" ${heuristiques[2]} ${wl[1]}
        echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps31.txt ./../resol "temp_var.cnf" ${heuristiques[3]} ${wl[1]}
        echo $nbVar | /usr/bin/time -f'%U' -o /tmp/variable_temps41.txt ./../resol "temp_var.cnf" ${heuristiques[4]} ${wl[1]}
        rm -f temp_var.cnf
        #temps00=`cat /tmp/variable_temps00.txt`
        #temps10=`cat /tmp/variable_temps10.txt`
        temps20=`cat /tmp/variable_temps20.txt`
        temps30=`cat /tmp/variable_temps30.txt`
        #temps40=`cat /tmp/variable_temps40.txt`
        #temps01=`cat /tmp/variable_temps01.txt`
        #temps11=`cat /tmp/variable_temps11.txt`
        temps21=`cat /tmp/variable_temps21.txt`
        temps31=`cat /tmp/variable_temps31.txt`
        temps41=`cat /tmp/variable_temps41.txt`
        
        #total00=`echo $total00 + $temps00 | bc`
        #total10=`echo $total10 + $temps10 | bc`
        total20=`echo $total20 + $temps20 | bc`
        total30=`echo $total30 + $temps30 | bc`
        #total40=`echo $total40 + $temps40 | bc`
        #total01=`echo $total01 + $temps01 | bc`
        #total11=`echo $total11 + $temps11 | bc`
        total21=`echo $total21 + $temps21 | bc`
        total31=`echo $total31 + $temps31 | bc`
        total41=`echo $total41 + $temps41 | bc`
        let "it = $it+1"
    done
    #temps00=`echo $total00 / 100.0 | bc -l`
    #temps10=`echo $total10 / 100.0 | bc -l`
    temps20=`echo $total20 / 100.0 | bc -l`
    temps30=`echo $total30 / 100.0 | bc -l`
    #temps40=`echo $total40 / 100.0 | bc -l`
    #temps01=`echo $total01 / 100.0 | bc -l`
    #temps11=`echo $total11 / 100.0 | bc -l`
    temps21=`echo $total21 / 100.0 | bc -l`
    temps31=`echo $total31 / 100.0 | bc -l`
    temps41=`echo $total41 / 100.0 | bc -l`
    echo $nbVar $temps20 $temps30 $temps21 $temps31 $temps41 >> ./variable.dat
    let "nbVar = $nbVar + $pas"
done


# a noter que vous pouvez passer un ou plusieurs arguments a ce
# script, auxquels vous ferez reference par $1, $2, etc. Par exemple,
# vous pourrez taper "bash run-tests.sh toto.dat (pour indiquer le nom
# du fichier rassemblant les resultats des tests), et faire dans ce
# fichier 'echo "argument Fibonacci Fibonacci-memo" >> $1
