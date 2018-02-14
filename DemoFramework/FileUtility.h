#pragma once

#include <stdio.h>

namespace Crawfis
{
	namespace IO
	{
		class FileUtility
		{
		public:
			static char* File2CharArray(const char *path)
			{
				FILE *fd;
				long len,
					 r;
				char *str;
			 
				if (!(fd = fopen(path, "r")))
				{
					fprintf(stderr, "Can't open file '%s' for reading\n", path);
					return NULL;
				}
			 
				fseek(fd, 0, SEEK_END);
				len = ftell(fd);
			 
				fseek(fd, 0, SEEK_SET);
			 
				if (!(str = (char*)malloc(len * sizeof(char))))
				{
					fprintf(stderr, "Can't malloc space for '%s'\n", path);
					return NULL;
				}
			 
				r = fread(str, sizeof(char), len, fd);
			 
				str[r - 1] = '\0'; /* Shader sources have to term with null */
			 
				fclose(fd);
			 
				return str;
			}
		};
	}
}