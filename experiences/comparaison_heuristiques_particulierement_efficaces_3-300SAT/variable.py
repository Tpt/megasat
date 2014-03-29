from os import *
import sys
import time


ranges=[(2,1),(3,1)]
heuristiques=["-malin", "-rand", "-moms", "-dlis", ""]
wl=["","-wl"]
nbVar=int(sys.argv[1])
maxVar=int(sys.argv[2])
pas=int(sys.argv[3])
itMax=2
popen("rm -f variable.dat")
fichier = open("variable.dat",O_WRONLY | O_CREAT)
write(fichier, "argument ")
for p in ranges:
    h=p[0]
    w=p[1]
    if heuristiques[h]=="" and wl[w]=="":
        write(fichier, "defaut ")
    else:
        write(fichier,heuristiques[h]+wl[w]+" ")
    
write(fichier,"\n")
popen("rm -f temp_var.cnf")

while nbVar<=maxVar:
    it=0            
    print("Nombre de variables "+str(nbVar))
    write(fichier,str(nbVar)+" ")
    
    for p in ranges:
        h=p[0]
        w=p[1]
        it=0
        total=0
        temps=0
        while it<itMax:
            popen("./../../gen/gen "+str(nbVar)+" 400 3 300 temp_var.cnf")
            temps=time.time()
            popen("./../../resol temp_var.cnf "+heuristiques[h]+" "+wl[w])
            total=time.time()-temps+total
            popen("rm -f temp_var.cnf")
            it+=1
        temps=total/itMax
        write(fichier,str(temps)+" ");
    write(fichier,"\n")
    nbVar=nbVar+pas

close(fichier)

popen("gnuplot -persist variable.p")
