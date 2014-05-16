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
    titles.push_back("Vous permettez que je machouille mes lunettes ?");
    titles.push_back("Bonjour, en guise de cadeau de bienvenue, je vous offre une spécialité culinaire : une graine de sésame.");
    titles.push_back("Si tu tiens à tes rêves, personne ne peut t'empêcher de les vivre. Sauf si ces personnes ont des seringues de tranquillisant et des antipsychotiques");
    titles.push_back("T'as pas peur, toi !");
    titles.push_back("Aussi loin que je me souvienne, j'ai toujours été amnésique.");
    titles.push_back("Darwin serait fier de toi");
    titles.push_back("Ce projet est riant. Mercure vous proteste d’en amuser la cour céleste ; j’en attends un succès heureux.");
    titles.push_back("Viens chez le psy, c’est ton ami. Vas-y, viens me voir. Raconte-moi tes conneries.");
    titles.push_back("Où en est le cocotier ?");
    titles.push_back("Je crois qu’on peut vous applaudir, ces crimes sont exemplaires");
    titles.push_back("Généralement quand un suicidaire menace de sauter, moi je lui dit de laisser tomber.");
    titles.push_back("Les filaments Duchmont sont les meilleurs du monde. Les filaments Duchmont toutes les ampoules en demandent");
    titles.push_back("Nous avons retrouvé cette tablette faisant référence à un astre brillant apparu dans le ciel le temps d’une nuit d’été australe. Les indigènes l’appelèrent Xantahouhastikatiimaritatouhoupetchiikahmaal. Ce qui signifie \"astre brillant apparu dans le ciel le temps d’une nuit d’été australe\"");
    titles.push_back("Bla bli bla");
    titles.push_back("Essaie de prononcer \"Dijkstra\"");
    titles.push_back("Plus il y a de littéraux, plus on rit");
    titles.push_back("La déduction, c'est vraiment pas naturel");
    titles.push_back("Un arbre pas vraiment équilibré");
    titles.push_back("Déduire ou ne pas déduire, tel est la question");
    titles.push_back("$++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.$");
    titles.push_back("$$\\int_{C^+}{P\\,\\mathrm dx + Q\\,\\mathrm dy} = \\iint_D\\left( \\frac{\\partial Q}{\\partial x} - \\frac{\\partial P}{\\partial y}\\right)  \\mathrm dx\\mathrm dy$$");
    titles.push_back(" Génial !");
    titles.push_back("100\\% pur jus !");
    titles.push_back("Peut contenir des traces d'arachides !");
    titles.push_back("Sexy !");
    titles.push_back("Fabriqué par un Orang-Outan et Scrat");
    titles.push_back("Le meilleur de la classe !");
    titles.push_back("Excitant !");
    titles.push_back("Regarde ça !");
    titles.push_back("La vache, mec !");
    titles.push_back("J'ai perdu");
    titles.push_back("Compatible clavier !");
    titles.push_back("Non documenté !");
    titles.push_back("À 90\\% sans bugs !");
    titles.push_back("Ceci n'est pas un titre !");
    titles.push_back("Logique !");
    titles.push_back("{\\color{red}C}{\\color{yellow}o}{\\color{green}u}{\\color{cyan}l}{\\color{blue}e}{\\color{magenta}u}{\\color{red}r}{\\color{yellow}s}");
    titles.push_back("Essaye-le !");
    titles.push_back("Essaye le ragoût de champignons !");
    titles.push_back("Sensationnel !");
    titles.push_back("NP n'est pas P !");
    titles.push_back("Polynomial !");
    titles.push_back("Scientifique !");
    titles.push_back("Plus cool que Spock !");
    titles.push_back("$\\sqrt{-1}$ love you !");
    titles.push_back("20 GOTO 10 !");
    titles.push_back("Cogito ergo sum !");
    titles.push_back("4815162342 lignes de code !");
    titles.push_back("Supercalifragilisticexpialidocious !");
    titles.push_back("Turing-complet !");
    titles.push_back("Ne pas regarder directement les bugs !");
    titles.push_back("Enfin terminé !");
    titles.push_back("Riche en fonctionnalités !");
    titles.push_back("Ne pas éviter les doubles négations !");
    titles.push_back("Technologic !");
    titles.push_back("Quoi de neuf, docteur ?");
    titles.push_back("Contient maintenant, 32 chats journaliers aléatoires !");
    titles.push_back("Coucou, tu veux voir mon satsolver ?");
    titles.push_back("Coucou, tu veux voir mon gros arbre de dérivation ?");
    titles.push_back("Heisenbugs inside!");
    titles.push_back("Powered by quantum physics!");
    //return titles[titles.size()-1];
    return titles[rd()%titles.size()];
}















//Bravo, vous avez trouvé la fonctionnalite cachee ! Demandez votre oeuf de Paques au prochain cours. :w



/**
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::##############                              :::::::::::::::::::
############################  ##############################  :::::::::::::::::
#########################  ######???????????????????????######  :::::::::::::::
=========================  ####??????????()????()?????????####  :::::::::::::::
=========================  ##????()??????????????    ()?????##  ::::    :::::::
------------=============  ##??????????????????  ;;;;  ?????##  ::  ;;;;  :::::
-------------------------  ##??????????()??????  ;;;;;;?????##    ;;;;;;  :::::
-------------------------  ##??????????????????  ;;;;;;         ;;;;;;;;  :::::
++++++++++++-------------  ##??????????????????  ;;;;;;;;;;;;;;;;;;;;;;;  :::::
+++++++++++++++++++++++++  ##????????????()??  ;;;;;;;;;;;;;;;;;;;;;;;;;;;  :::
+++++++++++++++++    ;;;;  ##??()????????????  ;;;;;;@@  ;;;;;;;;@@  ;;;;;  :::
~~~~~~~~~~~~~++++;;;;;;;;  ##????????????????  ;;;;;;    ;;;  ;;;    ;;;;;  :::
~~~~~~~~~~~~~~~  ;;  ~~~~  ####??????()??????  ;;[];;;;;;;;;;;;;;;;;;;;;[]  :::
$$$$$$$$$$$$$~~~~  ~~~~~~  ######?????????????  ;;;;;;              ;;;;  :::::
$$$$$$$$$$$$$$$$$$$$$$$$$    ###################  ;;;;;;;;;;;;;;;;;;;;  :::::::
$$$$$$$$$$$$$$$$$$$$$$$  ;;;;                                       :::::::::::
:::::::::::::$$$$$$$$$$  ;;;;  ::  ;;  ::::::::::::  ;;  ::  ;;;;  ::::::::::::
:::::::::::::::::::::::      ::::::    :::::::::::::     ::::      ::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::NN::::NN::YY::::YY:::AAAAAA:::NN::::NN:::!!::::::::::::::::::::
::::::::::::::::NNNN::NN::YY::::YY::AA::::AA::NNNN::NN:::!!::::::::::::::::::::
::::::::::::::::NNNN::NN::YY::::YY::AA::::AA::NNNN::NN:::!!::::::::::::::::::::
::::::::::::::::NN::NNNN::::YYYY::::AAAAAAAA::NN::NNNN:::!!::::::::::::::::::::
::::::::::::::::NN::NNNN:::::YY:::::AA::::AA::NN::NNNN:::::::::::::::::::::::::
::::::::::::::::NN::::NN:::::YY:::::AA::::AA::NN::::NN:::!!::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::YOU:HAVE:DONE:PROJECT:SAT:FOR:10368042:SECONDS!::::::::::::::::::
**/
