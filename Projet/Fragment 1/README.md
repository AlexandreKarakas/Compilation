# Projet de Compilation 

- Nady SADDIK
- Alexandre KARAKAS

## Langage

Nous avons décider d'utiliser le langage C pour créer le compilateur minijs, utilisation de flex et de bison

## Utilisation 

Pour notre compilateur, il faudra suivre plusieurs étapes : 
- Compiler le lexeur avec la commande :  flex lexer.l ce qui nous donne plusieurs fichiers

- Compiler le parseur avec la commande : bison -d parser.y

- Puis on compile tous les fichiers avec la commande gcc -o compilateur AST.c parser.tab.c main.c lex.yy.c

Pour utiliser notre compilateur, vous devrez entrer sur le terminal ./compilateur nom_fichier_code