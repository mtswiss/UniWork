#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

// Global variables
struct list *base;
struct list *ptr_list;
struct room *start_room;
struct room *goal_room;
struct room *ptr_room;

int player_doughnuts;
int player_milkshakes;

// Function declaration
struct room *create_room(const char *room_name, const int doughnuts, const int milkshakes);
struct list * newList(struct room *room_name);
int command(const char move);
void delete_rooms(struct list *myList);

struct room *create_room(const char *room_name, const int doughnuts, const int milkshakes){
	struct room *n = (struct room*)malloc(sizeof(struct room));
	strcpy(n->name, room_name);
	n->num_doughnuts = doughnuts;
	n->num_milkshakes = milkshakes;
	for(int i =0; i<4;i++){
		n->doors[i]=NULL;
	}
	return n;
}

struct list * newList(struct room * room_name){
	struct list *ptr = (struct list *)malloc(sizeof(struct list));
	ptr->room = room_name;
	ptr->next = NULL;
	return ptr;
}

void delete_rooms(struct list *myList){
	if(myList->next!=NULL){
		delete_rooms(myList->next);
	}
	free(myList->room);
	free(myList);
}

int
main(void){

	int rooms;
	int doors;
	
	char start[21];
	char goal[21];
	char action;
	
	scanf("\n%d", &rooms);
	if(rooms<=0){
		printf("error\n");
		delete_rooms(base);
		return -1;
	}
	for(int i=1;i<=rooms;i++){
		char name[21];
		int doughnuts;
		int milkshakes;
		scanf("\n%s %d %d", name, &doughnuts, &milkshakes);
		if(doughnuts <0 || milkshakes <0){
			printf("error\n");
			delete_rooms(base);
			return -1;
		}
		
		struct room * room_created = create_room(name, doughnuts, milkshakes);
		
		for(struct list *check_name = base; check_name !=NULL;check_name = check_name->next){
			if(strcmp(name, check_name->room->name)==0){
				printf("error\n");
				delete_rooms(base);
				free(room_created);
				return -1;
			}
		}
		
		if(i==1){
			base = newList(room_created);
			ptr_list = base;
		}
		else{
			ptr_list->next = newList(room_created);
			ptr_list = ptr_list->next;
		}
			
	}
	scanf("\n%d", &doors);
	if(doors<=0){
		printf("error\n");
		delete_rooms(base);
		return -1;
	}
	
	for(int i=1;i<=doors;i++){
		char name_1[21];
		char name_2[21];
		char direction;
		scanf("\n%s %c %s", name_1, &direction, name_2);
		
		if(strcmp(name_1, name_2)==0){
			printf("error\n");
			delete_rooms(base);
			return -1;
		}
		struct room *room_1;
		struct room *room_2;
		for(struct list *current = base; current!=NULL; current = current->next){
			if(strcmp(name_1, current->room->name)==0){
				room_1 = current->room;
			}
			else if(strcmp(name_2, current->room->name)==0){
				room_2 = current->room;
			}
		}
		if(room_1 == NULL || room_2 == NULL){
			printf("error\n");
			delete_rooms(base);
			return -1;
		}
		if(direction == 'L'){
			if(room_1->doors[LEFT]!=NULL || room_2->doors[RIGHT]!=NULL){
				printf("error\n");
				delete_rooms(base);
				return -1;
			}
			else{
				room_1->doors[LEFT]		= room_2;
				room_2->doors[RIGHT]	= room_1;
			}
		}
		else if(direction == 'R'){
				if(room_1->doors[RIGHT]!=NULL || room_2->doors[LEFT]!=NULL){
					printf("error\n");
					delete_rooms(base);
					return -1;
				}
				else{
					room_1->doors[RIGHT]	= room_2;
					room_2->doors[LEFT]		= room_1;
				}
			}
		else if(direction == 'U'){
				if(room_1->doors[UP]!=NULL || room_2->doors[DOWN]!=NULL){
					printf("error\n");
					delete_rooms(base);
					return -1;
				}
				else{
					room_1->doors[UP]		= room_2;
					room_2->doors[DOWN]		= room_1;
				}
			}
		else if(direction == 'D'){
				if(room_1->doors[DOWN]!=NULL || room_2->doors[UP]!=NULL){
					printf("error\n");
					delete_rooms(base);
					return -1;
				}
				else{
					room_1->doors[DOWN]		= room_2;
					room_2->doors[UP]		= room_1;
				}
			}
		else{
				printf("error\n");
				delete_rooms(base);
				return -1;
			}
	}
	scanf("\n%s %s", start, goal);
	for(struct list *current = base; current!=NULL; current = current->next){
			if(strcmp(start, current->room->name)==0){
				start_room = current->room;
			}
			else if(strcmp(goal, current->room->name)==0){
				goal_room = current->room;
			}
	}	
	//printf("\n%s %s", start_room->name, goal_room->name);
	ptr_room = start_room;
	while(scanf("\n%s",&action)!=EOF){
		printf("%s %d %d %d %d\n",ptr_room->name, ptr_room->num_doughnuts, ptr_room->num_milkshakes, player_doughnuts, player_milkshakes); 
		if(action!='G'&& action!='M'&& action!='L'&& action!='R'&& action!='U'&& action!='D'){
			printf("error\n");
			delete_rooms(base);
			return -1;
		}
		command(action);
		if(ptr_room==goal_room){
			printf("%s %d %d %d %d\n",ptr_room->name, ptr_room->num_doughnuts, ptr_room->num_milkshakes, player_doughnuts, player_milkshakes);
			printf("won\n");
			delete_rooms(base);
			return 0;
		}
		else if(ptr_room == NULL){
			printf("lost\n");
			delete_rooms(base);
			return -1;
		}	
	}
	if(ptr_room!=goal_room){
		printf("lost\n");
		delete_rooms(base);
		return -1;
	}	
	delete_rooms(base);
}

int command(char move){
	if(move=='G'){
		if(player_doughnuts==3 || ptr_room->num_doughnuts==0){
			ptr_room = NULL;
			return 0;
		}
		else{
			player_doughnuts++;
			ptr_room->num_doughnuts--;
			return 0;
		}
	}	
	else if(move=='M'){
		if(player_milkshakes==2|| ptr_room->num_milkshakes==0){
			ptr_room = NULL;
			return 0;
		}
		else{
			player_milkshakes++;
			ptr_room->num_milkshakes--;
			return 0;
		}
	}
	
	else if(player_doughnuts <1 || player_milkshakes < 1){
		ptr_room = NULL;
		return 0;
	}
	else if(move=='L'){
		player_doughnuts--;
		player_milkshakes--;
		if(ptr_room->doors[LEFT]!=NULL)
			ptr_room = ptr_room->doors[LEFT];
		return 0;
	}
	else if(move=='R'){
		player_doughnuts--;
		player_milkshakes--;
		if(ptr_room->doors[RIGHT]!=NULL)
			ptr_room = ptr_room->doors[RIGHT];
		return 0;
	}
	else if(move=='U'){
		player_doughnuts--;
		player_milkshakes--;
		if(ptr_room->doors[UP]!=NULL)
			ptr_room = ptr_room->doors[UP];
		return 0;
	}
	else if(move=='D'){
		player_doughnuts--;
		player_milkshakes--;
		if(ptr_room->doors[DOWN]!=NULL)
			ptr_room = ptr_room->doors[DOWN];
		return 0;
	}

	return 0;
}
