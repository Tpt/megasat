from os import *
import sys
import time

popen("rm -f variable_python.dat")
fichier = open("variable_python.dat",O_WRONLY | O_CREAT)

write(fichier, "argument -malin -rand -moms -dlis default -malin-wl -rand-wl -moms-wl -dlis-wl -wl\n")

nbVar=int(sys.argv[1])
maxVar=int(sys.argv[2])
pas=int(sys.argv[3])


heuristiques=["-malin", "-rand", "-moms", "-dlis", ""]

wl=["","-wl"]

popen("rm -f temp_var.cnf")

while nbVar<=maxVar:
    it=0            
    print("Nombre de variable "+str(nbVar))
    h=0
    write(fichier,str(nbVar)+" ")
    while h<5:
        w=0
        while w<2:
            it=0
            total=0
            temps=0
            while it<1:
                popen("./../gen/gen "+str(nbVar)+" 20 3 3 temp_var.cnf")
                temps=time.time()
                popen("./../resol temp_var.cnf "+heuristiques[h]+" "+wl[w])
                total=time.time()-temps+total
                popen("rm -f temp_var.cnf")
                it+=1
            temps=total/1
            write(fichier,str(temps)+" ");
            w+=1
        h+=1
    write(fichier,"\n")
    nbVar=nbVar+pas


# a noter que vous pouvez passer un ou plusieurs arguments a ce
# script, auxquels vous ferez reference par $1, $2, etc. Par exemple,
# vous pourrez taper "bash run-tests.sh toto.dat (pour indiquer le nom
# du fichier rassemblant les resultats des tests), et faire dans ce
# fichier 'echo "argument Fibonacci Fibonacci-memo" >> $1


close(fichier)

popen("gnuplot -persist variable_python.p")
