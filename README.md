WhisperNode
=================================================
Mael MAINCHAIN & Chloe GUILBAUD

# Procédure de déploiement du programme sur ARDUINO

**Première utilisation**
Installer le package PlatformIO IDE
Editeurs supportant PlatformIO IDE:
 - Visual Studio Code
 - Atom
 - (à compléter...)

Installer la librairy Talk2 
 - Menu plateformio -> install/update library platformio lib install "Talk2"
 - OU `$ pio lib install "Talk2"`

Installer la librairie de gestion des communications "RadioHead":
 - Menu plateformio -> install/update library platformio lib install "RadioHead"
 - OU `$ pio lib install "RadioHead"`

Installer la librairie de gestion de la consommation "LowPower":
 - Menu plateformio -> install/update library platformio lib install "LowPower"
 - OU `$ pio lib install "LowPower"`

**Utilisation**
Compilation:
 - Menu platformio -> Build
Déploiement sur l'appareil:
 - Menu platformio -> Upload to remote device

