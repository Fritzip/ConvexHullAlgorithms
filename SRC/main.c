#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include <math.h>  
#include <assert.h>
#include <GL/glut.h> 

#include "main.h"

/*----------------------------------------------------------------------------------*/
//                                  Graphic functions
/*----------------------------------------------------------------------------------*/
void affiche(Dllist *dll, int LNK, int GL_DRAW_STYLE, double r, double g, double b)
{
	glBegin(GL_DRAW_STYLE);
	glColor3f(r, g, b);

	Vertex *current = dll->root->links[LNK][FWD];

	for(int i = 0; i < dll->length[LNK]; i++)
	{
		glVertex2f(current->coords[0], current->coords[1]);
		current = current->links[LNK][FWD];
	}

	glEnd();
}

void display (void)
{
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	Dllist *dll_lnk = create_rd_data_struct();

	init_links(dll_lnk, JAR);
	// init_links(dll_lnk, GRA);

	// print_dll(dll_lnk, STD);
	// print_dll(dll_lnk, LEX);
	// print_dll(dll_lnk, POL);
	// print_dll(dll_lnk, GRA);
	// print_dll(dll_lnk, JAR);

	affiche(dll_lnk, POL, GL_LINE_LOOP, 1.0, 0.0, 0.0);
	
	affiche(dll_lnk, JAR, GL_LINE_LOOP, 1.0, 1.0, 1.0);
	// affiche(dll_lnk, GRA, GL_LINE_LOOP, 1.0, 1.0, 1.0);
	
	glFlush();
}


/*----------------------------------------------------------------------------------*/
//                                  Main
/*----------------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
	srand (time(NULL));
	int option;

	opterr = 0; /* set off std error messages in case wrong option is chosen */
	while ((option = getopt(argc, argv, "c:")) != EOF)
	{
		switch (option)
		{
		case 'c': if ((sscanf(optarg, "%d", &displayChoice) == 1) && displayChoice >= 0 && displayChoice <= 4)
				break;
		case '?': /* value returned by getopt if invalid option chosen */
		default : printf("Usage: %s -cX, with X = 1, 2, 3 or 4.\n", argv[0]);
				displayChoice = 0;
				break;
		}
	}

	assert(displayChoice >= 0 && displayChoice <= 4);
	printf("Executing %s with line option %d = %s.\n", argv[0], displayChoice, lineOption[displayChoice]);
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  

	glutInitWindowPosition(5,5);  
	glutInitWindowSize(maxX,maxY);  

	glutCreateWindow("My first OpenGL window...");  
	
	gluOrtho2D(minX, maxX, minY, maxY);

	glutDisplayFunc(display);  

	glutMainLoop();  
		
	return EXIT_SUCCESS; 
}