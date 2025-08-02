#include <ncurses.h>
#include <stdlib.h>

#define MARGIN 3

typedef struct {
	char* content;
	size_t size;
} Wikitext;

Wikitext read_file();
void write_from_line(int line, Wikitext* wikitext, int breadth, int length);
void newline(char** p, int breadth);

int main() {
	int breadth, length;
	char ch;

	initscr();
	noecho();
	//keypad(stdscr, TRUE);
	cbreak();

	getmaxyx(stdscr, length, breadth);

	//mvprintw(length/2+1,breadth/2,"Hello, world!");	

	Wikitext test_file = read_file();

	if (test_file.content != NULL) {
		write_from_line(0, &test_file, breadth, length);
	}

	char* p = test_file.content;
	int y = 0;
	int not_exiting = 1;
	int current_start = 0;
	move(0,0);
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
				if (y > length - 1 - MARGIN) {
					write_from_line(current_start++, &test_file, breadth, length);
					y = length - 1;
				}
				//mvprintw(0,0,"%d",y);
				break;
			case 'r':
				write_from_line(14, &test_file, breadth, length);
				break;
			default:
		}
		move(y,0);

	}

	endwin();
	free(test_file.content);
	return 0;
}

Wikitext read_file() {
	FILE* file = fopen("reading.txt", "r");
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

void write_from_line(int line, Wikitext* wikitext, int breadth, int length) {
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
			mvprintw(y, x, "\n");
			//p++;
			y++;
			x = -1;
		} else {
			mvprintw(y, x, "%c", *p);
		}
		if (*p == '\0')
			break;
		if (y >= length)
			break;
		p++;
		x++;
	}
	//mvprintw(0,0,"%d",line);
	//mvprintw(1,0,"%d",y);
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
