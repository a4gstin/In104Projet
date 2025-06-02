# In104Projet

Le projet est structuré au tour de deux fichiers :  main.c et Functions.c. Le fichier Functions.c est associé à des fichiers .h du même nom où on déclare les fonctions codées.



Nous avons codé dans le fichier Functions.c :

- des fonctions générales et simples

A. findUserIndex qui donne l'indice d'un utilisateur dans la list user à partir de son nom
B. printPath qui imprime un chemin donné avec les noms des utilisateurs parcourus (utiliser pour tester les fonctions de parcours codés dans searchFunctions)
C. findFriendshipStrength qui donne la force d'une amitié entre 2 utilisateurs
D. removeFriendship qui supprime une amitié entre 2 utilisateurs
E. addFriendship qui ajoute une amitié entre 2 utilisateurs
F. findAverageFriendshipStrenght qui calcule le "score" moyen d'amitié d'un utilisateur
G. initializeGraph qui initialise la matrice d'adjacence du graphe (elle la remplit de zéros)
H. addUserWithFriendships qui permet d'ajouter un nouvel utilisateur avec ses "forces" d'amitié avec les utilisateurs déjà existants
I. removeUser qui permet d'enlever un utilsateur de la matrice d'adjacence et de la liste des utilisateurs
J. modifyFriendship qui permet de modifier la force de l'amitié entre 2 amis (donnés en entrée)
K. orderUsersByFriendCount qui trie les utilsateurs par ordre décroissant de nombre d'ami

- des fonctions de parcours de graphe

1. findShortestPath qui donne la plus petite connexion (en terme de nombre d'ami) entre 2 utilsateurs (BFS)
2. findPotentialFriends qui donne une liste de tous les amis potentiels à un niveau de profondeur souhaité (BFS)
3. exploreAllFriendships qui donne la liste de tous les amis potentiels, sans contrainte de profondeur (DFS)
4. hasPath qui donne un bool sur le test :"il y a une connexion entre 2 utilsateurs" 
5. dijkstraWeakestPath qui trouve le chemin le plus faible (en force d'amitié) entre 2 utilsateurs (algorithme glouton)
6. aStarWeakestPath qui fait la même chose que l'algorithme de Dijkstra met en prenant en compte l'objectif (utilisateur final)
7. dfsForComponents et findConnectedComponents qui vérifient si le graphe représenté par adjacencyMatrix est connexe


Le fichier main.c contient lui le code qui permet l'utilisation de ces fonctions dans l'optique de faire fonctionner le réseau social de façon intéractive dans le terminal(comme un vrai réseau social).
Dans ce fichier, il y a 3 fonctions codées qui sont directement liées au fonctionnement du réseau social :

1. makelogo qui dessine le logo dans le terminal
2. readFromFile qui initialise les données du réseau social à partir d'un fichier .txt donné
3. saveToFile qui permet de créer un nouveau fichier .txt qui traduit la mise à jour du fichier initial .txt après utilisation du réseau social

Le main est lui rédigé en grand bloc qui regroupe les actions possibles :
1. See your friends (permet de voir ses amis et de réaliser des actions sur ces amis : en enlever, modifier la force d'amitié)
2. Search a Friend (permet de trouver de nouveaux amis suivant des filtres par défaut, d'en enlever, d'en rajouter, ...)
3. My page (permet de voir sa page avec ses stats et de la modifier - en mofifaint son pseudo, sa bio, le nom de son école)



Nous avons enfin rédigé un Makefile pour compiler le tout (il faut utiliser la commande "chmod +x ./main3.c" pour obtenir la permission de compiler, si celle-ci n'est pas accordée). Il faut exécuter le fichier noperc (nom de l'exécutable).
