#include<stdio.h>
#include<string.h>
struct team{
	int tid;
	char name[50];
	char pname[11][50];
	int page[11];
}team;
struct schedule{
	long int date;
	int id,id1,id2;
}sch;
int num_teams=0;
void add_team(){
	if(num_teams>8){
		printf("Maximum number of teams reached. Unable to add more.\n");
	}
	else{
		int i;
		FILE *fp;
		fp = fopen("Record", "a");
		printf("Enter Team ID: ");
		scanf("%d",&team.tid);
		fflush(stdin);
		printf("Enter Name: ");
		scanf("%s",&team.name);
		fflush(stdin);
		printf("\nEnter the 11 players: \n");
		for(i=0;i<2;i++){
			scanf("%s",team.pname+i);
			fflush(stdin);
			scanf("%d",&team.page[i]);
		}
		fwrite(&team, sizeof(team), 1, fp);
		num_teams++;
		printf("TEAM ADDED SUCCESSFULLY.");
		fclose(fp);
	}
}
void display_teams(){
	int i;
	FILE *fp;
	fp = fopen("Record", "r");
	if (fp == NULL){
        printf("\n No Teams Found.\n");
    }
	else {
        while(fread(&team,sizeof(team),1,fp)){
        	printf("\nTeam Name: %s\n",team.name);
        	printf("Team ID: %d\n",team.tid);
        	printf("Players: \n");
        	printf("%-15s\t%s\n------------------------------------------------------\n","Name","Age");
        	for(i=0;i<2;i++){
        	printf("%-15s\t%d\n",team.pname+i,team.page[i]);
			}
		}
    }
    fclose(fp);
}
int avlid(id){
	FILE *fp;
	int r=0;
	fp = fopen("Record", "r");
	while(fread(&team,sizeof(team),1,fp)){
		if(team.tid==id)
		r=1;
	}
	fclose(fp);
	return r;
}
void delete_teams()
{
	int avl;
	FILE *fpt;
	FILE *fpo;
	int s, id, ch;
	printf("\nEnter ID to delete:");
	scanf("%d", &id);
	avl = avlid(id);
	if (avl == 0)
	{
		printf("ID : %d is not available in the file\n", id);
	}
	else
	{
		fpo = fopen("Record", "r");
		fpt = fopen("TempFile", "w");
		while (fread(&team, sizeof(team), 1, fpo))
		{
			s = team.tid;
			if (s != id)
			fwrite(&team, sizeof(team), 1, fpt);
		}
		fclose(fpo);
		fclose(fpt);
		fpo = fopen("Record", "w");
		fpt = fopen("TempFile", "r");
		while (fread(&team, sizeof(team), 1, fpt))
		{
			fwrite(&team, sizeof(team), 1, fpo);
		}
		fclose(fpo);
		fclose(fpt);
		printf("\nRECORD DELETED\n");
	}
}
void update_teams()
{
	int i;
	int avl;
	FILE *fpt;
	FILE *fpo;
	int s, id, ch;
	printf("\nEnter ID to update:");
	scanf("%d", &id);
	avl = avlid(id);
	if (avl == 0)
	{
		printf("ID : %d is not available in the file\n", id);
	}
	else
	{
		fpo = fopen("Record", "r");
		fpt = fopen("TempFile", "w");
		while (fread(&team, sizeof(team), 1, fpo))
		{
			s = team.tid;
			if (s != id)
			fwrite(&team, sizeof(team), 1, fpt);
			else
			{
				printf("\n1. Update Name");
				printf("\n2. Update Players");
				printf("\n3. Update Both");
				printf("\n\nEnter your choice:");
				scanf("%d", &ch);
				switch (ch)
				{
					case 1:
					printf("Enter Name:");
					scanf("%s", &team.name);
					break;
					case 2:
					printf("\nEnter the 11 players: \n");
					for(i=0;i<2;i++){
						scanf("%s",team.pname+i);
						fflush(stdin);
						scanf("%d",&team.page[i]);
					}
					break;
					case 3:
						printf("Enter Name:");
						scanf("%s", &team.name);
						fflush(stdin);
						printf("\nEnter the 11 players: \n");
						for(i=0;i<2;i++){
							scanf("%s",team.pname+i);
							fflush(stdin);
							scanf("%d",&team.page[i]);
						}
					break;
					default:printf("Invalid Selection");
					break;
				}
			fwrite(&team, sizeof(team), 1, fpt);
			}
		}
		fclose(fpo);
		fclose(fpt);
		fpo = fopen("Record", "w");
		fpt = fopen("TempFile", "r");
		while (fread(&team, sizeof(team), 1, fpt))
		{
			fwrite(&team, sizeof(team), 1, fpo);
		}
		fclose(fpo);
		fclose(fpt);
		printf("\nRECORD UPDATED\n");
	}
}
void show_schedule(){
	FILE *fp;
	fp = fopen("Record1", "r");
	printf("%s\t%s\t%s\tvs.\t%s\n----------------------------------------------------------------------------\n","Schedule ID","Date","Team ID 1","Team ID 2");
	while (fread(&sch,sizeof(sch),1,fp))
	{
		printf("%d\t\t%ld\t%d\t\tvs.\t%d\n",sch.id,sch.date,sch.id1,sch.id2);
	}
	fclose(fp);
}
void generate_schedule(){
	FILE *fp;
	fp = fopen("Record1", "a");
	printf("Enter Schedule ID:");
	scanf("%d", &sch.id);
	fflush(stdin);
	printf("Enter Team 1:");
	scanf("%d", &sch.id1);
	fflush(stdin);
	printf("Enter Team 2:");
	scanf("%d", &sch.id2);
	fflush(stdin);
	printf("Enter Date of match: ");
	scanf("%ld", &sch.date);
	fflush(stdin);
	fwrite(&sch, sizeof(sch), 1, fp);
	printf("SCHEDULE ADDED SUCCESSFULLY.");
	fclose(fp);
}
int avlid1(id){
	FILE *fp;
	int r=0;
	fp = fopen("Record1", "r");
	while(fread(&sch,sizeof(sch),1,fp)){
		if(sch.id==id)
		r=1;
	}
	fclose(fp);
	return r;
}
void update_schedule(){
	int avl;
	FILE *fpt;
	FILE *fpo;
	int s, id, ch;
	printf("\nEnter ID to update:");
	scanf("%d", &id);
	avl = avlid1(id);
	if (avl == 0)
	{
		printf("ID : %d is not available in the file\n", id);
	}
	else
	{
		fpo = fopen("Record1", "r");
		fpt = fopen("TempFile1", "w");
		while (fread(&sch, sizeof(sch), 1, fpo))
		{
			s = sch.id;
			if (s != id)
			fwrite(&sch, sizeof(sch), 1, fpt);
			else{
				printf("Enter Team 1:");
				scanf("%d", &sch.id1);
				fflush(stdin);
				printf("Enter Team 2:");
				scanf("%d", &sch.id2);
				fflush(stdin);
				printf("Enter Date of match: ");
				scanf("%ld", &sch.date);
				fflush(stdin);
				fwrite(&sch, sizeof(sch), 1, fpt);
			}
		}
		fclose(fpo);
		fclose(fpt);
		fpo = fopen("Record1", "w");
		fpt = fopen("TempFile1", "r");
		while (fread(&sch, sizeof(sch), 1, fpt))
		{
			fwrite(&sch, sizeof(sch), 1, fpo);
		}
		fclose(fpo);
		fclose(fpt);
		printf("\nRECORD UPDATED\n");
	}
}
int main(){
	int ch;
	do{
		printf("\nMENU:\n");
		printf("1. Display Teams\n");
		printf("2. Add team\n");
		printf("3. Delete Team\n");
		printf("4. Update Team\n");
		printf("5. Generate Schedule\n");
		printf("6. Show Schedule\n");
		printf("7. Update Schedule\n");
		printf("8. Exit\n");
		printf("\nEnter Choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				display_teams();
				break;
			case 2:
				add_team();
				break;
			case 3:
				delete_teams();
				break;
			case 4:
				update_teams();
				break;
			case 5:
				generate_schedule();
				break;
			case 6:
				show_schedule();
				break;
			case 7:
				update_schedule();
				break;
			case 8:
				printf("Exiting Program...\n");
				break;
			default:
				printf("Invalid Choice!!!. Try Again...\n");
		}
	}while(ch != 8);
}
