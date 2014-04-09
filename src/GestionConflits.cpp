#include "../include/GestionConflits.h"
#include<iostream>

using namespace std;

GestionConflits::GestionConflits(int prochainConflit_)
: conflitsNum(0), prochainConflit(prochainConflit_)
{}

void GestionConflits::onConflit()
{
    conflitsNum++;
}

int GestionConflits::getConflitsNum() const
{
    return conflitsNum;
}


GestionConflitsApprentissage::GestionConflitsApprentissage(int prochainConflit) : GestionConflits(prochainConflit)
{}

void GestionConflitsApprentissage::onConflit()
{
    GestionConflits::onConflit();

    if(conflitsNum == prochainConflit)
        displayInterface();
}

void GestionConflitsApprentissage::displayInterface()
{
    cout << conflitsNum << " conflit !" << endl;

    char ch;
    while(cin >> ch)
    {
        switch(ch)
        {
            case 'g':
                cout << "Sortie du graphe des conflits." << endl;
                //TODO
                break;
            case 'c':
                cout << "Affichage lors du prochain conflit." << endl;
                prochainConflit++;
                return;
            case 's':
                int num;
                cin >> num;
                cout << "Affichage lors du " << num << " conflits plus loin." << endl;
                prochainConflit += num;
                return;
            case 't':
                cout << "Arrêt de l'affichage." << endl;
                return;
            default:
                cout << "Option inconnu : " << ch << endl;
        }
    }
}