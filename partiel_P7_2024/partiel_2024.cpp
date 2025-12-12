#include <iostream>
#include <array>
#include <string>
#include <fstream>

const int TMAX = 5;
using TabTirage = std::array <int, TMAX>;

struct date {
    int jours;
    int mois;
    int annee;
    date * suivant;
};
using ListeDate = date *;


struct noeud {
    TabTirage tirage;   // tirage est notre clé pour notre ABR
    ListeDate liste_date;
    noeud * sag;
    noeud * sad;
};
using historique = noeud *;



void affichage_date(date date_saisie) {
    std::cout << date_saisie.annee << "-" << date_saisie.mois<< "-" << date_saisie.jours << std::endl;
}


void affichage_listeDate(ListeDate liste) {
    if (liste != nullptr) {
        affichage_date(*liste);
        affichage_listeDate(liste->suivant);
    };
}


ListeDate init_listeDate() {
    ListeDate liste;
    liste = nullptr;
    return liste;
}


historique init_historique() {
    historique hist;
    hist = nullptr;
    return hist;
}


int ordre_date(date date1, date date2) {
    if (date1.annee < date2.annee) return -1;
    else if (date1.annee > date2.annee) return 1;
    else {
        if (date1.mois < date2.mois) return -1;
        else if (date1.mois > date2.mois) return 1;
        else {
            if (date1.jours < date2.jours) return -1;
            else if (date1.jours > date2.jours) return 1;
        };
    };
    return 0;
}



int ordre_tirage(TabTirage tirage1, TabTirage tirage2) {
    for (int i = 0; i < TMAX; ++i) {
        if (tirage1[i] < tirage2[i]) return -1;   // le premier tirage est plus petit que le second
        else if (tirage1[i] > tirage2[i]) return 1;
    };
    return 0;
}



void ajout_listeDate(ListeDate & liste, date date_saisie) {
    if (liste == nullptr) {
        liste = new date;
        liste->jours = date_saisie.jours;
        liste->mois = date_saisie.mois;
        liste->annee = date_saisie.annee;
        liste->suivant = nullptr;
    }
    else if (ordre_date(*liste, date_saisie) == 0) return;   //liste inchangé comme la date se trouve deja dans la liste
    else if (ordre_date(*liste, date_saisie) == 1) {            //ajout en tete
        ListeDate liste_tmp = init_listeDate();
        liste_tmp = new date;
        liste_tmp->annee = date_saisie.annee;
        liste_tmp->mois = date_saisie.mois;
        liste_tmp->jours = date_saisie.jours;
        liste_tmp->suivant = liste;
        liste = liste_tmp;
    }
    else ajout_listeDate(liste->suivant, date_saisie);
}





void ajout_tirage(historique & abr, TabTirage tirage, date date_saisie) {
    if (abr == nullptr) {   // on arrive a une feuille de l'abr donc on peut inserer le tirage (et sa date)
        abr = new noeud;
        abr->tirage = tirage;
        abr->liste_date = nullptr;              //Très important erreur fréquente !!!!   nullptr sinon garbage memory    (ligne 82)
        ajout_listeDate(abr->liste_date, date_saisie);
        abr->sag = nullptr;
        abr->sad = nullptr;
    }
    else if (ordre_tirage(abr->tirage, tirage) == 0) ajout_listeDate(abr->liste_date, date_saisie);
    else if (ordre_tirage(abr->tirage, tirage) == -1) ajout_tirage(abr->sad, tirage, date_saisie);
    else ajout_tirage(abr->sag, tirage, date_saisie);
}


//QUESTION 5
void ajout_fichier(historique & abr, std::string fichier) {
    std::ifstream var_flux;
    var_flux.open(fichier);
    if (var_flux.is_open()) {
        std::cout << "Ouverture du fichier de données réussit." << std::endl;
        while (var_flux.good()) {
            date date_tmp;
            var_flux >> date_tmp.jours;
            var_flux >> date_tmp.mois;
            var_flux >> date_tmp.annee;
            
   
            TabTirage tirage_tmp;
            for (int i = 0; i < TMAX; ++i) {
                var_flux >> tirage_tmp[i];
            };
            ajout_tirage(abr, tirage_tmp, date_tmp);
        };
    }
    else std::cout << "Echec de l'ouverture du fichier de données." << std::endl;
}

//Question 6
void affichage_dateSortie(historique abr, TabTirage tirage) {
    if (abr == nullptr) std::cout << "Tirage inédit" << std::endl;
    else if (ordre_tirage(abr->tirage, tirage) == 0) affichage_listeDate(abr->liste_date);
    else if (ordre_tirage(abr->tirage, tirage) == -1) affichage_dateSortie(abr->sad, tirage);
    else affichage_dateSortie(abr->sag, tirage);
}



int main() {
    /*

    -------------PARTIE TEST-----------------------------
   
    date date1;
    date1.annee = 2006;
    date1.mois = 6;
    date1.jours = 9;
    date date2;
    date2.annee = 2006;
    date2.mois = 6;
    date2.jours = 8;
    
    std::cout << ordre_date(date1, date2);
    

    TabTirage tirage1 = {6, 13, 25, 30, 32};
    TabTirage tirage2 = {4, 30, 38, 45, 46};
    std::cout << ordre_tirage(tirage1, tirage2);
    
    ListeDate liste = init_listeDate();
    ajout_listeDate(liste, date1);
    ajout_listeDate(liste, date2);
    affichage_listeDate(liste);
    */
    std::string fichier_data = "fake_loto.txt";
    historique hist = init_historique();
    ajout_fichier(hist, fichier_data);
    TabTirage tirage1 = {21, 27, 29, 44, 50};
    std::cout << std::endl;
    affichage_dateSortie(hist, tirage1);




    return 0;
}

/*fake_loto.txt de la forme :
04 01 1950 16 28 30 40 48
11 01 1950 8 18 25 32 47
18 01 1950 11 12 16 29 40
25 01 1950 12 21 28 35 47
01 02 1950 6 8 14 15 49
08 02 1950 25 28 30 39 49
15 02 1950 8 11 14 16 49
22 02 1950 8 23 25 26 45
01 03 1950 17 29 33 37 50
08 03 1950 1 8 23 34 49
15 03 1950 13 20 34 40 47
*/