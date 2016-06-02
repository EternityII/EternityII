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
 * Définit l'ordre de parcours de la corolle.
 *
 * @param int x coordonnée x d'origine
 * @param int y coordonnée y d'origine
 */
void Generator::coordinatesCreator()
{
    int position_nb = 0; // pièce en position 0, Initialisation du parcours

    for (int i = 0; i < jeu_size; ++i) {
        for (int j = 0; j < jeu_size; ++j) {
            addCoordinate(position_nb, i, j);
        }
    }

    corolle_size = jeu_size * jeu_size;

}

/**
 * Initialise le parcoursRowScan en position 0,0 en placant la premiere piece de bord
 *
 * @param int type_parcours le type de parcours à utiliser
 */
void Generator::parcoursRowScan()
{

    cout << "### parcoursRowScan()" << endl << endl;
    // preparation de tous les elements utilises dans la recursivite

    coordinatesCreator(); // crée les coordonnées

    cout << "Depart de la recursivite" << endl << endl;
    int position = 1; // initialisation du parcours

    int x = 0, y = 0;

    nb_noeuds_first.clear();
    nb_noeuds_first.str("");

    clock_t start = clock(); // initialise le chronometre
    jeu.getTabC()[0].setRotation(Piece::RIGHT); // Oriente la pièce 0
    putPiece(x, y, jeu.getTabC()[0]); // place la premiere pièce (pour eviter la duplication de solutions


    generationRecursive(position);

    cout << "|  |  |" << endl
        << "| --- | ---:" << endl
        << "| Premiere solution temps (sec) | `" << (first_solution - start) / (double) (CLOCKS_PER_SEC) << "`" << endl
        << nb_noeuds_first.str()
        << "| temps (sec) | `" << (clock() - start) / (double) (CLOCKS_PER_SEC) << "`" << endl;
    cout << "| nb_noeuds | `" << nb_noeuds << "`" << endl;
    cout << "| nb_solutions | `" << nb_solutions << "`" << endl << endl;

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
    if (position < corolle_size) { // si la corolle est incompleteint position_type;
        int coord_x;
        int coord_y;
        int position_type;

        getPositionInformation(position, position_type, coord_x, coord_y);

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
    } else if (position == corolle_size) {
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
void Generator::getPositionInformation(const int &position, int &position_type, int &coord_x, int &coord_y) const
{
    position_type = coordonnees[position][POS_TYPE];
    coord_x = coordonnees[position][POS_X];
    coord_y = coordonnees[position][POS_Y];
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
        first_solution = clock();
        nb_noeuds_first << "| nb_noeuds_first | `" << nb_noeuds << "`" << endl;
    }
}
