#include <ncurses.h>

int main() {
	initscr();
	cbreak();
	noecho();
	refresh();
	WINDOW *file_win;
	file_win = newwin(3, 10, 14, 8);
	box(file_win, 0, 0);
	mvwprintw(file_win, 0,0,"hi");
	wrefresh(file_win);
	getch();
	delwin(file_win);
	endwin();
	return 0;
}


//#include <ncurses.h>
//
//int main(int argc, char *argv[])
//{	WINDOW *my_win;
//
//	initscr();			/* Start curses mode 		*/
//	cbreak();			/* Line buffering disabled, Pass on
//					 * everty thing to me 		*/
//
//	refresh();
//	my_win = newwin(3, 10, 14, 8);
//	box(my_win, 0, 0);
//	mvwprintw(my_win, 0, 0, "hi");
//	wrefresh(my_win);
//	getch();
//
//		
//	endwin();			/* End curses mode		  */
//	return 0;
//}
