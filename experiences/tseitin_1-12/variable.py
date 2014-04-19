from os import *
import sys
import time


ranges = [(0,0,0),(1,0,0),(2,0,0),(3,0,0),(4,0,0),(0,1,0),(1,1,0),(2,1,0),(3,1,0),(4,1,0),(0,0,1),(1,0,1),(2,0,1),(3,0,1),(4,0,1),(0,1,1),(1,1,1),(2,1,1),(3,1,1),(4,1,1)]
heuristiques = ["-malin", "-rand", "-moms", "-dlis", ""]
wl = ["","-wl"]
cl = ["","-cl"]
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
    c = p[2]
    if heuristiques[h]=="" and wl[w]=="" and cl[c]=="":
        write(fichier, "defaut ")
    else :
        write(fichier,heuristiques[h]+wl[w]+cl[c]+" ")
    
write(fichier,"\n")
popen("rm -f temp_var.cnf")

while nbVar <= maxVar :
    it = 0            
    print("Nombre de variable "+str(nbVar))
    write(fichier,str(nbVar)+" ")
    for p in ranges :
        h = p[0]
        w = p[1]
        c = p[2]
        it = 0
        total = 0
        temps = 0
        print(heuristiques[h]+wl[w]+cl[c])
        while it < itMax :
            popen("./../../gen/genTseitin "+str(nbVar)+" 1 12 temp_var.txt")
            temps = time.time()
            popen("./../../tseitin temp_var.txt "+heuristiques[h]+" "+wl[w]+" "+cl[c])
            total += time.time()-temps
            popen("rm -f temp_var.txt")
            it += 1
        temps = total/itMax
        write(fichier,str(temps)+" ")
    write(fichier,"\n")
    nbVar += pas
close(fichier)

popen("gnuplot -persist variable.p")
