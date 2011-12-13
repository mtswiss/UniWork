#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

struct list *base;
struct room *pointer;
int player_doughnuts;
int player_milkshakes;
char move;

/* Function declaration */
int createRooms(int rooms);
int createDoors(int doors);
void delete_rooms(struct list *myList);

int
main(void) {

	struct room *start_room;	/* store start room */
	struct room *goal_room;		/* store goal room */

	int numRooms;
	int numDoors;
	char input_name[21];
	int input_doughnuts;
	int intput_milkshakes;
	char start[21];
	char goal[21];
	

	/*scan number of rooms from input and check if valid */
	scanf("\n%d", &numRooms);
	if(numRooms<=0){
		printf("\nerror");
		return -1;
	}

	base = (struct list *)malloc(sizeof(struct list));
	createRooms(numRooms);
	/*
	//loop that creates new room 
	for(int i=1; i<= numRooms;i++){
		scanf("\n%20s %d %d, &input_name, &input_doughnuts);
	}
	*/
	
	/*scan number of doors from input and check if valid */
	scanf("\n%d", &numDoors);
	if(numDoors<=0){
		printf("\nerror");
		return -1;
	}
	createDoors(numDoors);

	/* scan START and GOAL rooms */
	scanf("\n%s %s",&start, &goal);
	start_room = find_room(start, base);
	goal_room = find_room(goal, base);
	if(start_room == NULL || goal_room == NULL){
		printf("\nerror");
		return -1;
	}

	pointer = start_room;

	while(scanf("\n%c", &move)!=EOF){
			command();
			if(pointer == NULL){
				return -1;
			}
			else if(pointer == goal_room){
				printf("\nwon");
				return 0;
			}
			else{
				printf("\n %s %d %d %d %d", pointer->name, pointer->num_doughnuts, pointer->num_milkshakes, player_doughnuts, player_milkshakes);
			}
	}

	delete_rooms(base);
	return 0;
}
/*
struct list * newList(struct room *my_room){
	struct list *ptr = (struct list *)malloc(sizeof(struct list));
	ptr->room=my_room;
	ptr->next=NULL;
	return ptr;
}
*/

int createRooms(int rooms){
	char room_name[21]="";
	int doughnuts; 
	int milkshakes;
	struct list *ptr;

	for(int i=1;i<=rooms;i++){
		scanf("\n%s %d %d", room_name, &doughnuts, &milkshakes);
		if(doughnuts<0 || milkshakes <0){
			printf("\nerror");
			return -1;
		}

		//create room 
		struct room *room_created = create_room(room_name, doughnuts, milkshakes);

		//check wheter name is unique with new ptr traversing list 
		struct list *check_name = base;
		while(check_name->next!=NULL){
			if(room_created->name == check_name->room->name){
				printf("\nerror");
				return -1;
			}
			check_name = check_name->next;
		}
		
		//first line is set as base of new list 
		if(i==1){
			base = newList(room_created);
			ptr = base;
		}
		//otherwise create room and link it to ptr->next 
		else{
			ptr->next = newList(room_created);
			ptr = ptr->next;
		}
	}
}


int createDoors(int doors){
	char room_name[21];
	char room_name2[21];
	char direction;
	struct list *ptr = base;
	for(int i=1;i<=doors;i++){
			scanf("\n%s %c %s", &room_name, &direction, &room_name2);

			/* check for same room names */
			if(room_name==room_name2){
				printf("\nerror");
				return -1;
			}
			struct room *room_1;
			struct room *room_2;

			/* traverse the list to find the rooms */
			while(ptr->next!=NULL){
				if(ptr->room->name == room_name){
					room_1 = ptr->room;
				}
				if(ptr->room->name == room_name2){
					room_2 = ptr->room;
				}
			}

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
	}
}

int command(){
	if(move=='G'){
		if(player_doughnuts==3){
			printf("\nlost");
			pointer = NULL;
			return 0;
		}
		else{
			player_doughnuts++;
			return 0;
		}
	}
	else if(move=='M'){
		if(player_milkshakes==2){
			printf("\nlost");
			pointer = NULL;
			return 0;
		}
		else{
			player_milkshakes++;
			return 0;
		}
	}
	else if(player_doughnuts <1 || player_milkshakes < 1){
		printf("\nlost");
		pointer = NULL;
		return 0;
	}
	else if(move=='L'){
		player_doughnuts--;
		player_milkshakes--;
		if(pointer->doors[LEFT]!=NULL)
			pointer->doors[LEFT];
		return 0;
	}
	else if(move=='R'){
		player_doughnuts--;
		player_milkshakes--;
		if(pointer->doors[RIGHT]!=NULL)
			pointer->doors[RIGHT];
		return 0;
	}
	else if(move=='U'){
		player_doughnuts--;
		player_milkshakes--;
		if(pointer->doors[UP]!=NULL)
			pointer->doors[UP];
		return 0;
	}
	else if(move=='D'){
		player_doughnuts--;
		player_milkshakes--;
		if(pointer->doors[DOWN]!=NULL)
			pointer->doors[DOWN];
		return 0;
	}
	else{
		printf("\nerror");
		pointer = NULL;
		return 0;
	}
}

void delete_rooms(struct list *myList){
	if(myList->next!=NULL){
		delete_rooms(myList->next);
	}
	free(myList->room);
	free(myList);
}

