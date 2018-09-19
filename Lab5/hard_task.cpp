#include <unordered_map>
#include "Task.h"
#include <cstdio>

std::unordered_map<std::string, int> bigramm_hard_task(const char* path) {
	std::unordered_map<std::string, int> bigramm_map;
	FILE* file = std::fopen(path, "r");
	if (file) {
		char first;
		char second;
		first = getc(file);
		while ((second = getc(file)) != EOF) {
			if (first == '0' && second == '0')
				bigramm_map["00"]++;
			else if (first == '1' && second == '0')
				bigramm_map["10"]++;
			else if (first == '0' && second == '1')
				bigramm_map["01"]++;
			else if (first == '1' && second == '1')
				bigramm_map["11"]++;
			first = second;
		}
	}
	fclose(file);
	return bigramm_map;
}