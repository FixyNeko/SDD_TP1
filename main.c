#include "main.h"

list * messages;

int main(int argc, char** argv) {
	int error = 0;
	if(argc == 2) {
		FILE * readFile;
		readFile = fopen(argv[1], "r");
		if(readFile == NULL) {
			error = 2;
		}
		else {
			initList(messages);
			while(feof(readFile) == 0) {
				message * msg = (message *) malloc(sizeof(message));
				fgets(msg->beginTime, 8, readFile);
				fgetc(readFile); // skip space delimiter
				fgets(msg->endTime, 8, readFile);
				fgetc(readFile); // skip space delimiter;
				int i = 0;
				char c;
				while((c = fgetc(readFile)) != '\r' && i < TEXT_SIZE) {
					msg->text[i] = c;
				}
				msg->text[i] = '\0'; // mark end of text
				while(fgetc(readFile) != '\n'); // finish reading the file line

				addListElement(messages, msg);
			}

		}
	}
	else {
		error = 1;
	}
	return error;
}
