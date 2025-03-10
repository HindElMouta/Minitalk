# Projet : MiniTalk

## Description
MiniTalk est un projet permettant d'établir une communication entre un client et un serveur en utilisant des signaux UNIX (`SIGUSR1` et `SIGUSR2`). L'objectif est d'envoyer des messages depuis un programme client vers un programme serveur, qui les affiche à l'écran.

## Fonctionnement
### **1. Lancement du serveur**
Le serveur doit être exécuté en premier. Il affichera son PID (Process ID), qui devra être utilisé par le client pour envoyer un message.
```bash
./server
```

### **2. Envoi d'un message avec le client**
Une fois le serveur lancé, le client peut envoyer un message en lui passant le PID du serveur et le message à transmettre :
```bash
./client <PID_SERVEUR> "Votre message ici"
```
Exemple :
```bash
./client 2214 "Hello, serveur!"
```

## Explication des fichiers
### **1. `server.c`**
- Affiche son PID à l’exécution.
- Attend des signaux `SIGUSR1` et `SIGUSR2` pour reconstruire les caractères du message envoyé par le client.
- Utilise `pause()` pour attendre continuellement des signaux.

### **2. `client.c`**
- Convertit le message en une série de signaux `SIGUSR1` et `SIGUSR2`.
- Envoie chaque bit du message un par un au serveur via la fonction `kill(pid, signal)`.
- Attend un court délai (`usleep`) entre chaque signal pour assurer une bonne transmission.

### **3. `utils.c`**
- Contient des fonctions utilitaires comme `ft_putstr()`, `ft_putnbr()`, et `ft_atoi()` pour la conversion et l'affichage.

## Compilation
Utilise `make` pour compiler le projet :
```bash
make
```
Cela génère les exécutables `server` et `client`.

## Erreurs possibles et solutions
### **1. "Invalid PID" lors de l’exécution du client**
- Vérifie que le serveur est bien lancé et que tu utilises le bon PID.
- Assure-toi que le serveur n’a pas été fermé entre-temps.

### **2. "Commande introuvable" lors du lancement de WSL**
- Vérifie si WSL est bien installé avec :
  ```bash
  wsl --list --verbose
  ```
- Si nécessaire, réinstalle WSL avec `wsl --install` en mode administrateur.

## Améliorations possibles
- Ajouter une confirmation d’envoi et de réception des messages.
- Gérer des messages plus longs avec des paquets de données plus optimisés.
- Implémenter un affichage plus détaillé des erreurs pour faciliter le débogage.

---
### Auteur
Projet développé dans le cadre du cursus **42**.

