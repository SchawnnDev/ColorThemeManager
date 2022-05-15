# Color Theme Manager

## Installation

### Avec CMake

```
cmake -B build
```

Lancer l'application dans le dossier généré par cmake.

### Avec QMake

```
qmake
make
```

Lancer l'application dans le dossier QT.

## Liste des fonctionnalités

Toutes les fonctionnalités demandées ont été implémentées.

### Toolbar

- Importer un fichier (thème) (Ctrl + P)
- Calcul thème d'un fichier (Récupère toutes les couleurs d'un fichier et les met en source)
- Créer un nouveau thème (Ctrl + N)
- Charger les thèmes récents (Charge tout les thèmes enregistrés, sans limite)
- Sauvegarder tous les thèmes (Ctrl + S) (Sauvegarde tous les thèmes ouverts)
- Langage > Choix entre le Français et l'anglais

### Editeur de thèmes

- Changer le nom du thème
- Changer l'icône du thème
- Ajouter une paire de couleurs
- Importer des paires de couleurs (d'un fichier XML)
- Importer des paires de couleurs par URL (télécharge du XML par internet)
- Appliquer le thème a un fichier (remplace tous les codes HEX)
- Sauvegarder

### Editeur de paire de couleurs

- Changer le nom de la couleur
- Changer les couleurs par texte (code HEX)
- Changer les couleurs avec un color picker

### Traduction

- Traduire l'interface entièrement en anglais ou français

### Drag and drop

- Pouvoir changer la place d'un thème dans la liste des thèmes ouverts
- Pouvoir importer des thèmes (fichier .theme) en droppant des fichiers dans le mainwindow.

### Style

- Utilisation d'icones (feathericons)
- Choix volontaire de ne pas avoir changé le style des boutons

## Fonctionnalités non implémentées

- Niveau 9 tout sauf la traduction

## Bugs

Aucun bug a signaler