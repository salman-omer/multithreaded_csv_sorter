#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "multiThreadSorter_thread.h"
#include <dirent.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef enum { false, true } bool;

const int DEBUG = 0;
const int DEBUG2 = 0;
const int DEBUG3 = 0;
const int DEBUG4 = 0;
const int DEBUG5 = 0;
const int DEBUG6 = 0;
const int DEBUG8 = 0;

pthread_mutex_t lock; 
pthread_mutex_t lock2;

/*
struct threadsLL* allThreadsLL;



// add input tid to threads tid list
int addThreadsLL(pthread_t tid){
	threadsLL* curr = allThreadsLL;
	if(DEBUG6) { printf("%d\n", __LINE__);}
	while(curr != NULL){
		if(curr->tid == tid){
			return 0;
		}
		if(curr->next != NULL){
			curr = curr->next;
		} else {
			break;
		}
	}
	if(DEBUG6) { printf("%d\n", __LINE__);}
	threadsLL *newThreadLL = malloc(sizeof(threadsLL));
	newThreadLL->tid = tid;
	newThreadLL->head = NULL;
	newThreadLL->rear = NULL;
	newThreadLL->next = NULL;
	curr->next = newThreadLL; 
	if(DEBUG6) { printf("%d\n", __LINE__);}
	return 1;
}


// for the parent tid, find its LL and add its immediate child to its LL
int addImmediateChild(pthread_t parent, pthread_t child){
	threadsLL* curr = allThreadsLL;
	if(DEBUG6) { printf("%d\n", __LINE__);}
	while(curr != NULL){
		if(curr->tid == parent){
			threadMetaDataNode* newNode = malloc(sizeof(threadMetaDataNode));
			newNode->tid = child;
			newNode->next = NULL;
			if(curr->head == NULL){
				if(DEBUG6) { printf("%d\n", __LINE__);}
				curr->head = newNode;
				curr->rear = newNode;
				curr->size = 1;
				break;
			}
			if(DEBUG6) { printf("%d\n", __LINE__);}
			curr->rear->next = newNode;
			curr->rear = newNode;
			curr->size = curr->size + 1;
			break;
		}
		curr = curr->next;
	}
	if(DEBUG6) { printf("%d\n", __LINE__);}
	return 1;
}

int addThreadMetaDataNode(threadsLL* list, threadMetaDataNode* toAdd){
	if(list->size == 0){
		list->head = toAdd;
		list->rear = toAdd;
		list->size = 1;
		return 1;
	}

	if(DEBUG8){printf("%d\n", __LINE__);}
	if(list->rear == NULL){
		printf("very bad!!\n");
	}
	list->rear->next = toAdd;
	if(DEBUG8){printf("%d\n", __LINE__);}
	list->rear = toAdd;
	if(DEBUG8){printf("%d\n", __LINE__);}
	list->size = list->size + 1;
	if(DEBUG8){printf("%d\n", __LINE__);}
	return 1;

}

int concatQueueToMaster(threadsLL* master, threadsLL* toAdd){
	if(DEBUG8){printf("%d\n", __LINE__);}
	master->rear->next = toAdd->head;
	master->rear = toAdd->rear;
	master->size = master->size + toAdd->size;
	if(DEBUG8){printf("%d ret size %d\n", __LINE__, master->size);}
	return 1;
}

//creates a queue for ALL the children of this parent
threadsLL* createThreadsChildQueue(pthread_t parent){
	threadsLL* retQueue = malloc(sizeof(threadsLL));
	retQueue->size = 0;

	if(DEBUG8){printf("%d\n", __LINE__);}

	threadsLL* parentLL;
	threadsLL* curr = allThreadsLL;
	while(curr != NULL){
		if(curr->tid == parent){
			parentLL = curr;
			break;
		}
		curr = curr->next;
	}

	if(DEBUG8){printf("%d\n", __LINE__);}

	threadMetaDataNode* iter = parentLL->head;
	while(iter != NULL){
		// add iter to queue
		threadMetaDataNode* currThread = malloc(sizeof(threadMetaDataNode));
		if(DEBUG8){printf("%d\n", __LINE__);}
		currThread->tid = iter->tid;
		if(DEBUG8){printf("%d %lu\n", __LINE__, iter->tid);}
		currThread->next = NULL;
		addThreadMetaDataNode(retQueue, currThread);
		if(DEBUG8){printf("%d\n", __LINE__);}
		// then add all of its children to the queue
		concatQueueToMaster(retQueue, createThreadsChildQueue(currThread->tid));
		iter = iter->next;
		if(DEBUG8){printf("%d passing up %lu\n", __LINE__, currThread->tid);}
	}

	if(DEBUG8){printf("%d\n", __LINE__);}
	return retQueue;
}


pthread_t popQueue(threadsLL* queue){
	pthread_t retVal = queue->head->tid;
	queue->head = queue->head->next;
	queue->size = queue->size - 1;
	return retVal;
}

// print meta data to stdout from allThreadsLL
int printMetaData(){
	threadsLL* curr = allThreadsLL;
	while(curr != NULL){
		printf("Initial PID: %lu\n", curr->tid);
		if(DEBUG8){printf("%d\n", __LINE__);}
		int numThreads = 0;
	  	printf("TIDS of all spawned threads: ");
	  	if(DEBUG8){printf("%d\n", __LINE__);}
	  	threadsLL* currChildQueue = createThreadsChildQueue(curr->tid);
	  	if(DEBUG8){printf("%d\n", __LINE__);}
	  	while(currChildQueue->size != 0){
	  		printf("%lu,", popQueue(currChildQueue));
	  		numThreads++;
	  	}
	  	// want to make a new threads linked list to act as queue for all these spawned threads
	  	// first create that queue 

	  	printf("\b \nTotal number of threads: %d\n", numThreads);
	}

	return 1;
	
}

*/

// arg: pointer to movieLine
// ret 0 if completed
// this function intializes all the values for a movieline pointer
int initMovieLine(movieLine* movie){
	
	movie-> color = NULL;
	movie-> director_name = NULL;
	movie-> num_critic_for_reviews = -1;
	movie-> duration = -1;
	movie-> director_facebook_likes = -1;
	movie-> actor_3_facebook_likes = -1;
	movie-> actor_2_name = NULL;
	movie-> actor_1_facebook_likes = -1;
	movie-> gross = -1;
	movie-> genres = NULL;
	movie-> actor_1_name = NULL;
	movie-> movie_title = NULL;
	movie-> num_voted_users = -1;
	movie-> cast_total_facebook_likes = -1;
	movie-> actor_3_name = NULL;
	movie-> facenumber_in_poster = -1;
	movie-> plot_keywords = NULL;
	movie-> movie_imdb_link = NULL;
	movie-> num_user_for_reviews = -1;
	movie-> language = NULL;
	movie-> country = NULL;
	movie-> content_rating = NULL;
	movie-> budget = -1;
	movie-> title_year = -1;
	movie-> actor_2_facebook_likes = -1;
	movie-> imdb_score = -1;
	movie-> imdb_score_string = NULL;
	movie-> aspect_ratio = -1;
	movie-> aspect_ratio_string = NULL;
	movie-> movie_facebook_likes = -1;
	movie->next = NULL;
	movie->csvLine = NULL;/*
	movie-> color = "";
	movie-> director_name = "";
	movie-> num_critic_for_reviews = -1;
	movie-> duration = -1;
	movie-> director_facebook_likes = -1;
	movie-> actor_3_facebook_likes = -1;
	movie-> actor_2_name = "";
	movie-> actor_1_facebook_likes = -1;
	movie-> gross = -1;
	movie-> genres = "";
	movie-> actor_1_name = "";
	movie-> movie_title = "";
	movie-> num_voted_users = -1;
	movie-> cast_total_facebook_likes = -1;
	movie-> actor_3_name = "";
	movie-> facenumber_in_poster = -1;
	movie-> plot_keywords = "";
	movie-> movie_imdb_link = "";
	movie-> num_user_for_reviews = -1;
	movie-> language = "";
	movie-> country = "";
	movie-> content_rating = "";
	movie-> budget = -1;
	movie-> title_year = -1;
	movie-> actor_2_facebook_likes = -1;
	movie-> imdb_score = -1;
	movie-> imdb_score_string = "";
	movie-> aspect_ratio = -1;
	movie-> aspect_ratio_string = "";
	movie-> movie_facebook_likes = -1;
	movie->next = NULL;
	movie->csvLine = "";*/
	return 0;
}

int printMoviesAsCsv(movieLine* head, int numColumns, char** columnNames, char* filePath){
	int i;

	FILE *fp = fopen(filePath, "w");

	if(fp == NULL){
		write(2, "File not initializable\n", 24);
		return 1;
	}

	for (i = 0; i < numColumns; ++i)
	{
		fprintf(fp, "%s", columnNames[i]);
		if(i < numColumns - 1){
			fprintf(fp, ",");
		} else {
			fprintf(fp, "\r\n");
		}
	}
	movieLine* curr = head;
	while(curr != NULL){
		if(curr->next != NULL){
			if(curr->csvLine != NULL){
				fprintf(fp, "%s\n", curr->csvLine);
			}
		} else {
			if(curr->csvLine != NULL){
				fprintf(fp, "%s", curr->csvLine);
			}
		}
		curr = curr->next;
	}

	fclose(fp);
	return 0;
}


// threadsafe append other linked list to end of original
int appendLinkedList(movieLineLL* original, movieLineLL *other){

  	if(other == NULL){
  		return 1;
  	}

	pthread_mutex_lock(&lock); 
 

  	// if original is an empty linked list
  	if(original->size == 0){
  		original->head = other->head;
  		original->rear = other->rear;
  		original->size = other->size;
  	} else {
	  	original->rear->next = other->head;
	  	original->rear = other->rear;
	  	original->size = original->size + other->size;
  	}

  	if(DEBUG4) { printf("Master has %d lines\n", original->size);}
    pthread_mutex_unlock(&lock); 

    return 0;
}

// remove all "-1" from input string and replace with nothing
// also removes all "(nulls)"
char* removeNegativeOnes(char* str){
	char* ret = malloc(sizeof(char) * (strlen(str) + 1));
	int i;
	int j = 0;
	for(i = 0; i < strlen(str) + 1; i++){
		if(str[i] == '\0'){
			break;
		}
		if(str[i] == '-' && str[i+1] == '1'){
			i++;
			continue;
		}
		if(str[i] == '(' && str[i+1] == 'n' && str[i+2] == 'u' && str[i+3] == 'l' && str[i+4] == 'l' && str[i+5] == ')'){
			i = i + 5;
			continue;
		}

		ret[j] = str[i];
		j++;
	}
	ret[j] = '\0';
	return ret;
}

// returns string of csv line cosntructed from movie line object as per the project specifications
// args: movieline pointer m
char* constructCSVLine(movieLine* m){
	char *string;
	string = malloc(sizeof(char*[2000]));

	//want to remove all zeros from the float
	
	sprintf(string, "%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%s,%s,%d",
		m->color,
		m->director_name,
		m->num_critic_for_reviews,
		m->duration,
		m->director_facebook_likes,
		m->actor_3_facebook_likes,
		m->actor_2_name,
		m->actor_1_facebook_likes,
		m->gross,
		m->genres,
		m->actor_1_name,
		m->movie_title,
		m->num_voted_users,
		m->cast_total_facebook_likes,
		m->actor_3_name,
		m->facenumber_in_poster,
		m->plot_keywords,
		m->movie_imdb_link,
		m->num_user_for_reviews,
		m->language,
		m->country,
		m->content_rating,
		m->budget,
		m->title_year,
		m->actor_2_facebook_likes,
		m->imdb_score_string,
		m->aspect_ratio_string,
		m->movie_facebook_likes);

	//if(DEBUG6){ printf("Movie title:   %s\n", m->movie_title);}

	return string;
}



// sort input movielineLL using mergesort on the column to sort on arg
int sortMovieLineLL(movieLineLL* moviesLL, char* columnToSortOn){
	if ((strcmp(columnToSortOn, "color") == 0) || (strcmp(columnToSortOn, "director_name") == 0) || (strcmp(columnToSortOn, "actor_2_name") == 0) || (strcmp(columnToSortOn, "genres") == 0) || (strcmp(columnToSortOn, "actor_1_name") == 0) || (strcmp(columnToSortOn, "movie_title") == 0) || (strcmp(columnToSortOn, "actor_3_name") == 0) || (strcmp(columnToSortOn, "plot_keywords") == 0) || (strcmp(columnToSortOn, "movie_imdb_link") == 0) || (strcmp(columnToSortOn, "language") == 0) || (strcmp(columnToSortOn, "country") == 0) || (strcmp(columnToSortOn, "content_rating") == 0))
    {
    	if(moviesLL == NULL){
    		if(DEBUG8) {printf("%d\n", __LINE__);}
    	}
  		if(DEBUG8) {printf("%d\n", __LINE__);}
		mergeSort(&(moviesLL->head), columnToSortOn, NULL);

  		if(DEBUG8) {printf("%d\n", __LINE__);}

    }else if ((strcmp(columnToSortOn, "num_critic_for_reviews") == 0) || (strcmp(columnToSortOn, "duration") == 0) || (strcmp(columnToSortOn, "director_facebook_likes") == 0) || (strcmp(columnToSortOn, "actor_3_facebook_likes") == 0) || (strcmp(columnToSortOn, "actor_1_facebook_likes") == 0) || (strcmp(columnToSortOn, "gross") == 0) || (strcmp(columnToSortOn, "num_voted_users") == 0) || (strcmp(columnToSortOn, "cast_total_facebook_likes") == 0) || (strcmp(columnToSortOn, "facenumber_in_poster") == 0) || (strcmp(columnToSortOn, "num_user_for_reviews") == 0) || (strcmp(columnToSortOn, "budget") == 0) || (strcmp(columnToSortOn, "title_year") == 0) || (strcmp(columnToSortOn, "actor_2_facebook_likes") == 0) || (strcmp(columnToSortOn, "imdb_score") == 0) || (strcmp(columnToSortOn, "aspect_ratio") == 0) || (strcmp(columnToSortOn, "movie_facebook_likes") == 0))
    {

  		if(DEBUG6) {printf("%d\n", __LINE__);}
        mergeSort(&(moviesLL->head), NULL, columnToSortOn);

  		if(DEBUG6) {printf("%d\n", __LINE__);}
    }
    return 1;
}

int printMoviesAsFullLineCsv(movieLineLL* moviesLL, char* filePath){
	FILE *fp = fopen(filePath, "w");


	if(DEBUG4){ printf("%d %s\n", __LINE__, filePath); }

	if(fp == NULL){
		write(2, "File not initializable\n", 24);
		return 1;
	}

	fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\r\n",
		"color",
		"director_name",
		"num_critic_for_reviews",
		"duration",
		"director_facebook_likes",
		"actor_3_facebook_likes",
		"actor_2_name",
		"actor_1_facebook_likes",
		"gross",
		"genres",
		"actor_1_name",
		"movie_title",
		"num_voted_users",
		"cast_total_facebook_likes",
		"actor_3_name",
		"facenumber_in_poster",
		"plot_keywords",
		"movie_imdb_link",
		"num_user_for_reviews",
		"language",
		"country",
		"content_rating",
		"budget",
		"title_year",
		"actor_2_facebook_likes",
		"imdb_score",
		"aspect_ratio",
		"movie_facebook_likes");


	int counter = 0;
	movieLine* curr = moviesLL->head;
	while(curr != NULL){
		counter++;

		fprintf(fp, "%s\n", removeNegativeOnes(constructCSVLine(curr)));

		curr = curr->next;
	}

	if(DEBUG4){printf("lines iterated %d\n", counter);}

	fclose(fp);
	return 0;
}

// arg: movieline pointer
// ret: 0 if it is an empty node, 1 if it has any data
int hasNoFields(movieLine* movie){
	if(movie->color == NULL &&
		movie->director_name == NULL &&
		movie->num_critic_for_reviews == -1 &&
		movie->duration == -1 &&
		movie->director_facebook_likes == -1 &&
		movie->actor_3_facebook_likes == -1 &&
		movie->actor_2_name == NULL &&
		movie->actor_1_facebook_likes == -1 &&
		movie->gross == -1 &&
		movie->genres == NULL &&
		movie->actor_1_name == NULL &&
		movie->movie_title == NULL &&
		movie->num_voted_users == -1 &&
		movie->cast_total_facebook_likes == -1 &&
		movie->actor_3_name == NULL &&
		movie->facenumber_in_poster == -1 &&
		movie->plot_keywords == NULL &&
		movie->movie_imdb_link == NULL &&
		movie->num_user_for_reviews == -1 &&
		movie->language == NULL &&
		movie->country == NULL &&
		movie->content_rating == NULL &&
		movie->budget == -1 &&
		movie->title_year == -1 &&
		movie->actor_2_facebook_likes == -1 &&
		movie->imdb_score == -1 &&
		movie->aspect_ratio == -1 &&
		movie->movie_facebook_likes == -1 &&
		movie->next == NULL &&
		movie->csvLine == NULL){
		return 0;
	} else{
		return 1;
	}/*
	if(strcmp(movie->color,"") == 1 &&
		strcmp(movie->director_name,"") == 1 &&
		movie->num_critic_for_reviews == -1 &&
		movie->duration == -1 &&
		movie->director_facebook_likes == -1 &&
		movie->actor_3_facebook_likes == -1 &&
		strcmp(movie->actor_2_name,"") == 1 &&
		movie->actor_1_facebook_likes == -1 &&
		movie->gross == -1 &&
		strcmp(movie->genres,"") == 1 &&
		strcmp(movie->actor_1_name,"") == 1 &&
		strcmp(movie->movie_title,"") == 1 &&
		movie->num_voted_users == -1 &&
		movie->cast_total_facebook_likes == -1 &&
		strcmp(movie->actor_3_name,"") == 1 &&
		movie->facenumber_in_poster == -1 &&
		strcmp(movie->plot_keywords,"") == 1 &&
		strcmp(movie->movie_imdb_link,"") == 1 &&
		movie->num_user_for_reviews == -1 &&
		strcmp(movie->language,"") == 1 &&
		strcmp(movie->country,"") == 1 &&
		strcmp(movie->content_rating,"") == 1 &&
		movie->budget == -1 &&
		movie->title_year == -1 &&
		movie->actor_2_facebook_likes == -1 &&
		movie->imdb_score == -1 &&
		movie->aspect_ratio == -1 &&
		movie->movie_facebook_likes == -1 &&
		movie->next == NULL &&
		strcmp(movie->csvLine,"") == 1){
		return 0;
	} else{
		return 1;
	}*/
}

/* arg: column number, array of column headers, movie line pointer, string to add at that column
* ret 0 if completed
* adds data to the movie based on what kind of column it corresponds to
*/
int addFieldToMovie(int columnNumber, char** columnNames, movieLine* movie, char* value){
	// special case for csvline denoted by column number -1
	if(columnNumber < 0){
		movie->csvLine = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->csvLine, value);
		if(DEBUG){ printf("Line added %s\n", movie->csvLine);}
		return 0;
	}

	char* columnName = columnNames[columnNumber];
	if(DEBUG){ printf("value %s  at column %d\n", value, columnNumber);}
	if (strcmp(columnName, "color") == 0){
		movie->color = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->color, value);
		if (DEBUG) { printf("%s %d %s\n", "color", columnNumber, value); }
	}
	else if (strcmp(columnName, "director_name") == 0){
		movie->director_name = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->director_name, value);
		if (DEBUG) { printf("%s %s\n", "director_name", value); }
	}
	else if (strcmp(columnName, "num_critic_for_reviews") == 0){
		if(value[0] != '\0'){
			movie->num_critic_for_reviews = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "num_critic_for_reviews", atoi(value)); }
	}
	else if (strcmp(columnName, "duration") == 0){
		if(value[0] != '\0'){
			movie->duration = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "duration", atoi(value)); }
	}
	else if (strcmp(columnName, "director_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->director_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "director_facebook_likes", atoi(value)); }
	}
	else if (strcmp(columnName, "actor_3_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->actor_3_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "actor_3_facebook_likes", atoi(value)); }
	}
	else if (strcmp(columnName, "actor_2_name") == 0){
		movie->actor_2_name = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->actor_2_name, value);
		if (DEBUG) { printf("%s %s\n", "actor_2_name", value); }
	}
	else if (strcmp(columnName, "actor_1_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->actor_1_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "actor_1_facebook_likes", atoi(value)); }

	}
	else if (strcmp(columnName, "gross") == 0){
		if(value[0] != '\0'){
			movie->gross = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "gross", atoi(value)); }
	}
	else if (strcmp(columnName, "genres") == 0){
		movie->genres = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->genres, value);
		if (DEBUG) { printf("%s %s\n", "genres", value); }
	}
	else if (strcmp(columnName, "actor_1_name") == 0){
		movie->actor_1_name = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->actor_1_name, value);
		if (DEBUG) { printf("%s %s\n", "actor_1_name", value); }
	}
	else if (strcmp(columnName, "movie_title") == 0){
		movie->movie_title = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->movie_title, value);
		if (DEBUG) { printf("%s %s\n", "movie_title", value); }
	}
	else if (strcmp(columnName, "num_voted_users") == 0){
		if(value[0] != '\0'){
			movie->num_voted_users = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "num_voted_users", atoi(value)); }
	}
	else if (strcmp(columnName, "cast_total_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->cast_total_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "cast_total_facebook_likes", atoi(value)); }
	}
	else if (strcmp(columnName, "actor_3_name") == 0){
		movie->actor_3_name = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->actor_3_name, value);
		if (DEBUG) { printf("%s %s\n", "actor_3_name", value); }
	}
	else if (strcmp(columnName, "facenumber_in_poster") == 0){
		if(value[0] != '\0'){
			movie->facenumber_in_poster = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "facenumber_in_poster", atoi(value)); }
	}
	else if (strcmp(columnName, "plot_keywords") == 0){
		movie->plot_keywords = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->plot_keywords, value);
		if (DEBUG) { printf("%s %s\n", "plot_keywords", value); }
	}
	else if (strcmp(columnName, "movie_imdb_link") == 0){
		movie->movie_imdb_link = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->movie_imdb_link, value);
		if (DEBUG) { printf("%s %s\n", "movie_imdb_link", value); }
	}
	else if (strcmp(columnName, "num_user_for_reviews") == 0){
		if(value[0] != '\0'){
			movie->num_user_for_reviews = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "num_user_for_reviews", atoi(value)); }
	}
	else if (strcmp(columnName, "language") == 0){
		movie->language = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->language, value);
		if (DEBUG) { printf("%s %s\n", "language", value); }
	}
	else if (strcmp(columnName, "country") == 0){
		movie->country = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->country, value);
		if (DEBUG) { printf("%s %s\n", "country", value); }
	}
	else if (strcmp(columnName, "content_rating") == 0){
		movie->content_rating = malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(movie->content_rating, value);
		if (DEBUG) { printf("%s %s\n", "content_rating", value); }
	}
	else if (strcmp(columnName, "budget") == 0){
		if(value[0] != '\0'){
			movie->budget = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "budget", atoi(value)); }
	}
	else if (strcmp(columnName, "title_year") == 0){
		if(value[0] != '\0'){
			movie->title_year = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "title_year", atoi(value)); }
	}
	else if (strcmp(columnName, "actor_2_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->actor_2_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "actor_2_facebook_likes", atoi(value)); }
	}
	else if (strcmp(columnName, "imdb_score") == 0){
		if(value[0] != '\0'){
			movie->imdb_score = atof(value);
			movie->imdb_score_string = malloc(sizeof(char) * (strlen(value) + 1));
			strcpy(movie->imdb_score_string, value);
		}
		if (DEBUG) { printf("%s %f\n", "imdb_score", atof(value)); }
	}
	else if (strcmp(columnName, "aspect_ratio") == 0){
		if(value[0] != '\0'){
			movie->aspect_ratio = atof(value);
			movie->aspect_ratio_string = malloc(sizeof(char) * (strlen(value) + 1));
			strcpy(movie->aspect_ratio_string, value);
		}
		if (DEBUG) { printf("%s %f\n", "aspect_ratio", atof(value)); }
	}
	else if (strcmp(columnName, "movie_facebook_likes") == 0){
		if(value[0] != '\0'){
			movie->movie_facebook_likes = atoi(value);
		}
		if (DEBUG) { printf("%s %d\n", "movie_facebook_likes", atoi(value)); }
	}
	return 0;
}

// check if given file path is to a csv
// return 0 if true, not 0 otherwise
int isCSV(char* filePath){
	if(strlen(filePath) < 4){
		return 1;
	}
	char* csvPortion = &filePath[strlen(filePath) - 4];
	return strcmp(csvPortion, ".csv");
}

char* fileStringAppend(char* directory, char* fileName);

char* getOutputCSVFilePath(char* originalFilePath, char* outputDir, char* columnName){
	if(strcmp(outputDir, "./") != 0){
		// want to remove .csv from file path first
		char* filePathCopy = malloc(sizeof(char) * (strlen(originalFilePath) + 1));
		strcpy(filePathCopy, originalFilePath);

		filePathCopy[strlen(originalFilePath) - 4] = '\0';

		// now we want to remove all the beginning of the path
		int i;
		for(i = strlen(filePathCopy); i > -1; i--)
		{
			if(filePathCopy[i] == '/')
			{
				filePathCopy = &filePathCopy[i + 1];
			}
		}

		//printf("FILE WITHOUT CSV AND PATH %s\n", filePathCopy);

		char* temp = fileStringAppend(outputDir, filePathCopy);
		char* temp2 = fileStringAppend(temp, "-sorted-");
		char* temp3 = fileStringAppend(temp2, columnName);
		char* temp4 = fileStringAppend(temp3, ".csv");

		free(temp);
		free(temp2);
		free(temp3);
		if(DEBUG) { printf("Final csv output path %s\n", temp4); }
		return temp4;

	} else {
		// want to remove .csv from file path first
		char* filePathCopy = malloc(sizeof(char) * (strlen(originalFilePath) + 1));
		strcpy(filePathCopy, originalFilePath);

		filePathCopy[strlen(originalFilePath) - 4] = '\0';

		char* temp2 = fileStringAppend(filePathCopy, "-sorted-");
		char* temp3 = fileStringAppend(temp2, columnName);
		char* temp4 = fileStringAppend(temp3, ".csv");

		free(temp2);
		free(temp3);

		if(DEBUG) { printf("Final csv output path %s\n", temp4); }
		return temp4;
	}
}

// sort CSV as per the specifications of project 0
// args: argv from the program input, filepath to file for sorting
// ret: movieLinesLL created for this file (sorted)
movieLineLL* sortCsv(char* columnToSortOn, char* filePath){
    //check if command is correct



	//Check if file is already sorted
	if(strstr(filePath, "-sorted-") != NULL){
		return NULL;
	}


	//Check if file is a csv
	if(isCSV(filePath) != 0){
		if(DEBUG){ printf("%s is NOT a csv\n", filePath); }
		fprintf(stderr, "%s is NOT a csv\n", filePath);
		return NULL;
	} else {
		if(DEBUG4){ printf("%s IS a csv\n", filePath); }
	}

	if(DEBUG4){ printf("%d\n", __LINE__); }

	FILE* file = fopen(filePath, "r");

	if(DEBUG4){ printf("%d %s\n", __LINE__, filePath); }

	int fd = fileno(file);

	if(DEBUG4){ printf("File Descriptor: %d\n", fd); }
	//return 0;

	if(DEBUG4){ printf("%d\n", __LINE__); }

    char columnsLine[2000];
    char buffer;
    int lineCounter = 0;
    if(DEBUG) { printf("Reading in first line\n"); }
    read(fd, &buffer, 1);
    while(buffer != '\n'){
        if(DEBUG){printf("%c", buffer);}
        columnsLine[lineCounter] = buffer;
        lineCounter++;
        read(fd, &buffer, 1);
    }
    if(DEBUG){ printf("\n"); }
    columnsLine[lineCounter] = '\0';
    if(DEBUG){
        if(columnsLine[lineCounter - 1] == '\n' || columnsLine[lineCounter] == '\n'){
            printf("misplaced newline at the end of the columns string\n");
        }
    }

    if(DEBUG4){ printf("%d\n", __LINE__); }

    // now want to parse the first line so that we know the number of columns
    // number of columns = # of commas + 1
    int i;
    int numColumns = 1;
    for(i = 0; i < strlen(columnsLine); i++){
        if(columnsLine[i] == ','){
            numColumns++;
        }
    }
    if(DEBUG) { printf("Number of columns is %d\n", numColumns);}


    if(DEBUG4){ printf("%d\n", __LINE__); }


    // want to add each column header to an array of strings
    // array of strings of size numColumns, each string max size of 30, each index corresponds to that columns index
    char** columnNames;
    columnNames = malloc(numColumns * sizeof(char*));
    for(i = 0; i < numColumns; i++){
        columnNames[i] = malloc(30 * sizeof(char));
    }

    int currColumnNum = 0;
    int currStringIndex = 0;
    for(i = 0; i < strlen(columnsLine); i++){
        if(columnsLine[i] == ','){
            columnNames[currColumnNum][currStringIndex] = '\0';
            if(DEBUG){ printf("column name %s inserted into column names array\n", columnNames[currColumnNum]); }
            currColumnNum++;
            currStringIndex = 0;
            continue;
        }
        columnNames[currColumnNum][currStringIndex] = columnsLine[i];
        currStringIndex++;
    }

    columnNames[currColumnNum][currStringIndex - 1] = '\0';

    if(DEBUG4){ printf("%d\n", __LINE__); }
    if(DEBUG){
        printf("Last columnName is: %s\n", columnNames[numColumns - 1]);
        if(columnNames[numColumns - 1][strlen(columnNames[numColumns - 1])] == '\n'){
            printf("misplaced newline in the last character of last string\n");
        }
    }
    // print out column names for testing
    if(DEBUG){
        for(i = 0; i < numColumns; i++){
            printf("column: %s at number %d\n", columnNames[i], i);
            if(columnNames[i][strlen(columnNames[i] - 1)] == '\n'){
                    printf("misplaced newline in the last character of last string\n");
            }
        }
    }


    // now want to read in a row and put appropriate data in fields for the row object
    // to read in a row, we start at new line or EOF

    //make a new struct, make previous struct point to it, populate it
    if(DEBUG4){ printf("%d\n", __LINE__); }

    char currCellText[3000];
    int currCellTextIndex = 0;
    int cellNumber = 0;
    if(DEBUG2){ printf("Line %d\n", __LINE__);}
    movieLine* currMovie = malloc(sizeof(movieLine));
    initMovieLine(currMovie);
    movieLineLL* moviesLL = malloc(sizeof(movieLineLL));
    moviesLL->head = currMovie;
    moviesLL->rear = currMovie;
    moviesLL->size = 1;
    bool quotationMark = false;
    char individualMovieLine[500];
    int movieLineCharacterIndex = 0;
    if(DEBUG2){ printf("Line %d\n", __LINE__);}
    while(read(fd, &buffer, 1) != 0){
    	if(cellNumber >= numColumns){
    		write(2, "ERROR: more data than allowed columns, aborting\n", 49);
    		return NULL;
    	}
        if(buffer == '"'){
        	if(quotationMark == true){
        		quotationMark = false;
        	} else {
        		quotationMark = true;
        	}

            /* This is some old stuff that I am commenting out so that the quotes are stored in the strings
            individualMovieLine[movieLineCharacterIndex] = buffer;
            movieLineCharacterIndex++;
            continue;*/
        }
        if (buffer == ',' && (quotationMark == false))
        {
            individualMovieLine[movieLineCharacterIndex] = buffer;
            movieLineCharacterIndex++;
            // fill out the struct field based on this info
            currCellText[currCellTextIndex] = '\0';
            currCellTextIndex = 0;
            addFieldToMovie(cellNumber, columnNames, currMovie, currCellText);
            cellNumber++;
            currCellText[0] = '\0';
            continue;
        }
        if(buffer == '\n'){
            // complete the current movie and make the next one
            individualMovieLine[movieLineCharacterIndex] = '\0';
            movieLineCharacterIndex = 0;
            currCellText[currCellTextIndex - 1] = '\0';
            currCellTextIndex = 0;
            addFieldToMovie(cellNumber, columnNames, currMovie, currCellText);
            cellNumber = 0;
            currCellText[0] = '\0';
            if(DEBUG2){printf("%s\n", individualMovieLine);}

            movieLine* newMovie = malloc(sizeof(movieLine));
            addFieldToMovie(-1, columnNames, currMovie, individualMovieLine);
            initMovieLine(newMovie);
            //strcpy(currMovie->csvLine, individualMovieLine);
            moviesLL->rear = newMovie;
            currMovie->next = newMovie;
            currMovie = newMovie;
            moviesLL->size = moviesLL->size + 1;
            continue;
        }

        currCellText[currCellTextIndex] = buffer;
        currCellTextIndex++;
        individualMovieLine[movieLineCharacterIndex] = buffer;
        movieLineCharacterIndex++;

    }

    if(DEBUG4){ printf("%d\n", __LINE__); }

    movieLine* currIter = moviesLL->head;
    while(currIter->next != NULL){
    	if(hasNoFields(currIter->next) == 0){
    		moviesLL->rear = currIter;
    		moviesLL->size = moviesLL->size - 1;
    		free(currIter->next);
    		currIter->next = NULL;
    		break;
    	}
    	currIter = currIter->next;
    }


    int counter = 0;

    if ((strcmp(columnToSortOn, "color") == 0) || (strcmp(columnToSortOn, "director_name") == 0) || (strcmp(columnToSortOn, "actor_2_name") == 0) || (strcmp(columnToSortOn, "genres") == 0) || (strcmp(columnToSortOn, "actor_1_name") == 0) || (strcmp(columnToSortOn, "movie_title") == 0) || (strcmp(columnToSortOn, "actor_3_name") == 0) || (strcmp(columnToSortOn, "plot_keywords") == 0) || (strcmp(columnToSortOn, "movie_imdb_link") == 0) || (strcmp(columnToSortOn, "language") == 0) || (strcmp(columnToSortOn, "country") == 0) || (strcmp(columnToSortOn, "content_rating") == 0))
    {
        //all char * cases
        //printf("COLUMN NAME type is String!\n\n");
        for (i = 0; i < numColumns; i++)
        {
            //printf("%s\n", columnNames[i]);
            if (strcmp(columnToSortOn, columnNames[i]) == 0)   //case when there are only subsets of column names
            {
                counter = 1;
                break;
            }
        }

        if (counter == 1)   //sort only if the column name actually exists
        {
            //mergeSort(&(moviesLL->head), columnToSortOn, NULL);
            //printMoviesAsCsv(moviesLL->head, numColumns, columnNames, outputFilePath);
        }else
        {
            write(2, "ERROR: INPUTTED COLUMN NAME DOES NOT EXIST!\n\n", 46);
        }


    }else if ((strcmp(columnToSortOn, "num_critic_for_reviews") == 0) || (strcmp(columnToSortOn, "duration") == 0) || (strcmp(columnToSortOn, "director_facebook_likes") == 0) || (strcmp(columnToSortOn, "actor_3_facebook_likes") == 0) || (strcmp(columnToSortOn, "actor_1_facebook_likes") == 0) || (strcmp(columnToSortOn, "gross") == 0) || (strcmp(columnToSortOn, "num_voted_users") == 0) || (strcmp(columnToSortOn, "cast_total_facebook_likes") == 0) || (strcmp(columnToSortOn, "facenumber_in_poster") == 0) || (strcmp(columnToSortOn, "num_user_for_reviews") == 0) || (strcmp(columnToSortOn, "budget") == 0) || (strcmp(columnToSortOn, "title_year") == 0) || (strcmp(columnToSortOn, "actor_2_facebook_likes") == 0) || (strcmp(columnToSortOn, "imdb_score") == 0) || (strcmp(columnToSortOn, "aspect_ratio") == 0) || (strcmp(columnToSortOn, "movie_facebook_likes") == 0))
    {
        //all int + double cases
        //printf("COLUMN NAME type is int/double!\n\n");
        for (i = 0; i < numColumns; i++)
        {

            if (strcmp(columnToSortOn, columnNames[i]) == 0)   //case when there are only subsets of column names
            {
                counter = 1;
                break;
            }
        }

        if (counter == 1)   //sort only if the column name actually exists
        {
            //mergeSort(&(moviesLL->head), NULL, columnToSortOn);
            //printMoviesAsCsv(moviesLL->head, numColumns, columnNames, outputFilePath);
        }else
        {
            write(2, "ERROR: INPUTTED COLUMN NAME DOES NOT EXIST!\n\n", 46);
        }
    }else
    {
        write(2, "ERROR: INVALID COLUMN NAME!\n\n", 30);
    }
    if(DEBUG4){ printf("%d\n", __LINE__); }
    //After sorting!
    //printf("\n\n\n\n\nAfter Sorting!\n\n\n\n\n");
    free(columnNames);
    fclose(file);
    //printf("SUCCESS!\n\n");


    return moviesLL;
}

// arg: string 1 = base directory, str2 = directory to append to end
// ret: str1 + str2 + '/'
char* directoryStringAppend(char* str1, char* str2){
	char* ret;
	if( (ret = malloc((strlen(str1) + strlen(str2) + 2) * sizeof(char))) ) {
		strcpy(ret, str1);
		strcat(ret, str2);
		ret[strlen(str1) + strlen(str2) ] = '/';
		ret[strlen(str1) + strlen(str2) + 1] = '\0';
	}
	else{
		ret = "failure";
	}
	return ret;
}

// arg: string 1 = base directory, str2 = file to append to end
// ret: str1 + str2
char* fileStringAppend(char* directory, char* fileName){
	char* ret;
	if( (ret = malloc((strlen(directory) + strlen(fileName) + 1) * sizeof(char))) ) {
		strcpy(ret, directory);
		strcat(ret, fileName);
		if(DEBUG5){ printf("%d %s len      %s len \n", __LINE__, directory, fileName); }
		ret[strlen(directory) + strlen(fileName) + 1] = '\0';
		if(DEBUG5){ printf("%d %s\n", __LINE__, ret); }
	}
	else{
		ret = "failure";
	}
	return ret;
}

// given directory in path, get its base directory
// arg: directory
// ret: base directory string
char* getBaseDirectory(char* directory){
	int i;
	if(strlen(directory) <= 2){
		return directory;
	}
	for(i = strlen(directory) - 2; i > -1; i--){
		if(directory[i] == '/'){
			directory[i + 1] = '\0';
			break;
		}
	}
	return directory;
}

// function prototype for subLevelDriver
threadMetaDataNode* subLevelDriver(char* currDir, char* columnToSortOn, movieLineLL* master);


// takes the input file path, creates linked list, and adds it to the master linked list
void* fileThreadDriver(void *args){
	threadDriverStruct* argsStruct= (threadDriverStruct*)args;
	movieLineLL* temp = sortCsv(argsStruct->columnToSortOn, argsStruct->filePath);
	appendLinkedList(argsStruct->master, temp);

	printf("Initial PID: %d\n", getpid());
	printf("TIDS of all spawned threads: ");
	printf("\b \nTotal number of threads: %d\n\n", 0);


	threadMetaDataNode* fileNode = malloc(sizeof(threadMetaDataNode));
	fileNode->tid = pthread_self();
	fileNode->next = NULL;
	
	//addThreadsLL(pthread_self());
	return (void*) fileNode;
}

void* directoryThreadDriver(void* args){
	threadDriverStruct* argsStruct= (threadDriverStruct*)args;
	//addThreadsLL(pthread_self());
	// sublevel driver should return the filenode list appended to the directory node list

	threadMetaDataNode* ret = subLevelDriver(argsStruct->filePath, argsStruct->columnToSortOn, argsStruct->master);

	threadMetaDataNode* node = malloc(sizeof(threadMetaDataNode));
	node->tid = pthread_self();
	node->next = ret;


	threadMetaDataNode* curr = ret;

	printf("Initial PID: %d\n", getpid());
					if(DEBUG8){printf("%d\n", __LINE__);}
	int numThreads = 0;
	printf("TIDS of all spawned threads: ");
				  	if(DEBUG8){printf("%d\n", __LINE__);}
				  	//threadsLL* currChildQueue = createThreadsChildQueue(curr->tid);
	  				if(DEBUG8){printf("%d\n", __LINE__);}
	while(curr != NULL){
		if(DEBUG8){printf("%d\n", __LINE__);}
	  	printf("%lu,", curr->tid);
	  	if(DEBUG8){printf("%d\n", __LINE__);}
	  	numThreads++;
	  	curr = curr->next;
	}
	printf("\b \nTotal number of threads: %d\n\n", numThreads);
	return (void *) node;
}

// function to go through all the files in currDir and call the sort on them
// arg: curr directory to look through columnToSortOn from program input, master LL
// ret: head of this files linked list
threadMetaDataNode* parseFiles(char* currDir, char* columnToSortOn, movieLineLL* master){
	DIR *dir;
  	struct dirent *entry;
  	
  	void* status;

  	threadMetaDataNode* ret = NULL;

	if(DEBUG4){ printf("%d %s\n", __LINE__, currDir); }
  	
  	if ((dir = opendir(currDir)) == NULL){
    		perror("opendir() error");
	}
	else {
		if(DEBUG4){ puts("Files:"); }
		while ((entry = readdir(dir)) != NULL){

			// entry is a file
			if(entry->d_type == DT_REG){
				
				fflush(stdout);


				pthread_t tid;
					
				threadDriverStruct* args = malloc(sizeof(threadDriverStruct));
				char* filePath = fileStringAppend(currDir, entry->d_name);
				if(DEBUG6){ printf("CurrDir is %s for FilePath: %s for file: %s\n", currDir,filePath, entry->d_name); }


				args->filePath = filePath;
				args->master = master;
				args->columnToSortOn = columnToSortOn;
				pthread_create(&tid, NULL, fileThreadDriver, (void *)args);

				pthread_join(tid, &status);

					
				/*printf("Initial PID: %lu\n", curr->tid);
					if(DEBUG8){printf("%d\n", __LINE__);}
				int numThreads = 0;
				printf("TIDS of all spawned threads: ");
				  	if(DEBUG8){printf("%d\n", __LINE__);}
				  	//threadsLL* currChildQueue = createThreadsChildQueue(curr->tid);
				  	if(DEBUG8){printf("%d\n", __LINE__);}
				while(curr != NULL){
				  	printf("%lu,", curr->tid);
				  	numThreads++;
				  	curr = curr->next;
				}
				printf("\b \nTotal number of threads: %d\n", numThreads);*/



				pthread_mutex_lock(&lock2);


				threadMetaDataNode* thisNode = (threadMetaDataNode*)status;
				if(DEBUG8) { if(thisNode->next != NULL){ printf("%s\n", "BIG PROBLEM!!!");}}

				if(ret == NULL){
					ret = (threadMetaDataNode*)status;
				} else {
					/*threadMetaDataNode* rear = thisNode;
					while(rear->next != NULL){
						rear = rear->next;
					}
					rear->next = ret;*/
					thisNode->next = ret;
					ret = thisNode;
				}

				pthread_mutex_unlock(&lock2);

				//addImmediateChild(pthread_self(), tid);
				//if(DEBUG6) { printf("%d\n", __LINE__);}
				//numProcesses += (int)status;
				//if(DEBUG6) { printf("%d\n", __LINE__);}
				//if(DEBUG8){printf("%lu CurrDir is %s for FilePath: %s for file: %s\n,", tid, currDir,filePath, entry->d_name);}
				free(filePath);
				/*
				pid = fork();

				//if process is the child
				if(pid == 0){
					char* filePath = fileStringAppend(currDir, entry->d_name);
					if(DEBUG){ printf("%s\n", filePath); }
					sortCsv(columnToSortOn, filePath);
					free(filePath);
					exit(1);
				} 
				// if process is the parent
				else{
					pid_t cpid =  waitpid(pid, &stat, 0);
					printf("%d,", pid);
					if(DEBUG){ printf("Child %d terminated with status: %d\n", cpid, WEXITSTATUS(stat)); }
					numProcesses += WEXITSTATUS(stat);
					continue;
				}*/
			}
		}
		closedir(dir);
	}
	return ret;
}


// function to go through all the directories in currDir and call the subLevelDriver on them
// arg: curr directory to look through, output directory to put sorted files in, pid (should be 0 on input?), columnToSortOn from
// 	program input
// ret: head of this threads linked list
threadMetaDataNode* parseDirectories(char* currDir, char* columnToSortOn, movieLineLL* master){
	DIR *dir;
  	struct dirent *entry;
  	void *status;

  	threadMetaDataNode* ret = NULL;

	// go through directories
	if ((dir = opendir(currDir)) == NULL){
		perror("opendir() error");
	}
	else {
		if(DEBUG){ puts("\nDirectories:"); }
		if((entry = readdir(dir)) == NULL){
			exit(1);
		}
		while ((entry = readdir(dir)) != NULL){
			if(entry->d_type == DT_DIR){
				if(!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".git") == 0)){


	  				pthread_t tid;
	  				fflush(stdout);
	  				threadDriverStruct* args = malloc(sizeof(threadDriverStruct));
	  				char* directoryPath = directoryStringAppend(currDir, entry->d_name);
					args->filePath = directoryPath;
					args->master = master;
					args->columnToSortOn = columnToSortOn;

					if(DEBUG6){ printf("CurrDir is %s for DirectoryPath: %s", currDir,directoryPath); }
					

					pthread_create(&tid, NULL, directoryThreadDriver, (void *)args);

					pthread_join(tid, &status);

					// want to print the meta data for the status at this point

					/*threadMetaDataNode* curr = (threadMetaDataNode*)status;
					
					printf("Initial PID: %lu\n", curr->tid);
						if(DEBUG8){printf("%d\n", __LINE__);}
					int numThreads = 0;
					printf("TIDS of all spawned threads: ");
					  	if(DEBUG8){printf("%d\n", __LINE__);}
					  	//threadsLL* currChildQueue = createThreadsChildQueue(curr->tid);
					  	if(DEBUG8){printf("%d\n", __LINE__);}
					while(curr != NULL){
					  	printf("%lu,", curr->tid);
					  	numThreads++;
					  	curr = curr->next;
					}
					printf("\b \nTotal number of threads: %d\n", numThreads);*/

					pthread_mutex_lock(&lock2);

					threadMetaDataNode* thisNode = (threadMetaDataNode*)status;
					if(ret == NULL){
						ret = (threadMetaDataNode*)status;
					} else {
						threadMetaDataNode* rear = thisNode;
						while(rear->next != NULL){
							rear = rear->next;
						}
						rear->next = ret;
						ret = (threadMetaDataNode*)status;
					}

					pthread_mutex_unlock(&lock2);

					//if(DEBUG6) { printf("%d\n", __LINE__);}
					//addImmediateChild(pthread_self(), tid);

					//if(DEBUG8){ printf("%lu CurrDir is %s for DirectoryPath: %s\n,", tid, currDir,directoryPath); } 
					//numProcesses += (int)status;
					/*pid = fork();
					if(pid == 0){
						char* subDir = directoryStringAppend(currDir, entry->d_name);
						numProcesses = subLevelDriver(subDir, outputDir, pid, 1, columnToSortOn);
						if(DEBUG){ printf("%s\n", subDir); }
						free(subDir);
						exit(numProcesses);
					} else {
						pid_t cpid =  waitpid(pid, &stat, 0);
						printf("%d,", pid);
						if(DEBUG){ printf("Child %d terminated with status: %d\n", cpid, WEXITSTATUS(stat)); }
						numProcesses += WEXITSTATUS(stat);
						continue;
					}*/
				}

			}
		}

		closedir(dir);
	}

	return ret;
}


// calls parse files and pares directories for a particular sublevel of directories
// this is trypically called by each sub directory as well as the parent function
// arg: current directory, output directory, pid, number of processes total, columnToSortOn from program input
// ret: the number of processes
threadMetaDataNode* subLevelDriver(char* currDir, char* columnToSortOn, movieLineLL* master){
	threadMetaDataNode* ret = parseFiles(currDir, columnToSortOn, master);
	if(ret != NULL){
		threadMetaDataNode* rear = ret;
		while(rear->next != NULL){
			rear= rear->next;
		}
		rear->next = parseDirectories(currDir, columnToSortOn, master);
	} else {
		ret = parseDirectories(currDir, columnToSortOn, master);
	}
	return ret;
}


int main(int argc, char *argv[]){
    //check if there are correct # of argument inputs

    if (argc >= 3 && argc <= 7){

    	// testing if we can see all directory and file names as well as subdirectories
    	//DIR *dir;
  		//struct dirent *entry;
  		char* columnToSortOn = NULL;
  		char* currDir = "./";
  		char* outputDir = "./";

  		if(argc % 2 == 0){
  			printf("FATAL ERROR: INCORRECT NUMBER OF INPUTS\n");
  			write(2, "FATAL ERROR: INCORRECT NUMBER OF INPUTS\n", 41);
  			return 1;
  		}

  		if(DEBUG3) {printf("%d\n", __LINE__);}

  		bool c = false;
  		bool d = false;
  		bool o = false;

  		int i;
  		for(i = 1; i < argc; i = i + 2){
  			if(argv[i+1][0] == '-'){
  				printf("FATAL ERROR: ARGUMENT NOT SPECIFIED FOR TAG\n");
  				write(2, "FATAL ERROR: ARGUMENT NOT SPECIFIED FOR TAG\n", 45);
  				return 1;
  			}
  			if(strcmp(argv[i], "-c") == 0){
  				if(c == true){
  					printf("FATAL ERROR: DUPLICATE TAG\n");
  					write(2, "FATAL ERROR: DUPLICATE TAG\n", 45);
  					return 1;
  				}
  				c = true;

				//check if valid column name
				if (!(strcmp(argv[i+1], "color") == 0) && !(strcmp(argv[i+1], "director_name") == 0) && !(strcmp(argv[i+1], "num_critic_for_reviews") == 0) && !(strcmp(argv[i+1], "duration") == 0) && !(strcmp(argv[i+1], "director_facebook_likes") == 0) && !(strcmp(argv[i+1], "actor_3_facebook_likes") == 0) && !(strcmp(argv[i+1], "actor_2_name") == 0) && !(strcmp(argv[i+1], "actor_1_facebook_likes") == 0) && !(strcmp(argv[i+1], "gross") == 0) && !(strcmp(argv[i+1], "genres") == 0) && !(strcmp(argv[i+1], "actor_1_name") == 0) && !(strcmp(argv[i+1], "movie_title") == 0) && !(strcmp(argv[i+1], "num_voted_users") == 0) && !(strcmp(argv[i+1], "cast_total_facebook_likes") == 0) && !(strcmp(argv[i+1], "actor_3_name") == 0) && !(strcmp(argv[i+1], "facenumber_in_poster") == 0) && !(strcmp(argv[i+1], "plot_keywords") == 0) && !(strcmp(argv[i+1], "movie_imdb_link") == 0) && !(strcmp(argv[i+1], "num_user_for_reviews") == 0) && !(strcmp(argv[i+1], "language") == 0) && !(strcmp(argv[i+1], "country") == 0) && !(strcmp(argv[i+1], "content_rating") == 0) && !(strcmp(argv[i+1], "budget") == 0) && !(strcmp(argv[i+1], "title_year") == 0) && !(strcmp(argv[i+1], "actor_2_facebook_likes") == 0) && !(strcmp(argv[i+1], "imdb_score") == 0) && !(strcmp(argv[i+1], "aspect_ratio") == 0) && !(strcmp(argv[i+1], "movie_facebook_likes") == 0))
				{
					printf("FATAL ERROR: INVALID COLUMN NAME\n");
  					write(2, "FATAL ERROR: INVALID COLUMN NAME\n", 45);
					return 1;
				}

  				columnToSortOn = malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
  				strcpy(columnToSortOn, argv[i+1]);
  				if(DEBUG3){printf("%s\n", columnToSortOn);};
  			}
  			else if(strcmp(argv[i], "-d") == 0){
  				if(d == true){
  					printf("FATAL ERROR: DUPLICATE TAG\n");
  					write(2, "FATAL ERROR: DUPLICATE TAG\n", 45);
  					return 1;
  				}
  				d = true;
  				currDir = directoryStringAppend(currDir, argv[i+1]);
  			}
  			else if(strcmp(argv[i], "-o") == 0){
  				if(o == true){
  					printf("FATAL ERROR: DUPLICATE TAG\n");
  					write(2, "FATAL ERROR: DUPLICATE TAG\n", 45);
  					return 1;
  				}
  				o = true;
  				outputDir = directoryStringAppend(outputDir, argv[i+1]);
  			}
  			else {
  				printf("FATAL ERROR: ARGUMENTS WITHOUT TAG\n");
  				write(2, "FATAL ERROR: ARGUMENTS WITHOUT TAG\n", 36);
  				//would like program to terminate after this so it doesnt print stff below.
  				return 1;
  			}

  		}

  		if(columnToSortOn == NULL){
  			printf("FATAL ERROR: NO COLUMN TO SORT ON\n");
  			write(2, "FATAL ERROR: NO COLUMN TO SORT ON\n", 35);
  			return 1;
  		}



  		if (pthread_mutex_init(&lock, NULL) != 0) { 
        	printf("\n mutex init has failed\n"); 
        	return 1; 
    	} 

/*
    	allThreadsLL = malloc(sizeof(threadsLL));
    	allThreadsLL->tid = pthread_self();
    	allThreadsLL->head = NULL;
    	allThreadsLL->rear = NULL;
    	allThreadsLL->next = NULL;
*/

    	char outputFileName[150];

    	strcpy(outputFileName, "AllFiles-sorted-");
    	strcat(outputFileName, columnToSortOn);
    	strcat(outputFileName, ".csv");
    	outputDir = fileStringAppend(outputDir, outputFileName);

    	movieLineLL* master = malloc(sizeof(movieLineLL));
   		master->size = 0;

  		
  		fflush(stdout);

  		threadMetaDataNode* final = subLevelDriver(currDir, columnToSortOn, master);

  		threadMetaDataNode* curr = (threadMetaDataNode*)final;
					
		printf("Initial PID: %d\n", getpid());
			if(DEBUG8){printf("%d\n", __LINE__);}
		int numThreads = 0;
		printf("TIDS of all spawned threads: ");
		  	if(DEBUG8){printf("%d\n", __LINE__);}
		  	//threadsLL* currChildQueue = createThreadsChildQueue(curr->tid);
		  	if(DEBUG8){printf("%d\n", __LINE__);}
		while(curr != NULL){
		  	printf("%lu,", curr->tid);
		  	numThreads++;
		  	curr = curr->next;
		}
		
		printf("\b \nTotal number of threads: %d\n", numThreads);

		if(DEBUG8){printf("%d\n", __LINE__);}
  		sortMovieLineLL(master, columnToSortOn);
  		if(DEBUG8){printf("%d\n", __LINE__);}
  		printMoviesAsFullLineCsv(master, outputDir);


		if(DEBUG8){printf("%d\n", __LINE__);}

        free(columnToSortOn);
    	//sortCsv(argv);
    }else {
//        fprintf(stderr, "\nERROR: ENTER IN CORRECT NUMBER OF ARGUMENTS\n");   - same error statement but with stderr
        printf("ERROR: ENTER IN CORRECT NUMBER OF ARGUMENTS!\n\n");
        write(2, "ERROR: ENTER IN CORRECT NUMBER OF ARGUMENTS!\n\n", 47);
    }
    return 0;
}


