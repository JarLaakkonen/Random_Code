# TL_Project_Week6

## 0. Ohjeet Scrum tiimille (= 6 työparia) 
	  Viikon vastuullinen työpari pitää daily palaverit keskiviikkoisin ja torstaisin.
	  Scrum-tiimin discord kanavalle raportoidaan daily palaverin tulokset (ketkä paikalla, missä
	  kukin työpari on menossa ja mahdolliset ongelmat). 
	  
	  Viikon vastuullinen työpari järjestää perjantaisin sprint review palaverin Scrum tiimille
	  ja koostaa Scrum-tiimin discord kanavalle raportin viikon tuloksista kunkin työparin osalta.
	  Raportissa kerrotaan myös mikä on seuraavan viikon vastuullinen pari.	  
	  
	  Tutustukaa alla oleviin viikon tehtäviin ja tehkää githubin projektin Kanban tauluun 
	  suunnitelma, minkälaisissa stepeissä aiotte viikon tehtävät tehdä ja testata. 

## 1. Viikon perustavoite = Opetetun K-means algoritmin toteutus ja suorituskyvyn mittaus

Toteutetaan K-means algoritmi nrf5340dk alustalle. Eli mitataan kiihtyvyysanturilla x,y,z
kiihtyvyysarvot ja lasketaan tuon 3D-pisteen etäisyys kaikkiin 6 keskipisteeseen, jotka
on edellisellä viikolla opetettu pythonilla. Nyt pitäisi siis olla esim keskipisteet.h
tiedosto, jonka voisi incluudata c-ohjelmaan helposti.

Saat tehtävässä annettuna github repositoryn https://github.com/kajyrkka/TL_Project_Week6. 
Kloonaa se omalle koneelle, käännä repositoryn mukana tullut nrf5340dk ohjelma ja tutustu
koodiin. Sinun tehtävänä on toteuttaa confusion.c tiedostoon sieltä puuttuvat aliohjelmien
toteutukset ja tehdä sen jälkeen mittaukset omalla laitteellasi ja kiintyvyysanturilla,
jota käytit viikon 2 ja 3 aikana, jolloin opetusdata kerättiin. Tee jokaiseen 6 suuntaan
n. 100 kpl mittauksia.

Tuloksena pitäisi olla confusion matrix K-means luokittelu algoritmin toiminnasta/hyvyydestä.
Lisää confusion matrix kuva omaan github repositoryyn readme-tiedostoon.

Jos et pääse alkuun pelkkään koodiin tutustumalla, niin katso https://youtu.be/O2OIN-gJeo4,
joka selittää ohjelmaa ja tehtävää vielä vähän lisää. 


## 2. Viikon ylimääräinen tavoite = Opetetun neuroverkon toteutus ja suorituskyvyn mittaus

Toteuta Colabissa opettamasi neuroverkko nrf5340dk alustalle ja mittaa algoritmin suorituskyky
laskemalla ja tulostamalla confusion matrix.


