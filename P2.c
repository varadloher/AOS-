/* write a c program which receives file names as command line arguments and display those filenames in ascending order according to their sizes*/

#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>


struct FileInfo{
	char *name;
	long size;
};

int main(int argc,char *argv[]){
	int i,j;
	if(argc<2){
		printf("Usage : %s \n",argv[0]);
		return 1;
	}

struct FileInfo fileInfos[argc - 1];

for(i=1;i<argc;i++){
	fileInfos[i-1].name = argv[i];
	struct stat fileStat;

	if(stat(argv[i],&fileStat) == 0 && S_ISREG(fileStat.st_mode)){
		fileInfos[i-1].size = fileStat.st_size;
	}
	else{
		printf("Skip non-regular file : %s\n",argv[i]);
		fileInfos[i-1].size = -1;
	}
}

for(i=0;i<argc - 1;i++){
	for(j=0;j<argc-1-i;j++){
		if(fileInfos[j].size > fileInfos[j+1].size){
		struct FileInfo temp = fileInfos[j];
		fileInfos[j] =fileInfos[j+1];
		fileInfos[j+1] = temp;
		}
	}
}

for(i=0;i<argc-1;i++){
	if(fileInfos[i].size>=0){
		printf("%s - %Id bytes \n",fileInfos[i].name,fileInfos[i].size);
	}
}
return 0;
}

