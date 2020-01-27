## TP évalué : rattrapage


## Rendu

L'ensemble du code permettant de compiler votre TP (y compris les fichiers annexes donc) devra être placé dans un répertoire 'TP-note'  sur votre dépôt git.

Le programme doit se compiler avec la commande `make`.
Vérifier les points suivants :

- votre dépôt doit être privé
- vos deux enseignants doivent avoir les droits 'reporter'.

Effectuez des commits réguliers de votre travail et **n'oubliez pas** le `push` final.


## Carte de contours

Une carte de contours est obtenue à partir d'un seuillage sur une image gradient. On souhaite calculer plusieurs cartes de contours obtenues pour différentes versions filtrées d'une image.

### Filtrage gaussien

L'image originale est filtrée par un filtre gaussien d'écart-type $`\sigma`$.
Ecrire la fonction :
```c++
Image<double> gaussianFiltering(const Image<uint8_t> &image, double sigma)
```
Cette fonction retourne une image à valeurs réelles.

### Image gradient

On estime le gradient dans les directions horizontales et verticales par les filtres de Prewitt :

$`P_x= 
\begin{bmatrix}
-1&0&1\\
-1&0&1\\
-1&0&1
\end{bmatrix},
P_y=\begin{bmatrix}
-1&-1&-1\\
0&0&0\\
1&1&1
\end{bmatrix}`$

Ecrire les fonctions :
```c++
Image <double> computeGx(const Image<double> &image);
Image <double> computeGy(const Image<double> &image);
```
qui calculent et retournent les  images $`G_x=I \ast P_x`$ et $`G_y=I \ast P_y`$.

À partir de ces deux images, la magnitude du vecteur gradient se calcule en chaque point avec :

$`M(x) = \sqrt{(G_x(x)) ^2 + (G_y(x))^2}`$.

Ecrire la fonction :
```c++
Image<double> computeMagnitude(const Image<double> &Gx, const Image<double> &Gy)
```

### Cartes de contours

Ecrire un programme qui prend en paramètres : 
- une image au format pgm
- une valeur pour sigma
- un seuil s

et qui calcule et écrit sur le disque une image `carte.pgm`, obtenue par seuillage au niveau s de la magnitude du gradient sur l'image filtrée.

### Tests

Générer plusieurs cartes de contours pour différentes valeurs de $`\sigma`$ pour l'image `lena.pgm`.
