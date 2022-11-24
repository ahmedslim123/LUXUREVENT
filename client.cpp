#include "client.h"


Client::Client()
{
   cin="";
   prenom="";
   nom="";
}

void Client::setcin(QString n){cin=n;}
void Client::setprenom(QString n){prenom=n;}
void Client::setnom(QString n){nom=n;}

QString Client::get_cin(){return cin;}
QString Client::get_prenom(){return prenom;}
QString Client::get_nom(){return nom;}
