#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define SUB "(*cur)--;\n"
#define ADD "(*cur)++;\n"
#define LFT "(cur--);\n"
#define RHT "(cur++);\n"
#define LBR "while(*cur){\n"
#define RBR "}\n"
#define OUT "putchar(*cur);\n"
#define INP "*cur = getchar();\n"

int main(int argc, char *argv[]){
        int val;
        char * fname = "";
        char * ofname = "a.out";
        char * mfname = "bf.bftoc";
        char * mem_size = "1000";

        char rm_mid_file = 1;
        while((val = getopt(argc, argv, "o:m:k")) != -1){
                switch(val){
                        case 'o':
                            ofname = optarg; 
                            break;
                        case 'm':
                            mem_size = optarg;
                            break;
                        case 'k':
                            rm_mid_file = 0;
                            break;
                }

        }
        if(optind < argc){
            fname = argv[optind];
        } else {
            _exit(1);
        }

        mfname = malloc((strlen(fname) + 3) * sizeof(char));
        strcpy(mfname, fname);
        strcat(mfname,".c");
        
        printf("%s\n", fname);
	FILE *fd = fopen(fname,"r");
	FILE *of = fopen(mfname,"w");
	char c;
	fputs("#include <stdio.h>\nchar arr[", of);
        fputs(mem_size, of);
        fputs("];\nint main(){\nchar *cur = arr;\n", of);
	while((c = fgetc(fd)) != EOF){
		putchar(c);
		switch(c){
			case '-':
				fputs(SUB,of);
				break;
			case '+':
				fputs(ADD, of);
				break;
			case '[':
				fputs(LBR, of);
				break;
			case ']':
				fputs(RBR, of);
				break;
			case '<':
				fputs(LFT, of);
				break;
			case '>':
				fputs(RHT, of);
				break;
			case ',':
				fputs(INP, of);
				break;
			case '.':
				fputs(OUT, of);
				break;
		}
	}
	fputc('}', of);
	fclose(fd);
	fclose(of);
        int len = strlen(mfname) + strlen(ofname) + 9;
        char * comp = malloc(len * sizeof(char));
        strcpy(comp, "gcc ");
        strcat(comp, mfname);
        strcat(comp, " -o ");
        strcat(comp, ofname);

	system(comp);
        free(comp);
        
        if(rm_mid_file){
            char * torm = malloc((strlen(mfname) + 4) * sizeof(char));
            strcpy(torm, "rm ");
            strcat(torm, mfname);

	    system(torm);
            free(torm);
        }
        free(mfname);

}
