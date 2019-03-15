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
#define MEM_TEST_FIRST "if(cur < arr || cur >= arr + "
#define MEM_TEST_LAST "){\nprintf(\"Memory read error!\\n\");\n}"

int main(int argc, char *argv[]){
        int val;
        int bracket_cnt = 0;
        char * fname = "";
        char * ofname = "a.out";
        char * mfname = "bf.bftoc";
        char * mem_size = "30000";

        char rm_mid_file = 1;
        char do_not_build = 0;
        char invalid_syntax = 0;
        char debug_mem = 0;

        while((val = getopt(argc, argv, "o:m:kDd")) != -1){
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
                        case 'D':
                            do_not_build = 1;
                            break;
                        case 'd':
                            debug_mem = 1;
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
        
	FILE *fd = fopen(fname,"r");
	FILE *of = fopen(mfname,"w");
	char c;
	fputs("#include <stdio.h>\nchar arr[", of);
        fputs(mem_size, of);
        fputs("];\nint main(){\nchar *cur = arr;\n", of);
	while((c = fgetc(fd)) != EOF){
		switch(c){
			case '-':
				fputs(SUB,of);
				break;
			case '+':
				fputs(ADD, of);
				break;
			case '[':
				fputs(LBR, of);
                                bracket_cnt++;
				break;
			case ']':
				fputs(RBR, of);
                                bracket_cnt--;
                                if(bracket_cnt < 0){
                                    invalid_syntax = 1;
                                }
				break;
			case '<':
				fputs(LFT, of);
                                if(debug_mem){
                                    fputs(MEM_TEST_FIRST, of);
                                    fputs(mem_size, of);
                                    fputs(MEM_TEST_LAST, of);
                                }
				break;
			case '>':
				fputs(RHT, of);
                                if(debug_mem){
                                    fputs(MEM_TEST_FIRST,of);
                                    fputs(mem_size, of);
                                    fputs(MEM_TEST_LAST, of);
                                }
				break;
			case ',':
				fputs(INP, of);
				break;
			case '.':
				fputs(OUT, of);
				break;
                        case '#':
                                while((c = fgetc(fd)) != EOF && c != '\n');
                                break;
		}
	}
	fputc('}', of);
	fclose(fd);
	fclose(of);
        if(bracket_cnt != 0 || invalid_syntax){
            do_not_build = 1;
            rm_mid_file = 1;
            printf("Invalid Syntax\n");
        }

        if(!do_not_build){
            int len = strlen(mfname) + strlen(ofname) + 9;
            char * comp = malloc(len * sizeof(char));
            strcpy(comp, "gcc ");
            strcat(comp, mfname);
            strcat(comp, " -o ");
            strcat(comp, ofname);

	    system(comp);
            free(comp);
        }
        
        if(rm_mid_file){
            char * torm = malloc((strlen(mfname) + 4) * sizeof(char));
            strcpy(torm, "rm ");
            strcat(torm, mfname);

	    system(torm);
            free(torm);
        }
        free(mfname);

}
