# Projet IoT

Dans ce repertoire vous allez enregistrez les démarches que votre équipe suit
pour mettre en place une chaîne IoT fonctionnel.

Dans les fichiers `README.md` vous devez décrire en format Markdown chacune des étapes, pensez bien à la répartition des tâches dans votre équipe et si besoin créez d'autres repertoires.

Dans ce fichier décrivez bien chacune des étapes et si vous voulez détailler plus, utilisez des sous-dossiers.

## Équipe
Hamza AL-SATARI

Jérémy DELGADO

Audrey FOURNIER

Guillaume RENOTTON

Nacereddine TOUMI

## Description du Projet

Le sujet initial est dans le fichier [sujet.md](sujet.md)
Vous devez décrire ici les fonctionnalités et applications de la maquette que vous avez décidé d'implementer.
Ce projet a pour but de réaliser une station météo connectée avec reconnaissance vocale. Pour ce faire nous avons à disposition différents capteurs, un BeagleBoneBlack et un Arduino Mega.

### Capteurs

Capteur météo (Weather Click)

Capteur de voix (SpeakUp Click)

Modules WiFi : CC3000 Click et WiFi3 Click(ESP8266)

### Cas d'utilisation



## Répartition des tâches



### Suivi journalier



## Procédure de mise en place de votre chaîne IoT

### Première étape : Les Capteurs

#### Capteur de voix

Tout d'abord il faut configurer le capteur. Pour cela, il faut télécharger le logiciel associé au SpeakUp Click : https://download.mikroe.com/setups/add-on-boards/click/speakup/speakup-configuration-software-v100.zip

Ce logiciel permet d'enregistrer des mots ou phrases d'une seconde maximum afin de remplir la base de donnée du capteur. Le principe étant que chaque mot enregistré correspond à un numéro. Lors de la détection d'un mot par le capteur, celui-ci renverra via le port série le numéro associé. Une fois les configurations faites, il suffit d'uploader la configuration directement sur le Click. Pour cela, il faut choisir dans les paramètres le baud rate ainsi que le seuil de détection. <b>Attention</b> : Afin que le numéro soit bien envoyé sur le serial par la suite, il faut augmenter le seuil à un minimum de 40. Dans le cas contraire, la réception via le serial du numéro ne se fera pas.

Une fois la configuration faite, il ne reste plus qu'à connecter le click à l'Arduino et à réaliser le code. Pour la connexion, chaque socket de l'arduino correspond à un Serial, le socket1 correspond au Serial1, le socket2 correspond au Serial2 et le socket3 au Serial3. Le Serial0 (ou Serial), est utilisé pour la communication entre l'Arduino et l'ordinateur et uniquement pour celle-ci.

Il faut finalement réaliser le code permettant de différencier chaque réception. Il faut simplement utiliser les fonctions suivantes : Serial?.begin('baud rate') pour démarrer le port Serial; Serial?.available(), qui permet d'attendre une réception sur le port Serial voulu; Serial?.read() pour lire sur le port Serial voulu.


#### Capteur Météo (BME280)

Ce capteur ne nécessite pas de configuration particulière. Il faut installer la bibliothèque associée. Soit l'installer depuis le lien suivant : https://github.com/adafruit/Adafruit_BME280_Library; soit l'installer directement depuis l'IDE Arduino via l'onglet Croquis-->Inclure une bibliothèque.

Une fois la bibliothèque installée, des exemples d'utilisation du capteur sont à disposition et contiennent les fonctions à utiliser pour récupérer les différentes valeures du capteur.<b>Attention : </b>Il faut également rajouter en début de code la ligne bme.begin(0x76), le 0x76 permettant de lancer le capteur en mode I2C et non pas en Serial. 


### Deuxième étape : Capteur WiFi CC3000

Ce capteur qui à pour but de se connecter à un point d'accès a besoin d'une bibliothèque spéciale pour fonctionner. Pour cela, il faut installer la bibliothèqe associée au CC3000 : https://github.com/adafruit/Adafruit_CC3000_Library

Une fois la bibliothèque installée, un code test est disponible : buildtest. Ce code permet de tester le fonctionnement du CC3000. Ce code fonctionne directement sur un Arduino Uno. Cependant nous utilisons un Arduino Mega et les pins sont donc différents. Le Socket1 ne peut pas être utilisé pour le CC3000 car le pin d'interruption n'en est pas un sur ce Socket. Pour le Socket2, les digital pins à utiliser sont les suivants : Socket2(Int : 2, EN : 48, CS : 46) et Socket3(Int : 3, EN : 47, CS : 45).
De plus pour fonctionner sur un Arduino Mega


## Conclusions et recommandations
