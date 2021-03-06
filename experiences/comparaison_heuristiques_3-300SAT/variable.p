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

set pointsize 0.5   # la taille des points


# on trace deux courbes: avec les colonnes 1 et 2, avec les colonnes 1 et 3
# a chaque fois, le nom de la courbe est lu en tete de colonne
plot "variable.dat" using 1:2 title columnheader(2), \
     "variable.dat" using 1:3 title columnheader(3), \
     "variable.dat" using 1:4 title columnheader(4), \
     "variable.dat" using 1:5 title columnheader(5), \
     "variable.dat" using 1:6 title columnheader(6), \
     "variable.dat" using 1:7 title columnheader(7), \
     "variable.dat" using 1:8 title columnheader(8), \
     "variable.dat" using 1:9 title columnheader(9), \
     "variable.dat" using 1:10 title columnheader(10), \
     "variable.dat" using 1:11 title columnheader(11), \
     "variable.dat" using 1:12 title columnheader(12), \
     "variable.dat" using 1:13 title columnheader(13), \
     "variable.dat" using 1:14 title columnheader(14), \
     "variable.dat" using 1:15 title columnheader(15), \
     "variable.dat" using 1:16 title columnheader(16), \
     "variable.dat" using 1:17 title columnheader(17), \
     "variable.dat" using 1:18 title columnheader(18), \
     "variable.dat" using 1:19 title columnheader(19), \
     "variable.dat" using 1:20 title columnheader(20), \
     "variable.dat" using 1:21 title columnheader(21)
