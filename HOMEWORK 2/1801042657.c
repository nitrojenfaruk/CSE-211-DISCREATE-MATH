#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 1000
#define INPUT "input.txt"
#define OUTPUT "output.txt"

FILE *fp;
FILE *op;

int reflexive(char arr[ROWS], char str[ROWS], long int length, long int length_2);
void symmetric(char arr[ROWS], long int length_2);
void asymmetric(char arr[ROWS], long int length_2);
void transitive(char arr[ROWS], long int length_2);

void main()
{
	int i, j, num, flag, count;
	long int length, length_2;
	char chr, relation[ROWS], arr[ROWS], str[ROWS];

	fp = fopen(INPUT,"r+");
	op = fopen(OUTPUT,"w+");

	while(fscanf(fp, "%s", relation)!=EOF){

		num = atoi(relation);	// num is equal to number of relations.
		fprintf(op,"n\n");

		fscanf(fp, "%s", relation);
		strcpy(str,relation);	// str has the elements of the set.
		length = strlen(str);   // the length of set.

		/* Transferring all relations to arr. */
		for(i=0; i<num; i++){
			fscanf(fp, "%s", relation);
			strcat(arr,relation);
			fprintf(op,"(%s)",relation);
		}

		// Every row has 3 value -> a,b -> arr[0]=a  arr[1]=,  arr[2]=b

		length_2 = strlen(arr);   // the length of relations

		flag=0;
		count=1;

		/*   ERROR HANDLING PART
		Comparison between str(the elements of set) and arr(all relations) */
		for(i=0; i<length_2; i+=2){
			count++;

			for(j=0; j<length; j+=2){
				if(arr[i]==str[j]){   // Relation is found in arr.
					flag=1;
					break;
				}
				else{   // Relation is not found in arr.
					flag=0;
					chr = arr[i];
				}
			}
			if((count%2)==1){   // for line break.
				i--;
			}
			if(flag==0){
				fprintf(op,"\nERROR!!! (%c) is not found in the set.\n",chr);
				break;
			}
		}

		if(flag != 0){  // If there is not an error..
			if(reflexive(arr, str, length, length_2)!=1){
				symmetric(arr, length_2);
				asymmetric(arr, length_2);
				transitive(arr, length_2);
			}
		}

		/* Reset everything for the next set */
		length=0;
		length_2=0;
		memset(arr, '\0', sizeof(arr));
		memset(str, '\0', sizeof(str));
		memset(relation, '\0', sizeof(relation));

	}

	fclose(fp);
	fclose(op);
}


int reflexive(char arr[ROWS], char str[ROWS], long int length, long int length_2){

	char chr;
	int i, j, k, flag, count, check=0;

	fprintf(op,"\nReflexive: ");

	count=0;

	for(j=0; j<length; j+=2){

		flag=0;

		for(k=0; k<length_2; k+=3){

			chr = str[j];  // If the relation will not be found, we'll use that for explanation that's why we stored the relation.

			/* --Reflexive part --
			Comparison between str(the elements of set) and arr(all relations) */
			if(str[j]==arr[k] && str[j]==arr[k+2]){
				flag=1;
				count++;
			}

		}

		/* At least 1 element is not found */
		if(flag==0){
				fprintf(op,"No, (%c,%c) is not found.\n",chr,chr);
				break;
		}

	}

	/* If all values are reflexive, count must be equal to the number of rows(number of relations / 3(every row has 3 value)) */
	if(count == length_2 / 3 && flag==1){
		fprintf(op,"Yes, all elements are present.\n");
		fprintf(op,"Symmetric: Yes, because all values are reflexive.\n");
		fprintf(op,"Asymmetric: Yes, because all values are reflexive.\n");
		fprintf(op,"Transitive: Yes, because all values are reflexive.\n");
		check=1;  /*!!! After this assignment, 'the following if condition' will not occur.*/
	}

	if(flag==1 && check != 1){
		fprintf(op,"Yes, all elements are present.\n");
	}

	return check;
}


void symmetric(char arr[ROWS], long int length_2){

	char chr, chr_1, chr_2, chr_3, chr_4, chr_5, temp[ROWS];
	int i, j, flag;

	fprintf(op,"Symmetric: ");

    flag=1;

	for(i=0; i<length_2; i+=3){

		/* When 2 elements of the relation are not same and next relation was not found, we enter this condition. */
		if(arr[i] != arr[i+2] && arr[i] != chr_2 && arr[i+2] != chr_3){

			// If the relation will not be found, we'll use that for explanation that's why we stored the relation.
			chr_4 = arr[i];
			chr_5 = arr[i+2];

			flag=0;

			for(j=i+3; j<length_2; j+=3){

				/* Symmetric Case */
				if(arr[j]==arr[i+2] && arr[j+2]==arr[i]){  // (a,b)-(b,a)
					flag = 1;
					/* Storing the symmetric relation */
					chr = arr[i];
					chr_1 = arr[i+2];
					chr_2 = arr[j];
					chr_3 = arr[j+2];
				    break;
				}

			}

		}
		if(flag==0){
			fprintf(op,"No, (%c,%c) is not found where (%c,%c) is found.\n",chr_5,chr_4,chr_4,chr_5);
			break;
		}

	}

	if(flag==1){
		fprintf(op,"Yes, (%c,%c) is found where (%c,%c) is found and all other values adapt this rule.\n",chr_1,chr,chr,chr_1);
	}

}


void asymmetric(char arr[ROWS], long int length_2){

	char chr, chr_1, chr_2, chr_3, temp[ROWS];
	int i, j, flag, count;

	fprintf(op,"Antisymmetric: ");

	count=0;

	for(i=0; i<length_2; i+=3){

		/* When 2 elements of the relation are not same and next relation was not found, we enter this condition. */
		if(arr[i] != arr[i+2] && arr[i] != chr_3 && arr[i+2] != chr_2){

			flag=0;

			for(j=i+3; j<length_2; j+=3){

				/* Symmetric relation search */
				if(arr[j]==arr[i+2] && arr[j+2]==arr[i]){  // (a,b)-(b,a)
					flag=1;
					count++;  // If there is a couple which are symmetric, count increase.
					/* Storing symmetric relation for explanation */
					chr_2 = arr[j];
					chr_3 = arr[j+2];
				}

			}

			/* Asymmetric Case */
			if(flag==0){
				chr = arr[i];
				chr_1 = arr[i+2];
			}

		}

	}

	if(count>0){
		fprintf(op,"No, (%c,%c) is found where (%c,%c) is found.\n",chr_2,chr_3,chr_3,chr_2);
	}

	else if(flag==0){
		fprintf(op,"Yes, (%c,%c) is not found where (%c,%c) is found and all other values adapt this rule.\n",chr_1,chr,chr,chr_1);
	}

}


void transitive(char arr[ROWS], long int length_2){

	char chr, chr_1, chr_2, chr_3, chr_4, chr_5, chr_6, chr_7;
	int i, j, k, flag;

	fprintf(op,"Transitive: ");

	flag=0;

	for(i=0; i<length_2; i+=3){

		/* When 2 elements of the relation are not same, we enter this condition. */
		if(arr[i] != arr[i+2]){ // a,b

			for(j=0; j<length_2; j+=3){

				/* The situation where the second element of our relation is found.*/
				if(arr[j] == arr[i+2]){  // b is found.

					for(k=0; k<length_2; k+=3){

						/* Transitive Case
						(a,b) ∧ (b,c) -> (a,c) ---- The situation where (a,c) is found */
						if(arr[k] == arr[i] && arr[k+2] == arr[j+2]){
							flag=0;
							/*Storing transitive relation for (yes) explanation*/
							chr = arr[i];
							chr_1 = arr[j+2];
							chr_6 = arr[i+2];
							chr_7 = arr[j];
							break;
						}

						else{
							flag=1;
						}

					}
					/* The situation where (a,c) is not found */
					if(flag==1){
						/* Storing relations for (no) explanation */
						chr_2 = arr[i];
						chr_3 = arr[j+2];
						chr_4 = arr[i+2];
						chr_5 = arr[j];
						break;
					}

				}

			}
			if(flag==1)
				break;
		}
	}

	if(flag==1){
		fprintf(op,"No, (%c,%c) is not found where (%c,%c) and (%c,%c) are found.\n",chr_2,chr_3,chr_2,chr_4,chr_5,chr_3);
	}

	else{
		fprintf(op,"Yes, (%c,%c) is found where (%c,%c) and (%c,%c) are found.\n",chr,chr_1,chr,chr_6,chr_7,chr_1);
	}

}
