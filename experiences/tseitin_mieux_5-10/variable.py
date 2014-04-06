from os import *
import sys
import time


ranges = [(0,1),(1,1),(2,1),(3,1),(4,1)]
heuristiques = ["-malin", "-rand", "-moms", "-dlis", ""]
wl = ["","-wl"]
nbVar = int(sys.argv[1])
maxVar = int(sys.argv[2])
pas = int(sys.argv[3])
itMax = 1
popen("rm -f variable.dat")
fichier = open("variable.dat",O_WRONLY | O_CREAT)
write(fichier, "argument ")
for p in ranges :
    h = p[0]
    w = p[1]
    if heuristiques[h]=="" and wl[w]=="" :
        write(fichier, "defaut ")
    else :
        write(fichier,heuristiques[h]+wl[w]+" ")
    
write(fichier,"\n")
popen("rm -f temp_var.cnf")

while nbVar <= maxVar :
    it = 0            
    print("Nombre de variable "+str(nbVar))
    write(fichier,str(nbVar)+" ")
    for p in ranges :
        h = p[0]
        w = p[1]
        it = 0
        total = 0
        temps = 0
        while it < itMax :
            popen("./../../gen/genTseitin "+str(nbVar)+" 5 10 temp_var.txt")
            temps = time.time()
            popen("./../../tseitin temp_var.txt "+heuristiques[h]+" "+wl[w])
            total += time.time()-temps
            popen("rm -f temp_var.txt")
            it += 1
        temps = total/itMax
        write(fichier,str(temps)+" ")
    write(fichier,"\n")
    nbVar += pas
close(fichier)

popen("gnuplot -persist variable.p")
