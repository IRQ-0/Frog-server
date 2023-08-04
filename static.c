#include "static.h"

#define BUFFER_SIZE 10000

char* getOut(int* err, char* command) {
	FILE *f;
	int lines = 0;
	char buffer[BUFFER_SIZE];
	char* out;

	memset(buffer, 0, sizeof(buffer));

	f = popen(command, "r");
	if (!f) {
		//return POPEN_ERROR;
		*err = POPEN_ERROR;
	}

	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		lines++;
	}

	pclose(f);
	
	size_t size = (sizeof(char) * lines) * MAX_LINE_LENGTH;

	out = (char*) malloc(size);
	if (!out) {
		//return MALLOC_ERROR;
		*err = MALLOC_ERROR;
	}

	memset(out, 0, size);

	f = popen(command, "r");
	if (!f) {
		//return POPEN_ERROR;
		*err = POPEN_ERROR;
	}
	
	long long i = 0;
	memset(buffer, 0, sizeof(buffer));

	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		memcpy(out + i, buffer, strlen(buffer));
		i += strlen(buffer);
	}

	pclose(f);

	return out;

}

char* getTop(int* err) {
	char* out = getOut(err, TOP_COMMAND);

	return out;
}

char* getDf(int* err) {
	char* out = getOut(err, DF_COMMAND);

	return out;
}

char* getBlk(int* err) {
	char* out = getOut(err, BLK_COMMAND);

	return out;
}

char* getIf(int* err) {
	char* out = getOut(err, IF_COMMAND);

	return out;
}

char* getService(char* service, int* err) {
	char buffer[1000];
	strcpy(buffer, SERVICE_COMMAND);
	strcat(buffer, service);

	char* out = getOut(err, buffer);

	return out;
}
