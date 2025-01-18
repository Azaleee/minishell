# Minishell

## Description
Minishell est un projet de l'école 42 visant à recréer un shell minimaliste en C. Il a pour objectif d'approfondir la compréhension des concepts fondamentaux de l'exécution des commandes sur un système UNIX, de la gestion des processus, et de l'interaction utilisateur avec une interface en ligne de commande.

## Fonctionnalités

### Obligatoires :
- **Prompt personnalisé**
  - Affiche le nom du répertoire courant avec des couleurs.
- **Exécution de commandes**
  - Supporte les commandes présentes dans le `$PATH` via `execve`.
- **Redirections**
  - `<` : Redirection d'entrée.
  - `>` : Redirection de sortie.
  - `>>` : Redirection de sortie en mode append.
  - `<<` : Hérédoc avec gestion de mot-clé de fin.
- **Pipelines**
  - Support des pipelines (`|`) pour chaîner plusieurs commandes.
- **Variables d'environnement**
  - Expansion des variables (e.g., `$HOME`, `$USER`).
- **Gestion des erreurs**
  - Messages d'erreurs clairs pour les erreurs de syntaxe et d'exécution.
- **Builtins**
  - Implémentation des commandes internes suivantes :
    - `cd`
    - `echo`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`

## Compilation et Exécution

### Prérequis
- GCC ou tout autre compilateur C compatible.
- GNU Make.
- Bibliothèque readline (installable via votre gestionnaire de paquets).

### Instructions
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/votre-utilisateur/minishell.git
   cd minishell
   ```
2. Compilez le projet :
   ```bash
   make
   ```
3. Lancez le shell :
   ```bash
   ./minishell
   ```

## Structure du Projet

### Arborescence des fichiers
```
minishell/
├── Makefile
├── src/
│   ├── main.c
│   ├── parser/
│   │   └── lexer.c
│   ├── executor/
│   │   ├── pipes.c
│   │   └── redirections.c
│   ├── builtins/
│   │   ├── cd.c
│   │   └── echo.c
│   └── utils/
│       ├── error.c
│       └── env.c
├── include/
│   └── minishell.h
├── libft/
│   └── [Librairie personnalisée]
└── README.md
```

### Principaux Modules
- **Lexer** : Analyse la ligne de commande pour identifier les tokens.
- **Parser** : Crée une structure compréhensible à partir des tokens (abstract syntax tree).
- **Executor** : Gère l'exécution des commandes, des pipes, et des redirections.
- **Builtins** : Implémentation des commandes internes.

## Ressources Utiles
- [Documentation GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Manpage execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- [Manpage pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [Introduction aux shells UNIX](https://linuxcommand.org/)

---

## Auteur
Projet réalisé dans le cadre du cursus **42** par :
- Azaleee & eliamd

