# In104Projet

Le projet est structuré au tour du fichier p1.c qui comprend les fonctions demandées dans la fiche du projet.

A ce stade, nous avons codé dans ce fichier :

1. initializeGraph qui initialise la matrice d'adjacence du graphe (elle la remplit de zéros)
2. addUserWithFriendships qui permet d'ajouter un nouvel utilisateur avec ses "forces" d'amitié avec les utilisateurs déjà existants
3. removeUser qui permet d'enlever un utilsateur de la matrice d'adjacence et de la liste des utilisateurs
4. modifyFriendship qui permet de modifier la force de l'amitié entre 2 amis (donnés en entrée)
5. findShortestPath pour trouver la plus petite connexion (en terme de longueur du chemin = nombre d'ami) entre 2 personnes du réseau social

Nous avons commencé le codage d'autres fonctions mais que nous n'avons pas finies.

Nous avons mis à jour le fichier main.c fourni en main3.c pour qu'il soit cohérent avec p1.c avec un exemple d'utilisation des fonctions que nous avons codées.

Nous avons enfin rédigé un Makefile pour compiler le tout.

Nous prévoyons dans la suite de :
    finaliser les fonctions requises dans la description du projet
    améliorer la complexité de l'algorithme en itérant de façon dynamique au lieu d'itérer sur MAXUSERS
    améliorer le main pour qu'il soit dynamique (comme si il y avait un utilisateur en acion)
