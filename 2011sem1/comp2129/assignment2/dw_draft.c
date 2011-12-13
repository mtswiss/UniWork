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
struct room * create_room(const char *room_name, const int doughnuts, const int milkshakes);
struct list * create_rooms(int rooms);
struct list * newList(struct room *my_room);

int
main(void){
	
	int rooms;
	int doors;
		
	char start[21];
	char goal[21];
	
	scanf("\n%d", &rooms);
	if(rooms<=0){
		printf("\nerror");
		return -1;
	}
	base = (struct list *)malloc(sizeof(struct room));
	//printf("\n%i",rooms);
	for(int i=1;i<=rooms;i++){
		char name[21];
		int doughnuts;
		int milkshakes;
		int value;
		scanf("\n%s %d %d", name, &doughnuts, &milkshakes);
		if(doughnuts <0 || milkshakes <0){
			printf("\nerror");
			return -1;
		}
		
		
		struct room *room_created = create_room(name, doughnuts, milkshakes);
		struct list *check_name;
		printf("%s", check_name->room->name);
		
		for(check_name = base; check_name !=NULL;check_name = check_name->next){
			value = strcmp(name,check_name->room->name);
			printf("%d", value);
			
		
		}
		
		while(check_name->next=NULL){
			value = strcmp(name, check_name->room->name);
			
			printf("%s %d136363", check_name->room->name, value);
			printf("here");
			if(strcmp(name, check_name->room->name)){
				printf("%d",i);
				printf("\nerroasfr");
				return -1;
			}
			check_name = check_name-> next;
		}
		
		if(i==1){
			base = newList(room_created);
			ptr_list = base;
		}
		else{
			
			ptr_list->next = newList(room_created);
			ptr_list = ptr_list-> next;
			printf("\n%d %s", i, ptr_list->room->name);
		}
	}
	
	scanf("\n%d", &doors);
	if(doors<=0){
		printf("\nerror");
		return -1;
	}
	
	for(int i=1;i<=doors;i++){
		char name[21];
		char name2[21];
		char direction;
		scanf("\n%s %c %s", name, &direction, name2);
		
		if(name==name2){
			printf("\nerror");
			return -1;
		}
		struct room *room_1 = (struct room *)malloc(sizeof(struct room));
		struct room *room_2 = (struct room *)malloc(sizeof(struct room));
		
		ptr_list=base;
		//printf("\n1234%s", ptr_list->next->room->name);
		
		printf(strcmp(name, ptr_list->room->name));
		for(int j=1;j<=rooms;j++){
			if(strcmp(name, ptr_list->room->name)){
				printf("here");
				room_1 = ptr_list->room;
			}
			else if(strcmp(name2, ptr_list->room->name)){
				
				room_2 = ptr_list->room;
			}
		}
		
		/*
		while(ptr_list->next!=NULL){
			// strcmp(name, ptr_list->room-name) returns 0 if true
			printf("\n%s66", ptr_list->room->name);
				
			
			ptr_list = ptr_list->next;
			printf("\n%s25", ptr_list->room->name);
			printf("\n%s", ptr_list->next);
		}
		
		printf("\n%s %s", room_1->name, room_2->name);
		//printf("\n%s", room_1->name);
		/*
		if(room_1 == NULL || room_2 ==NULL){
			printf("\nerror");
			return -1;
		}
		
		// diff cases for the diff directions 
		if(direction == 'L'){
				if(room_1->doors[LEFT]!=NULL || room_2->doors[RIGHT]!=NULL){
					printf("\nerror");
					return -1;
				}
				else{
					room_1->doors[LEFT]		= room_2;
					room_2->doors[RIGHT]	= room_1;
				}
			}
		else if(direction == 'R'){
				if(room_1->doors[RIGHT]!=NULL || room_2->doors[LEFT]!=NULL){
					printf("\nerror");
					return -1;
				}
				else{
					room_1->doors[RIGHT]	= room_2;
					room_2->doors[LEFT]		= room_1;
				}
			}
		else if(direction == 'U'){
				if(room_1->doors[UP]!=NULL || room_2->doors[DOWN]!=NULL){
					printf("\nerror");
					return -1;
				}
				else{
					room_1->doors[UP]		= room_2;
					room_2->doors[DOWN]		= room_1;
				}
			}
		else if(direction == 'D'){
				if(room_1->doors[DOWN]!=NULL || room_2->doors[UP]!=NULL){
					printf("\nerror");
					return -1;
				}
				else{
					room_1->doors[DOWN]		= room_2;
					room_2->doors[UP]		= room_1;
				}
			}
		else{
			printf("\nerror");
			return -1;
			}
			*/
	}
}


//function to create single room
struct room * create_room(const char *room_name, const int doughnuts, const int milkshakes){
	struct room *n = (struct room *)malloc(sizeof(struct room));
	strcpy(n->name, room_name);
	n->num_doughnuts = doughnuts;
	n->num_milkshakes = milkshakes;
	for(int i = 0; i<4;i++){
		n->doors[i]=NULL;
	}
	return n;
}

//function to create sigle list element
struct list * newList(struct room *my_room){
	struct list *ptr = (struct list * )malloc(sizeof(struct list));
	ptr->room=my_room;
	ptr->next = NULL;
	return ptr;
}


