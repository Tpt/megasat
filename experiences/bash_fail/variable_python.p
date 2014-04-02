# pour visualiser le dessin trace par ce script gnuplot, taper
# gnuplot -persist script-plot.p
#  (en s`assurant que le fichier comparaison.dat est present dans le repertoire)

reset

### decommenter les 2 lignes ci-dessous pour engendrer un fichier pdf
### plutot qu`un dessin a l`ecran
 set term pdfcairo
 set output "variable.pdf" # le nom du fichier qui est engendre

set title "t=f(V) pour les différentes heuristiques"
set xlabel "Nombre de variables"
set ylabel "Temps de résolution"
set key out vert
set key center right



# Dessin en joignant des points
set style data linespoints

set pointsize 0.5   # la taille des points


# on trace deux courbes: avec les colonnes 1 et 2, avec les colonnes 1 et 3
# a chaque fois, le nom de la courbe est lu en tete de colonne
plot "variable_python.dat" using 1:2 title columnheader(2), \
     "variable_python.dat" using 1:3 title columnheader(3), \
     "variable_python.dat" using 1:4 title columnheader(4), \
     "variable_python.dat" using 1:5 title columnheader(5), \
     "variable_python.dat" using 1:6 title columnheader(6), \
     "variable_python.dat" using 1:7 title columnheader(7), \
     "variable_python.dat" using 1:8 title columnheader(8), \
     "variable_python.dat" using 1:9 title columnheader(9), \
     "variable_python.dat" using 1:10 title columnheader(10), \
     "variable_python.dat" using 1:11 title columnheader(11)