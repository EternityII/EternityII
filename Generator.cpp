#include "Generator.h"


Generator::Generator(Jeu jeu)
    : jeu(jeu)
{
    nb_noeuds = 0;
    jeu_size = jeu.getSize();

    cout << "## Generator " << jeu_size << endl << endl;

    for (int i = 0; i < JEU_PIECES_MAX; ++i) {
        disponibles[i] = true;
    }
}

/**
 * Retourne le type de pièce suivant les coordonnée x et y
 *
 * @param int x
 * @param int y
 */
const int Generator::pieceTypeByPosition(const int &x, const int &y)
{
    if (x == 0 && y == 0) {
        return POS_TYPE_COIN_NW;
    } else if (x == jeu_size - 1 && y == 0) {
        return POS_TYPE_COIN_NE;
    } else if (x == jeu_size - 1 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SE;
    } else if (x == 0 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SW;
    } else if (x == 0) {
        return POS_TYPE_BORD_LEFT;
    } else if (y == 0) {
        return POS_TYPE_BORD_TOP;
    } else if (x == jeu_size - 1) {
        return POS_TYPE_BORD_RIGHT;
    } else if (y == jeu_size - 1) {
        return POS_TYPE_BORD_BOTTOM;
    } else {
        return POS_TYPE_INTERIEUR;
    }
}

/**
 * Ajoute une la coordonnée x,y à la position voulue, si x et y existent. Incrémente la position
 *
 * @param int &position_nb position a laquelle places les coordonnées
 * @param int x coordonnées x à verifier
 * @param int y coordonnées y à vérifier
 */
void Generator::addCoordinate(int &position_nb, const int &x, const int &y)
{
    if (x >= 0 && x < jeu_size && y >= 0 && y < jeu_size) {
        coordonnees[position_nb][POS_X] = x;
        coordonnees[position_nb][POS_Y] = y;
        coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(x, y);
        position_nb++;
    }
}

/**
 * Positionne les coordonnées en diagonale.
 * en partant du point jusqu'a length - 1
 *
 * @param int position_nb ordre de positionnement pour reformer la corolle.
 * @param int x, position x d'origine
 * @param int y, position y d'origine
 * @param int orientation direction de la diagonale.
 * @param int length longueur de la diagonale.
 */
void Generator::diagonalWalker(int &position_nb, int &x, int &y, const int orientation, const int &length)
{
    if (position_nb < 0 || orientation < 0 || length < 0) {
        perror("Invalid diagonalWalker values");
        exit(EXIT_FAILURE);
    }

    int walker_x = x,
        walker_y = y;
    int to_x = 1,
        to_y = 1;

    if (orientation == SW) {
        to_x = -1;
    } else if (orientation == NE) {
        to_y = -1;
    } else if (orientation == NW) {
        to_x = -1;
        to_y = -1;
    }

    for (int i = 0; i < length; ++i) {
        walker_x = x + i * to_x;
        walker_y = y + i * to_y;

        addCoordinate(position_nb, walker_x, walker_y);
    }

    // Fin du parcours diagonal, passage des valeurs au parcours suivant
    x = walker_x;
    y = walker_y;
}

/**
 * Parcours le plateau en ligne droite et positionne les coordonnées
 * en partant du point (non compris) jusqu'a length du coup (0 non, 1 oui, 2 oui) si length = 2
 *
 * @param int position_nb ordre de positionnement pour reformer la corolle.
 * @param int x, position x d'origine
 * @param int y, position y d'origine
 * @param int orientation direction de parcours (N[ord], E[st], S[outh], W[est] ).
 * @param int length longueur de la diagonale.
 */
void Generator::straightWalker(int &position_nb, int &x, int &y, const int orientation, const int &length)
{
    // Verification des parametres
    if (position_nb < 0 || orientation < 0 || length < 0) {
        perror("Invalid diagonalWalker values");
        exit(EXIT_FAILURE);
    }

    int walker_x = x,
        walker_y = y;

    // walker ne bouge pas en x ni en y
    int to_x = 0,
        to_y = 0;

    if (orientation == N) {
        to_y = -1; // recule en y
    } else if (orientation == E) {
        to_x = 1; // avance en x
    } else if (orientation == S) {
        to_y = 1; // avance en y
    } else if (orientation == W) {
        to_x = -1; // recule en x
    }

    for (int i = 1; i <= length; ++i) {
        // avance sur la longeur length desiree (peut etre egale a 1)
        walker_x = x + i * to_x;
        walker_y = y + i * to_y;

        // ajoute la coordonee
        addCoordinate(position_nb, walker_x, walker_y);
    }

    // on met a jour x et y
    x = walker_x;
    y = walker_y;

}

/**
 * Définit l'ordre de parcours de la corolle. (si non dynamique)
 *
 * @param int x coordonnée x d'origine
 * @param int y coordonnée y d'origine
 */
void Generator::coordinatesCreator()
{
    int position_nb = 0; // pièce en position 0, Initialisation du parcours

    if (type_parcours == PARCOURS_ROW) {
        // # creation du parcours horizontal
        for (int i = 0; i < jeu_size; ++i) {
            for (int j = 0; j < jeu_size; ++j) {
                addCoordinate(position_nb, i, j);
            }
        }

        taille_plateau = jeu_size * jeu_size;

    } else if (type_parcours == PARCOURS_DIAGONAL) {
        // # creation du parcours diagonal

        // premiere partie
        for (int i = 0; i < jeu_size; ++i) {
            for (int xi = i, yi = 0; yi < jeu_size; --xi, ++yi) {
                addCoordinate(position_nb, xi, yi);
            }
        }

        // seconde partie
        for (int i = 1; i < jeu_size; ++i) {
            for (int xi = jeu_size - 1, yi = i; yi < jeu_size; --xi, ++yi) {
                addCoordinate(position_nb, xi, yi);
            }
        }

        taille_plateau = jeu_size * jeu_size;

    } else if (type_parcours == PARCOURS_SPIRALE_IN) {
        //on part de
        int x = 0,
            y = 0;

        for (int iteration = jeu_size - 1; iteration > 0; iteration -= 2) {
            addCoordinate(position_nb, x, y); // on ajoute la coordonnee initiale
            straightWalker(position_nb, x, y, E, iteration); // Génération des coordonnées vers le E
            straightWalker(position_nb, x, y, S, iteration); // vers le S
            straightWalker(position_nb, x, y, W, iteration); // vers le W
            straightWalker(position_nb, x, y, N, iteration - 1); // vers le N
            x++; // réduction du carré
        }

        if (jeu_size % 2 == 1) { // si impair, il reste un trou au milieu
            addCoordinate(position_nb, x, y); // on ajoute la coordonnee finale
        }
        taille_plateau = jeu_size * jeu_size;

    } else if (type_parcours == PARCOURS_SPIRALE_OUT) {
        // on cherche le centre du plateau
        int size_begin;

        int x, y;
        if (jeu_size % 2 == 0) { // le plateau est pair
            x = jeu_size / 2;
            size_begin = 1;
        } else { // impair
            x = (jeu_size - 1) / 2;
            addCoordinate(position_nb, x, x);
            size_begin = 2;
        }
        x--;
        y = x;

        for (int size = size_begin; size < jeu_size; size += 2) {
            straightWalker(position_nb, x, y, S, size);
            straightWalker(position_nb, x, y, E, size);
            straightWalker(position_nb, x, y, N, size);
            straightWalker(position_nb, x, y, W, size);
            x--;
            y--;
        }

        taille_plateau = jeu_size * jeu_size - 1;
    }
}

/**
 * Initialise le parcours bruteforce en définissant le type de parcours et le choix de variable
 *
 * voir constantes PARCOURS_* et VAR_*
 */
void Generator::parcoursBruteForce(const int type_parcours, const int type_variable)
{
    this->type_parcours = type_parcours;
    this->type_variable = type_variable;

    cout
        << "| Type Parcours | Nombre de noeuds (first) | Temps first (sec) | Nombre de noeuds (all) | Temps all (sec) | Nombre de solutions"
        << endl
        << "| --- | ---: | ---: | ---: | ---:" << endl;

    parcoursBruteForce();
}
/**
 * Initialise le parcoursBruteForce en position 0,0 en placant la premiere piece de bord
 *
 * @param int type_parcours le type de parcours à utiliser
 */
void Generator::parcoursBruteForce()
{
    // cout << "#### parcoursBruteForce()" << endl << endl;
    // preparation de tous les elements utilises dans la recursivite

    coordinatesCreator(); // crée les coordonnées

    // cout << "Depart de la recursivite" << endl << endl;
    int position = 1; // initialisation du parcours

    if (type_parcours == PARCOURS_SPIRALE_OUT) {
        position = 0;
    }

    nb_noeuds = 0;
    nb_solutions = 0;

    cout << "| " << getNomParcours();

    start = clock(); // initialise le chronometre

    int x = 0, y = 0;
    jeu.getTabC()[0].setRotation(Piece::RIGHT); // Oriente la pièce 0
    putPiece(x, y, jeu.getTabC()[0]); // place la premiere pièce (pour eviter la duplication de solutions

    generationRecursive(position);

    cout << " | `" << nb_noeuds << "` | `" << (clock() - start) / (double) (CLOCKS_PER_SEC)
        << "` | `" << nb_solutions << "`" << endl;
}

string Generator::getNomParcours() const
{
    string nom_parcours = "inconnu";

    if (type_parcours == PARCOURS_ROW) {
        nom_parcours = "row";
    } else if (type_parcours == PARCOURS_DIAGONAL) {
        nom_parcours = "diagonal";
    } else if (type_parcours == PARCOURS_SPIRALE_IN) {
        nom_parcours = "spirale_in";
    } else if (type_parcours == PARCOURS_SPIRALE_OUT) {
        nom_parcours = "spirale_out";
    } else if (type_parcours == PARCOURS_DYNAMIQUE_OPTIMISTE) {
        nom_parcours = "dynamique_optimiste";
    } else if (type_parcours == PARCOURS_DYNAMIQUE_PESSIMISTE) {
        nom_parcours = "dynamique_pessimiste";
    }
    return nom_parcours;
}

/*
* Initialise la génération multiple de toutes les corolles possibles en fonction de la taille du jeu
*/
void Generator::multipleGeneration()
{
    cout << "### multipleGeneration()" << endl << endl;

    cout
        << "| Type Parcours | Nombre de noeuds first | Temps first (sec) | Nombre de noeuds all | Temps all (sec) | Nombre de solutions"
        << endl;
    cout << "| --- | ---: | ---: | ---: | ---: | ---:" << endl;
    for (int i = 0; i < PARCOURS_DYNAMIQUE_OPTIMISTE; i++) {
        type_parcours = i;
        parcoursBruteForce(); // lance le parcoursBruteForce
    }

    cout << endl;
}

/**
 * Compare deux bord de deux pièces
 *
 * @param Piece a La premiere pièce a comparer
 * @param Piece b La deuxieme pièce a comparer
 * @param int side_a le bord a comparer de la pièce a
 * @param int side_b le bord a comparer de la pièce b
 */
const bool Generator::compareColors(Piece &a, Piece &b, const int side_a, const int side_b)
{
    return a.getColor(side_a) == b.getColor(side_b);
}

/**
 * Compare un bord d'une pièce à la position souhaitée
 *
 * @return true si le les bords correspondent ou si le voisin est vide
 */
const bool Generator::compareSides(Piece &piece, const int &x, const int &y, const int side_to_compare)
{
    if (side_to_compare == Piece::TOP && y > 0) { // on verifie en haut
        if (plateau[x][y - 1].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y - 1], Piece::TOP, Piece::BOTTOM);
        }
    } else if (side_to_compare == Piece::RIGHT && x < jeu_size - 1) {// on verifie a droite
        if (plateau[x + 1][y].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x + 1][y], Piece::RIGHT, Piece::LEFT);
        }
    } else if (side_to_compare == Piece::BOTTOM && y < jeu_size - 1) { // on verifie en bas
        if (plateau[x][y + 1].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y + 1], Piece::BOTTOM, Piece::TOP);
        }
    } else if (side_to_compare == Piece::LEFT && x > 0) { // on verifie a gauche
        if (plateau[x - 1][y].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x - 1][y], Piece::LEFT, Piece::RIGHT);
        }
    } else {
        perror("Valeur de int side_to_compare est invalide");
        return false;
    }
}

/**
 * Vérifie si on peut mettre la pièce sur le plateau
 */
const bool Generator::canPutPiece(Piece &piece, const int &x, const int &y, const int position_type)
{
    if (position_type > POS_TYPE_BORD) { //POS_TYPE_BORD_* on verifie les cotés non-bord
        bool can_put_piece = true; // on suppose que ca marche de base XD

        if (position_type != POS_TYPE_BORD_TOP) {
            can_put_piece &= compareSides(piece, x, y, Piece::TOP);
        }
        if (position_type != POS_TYPE_BORD_RIGHT) {
            can_put_piece &= compareSides(piece, x, y, Piece::RIGHT);
        }
        if (position_type != POS_TYPE_BORD_BOTTOM) {
            can_put_piece &= compareSides(piece, x, y, Piece::BOTTOM);
        }
        if (position_type != POS_TYPE_BORD_LEFT) {
            can_put_piece &= compareSides(piece, x, y, Piece::LEFT);
        }

        return can_put_piece;
    } else if (position_type < POS_TYPE_COIN) { //POS_TYPE_COIN_* on verifie les cotés non bords
        if (position_type == POS_TYPE_COIN_NW) {
            return compareSides(piece, x, y, Piece::RIGHT) && compareSides(piece, x, y, Piece::BOTTOM);
        } else if (position_type == POS_TYPE_COIN_NE) {
            return compareSides(piece, x, y, Piece::BOTTOM) && compareSides(piece, x, y, Piece::LEFT);
        } else if (position_type == POS_TYPE_COIN_SE) {
            return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::LEFT);
        } else if (position_type == POS_TYPE_COIN_SW) {
            return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::RIGHT);
        }
    } else if (position_type == POS_TYPE_INTERIEUR) { // on verifie tout les cotes pour
        return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::RIGHT) &&
            compareSides(piece, x, y, Piece::BOTTOM) && compareSides(piece, x, y, Piece::LEFT);
    } else {
        perror("Valeur int position_type incorrecte");
    }

    return false;
}

/**
 * Met la piece sur le plateau
 */
void Generator::putPiece(const int &x, const int &y, Piece &piece)
{
    putPieceEvent();
    plateau[x][y] = piece;
    disponibles[piece.getId()] = false;
}

/**
 * Enleve la piece du plateau
 */
void Generator::pickOffPiece(const int &numero_piece, const int &x, const int &y)
{
    pickOffPieceEvent();
    Piece piece_vide;
    plateau[x][y] = piece_vide;
    disponibles[numero_piece] = true;
}

/**
 * Génére et parcours récursivement l'arbre des possibilités
 *
 */
void Generator::generationRecursive(int &position)
{
    if (position < taille_plateau) { // si la corolle est incompleteint position_type;
        int coord_x;
        int coord_y;
        int position_type;
        coordinateChooser(position, position_type, coord_x, coord_y);

        if (position_type < POS_TYPE_COIN) { // si position est un coin
            for (int numero_piece = 0; numero_piece < 4; numero_piece++) { // parcours des coins

                Piece piece_coin = jeu.getTabC()[numero_piece];

                if (disponibles[piece_coin.getId()]) { // si la piece est disponible
                    if (position_type == POS_TYPE_COIN_NW) { //bonne orientation de la piece de coin
                        piece_coin.setRotation(Piece::RIGHT);
                    } else if (position_type == POS_TYPE_COIN_NE) { //bonne orientation de la piece de coin
                        piece_coin.setRotation(Piece::TOP);
                    } else if (position_type == POS_TYPE_COIN_SE) {
                        piece_coin.setRotation(Piece::LEFT);
                    } else if (position_type == POS_TYPE_COIN_SW) {
                        piece_coin.setRotation(Piece::BOTTOM);
                    }

                    placerPieceRecursion(position, coord_x, coord_y, position_type, piece_coin);
                }
            }
        } else if (position_type > POS_TYPE_BORD) { // si la position est un bord

            for (int numero_piece = 0; numero_piece < ((jeu_size - 2) * 4); ++numero_piece) {
                // parcours des pieces de bord

                Piece piece_bord = jeu.getTabB()[numero_piece];

                if (disponibles[piece_bord.getId()]) {// is la piece est disponible
                    if (position_type == POS_TYPE_BORD_TOP) { // bonne orientation de la piece de bord
                        piece_bord.setRotation(Piece::TOP);
                    } else if (position_type == POS_TYPE_BORD_RIGHT) { // bonne orientation de la piece de bord
                        piece_bord.setRotation(Piece::LEFT);
                    } else if (position_type == POS_TYPE_BORD_BOTTOM) {
                        piece_bord.setRotation(Piece::BOTTOM);
                    } else if (position_type == POS_TYPE_BORD_LEFT) {
                        piece_bord.setRotation(Piece::RIGHT);
                    }

                    placerPieceRecursion(position, coord_x, coord_y, position_type, piece_bord);
                }
            }
        } else if (position_type == POS_TYPE_INTERIEUR) { // si la position est interieure

            for (int numero_piece = 0; numero_piece < (jeu_size - 2) * (jeu_size - 2); ++numero_piece) {
                Piece piece_interieur = jeu.getTabI()[numero_piece];

                if (disponibles[piece_interieur.getId()]) { // si la piece est disponible

                    for (int rotation = 0; rotation < 4; ++rotation) {// test  des rotations possibles
                        piece_interieur.setRotation(rotation);// rotation de la piece

                        placerPieceRecursion(position, coord_x, coord_y, position_type, piece_interieur);
                    }
                }
            }
        }
    } else if (position == taille_plateau) {
        solutionFoundEvent();
    }
}

void Generator::placerPieceRecursion(int &position, int coord_x, int coord_y, int position_type, Piece &piece_coin)
{
    if (canPutPiece(piece_coin, coord_x, coord_y, position_type)) { // vérifie si la piece est placable
        putPiece(coord_x, coord_y, piece_coin);
        generationRecursive(++position);
        --position;
        pickOffPiece(piece_coin.getId(), coord_x, coord_y);
    }
}

/**
 * définit position_type, coord_x et coord_y suivant la stratégie choisie
 */
void Generator::coordinateChooser(const int &position, int &position_type, int &coord_x, int &coord_y) const
{
    if (type_parcours == PARCOURS_DYNAMIQUE_OPTIMISTE) {

    } else if (type_parcours == PARCOURS_DYNAMIQUE_PESSIMISTE) {

    } else {
        position_type = coordonnees[position][POS_TYPE];
        coord_x = coordonnees[position][POS_X];
        coord_y = coordonnees[position][POS_Y];
    }

}

// Evenements
/**
 * Evenement declanche lorsqu'une piece est posee
 *
 */
void Generator::putPieceEvent()
{
    nb_noeuds++;
}

/**
 * Evenement declanche lorsqu'une piece est enlevee
 */
void Generator::pickOffPieceEvent()
{

}

/**
 * Declanche lorsqu'une solution est trouvee
 */
void Generator::solutionFoundEvent()
{
    nb_solutions++;

    if (nb_solutions == 1) {
        cout << " | `" << nb_noeuds << "` | `" << (clock() - start) / (double) (CLOCKS_PER_SEC) << "`" << flush;
    }
}
