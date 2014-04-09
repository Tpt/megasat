#ifndef GestionConflits_H
#define GestionConflits_H

class GestionConflits
{
public:
    GestionConflits(int prochainConflit = 0);
    void onConflit();
    int getConflitsNum() const __attribute__((pure));
protected:
    int conflitsNum;
    int prochainConflit;
};

class GestionConflitsApprentissage : public GestionConflits
{
public:
    GestionConflitsApprentissage(int prochainConflit = 0);
    void onConflit();
private:
    void displayInterface();
};

#endif