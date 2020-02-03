# Traitement d'images en C++

# Séance 2

## Seuillage automatique

### Algorithme d'Otsu

#### Introduction

L'algorithme d'Otsu permet de calculer un seuil de manière automatique dans le contexte d'une segmentation binaire (séparation en deux classes) aussi appelée *binarisation* d'image.

Soit une image $`f:E \rightarrow V`$ et un seuil $`s`$. On considère les deux classes suivantes :

- l'ensemble des pixels qui ont une valeur supérieure au seuil, ou *points objet* $`X_o=\{p \in E \mid f(p)\geq s) \}`$
- l'ensemble des pixels qui ont une valeur inférieure au seuil ou *points fond* $`X_f=\{p \in E \mid f(p) < s) \}`$.

Image originale |      Image seuillée (s=110)
:--------------:|:-----------------:
![](images/grumpy.png)|![](images/grumpy-thres.png)

En blanc : les points objet $`X_o`$ 
En noir : points fond $`X_f`$.


On se donne une mesure d'homogénéité pour une classe : celle-ci peut se fonder par exemple sur la variance des valeurs des points : $`\sigma^2_o`$ pour la variance des points objet, $`\sigma^2_f`$ pour la variance des points fond. On appelle cette mesure de variance pour une classe donnée la *variance intra-classe*. Plus les points d'une classe sont homogènes, plus la variance est petite (pour une classe parfaitement homogène, la variance est nulle).

Le principe de l'algorithme d'Otsu est de choisir le seuil qui permet d'obtenir les classes les plus homogènes possibles au sens de la variance intra-classe.
Le seuil calculé est celui qui minimise la  variance intra-classe totale (*within class variance*) définie par :

```math
\sigma^2_w=w_f \sigma^2_f+w_o\sigma^2_o,
```

où :

- $`w_f`$ est la proportion de points fond : $`w_f=\mid X_f \mid/N`$
- $`w_o`$ est la proportion de points objet : $`w_o=\mid X_o \mid/N`$
- $`N`$ est le nombre de points de l'image : $`N=\mid E \mid`$
- $`\sigma^2_f`$ est la variance  des points fond : $`\sigma^2_f=\frac{1}{N}\sum_{x\in X_f}(f(x)-\mu_f)^2`$
- $`\sigma^2_o`$ est la variance des points objet : $`\sigma^2_o=\frac{1}{N}\sum_{x\in X_o}(f(x)-\mu_o)^2`$
- $`\mu_f`$ est la moyenne des points fond : $`\mu_f=\frac{1}{N}\sum_{x\in X_f}f(x)`$
- $`\mu_o`$ est la moyenne des points objet : $`\mu_o=\frac{1}{N}\sum_{x\in X_o}f(x)`$

On peut montrer que le seuil optimal d'Otsu maximise également la variance inter-classe (*between class variance*) définie par :

```math
\sigma^2_b=\sigma^2-\sigma^2_w
```

avec : $`\sigma^2`$  la variance totale de l'image.

Finalement  l'expression de  $`\sigma^2_b`$ se réduit à :

```math
\sigma^2_b=w_f w_o (\mu_f-\mu_o)^2
```

Intuitivement, maximiser la variance inter-classe revient à choisir un seuil qui maximise la dissimilarité entre les deux classes.

#### Implémentation de l'algorithme 

L'implémentation de l'algorithme d'Otsu peut s'appuyer soit sur la minimisation de la variance intra-classe soit sur la maximisation de la variance inter-classe. On choisira plutôt la seconde formulation qui permet d'éviter le calcul explicite des variances.

L'histogramme de l'image contient toute l'information nécessaire au calcul des différentes variables intermédiaires.

L'algorithme se formule donc de la manière suivante :

1. Calcul de l'histogramme
2. Pour tous les seuils `s` possibles :
   1. Mettre à jour $`w_o,w_f,\mu_o,\mu_f`$ en utilisant l'histogramme
   2. Calculer $`\sigma^2_b`$
3. Retourner le seuil $`s`$ qui maximise $`\sigma^2_b`$

#### Programme à réaliser

Description :

- `otsu`: Calcule le résultat du seuillage d'une image à niveaux de gris à partir du seuil optimal déterminé par l'algorithme d'Otsu

Paramètres :

- Nom de fichier de l'image d'entrée
- Nom de fichier de l'image de sortie

Retour :

- Écriture sur la sortie standard du seuil choisi par l'algorithme
- Écriture sur le disque de l'image seuillée par l'algorithme d'Otsu

Exemple :

```sh
otsu input.pgm output.pgm
```






### Algorithme des k-moyennes 

Image originale |      Image seuillée (k=...)
:--------------:|:-----------------:
![](images/grumpy.png)|![](images/grumpy-thres.png)

Description :

- `kmeans`: Calcule le seuillage d'une image à niveaux de gris à partir de l'algorithme des k-moyennes

Paramètres :

- Nom de fichier de l'image d'entrée
- Nom de fichier de l'image de sortie
- `k` : nombre de classes

Retour :

- Écriture sur le disque de l'image seuillée par l'algorithme des k-moyennes

Exemple :

```sh
kmeans input.pgm output.pgm 4
```
