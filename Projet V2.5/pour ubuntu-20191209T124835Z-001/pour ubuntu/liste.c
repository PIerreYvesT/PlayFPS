
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "monster.h";
#include "liste.h";

liste l_vide ()
{
  return NULL ;
}

liste cons (Monster* x, liste L)
{
  liste M ;
  // Réservation de la place mémoire nécessaire pour une cellule :
  M = malloc (sizeof (*M)) ;
  M->premier = x ; // On peut aussi écrire " M->premier = x ; "
  M->suivant = L ;
  return M ;
}

/* Accès */
bool est_vide (liste L)
{
  return L == NULL ;
}

Monster* prem (liste L)
{
  if (est_vide (L))
    {
      printf ("Calcul de prem sur liste vide !\n") ;
      exit (0) ;
    }
  return L->premier ;
}

liste reste (liste L)
{
  if (est_vide(L))
    {
        return L;
    }

    return L->suivant ;
}

/* Autres opérations primitives (hors type-abstrait) */
void liberer_liste (liste L)
{
  if (est_vide (L))
    {
      return ;
    }
  liberer_liste (reste (L)) ;
  free(L) ;
}

/*void ecrire_prem (Monster* x, liste L)
{
  L->premier = x ;
}*/

void ecrire_reste (liste R, liste L)
{
  L->suivant = R ;
}

/* OPERATIONS NON PRIMITIVES */
unsigned int longueurR (liste L)
{
  if (est_vide (L))
    return 0 ;
  return 1 + longueurR (reste (L)) ;
}

unsigned int longueurI (liste L)
{
  unsigned int lg ;
  lg = 0 ;
  while (!est_vide (L))
    {
      lg = lg + 1 ;
      L = reste (L) ;
    }
  return lg ;
}

/*void afficher_liste (liste L)
{
  printf ("(") ;
  while (!est_vide (L))
    {
      printf ("%d%s",
	      prem (L),
	      (est_vide (reste(L)) ? "" : " ")) ;
      L = reste (L) ;
    }
  printf (")") ;
}

liste renverser (liste L)
{
  liste R, M ;
  R = l_vide () ;
  M = L ;
  while (!est_vide(M))
    {
      R = cons (prem(M), R) ;
      M = reste (M) ;
    }
  return R ;
}
*/
// Opération non destructrice 
/*liste repeter_elements (liste L)
{
  int x ;
  if (est_vide (L))
    {
      return l_vide () ;
    }
  x = prem (L) ;
  return cons (x, cons (x, repeter_elements (reste(L)))) ;
}
*/
/* Opération destructrice */
/*void repeter_elements_D (liste L)
{
  int x ;
  if (est_vide (L))
    {
      return ; /// quitter la procédure 
    }
  x = prem (L) ;
  ecrire_reste (cons (x, reste (L)), L) ;
  repeter_elements_D (reste (reste (L))) ;
}*/

/* Opération pour /modifier/ une liste L en insérant la valeur x
   à la nème position. Sauf dans le cas d'une erreur ou dans le
   cas d'une insertion en première position, cette fonction
   modifie la liste (opération destructrice).
   Si n est trop grand, alors on insère à la fin.
*/
liste inserer_liste_D (unsigned int n, Monster* x, liste L)
{
  unsigned int i ;
  liste M ;
  if (n == 0 || est_vide(L))
    {
      printf ("Utilisation d'inserer_liste_D incorrecte\n") ;
      exit(EXIT_FAILURE) ;
    }
  if (n == 1)
    {
      return cons (x, L) ;
    }
  M = L ;
  i = 1 ;
  while (!est_vide(reste(M)) && i < n - 1) {
      M = reste(M) ;
      i = i + 1 ;
  }
  ecrire_reste (cons(x, reste(M)), M) ;
  return L ;
}





liste CreateListeMonster(int nbmonster,SDL_Renderer *pRenderer)
{
	liste M= cons(CreateMonster(pRenderer),l_vide());
	int i;
	for (i=1; i<nbmonster;i++)
	{
		M=cons(CreateMonster(pRenderer),M);
	}
	
	return M;
}




void RenderListeMonster(SDL_Renderer* renderer,liste M)
{
	int cpt=1;
	while (!est_vide(M))
	{
		
		RenderMonster(renderer, prem(M));
		M=reste(M);
		printf("compteur render:%d",cpt);
		cpt=cpt+1;
	}

}



