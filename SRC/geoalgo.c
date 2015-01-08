#include <stdio.h>
#include <stdlib.h>

#include "geoalgo.h"

/*----------------------------------------------------------------------------------*/
//                                  Ordering functions
/*----------------------------------------------------------------------------------*/

int isSuperior(Vertex const *p, Vertex const *q, Dllist const *dll, int const LNK)
{
	switch (LNK)
	{
		case LEX: if ((p->coords[0] > q->coords[0]) || (p->coords[0] == q->coords[0] && p->coords[1] >= q->coords[1])) return 1;
			else return 0;
		case POL: return ( orientation( dll->root->links[LEX][FWD], p, q ) + 1 ) / 2 ; // gestion pts alignés 
		default: printf("Error in isSuperior function\n");
			break;
	}
	return -1;
}

void graham(Dllist *dll)
{
	add_end_dll(dll, dll->root->links[POL][FWD], GRA); // 1st in polar order
	add_end_dll(dll, dll->root->links[POL][FWD]->links[POL][FWD], GRA); // 2nd in polar order
	Vertex *current = dll->root->links[POL][FWD]->links[POL][FWD]->links[POL][FWD]; // 3rd in polar order
	int height = 2;

	for (int i = 3; i <= dll->length[POL]; ++i)
	{
		while ( ( height >= 2 ) && ( orientation(dll->root->links[GRA][BWD]->links[GRA][BWD], dll->root->links[GRA][BWD], current) >= 0 ) )
		{
			rm_end_dll(dll, GRA);
			height--;
		}
		add_end_dll(dll, current, GRA);
		height++;
		current = current->links[POL][FWD];
	}
}

void jarvis(Dllist *dll)
{
	Vertex *p = dll->root->links[LEX][FWD];
	Vertex *q = NULL;
	Vertex *r = NULL;
	add_end_dll(dll, p, JAR);
	do
	{
		q = p->links[POL][FWD];
		r = q->links[POL][FWD];
		while (r != dll->root)
		{
			if ( orientation(p, q, r) >= 0 )
			{
				q = r;
			}			
			r = r->links[POL][FWD];
		}
		p = q;
		add_end_dll(dll, p, JAR);
	} while (p != dll->root->links[POL][BWD]);
}

Vertex* merge(Vertex* p, int P, Vertex* q, int Q, Dllist *dll, int LNK)
{
	while (1)
	{
		if ( isSuperior( p->links[LNK][FWD], q->links[LNK][FWD], dll, LNK ) )
		{
			move_after(p, q->links[LNK][FWD], LNK);

			if ( Q == 1 ) break;
			Q = Q - 1;
		}
		else
		{
			if ( P == 1 )
			{
				while ( Q >= 1 )
				{
					q = q->links[LNK][FWD];
					Q = Q - 1;
				}
				break;
			}
			P = P - 1;
		}
		p = p->links[LNK][FWD];
	}
	return q;
}


Vertex* sort(Vertex *p, int n, Dllist *dll, int LNK)
{
	Vertex *q = NULL;
	int Q = n / 2;
	int P = n - Q;
	if ( P >= 2 )
	{
		q = sort(p, P, dll, LNK);
		if ( Q >= 2 ) sort(q, Q, dll, LNK);
	}
	else
	{
		q = p->links[LNK][FWD];
	}
	q = merge(p, P, q, Q, dll, LNK);
	dll->up2date[LNK] = 1;
	return q;
}
