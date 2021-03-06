from os import *
import sys
import time


ranges=[(2,1,0),(3,1,0),(2,1,1),(3,1,1)]
heuristiques=["-malin", "-rand", "-moms", "-dlis", "-simple"]
wl=["-dpll","-wl"]
cl=["","-cl"]
nbVar=int(sys.argv[1])
maxVar=int(sys.argv[2])
pas=int(sys.argv[3])
itMax=1
popen("rm -f variable.dat")
fichier = open("variable.dat",O_WRONLY | O_CREAT)
write(fichier, "argument ")
for p in ranges:
    h=p[0]
    w=p[1]
    c=p[2]
    if heuristiques[h]=="" and wl[w]=="" and cl[c]=="":
        write(fichier, "defaut ")
    else:
        write(fichier,heuristiques[h]+wl[w]+cl[c]+" ")

write(fichier,"\n")



popen("rm -f temp_var.cnf")

while nbVar<=maxVar:
    it=0
    print("Nombre de variables "+str(nbVar))
    write(fichier,str(nbVar)+" ")
    for p in ranges:
        h=p[0]
        w=p[1]
        c=p[2]
        it=0
        total=0
        temps=0
        print(heuristiques[h]+wl[w]+cl[c])
        while it<itMax:
            popen("./../../gen/gen "+str(nbVar)+" "+str(3*nbVar)+" 3 3 temp_var.cnf")
            temps=time.time()
            popen("./../../resol temp_var.cnf "+heuristiques[h]+" "+wl[w]+" "+cl[c])
            total+=time.time()-temps
            popen("rm -f temp_var.cnf")
            it+=1
        temps=total/itMax
        write(fichier,str(temps)+" ")
    write(fichier,"\n")
    nbVar+=pas

close(fichier)

popen("gnuplot -persist variable.p")
