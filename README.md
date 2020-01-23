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

#### Le 20 janvier 2020 :

- Hamza  :
Mise en place du BeagleBone : En cours de finition

- Nacereddine :
Mise en place du Cloud avec Ubidots : Fait
Mise en place de l'envoie de donnée : En cours de finition

- Jérémy et Guillaume :
Mise en place du Wifi CC3000 : Gros problème lors de la mise en place, désormais fonctionnel
Test fonctionnement envoie des données sur un serveur HTTP tiers : Fonctionnel

- Guillaume et Audrey :
Configuration du Click Weather : Fait
Configuration du SpeakUp Click : Fait

- Audrey :
Recherche documentaire sur les composant pour aider Guillaume et Jérémy à résoudre les problèmes survenus


#### LE 21 janvier 2020 :

- Tout le monde :
Configuration du BeagleBone : Problème de version sur le BeagleBone, résolution toujours en cours, Tests de toutes les versions possibles

- Jérémy, Guillaume et Audrey :
Carte Wifi3 click (ESP8266) : Recherche documentaire pour configuration, Standby le temps de finir la configuration du BeagleBone

- Nacereddine :
Configuration du cloud : En cours



#### Le 22 janvier 2020 :

- Configuration beagle bone : fini
- Configuration wifi 3 click : fini
- Wifi 3 click : HS, utilisation de la carte autre groupe + test flash de l'ancienne carte.
- Envoi des données jusqu'au cloud : fini
- Mise en place du tutoriel : à faire
- Différents tests à faire ( format, affichage, etc)

Au cours de cette journée, tous les membres de l'équipe ont travaillé de manière conjointe sur chacun des aspects


## Procédure de mise en place de votre chaîne IoT


### Première étape : Les Capteurs

#### Capteur de voix

Tout d'abord il faut configurer le capteur. Pour cela, il faut télécharger le logiciel associé au SpeakUp Click : https://download.mikroe.com/setups/add-on-boards/click/speakup/speakup-configuration-software-v100.zip

Ce logiciel permet d'enregistrer des mots ou phrases d'une seconde maximum afin de remplir la base de donnée du capteur. Le principe étant que chaque mot enregistré correspond à un numéro. Lors de la détection d'un mot par le capteur, celui-ci renverra via le port série le numéro associé. Une fois les configurations faites, il suffit d'uploader la configuration directement sur le Click. Pour cela, il faut choisir dans les paramètres le baud rate ainsi que le seuil de détection. <b>Attention</b> : Afin que le numéro soit bien envoyé sur le serial par la suite, il faut augmenter le seuil à un minimum de 40. Dans le cas contraire, la réception via le serial du numéro ne se fera pas.

Une fois la configuration faite, il ne reste plus qu'à connecter le click à l'Arduino et à réaliser le code. Pour la connexion, chaque socket de l'arduino correspond à un Serial, le socket1 correspond au Serial1, le socket2 correspond au Serial2 et le socket3 au Serial3. Le Serial0 (ou Serial), est utilisé pour la communication entre l'Arduino et l'ordinateur et uniquement pour celle-ci.

Il faut finalement réaliser le code permettant de différencier chaque réception. Il faut simplement utiliser les fonctions suivantes : Serial?.begin('baud rate') pour démarrer le port Serial; Serial?.available(), qui permet d'attendre une réception sur le port Serial voulu; Serial?.read() pour lire sur le port Serial voulu.


#### Capteur Météo (BME280)

Ce capteur ne nécessite pas de configuration particulière. Il faut installer la bibliothèque associée. Soit l'installer depuis le lien suivant : https://github.com/adafruit/Adafruit_BME280_Library; soit l'installer directement depuis l'IDE Arduino via l'onglet Croquis-->Inclure une bibliothèque.

Une fois la bibliothèque installée, des exemples d'utilisation du capteur sont à disposition et contiennent les fonctions à utiliser pour récupérer les différentes valeures du capteur. <b>Attention : </b>Il faut également rajouter en début de code la ligne bme.begin(0x76), le 0x76 permettant de lancer le capteur en mode I2C et non pas en Serial. 


### Deuxième étape : Capteur WiFi CC3000

Ce capteur qui à pour but de se connecter à un point d'accès a besoin d'une bibliothèque spéciale pour fonctionner. Pour cela, il faut installer la bibliothèqe associée au CC3000 : https://github.com/adafruit/Adafruit_CC3000_Library

Une fois la bibliothèque installée, un code test est disponible : buildtest. Ce code permet de tester le fonctionnement du CC3000. Ce code fonctionne directement sur un Arduino Uno. Cependant nous utilisons un Arduino Mega et les pins sont donc différents. Le Socket1 ne peut pas être utilisé pour le CC3000 car le pin d'interruption n'en est pas un sur ce Socket. Pour le Socket2, les digital pins à utiliser sont les suivants : Socket2(Int : 2, EN : 48, CS : 46) et Socket3(Int : 3, EN : 47, CS : 45).
De plus pour fonctionner sur un Arduino Mega il faut souder certains pins entre eux car le pin d'interruption demandé n'est pas au bon endroit sur l'Arduino. Voici une photo montrant les pins à souder : 

![alt-text](https://github.com/CPELyon/projet-iot-5a-2019-2020-jangh/blob/master/images/SoudageCC3000_LI.jpg)

Ces changements réalisés, le code est fonctionnel.


### Troisième étape : Fusion des codes des capteurs

Une fois les codes réalisés et fonctionnels chacun de leur côté, il suffit de les regrouper de façon à ce qu'il réalise la chaine voulue. Pour ce projet, on commence par l'initialisation et la connexion du CC3000 à un point d'accès, puis on attend un mot de l'utilisateur comme "Température", et en fonction de ce mot, on envoie via le module WiFi la valeur voulue.


### Quatrième étape : Configuration du BeagleBoneBlack(BBB)

Pour configurer le BeagleBone, il faut tout d'abord flasher la carte SD avec une certaine version de Debian afin de pouvoir par la suite configurer le module WiFi3. Afin de flasher la SD, on utilise le logiciel BalenaEtcher et la version de Debian suivante : https://debian.beagleboard.org/images/bone-debian-8.6-iot-armhf-2016-11-06-4gb.img.xz

Une fois la carte SD flashée, il suffit de l'insérer dans le BBB et de brancher celui-ci à un ordinateur. On peut ensuite se connecter via l'adresse du BBB : 192.168.7.2.

Après avoir installer et lancer le beagle bone, il est nécessaire de connecter le beagle bone à internet pour le mettre à jour. Pour cela on vas utiliser l'ordinateur de CPE comme passerelle avec un pfsense. Cela se passe en plusieurs étapes : 
* Il faut connecter un cable éthernet entre le beagle bone et l'ordinateur.
* Il faut définir une adresse ip sur eth0 du beagle bone. (via /etc/network/interfaces)
* Il faut installer un pfsense et mettre en WAN le lien vers CPE et en LAN le lien vers le beagle bone (même réseau que le beagle bone)
* Il faut également paramétrer le DNS, pour cela 2 solutions est possible, soit faire un DNS forwarder ou bien mettre l'adresse du DNS de CPE.
* Changer l'adresse du DNS (soit DNS CPE ou DNS pfsense) dans le fichier /etc/resolv.conf
* Maintenant nous avons internet au sein du beagle bone et donc pouvons mettre à jour celui-ci et installer les packages nécessaires.


### Cinquième étape : Configuration du WiFi3 Click

Pour configurer le WiFi3, nous avons suivi le tutoriel suivant : https://v37e00e.blogspot.com/2015/12/beaglebone-black-bbb-uart2-with-esp8266.html

Ce tutoriel permet d'activer l'UART2 et d'autoriser la communication entre le module WiFi et le BBB. Le Socket1 du BBB correpsond au ttyO2-UART2.

Il faut bien décommenter toutes les lignes dans le /boot/uENV.txt commençant par dtb=... 

Il faut également supprimer la fin de la ligne après le "quite" : "cape_universal=enable"

Une fois cela réalisé, le prochain branchement du module CC3000 devrait afficher un "Ready" dans le ttyO2.


### Sixième étape : Cloud avec Ubidots

Concernant le cloud, Si on a un Raspberry Pi, Beaglebone ou un autre appareil basé sur Linux, et on souhaite interagir avec Ubidots, voici un descriptif qui montre comment on a créé notre cloud sous Ubidots et comment on a pu le tester avec les avantages de ce dernier. Pour notre cas on a travaillé avec un Beaglebone.

On a commencé par créer un compte ubidots sur https://industrial.ubidots.com, avec ce compte on a une version de test gratuite pendant 30 jours où on peut utiliser toutes les fonctionnalités d'Ubidots mais parfois avec des limitations qu'on verra plus tard dans ce descriptif.

On a créé par la suite un device qu'on a appelé "jangh" sur lequel on a ajouté les variables qu'on souhaite avoir sur le cloud comme données depuis le beaglebone, les variables sont les suivantes : Lattitude, Temperature, Humidity, Pressure chacune de ces variables a une "API label" qu'on utilisera plus tard dans notre script qui permet d'envoyer les données.

Ensuite je me suis penché sur un script python (Cloud.py) qui va me permettre de simuler l'envoie les données, dans un premier temps j'ai commencé par envoyer des données random afin de tester mon script et dans un deuxième temps faire la connexion entre les données reçu dans le beaglebone et le cloud. Il faut tout d'abord s'assurer qu'on a bien python installer ainsi que certaines bibliothèques (json, requests, ...) voir la documentation sur internet pour l'installation.

Sur ubidots nous avons déjà notre device mise en place et paramétré à recevoir les valeurs concernant ses capteurs qui sont  Lattitude, Temperature, Humidity et Pressure. Pour chacun de ses capteurs on peut voir un graphe de toutes les valeurs reçu dans le temps depuis la mise en place du device. Ensuite pour permettre à tout utilsateur de visualiser les données envoyé par notre device (weather station) de façon simplifiée nous avons mis en place un dashboard regroupant toute les données affichées à l'aide de widget et de graphique.

Ensuite nous avons mis en place des alertes sur les différentes variables avec des règles d'astreinte comme par exemple si la température dépasse un certain seuil on envoie un message sur telegram (la semaine de 00:00-23h49), un mail (la semaine de 08:00-18:00), un sms (le week-end de 00:00-23h59). Nous avons aussi mis en place un envoie de rapport quotidien nous résumant ce qu'il s'est passé la veille.


## Conclusions et recommandations

L'utilisation des clicks facilite grandement le projet. En effet, tous les capteurs possèdent une documentation associée permettant facilement de comprendre comment les utiliser et les faire fonctionner. La partie la plus compliquée est la mise en place de la partie communication entre l'Arduino et le BBB. En effet, les modules comme le WiFi3 Click n'ont que très peu de documentation. Il faut donc savoir que ce Click utilise un module WiFi ESP8266 et que ce sont donc des documentations sur ce module qu'il faut rechercher. 

La principale recommandation pour ce genre de projet est de bien comprendre le fonctionnement de chaque module afin d'avoir une vision globale du projet et à tout moment de savoir dans quel direction s'orienter pour faire fonctionner la globalité de la maquette.

![alt-text](https://github.com/CPELyon/projet-iot-5a-2019-2020-jangh/blob/master/images/Arduino.jpg)
![alt-text](https://github.com/CPELyon/projet-iot-5a-2019-2020-jangh/blob/master/images/BBB.jpg)
