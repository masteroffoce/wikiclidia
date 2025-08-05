#include <ncurses.h>
#include <stdlib.h>
#include "scrape.h"
#include "parse.h"

#define MARGIN 3 //Counter: number of times I've fixed something else instead of this: 4

Wikitext read_file();
Wikitext get_content();
void write_from_line(int line, Wikitext* wikitext, int breadth, int length, WINDOW** file_win);
void newline(char** p, int breadth);

int main() {
	char *x = "<html><div><h1>hi</h1></div></html>";
	html_to_text(x);
	printf("%s",x);

	Wikitext *soup = scrape();
	//printf("%s", soup->content);
	free(soup);

	int breadth, length;
	char ch;

	initscr();
	noecho();
	//keypad(stdscr, TRUE);
	cbreak();

	getmaxyx(stdscr, length, breadth);

	//mvprintw(length/2+1,breadth/2,"Hello, world!");	

	//Wikitext test_file = read_file();
	Wikitext test_file = get_content();
	parse(&test_file);

	refresh();
	WINDOW *file_win = newwin(length - 2, breadth, 1, 0);
	box(file_win, 0, 0);
	wrefresh(file_win);

	if (test_file.content != NULL) {
		write_from_line(0, &test_file, breadth, length, &file_win);
	}
	wrefresh(file_win);

	char* p = test_file.content;
	int y = 1; //Current y coordinate of cursor
	int not_exiting = 1; //Set to 0 when program exits
	int current_start = 1; //Curent first line on screen
	move(1,0);
	while (not_exiting) {
		ch = getch();
		switch(ch) {
			case 'f':
				not_exiting = 0;
				break;
			case 'n':
				newline(&p, breadth);
				y++;
				//write_from_line(current_start++, &test_file, breadth, length);
				if (y > length - 2) {
					write_from_line(current_start++, &test_file, breadth, length, &file_win);
					y = length - 2;
				}
				//mvprintw(0,0,"%d",y);
				break;
			case 'r':
				write_from_line(14, &test_file, breadth, length, &file_win);
				break;
			default:
		}
		mvprintw(0,0,"start:%d;y:%d;*p:%c",current_start,y,*p);
		move(y,0);

	}

	endwin();
	free(test_file.content);
	return 0;
}


Wikitext read_file() {
	FILE* file = fopen("thebestyoucanisgoodenough", "r");
	if (file == NULL) exit(1);

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char* buffer = malloc(file_size + 1);
	if (buffer == NULL) {
		fclose(file);
		exit(1);
	}

	size_t bytes_read = fread(buffer, 1, file_size, file);
	if (bytes_read != file_size) {
		free(buffer);
		fclose(file);
		exit(1);
	}

	buffer[bytes_read] = '\0';

	fclose(file);

	Wikitext file_content = {
		.content = buffer,
		.size = bytes_read
	};

	return file_content;

}

Wikitext get_content() {
	Wikitext *content = scrape();
	return *content;
}

void write_from_line(int line, Wikitext* wikitext, int breadth, int length, WINDOW** file_win) {
	char *p = wikitext->content;
	for (int i = 0; i < line; i++) {
		newline(&p, breadth);
	}

	int x = 0;
	int y = 0;

	while (*p != '\0' && y < length) {
		if (x > breadth) {
			y++;
			x = 0;
			p--; //p shouldn't increment later
		}
		if (*p == '\n') {
			mvwprintw(*file_win, y, x, "\n");
			//p++;
			y++;
			x = -1;
		} else {
			mvwprintw(*file_win, y, x, "%c", *p);
		}
		if (*p == '\0')
			break;
		if (y >= length)
			break;
		p++;
		x++;
	}
	wrefresh(*file_win);
	//mvprintw(0,0,"%d",line);
}

void newline(char** p, int breadth) {
	for (int i = 0; i < breadth; i++) {
		
		if (**p == '\n') {
			(*p)++;
			break;
		}
		(*p)++;
		
	}
	/*
	mvprintw(0,0,"          ");
	if (**p == '\n')
		mvprintw(0,0,"\\n");
	else
		mvprintw(0,0,"//%c//",**p);
	*/
}
