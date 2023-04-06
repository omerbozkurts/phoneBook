#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char name[30];
	char surname[30];
	unsigned int number;
	char department[100];
	
}Person;

int menu();
int searchMenu();
int updateMenu();
int personCheck(FILE *,Person,int);
void addPerson(FILE *);
void searchPerson(FILE *,int);
void update(FILE *);
void deletePerson(FILE *);
void listPerson(FILE *);
void callSwitch(FILE *);

int main(){
	
	FILE *file;
	callSwitch(file);
	
	return 0;
}

int menu(){
	int option;
    printf("\n1. Add a number\n2. Search by\n3. Update\n4. Delete\n5. List\n6. Exit\n");
    printf("enter your choice:");
    scanf("%d", &option);
    printf("\n");
    return option;
}

int searchMenu(){
	int option;
    printf("\n1. Name\n2. Last Name\n3. Phone\n4. Department\n");
    printf("enter your choice:");
    scanf("%d", &option);
    printf("\n");
    return option;
}

int updateMenu(){
	int option;
    printf("\n1. Yes\n2. No\n");
    printf("enter your choice:");
    scanf("%d", &option);
    printf("\n");
    return option;
}

void callSwitch(FILE *file){
	switch(menu()){
		case 1:
			addPerson(file);
			break;
		case 2:
			printf("Choose a search criteria:");
			switch(searchMenu()){
				case 1:
					searchPerson(file,1);
					break;
				case 2:
					searchPerson(file,2);
					break;
				case 3:
					searchPerson(file,3);
					break;
				case 4:
					searchPerson(file,4);
					break;
				default:
					printf("\n invalid option");
					callSwitch(file);
					break;
			}
				
			break;
		case 3:
			update(file);
			break;
		case 4:
			deletePerson(file);
			break;
		case 5:
			listPerson(file);
			break;
		case 6:
			break;
		default:
			printf("\n invalid option");
			callSwitch(file);
			break;
	}	
}

void addPerson(FILE *file){
	
	file=fopen("person.txt","a+");
	Person person;
	int flag=0;
	if(file==NULL){
		printf("cannot open the file");
		return EXIT_FAILURE;		
	}
	printf("First Name:");
	scanf("%s",&person.name);
	printf("Last Name:");
	scanf("%s",&person.surname);
	printf("Phone Number:");
	scanf("%d",&person.number);
	printf("Department:");
	scanf("%s",&person.department);
	personCheck(file,person,flag);
	if(!flag){
		fseek(file,0,SEEK_END);
		fprintf(file,"%s %s %d %s\n",person.name,person.surname,person.number,person.department);
		printf("Added");
	}
	fclose(file);
	callSwitch(file);
}
int personCheck(FILE *file,Person person,int flag){
	if(person.number>9999){
		printf("number is bigger than 4-digit");
		callSwitch(file);
		return NULL;
	}
	
	fseek(file,0,SEEK_SET);
	int number;
	char name[30],surname[30],department[100];
	while(!feof(file)){			
		fscanf(file,"%s%s%d%s",&name,&surname,&number,&department);
		if(number==person.number){
			printf("number %d already exist",person.number);
			callSwitch(file);
			flag=1;
			return flag;
		}
	}
}

void searchPerson(FILE *file,int flag){
	file=fopen("person.txt","r+");
	fseek(file,0,SEEK_SET);
	Person person;
	int number,noResult=1;
	if(flag==1){ 
		char search[30];
		printf("Enter the name you want to search for:");
		scanf("%s",search);
		int sizeSearch=strlen(search);
		printf("\nSearch results:\n");
		int lineNum=0;
		while(!feof(file)){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			lineNum++;
		}
		fseek(file,0,SEEK_SET);
		while(lineNum-1){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			int sizePerson=strlen(person.name);
			int i,counter=0;
			for(i=0;i<sizeSearch;i++){
				if(search[i]==person.name[i])
					counter++;
			}
			if(sizePerson==sizeSearch&&counter==sizeSearch){
				printf("%s %s %d %s\n",person.name,person.surname,person.number,person.department);
				noResult=0;
			}
			lineNum--;
		}
		if(noResult)
			printf("\nNo Result\n");
		
	}
	else if(flag==2){
		char search[30];
		printf("Enter the surname you want to search for:");
		scanf("%s",&search);
		int sizeSearch=strlen(search);
		printf("\nSearch results:\n");
		int lineNum=0;
		while(!feof(file)){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			lineNum++;
		}
		fseek(file,0,SEEK_SET);
		while(lineNum-1){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			int sizePerson=strlen(person.surname);
			int i,counter=0;
			for(i=0;i<sizeSearch;i++){
				if(search[i]==person.surname[i])
					counter++;
			}
			if(sizeSearch==sizePerson&&counter==sizeSearch){
				printf("%s %s %d %s\n",person.name,person.surname,person.number,person.department);
				noResult=0;
			}
			lineNum--;
		}
		if(noResult)
			printf("\nNo Result\n");
	}
	else if(flag==3){
		int search;
		printf("Enter the number you want to search for:");
		scanf("%d",&search);
		int lineNum=0;
		while(!feof(file)){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			lineNum++;
				
		}
		fseek(file,0,SEEK_SET);
		while(lineNum-1){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			if(search==person.number){
				printf("%s %s %d %s\n",person.name,person.surname,person.number,person.department);
				noResult=0;
			}			
			lineNum--;
		}
		if(noResult)
			printf("\nNo Result\n");
	}
	else if(flag==4){
		char search[100];
		printf("Enter the depertmant you want to search for:");
		scanf("%s",&search);
		int sizeSearch=strlen(search);
		printf("\nSearch results:\n");
		int lineNum=0;
		while(!feof(file)){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			lineNum++;			
		}
		fseek(file,0,SEEK_SET);
		while(lineNum-1){
			fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
			int sizePerson=strlen(person.department);
			int i,counter=0;
			for(i=0;i<sizeSearch;i++){
				if(search[i]==person.department[i])
					counter++;
			}
			if(sizeSearch==sizePerson&&counter==sizeSearch){
				printf("%s %s %d %s\n",person.name,person.surname,person.number,person.department);
				noResult=0;
			}
			lineNum--;
		}
		if(noResult)
			printf("\nNo Result\n");
	}
	fclose(file);
	callSwitch(file);
}

void update(FILE *file){
	file=fopen("person.txt","r+");
	Person person,newPerson;
	printf("enter the phone number of the person they want to update:");
	int number,counter=0,flag=0,numLine,allLine=0;
	scanf("%d",&number);
	while(!feof(file)){
		allLine++;
		fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
		if(person.number==number){
			printf("%s %s %d %s",person.name,person.surname,person.number,person.department);
			counter=1;
			numLine=allLine-1;
		}		
	}
	if(counter==1){
		printf("\nDo you want to update ?");
		switch(updateMenu()){
				case 1:
					printf("Enter updated information\n");
					printf("First Name:");
					scanf("%s",&newPerson.name);
					printf("Last Name:");
					scanf("%s",&newPerson.surname);
					printf("Phone Number:");
					scanf("%d",&newPerson.number);
					printf("Department:");
					scanf("%s",&newPerson.department);
					personCheck(file,newPerson,flag);
					fclose(file);
					if(!flag){
						file=fopen("person.txt","r");
						FILE *tempFile;
						tempFile=fopen("temp.txt","w");
						int curLine=0;
						while(allLine-1){
							fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
							if(numLine!=curLine){
								fprintf(tempFile,"%s %s %d %s\n",person.name,person.surname,person.number,person.department);
							}
							else if(numLine==curLine){
								fprintf(tempFile,"%s %s %d %s\n",newPerson.name,newPerson.surname,newPerson.number,newPerson.department);
							}
							curLine++;
							allLine--;
						}
						fclose(file);
						fclose(tempFile);
						remove("person.txt");
						rename("temp.txt","person.txt");
						remove("temp.txt");
						printf("\nupdated\n");		
					}
					break;
				case 2:
					break;
				default:
					printf("\n invalid option");
					break;
			}
	}
	else if(counter==0)
		printf("Number %d not found",number);
	fclose(file);
	callSwitch(file);
}

void deletePerson(FILE *file){
	file=fopen("person.txt","r+");
	Person person;
	printf("enter the phone number of the person they want to delete:");
	int counter=0,number,numLine,allLine=0;
	scanf("%d",&number);
	while(!feof(file)){
		allLine++;
		fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
		if(person.number==number){
			printf("%s %s %d %s",person.name,person.surname,person.number,person.department);
			counter=1;
			numLine=allLine-1;
		}		
	}
	if(counter==1){
		printf("\nDo you want to delete ?");
		switch(updateMenu()){
				case 1:
					fclose(file);
						file=fopen("person.txt","r");
						FILE *tempFile;
						tempFile=fopen("temp.txt","w");
						int curLine=0;
						while(allLine-1){
							fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
							if(numLine!=curLine)
								fprintf(tempFile,"%s %s %d %s\n",person.name,person.surname,person.number,person.department);
							
							curLine++;
							allLine--;
						}
						fclose(file);
						fclose(tempFile);
						remove("person.txt");
						rename("temp.txt","person.txt");
						remove("temp.txt");
						printf("\ndeleted\n");		
					break;
				case 2:
					break;
				default:
					printf("\n invalid option");
					break;
			}
	}
	else if(counter==0)
		printf("Number %d not found",number);
	fclose(file);
	callSwitch(file);
}

void listPerson(FILE *file){
	file=fopen("person.txt","r");
	Person person;
	int lineNum=0;
	while(!feof(file)){
		fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
		lineNum++;	
	}
	fseek(file,0,SEEK_SET);
	while(lineNum-1){
		fscanf(file,"%s%s%d%s",&person.name,&person.surname,&person.number,&person.department);
		printf("%s %s %d %s\n",person.name,person.surname,person.number,person.department);
		lineNum--;
	}
	fclose(file);
	callSwitch(file);
}
