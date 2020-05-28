# Projet de Compilation 

- Nady SADDIK
- Alexandre KARAKAS

## Langage

Nous avons décidé d'utiliser le langage C pour créer le compilateur MiniJS. On utilise Flex et Bison pour lexeur et parseur.

## Utilisation 

Pour notre compilateur, il faudra suivre plusieurs étapes : 
- Compiler le parseur avec la commande : bison -d parser.y
- Compiler le lexeur avec la commande :  flex lexer.l
- Puis on compile tous les fichiers avec la commande : gcc -o compilateur main.c parser.tab.c lex.yy.c


Créez ensuite un fichier qui contiendra le code que vous souhaitez compiler.
Enfin, pour utiliser notre compilateur, vous devrez entrer sur le terminal ./compilateur nom_du_fichier_a_compiler
