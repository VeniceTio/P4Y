# Séances 4 et 5

## Convolution

La convolution discrète d'une image $`I`$ à deux dimensions par un masque ou noyau de convolution $`M`$ de taille $`n\times n`$ est définie en un point par :


```math
(I\ast M)(i,j)=\sum_{k=0}^{n-1} \sum_{l=0}^{n-1}  I(i+k-c,j+l-c)M(k,l),
```

où $`c=\lfloor{\frac{n}{2}\rfloor}`$. Le masque peut être vu comme une image dont les coordonnées $`(0,0)`$ représentent le coin supérieur gauche, $`(n-1,n-1)`$ le coin inférieur droit et $`(c,c)`$ le centre.

Généralement le masque est de taille impaire.

Les coefficients du masque sont à valeurs réelles ; le résultat (l'image convoluée) est donc également à valeurs réelles.

Pour plus de détails sur l'opérateur de convolution, vous pouvez consulter [l'annexe](#annexe).

Comme vu en cours, selon le noyau utilisé, on peut distinguer deux grandes classes de filtres :

- les filtres qui transforment une image $`I:E\rightarrow V`$ en une autre image $`I':E\rightarrow V`$ : l'espace des points ainsi que l'espace des valeurs sont préservés. C'est le cas des filtres de lissage et des filtres de réhaussement de contours ;
- les filtres qui transforment une image $`I:E\rightarrow V`$ en une carte de réponse $`I':E\rightarrow R`$ : l'espace des points est le même, mais l'espace des valeurs $`R`$ n'a pas la même sémantique que l'espace de départ $`V`$. Les valeurs de $`R`$ ne s'interprétent plus comme des valeurs d'intensité mais comme des valeurs de réponse, qui associent à chaque point $`p`$ de $`E`$ la réponse correspondante $`I'(p)`$ du filtre en ce point. En particulier, les valeurs de $`R`$ ne sont plus nécessairement entières ni nécessairement positives : $`R\subseteq \mathbb R`$. Pour visualiser la carte de réponse, il est donc nécessaire d'utiliser une fonction de transformation $`g:R\rightarrow V`$, qui transforme une valeur de réponse en une valeur d'intensité représentable (par exemple $`V=[0\ldots 255]`$ pour des images 8 bits).

Pour plus de détails, consulter le cours (notamment le "bestiaire" des filtres de convolution).

Pour les aspects de normalisation, consulter le cours ou [cette page](https://dpt-info.u-strasbg.fr/~cronse/TIDOC/FILTER/normlin.html).

### Travail à réaliser

L'objectif est de coder une fonction de convolution générique, capable de traiter les deux catégories de filtres. Pour cela, l'image résultante de la convolution sera codée avec des valeurs flottantes.
Écrire une fonction `convolve` qui calcule la convolution d'une image à partir d'un masque passé en paramètres et qui retourne l'image convoluée. Le type du résultat sera donc une image de type `double`.
Les coefficients du masque pourront être stockés également dans une image de type `double`.
La valeur des points situés en dehors du support de l'image sera fixée arbitrairement à 0.

## Filtres de lissage

Les filtres de lissage utilisent des masques dont les valeurs sont toutes positives.
Voici des exemples de masques de lissage :

$` 
M_1=
\frac{1}{9}
\begin{bmatrix}
1 & 1 & 1\\
1 & 1 & 1\\
1 & 1 & 1
\end{bmatrix}
`$,
$`\;
M_2=
\frac{1}{16}
\begin{bmatrix}
1 & 2 & 1\\
2 & 4 & 2\\
1 & 2 & 1
\end{bmatrix}
`$

### Masque gaussien

Un masque gaussien est obtenu en discrétisant la fonction gaussienne définie en 2D par :
```math
G_\sigma(x,y)= \frac{1}{2\pi\sigma^2}  e^{{\textstyle -\frac{x^2+y^2}{2\sigma^2}}}
```

Le support (ensemble des points où la fonction est non nulle) de cette fonction est non borné, mais ses valeurs décroissent rapidement à mesure qu'on s'éloigne de l'origine (comme l'inverse de l'exponentielle du carré de la distance à l'origine !). On adopte donc la convention de l'approcher par un masque de taille $`n\times n`$ avec $`n\approx 5\sigma`$, impair. 

Dans un second temps, il est nécessaire de re-normaliser les coefficients de manière à ce que la somme des poids du masque soit égale à 1.

### Travail à réaliser

- Tester votre fonction de convolution avec les masques précalculés $`M_1`$ et $`M_2`$. 
- Écrire une fonction `gaussianMask` qui renvoie un masque gaussien pour une valeur de $`\sigma`$ passée en paramètre.   
- Expérimenter des convolutions avec des masques gaussiens pour  $`\sigma=1`$, $`\sigma=2`$, $`\sigma=1/2`$.
- Les images résultant des convolutions seront converties en images 8 bits par arrondi des valeurs. 

## Filtres de réhaussement des contours

Les filtres réhausseurs de contours utilisent des masques à coefficients positifs et négatifs dont la somme des poids vaut 1. Ainsi dans les zones homogènes de l'image les niveaux de gris ne sont pas altérés, et dans les zones de transition les contours sont renforcés. Voici des exemples de tels filtres :

$`M_3=
\begin{bmatrix}
0&-1&0\\
-1&5&-1\\
0&-1&0
\end{bmatrix}`$,
$`\;M_4=
\begin{bmatrix}
-1&-1&-1\\
-1&9&-1\\
-1&-1&-1
\end{bmatrix}`$

Les valeurs de l'image résultante peuvent sortir de l'intervalle des valeurs de l'image initiale.
Habituellement on effectue une troncature du résultat en calculant pour chaque valeur v :

$`
v=\left\{
\begin{array}{cl}
0, &  \text{si } v\leq 0  \\
v, &   \text{si }v \in [0\ldots 255]  \\
255, &  \text{si }v\geq 255 
\end{array}\right.`$

### Travail à réaliser

- Expérimenter les filtres de réhaussement des contours définis par les masques $`M_3`$ et $`M_4`$.
- Expérimenter des réhaussements de contours sur des images lissées par des filtres gaussiens pour plusieurs valeurs de $`\sigma`$.

## Filtres détecteurs d'arêtes

Les masques de Sobel horizontaux et verticaux définissent des filtres détecteurs d'arête  :

$`S_x= 
\begin{bmatrix}
-1&0&1\\
-2&0&2\\
-1&0&1
\end{bmatrix},\;`$
et 
$`S_y=\begin{bmatrix}
-1&-2&-1\\
0&0&0\\
1&2&1
\end{bmatrix}`$

Il est à noter que les valeurs de l'image résultante peuvent sortir de l'intervalle des valeurs de l'image initiale, et qu'on s'intéresse ici davantage à la *valeur absolue* de la réponse du filtre en chaque point, qu'à l'image elle même. 

Cependant si l'on souhaite visualiser le résultat dans une image 8 bits, il est nécessaire, d'une part, de calculer la valeur absolue de la réponse, d'autre part, de normaliser les valeurs par la somme des poids "positifs" (ici P=4).
Enfin, toujours à des fins de visualisation, il peut être intéressant d'étirer le contraste de l'image afin que la valeur maximale soit égale à 255.

### Travail à réaliser

- À partir de ces noyaux, écrire un programme  permettant de calculer et de stocker dans une image `uint8_t` une carte des contours par approximation de la norme (ou magnitude) du gradient.

## Bonus

L'opérateur de convolution en deux dimensions peut vite devenir coûteux en temps de calcul pour des tailles élevées du masque.
Un moyen de réduire fortement les temps de calcul est d'utiliser la propriété d'associativité de la convolution.
Un masque $`M`$ est dit séparable s'il peut être décomposé en deux masques $`M_1`$ et $`M_2`$ tels que : $`M=M_1\ast M_2`$.
Comme la convolution est associative, on peut alors écrire :
```math
I\ast M=I\ast (M_1\ast M_2)=(I\ast M_1)\ast M_2
```

Par exemple un filtre moyenneur (ce qui signifie : dont tous les coefficients sont égaux et de somme 1) est séparable puisqu'on peut écrire :

```math
\frac{1}{9}
\begin{bmatrix}
1 & 1 & 1\\
1 & 1 & 1\\
1 & 1 & 1
\end{bmatrix}
=
\left(
\frac{1}{3}\begin{bmatrix}
1 \\ 
1 \\ 
1
\end{bmatrix}
\ast \frac{1}{3}
\begin{bmatrix}
1 & 1 & 1
\end{bmatrix}
\right)
```

Un filtre moyenneur par un masque 2D peut donc se décomposer en deux filtres moyenneurs par des masques 1D (plus rapides à calculer).

### Travail à réaliser

- Le masque gaussien est séparable. Écrire une fonction qui calcule un filtre gaussien pour un écart-type donné en utilisant le principe de décomposition ci-dessus. Comparer avec les résultats obtenus avec un masque 2D.
- Comparer le nombre de multiplications à effectuer :
	- pour calculer la convolution d'une image de $`N`$ pixels par un masque 2D de taille $`M\times M`$
	- pour calculer deux convolutions d'une image de $`N`$ pixels par deux masques 1D de taille $`M`$

## Annexe

### Convolution ou corrélation ?

En réalité la définition de la convolution implique une symétrisation du noyau :

```math
(f\ast h)(t)=\sum_{k=-\infty}^{+\infty}  f(k)h(t-k)=\sum_{k=-\infty}^{+\infty} f(t-k)h(k)
```

En effet le signe $`-`$ implique un parcours des éléments de $`f`$ et de $`h`$ dans un sens opposé.
La convolution est très utilisée dans le domaine du traitement du signal, et dans ce cas la symétrisation est naturelle :
la réponse impulsionnelle d'un système LTI (linéaire, invariant par translation) à un instant $`t`$ est calculé en effectuant une somme pondérée impliquant les valeurs du signal aux temps précédents : $`y[t]=h[0]x[t]+h[1]x[t-1]+h[2]x[t-2]+\ldots`$, avec x le signal d'entrée, y le signal de sortie et h le noyau de convolution (encore appelé réponse impulsionnelle du filtre en traitement du signal).
Par exemple en considérant des signaux discrets $`x`$ et $`h`$ :

```math
x=[0,0,1,2,3,0,0], h=[1,2,3]
``` 

Les valeurs sont indexées en partant de 0 (donc x[0]...x[6] pour x et h[0]...h[2] pour h). Les valeurs en dehors de ces bornes sont nulles.
Le résultat de la convolution $`y`$ est donc calculé ainsi :
- $`y[0]=x[0]*h[0]=0`$
- $`y[1]=x[0]*h[1]+x[1]*h[0]=0`$
- $`y[2]=x[0]*h[2]+x[1]*h[1]+x[2]*h[0]=1`$
- $`y[3]=x[1]*h[2]+x[2]*h[1]+x[3]*h[0]=4`$
- $`y[4]=x[2]*h[2]+x[3]*h[1]+x[4]*h[0]=10`$
- $`y[5]=x[3]*h[2]+x[4]*h[1]+x[5]*h[0]=12`$
- $`y[6]=x[4]*h[2]+x[5]*h[1]+x[6]*h[0]=9`$

Finalement $`y=[0,0,1,4,10,12,9]`$

Historiquement, le traitement d'images a été abordé au début sous l'angle du traitement du signal, l'image étant vue comme un signal à deux dimensions. La convolution en tant qu'opérateur de filtrage linéaire a donc été naturellement utilisée sur des images.
La différence est qu'une image est généralement connue dans son intégralité avant l'opération de filtrage.
De plus, d'un point de vue intuitif il est assez naturel de voir l'opérateur de convolution comme un opérateur qui compare une partie de l'image (un patch) avec le noyau, qui joue le rôle de "template" (on appelle cela du template-matching). 

C'est exactement le principe de la corrélation croisée, qui ne se distingue de la convolution que par le signe $`-`$ qui devient $`+`$ :

```math
(f\star h)(t)=\sum_{k=-\infty}^{+\infty}  f(k)h(t+k)
```

Là, l'indice $`k`$ parcourt bien les deux fonctions dans le même sens. 
Ce qu'on appelle convolution dans ce cours correspond donc techniquement à l'opérateur de corrélation croisée.
Cependant, par abus de langage, l'usage du terme "convolution" se substitue parfois au terme "corrélation croisée", notamment dans le domaine du traitement d'images. Vous pourrez donc trouver sous le terme "convolution" parfois la définition exacte, parfois la définition de la corrélation croisée.

La seule conséquence à retenir est que l'opérateur de convolution est commutatif, mais pas l'opérateur de corrélation.
En général, cela ne prête pas à conséquence, puisque les noyaux utilisés sont symétriques (éventuellement anti-symétriques).
Si le noyau est symétrique, alors $`(f\ast h)(t)=(f\star h)(t)`$. Si le noyau est anti-symétrique, alors $`(f\ast h)(t)=-(f\star h)(t)`$.

Dans ce cours, pour des raisons de simplicité, nous avons fait le choix d'assimiler convolution et corrélation croisée.

Pour plus de précisions, consulter [cette page](https://dpt-info.u-strasbg.fr/~cronse/TIDOC/FILTER/lin.html).


#### En bref

Par abus de langage on assimile dans ce cours la convolution à la corrélation croisée.
Ça ne change rien tant que le noyau et symétrique. Si le noyau n'est pas symétrique, on perd la propriété de commutativité.

### Convolution 1D

On prend donc la formule de convolution suivante :

```math
I'(x)=(I\ast h)(x)=\sum_{k=-\infty}^{+\infty} I(x+k)h(k)
```

Soient les images $`f`$ et $`h`$ indexées à partir de 0 :
$`x=[0,0,1,2,3,0,0]`$, $`h=[1,2,3]`$.

On obtient : 

- $`I'(0)=I(0)*h(0)+I(1)*h(1)+I(2)*h(2)=3`$
- $`I'(1)=I(1)*h(0)+I(2)*h(1)+I(3)*h(2)=8`$
- $`I'(2)=I(2)*h(0)+I(3)*h(1)+I(4)*h(2)=14`$
- $`I'(3)=I(3)*h(0)+I(4)*h(1)+I(5)*h(2)=8`$
- $`I'(4)=I(4)*h(0)+I(5)*h(1)+I(6)*h(2)=3`$
- $`I'(5)=I(5)*h(0)+I(6)*h(1))=0`$
- $`I'(6)=I(6)*h(0)=0`$


Finalement : $`I'=[3,6,14,8,3,0,0]`$.

Un point de $`x`$ est donc filtré en calculant une somme pondérée (ou produit scalaire) impliquant lui-même et ses voisins de droite uniquement. On aimerait centrer le noyau de manière à ce qu'un point soit pondéré à la fois par ses voisins de gauche et ses voisins de droite.
Dans cet exemple, le centre de  $`h`$ est situé à l'indice 1. Donc lors du calcul on effectue une translation de l'image d'un indice vers la gauche, ce qui se traduit par cette formule :

```math
I'(x)=(I\ast h)(x)=\sum_{k=-\infty}^{+\infty}  I(x+k-1)h(k)
```

Maintenant on obtient $`I'=[0,3,6,14,8,3,0]`$, chaque point dans le résultat est obtenu par pondération avec les voisins à gauche et à droite. De manière générale, pour un noyau quelconque de taille $`n`$, le décalage est de $`c=\lfloor \frac{n}{2} \rfloor`$ vers la gauche :

```math
I'(x)=(I\ast h)(x)=\sum_{k=-\infty}^{+\infty}  I(x+k-c)h(k)
```







