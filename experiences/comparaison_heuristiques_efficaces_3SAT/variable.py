from os import *
import sys
import time


ranges=[(0,0,0),(1,0,0),(2,0,0),(3,0,0),(4,0,0),(2,1,0),(3,1,0),(0,0,1),(1,0,1),(2,0,1),(3,0,1),(4,0,1),(2,1,1),(3,1,1)]
heuristiques=["-malin", "-rand", "-moms", "-dlis", "-simple"]
wl=["-dpll","-wl"]
cl=["","-cl"]
itMax=2
nbVar=int(sys.argv[1])
maxVar=int(sys.argv[2])
pas=int(sys.argv[3])
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
            popen("./../../gen/gen "+str(nbVar)+" 400 3 3 temp_var.cnf")
            temps=time.time()
            popen("./../../resol temp_var.cnf "+heuristiques[h]+" "+wl[w]+" "+cl[c])
            total=time.time()-temps+total
            popen("rm -f temp_var.cnf")
            it+=1
        temps=total/itMax
        write(fichier,str(temps)+" ");
    write(fichier,"\n")
    nbVar=nbVar+pas


# a noter que vous pouvez passer un ou plusieurs arguments a ce
# script, auxquels vous ferez reference par $1, $2, etc. Par exemple,
# vous pourrez taper "bash run-tests.sh toto.dat (pour indiquer le nom
# du fichier rassemblant les resultats des tests), et faire dans ce
# fichier 'echo "argument Fibonacci Fibonacci-memo" >> $1


close(fichier)

popen("gnuplot -persist variable.p")
