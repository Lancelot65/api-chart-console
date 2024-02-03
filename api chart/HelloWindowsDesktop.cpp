#include <Windows.h>

#include <chartdir/chartdir.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    double dataX[] = { 1, 2, 3, 4, 5 };
    double dataY[] = { 3, 4, 2, 5, 6 };

    // Cr�ation d'un objet XYChart de largeur 600 pixels et de hauteur 400 pixels
    XYChart* c = new XYChart(600, 400);

    // Configuration du titre du graphique
    c->addTitle("Courbe simple", "Arial", 12);

    // Ajout d'une courbe � XYChart en utilisant les donn�es fournies
    c->addLineLayer(DoubleArray(dataY, sizeof(dataY) / sizeof(dataY[0])), 0xff0000, "Courbe 1");

    // Configuration de l'axe X pour afficher les valeurs de 1 � 5 avec une �tiquette de pas de 1
    c->xAxis()->setLinearScale(1, 5, 1);

    // Configuration de l'axe Y pour afficher les valeurs de 0 � 7 avec une �tiquette de pas automatique
    c->yAxis()->setLinearScale(0, 7);

    // Configuration de la l�gende pour qu'elle apparaisse en bas du graphique
    c->addLegend(50, 350, false, "Arial", 10)->setBackground(Chart::Transparent);

    // Rendu du graphique dans un fichier PNG nomm� "chart.png"
    c->makeChart("chart.png");

    // Nettoyage de la m�moire
    delete c;
    return 0;
}
