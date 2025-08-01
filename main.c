#include <ncurses.h>
#include <stdlib.h>

typedef struct {
	char* content;
	size_t size;
} Wikitext;

Wikitext read_file();
void write_from_line(int line);

int main() {
	int row, col;
	char ch;

	initscr();
	noecho();
	//keypad(stdscr, TRUE);
	cbreak();

	getmaxyx(stdscr, row, col);

	mvprintw(row/2+1,col/2,"Hello, world!");	

	Wikitext test_file = read_file();

	if (test_file.content != NULL) {
		mvprintw(0, 0, "%s", test_file.content);
	}

	char* p = test_file.content;
	int y = 0;
	int not_exiting = 1;
	while (not_exiting) {
		ch = getch();
		switch(ch) {
			case 'f':
				not_exiting = 0;
				break;
			case 'n':
				while (*p != '\n')
					p++;
				p++;
				y++;
				break;
			case 'e':
				p--;
				while (*p != '\n')
					p--;
				y--;
				break;
			default:
		}

		/*
		if (ch == 'f') break;
		if (ch == 'n') p += col;
		if (ch == 'e') p -= col;
		if (ch == 'i') p++;
		if (ch == 'm') p--;
		*/
		mvprintw(row/2-1,0, "%p",p);
		mvprintw(row/2,0, "%c",*p);
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
