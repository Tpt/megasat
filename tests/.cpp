#include<vector>
#include<string>
#include<random>

using namespace std;
string genTitle();

string genTitle()
{
    random_device rd;
    vector<string> titles;
    titles.push_back("Une preuve !");
    titles.push_back("De la beauté des preuves mathématiques");
    titles.push_back("A propos du seul arbre qui pousse vers le haut en info");
    titles.push_back("J'aime les pommes de terre");
    titles.push_back("Convex Algebra");
    titles.push_back("Par moi, vous pénétrez dans la cité des peines ; \\\\"
            "par moi, vous pénétrez dans la douleur sans fin ;\\\\"
            "par moi, vous pénétrez parmi la gent perdue.\\\\"
            "La justice guidait la main de mon auteur ;\\\\"
            "le pouvoir souverain m'a fait venir au monde,\\\\"
            "la suprême sagesse et le premier amour.\\\\"
            "Nul autre objet créé n'existait avant moi,\\\\"
            "à part les éternels ; et je suis éternelle.\\\\"
            "Vous, qui devez entrer, abandonnez l'espoir. ");
    titles.push_back("La logique mène à tout, à condition d'en sortir");
    titles.push_back("Je suis une licorne !");
    titles.push_back("What does the fox say ?");
    titles.push_back("J'aime ce projet, man ! Et il est libre... man !\\\\ Et moi, ce qui est libre, j'en veux. Man !");
    titles.push_back("Je suis l'esprit qui toujours nie tout");
    titles.push_back("La maman des poissons, elle a l'oeil tout rond. Ses petits l'aime bien, elle est bien gentille et moi, je l'aime bien avec du citron.");
    titles.push_back("Je veux un trésor qui les contient tous !... Je veux la jeunesse !");
    titles.push_back("Nos chansons feront fuir les soucis et les pleurs !");
    titles.push_back("Sie war schön, sagst du ? Sie ist schön ! Sie ist ! Sie ist !");
    titles.push_back("Vous permettez que je machouilles mes lunettes ?");
    titles.push_back("Bonjour, en guise de cadeau de bienvenue, je vous offre une spécialité culinaire : une graine de sésame.");
    titles.push_back("Si tu tiens à tes rêves, personne ne peut t'empêcher de les vivre. Sauf si ces personnes ont des seringues de tranquillisant et des antipsychotiques");
    titles.push_back("T'as pas peur, toi !");
    titles.push_back("Aussi loin que je me souvienne, j'ai toujours été amnésique.");
    titles.push_back("Darwin serait fier de toi");
    titles.push_back("J'ai lu dans ses yeux pervers, qu'elle me réclamait la suite, la suite du concert");
    titles.push_back("Tous ont péri ! Que Dieu les bénisse.");
    titles.push_back("Vous y trouverez des gens qui aiment fort tout ceux qui, comme vous, ont de l'adresse et du courage");
    titles.push_back("\\`{E} vano l'orgoglio... il re s'avanza");
    titles.push_back("Oui, la vengeance, une terrible vengeance, c'est la seule chose que mon âme désire");
    titles.push_back("Libiamo, libiamo ne' lieti calici,\\\\ che la bellezza infiora;\\\\e la fuggevol, fuggevol ora\\\\s'inebri a voluttà.");
    titles.push_back("Des dieux, l'immortelle sagesse, me réserve un drôle d'emploi. S'il en faut un à la déesse, pourquoi faut-il que ce soit moi ? Son mari lui devrait suffire.");
    titles.push_back("");
    return titles[titles.size()-1];
    return titles[rd()%titles.size()];
}
