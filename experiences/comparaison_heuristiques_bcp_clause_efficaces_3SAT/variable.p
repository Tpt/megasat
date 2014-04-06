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
set ylabel "Temps de résolution (s)"
set key left



# Dessin en joignant des points
set style data linespoints

set pointsize 0.1   # la taille des points


# on trace deux courbes: avec les colonnes 1 et 2, avec les colonnes 1 et 3
# a chaque fois, le nom de la courbe est lu en tete de colonne
plot "variable.dat" using 1:2 title columnheader(2), \
     "variable.dat" using 1:3 title columnheader(3)
