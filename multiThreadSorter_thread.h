/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

#ifndef scannerCSVsorter_h
#define scannerCSVsorter_h

//Suggestion: define a struct that mirrors a record (row) of the data set
typedef struct movieLine{
	char* color;
	char* director_name;
	int num_critic_for_reviews;
	int duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char* actor_2_name;
	int actor_1_facebook_likes;
	int gross;
	char* genres;
	char* actor_1_name;
	char* movie_title;
	int num_voted_users;
	int cast_total_facebook_likes;
	char* actor_3_name;
	int facenumber_in_poster;
	char* plot_keywords;
	char* movie_imdb_link;
	int num_user_for_reviews;
	char* language;
	char* country;
	char* content_rating;
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;
	char* csvLine;
	struct movieLine* next;
} movieLine;

typedef struct movieLineLL
{
	movieLine* head;
	movieLine* rear;
	int size;
} movieLineLL;

typedef struct threadDriver
{
	char* filePath;
	movieLineLL* master;
	char* columnToSortOn;
} threadDriverStruct;

// a dual graph and linked list node
// nextNode is the next node in the full linked list
typedef struct threadMetaDataNode{
	pthread_t tid;
	struct threadMetaDataNode* next;
} threadMetaDataNode;

// this is also a type of linked list
// a threads LL refers to one TID
// The linked list in that thread is all the immediate children of that TID
// the next linked list is another TID
// for every single thread, we make a threadsLL and populate its first children linked list
typedef struct threadsLL
{
	pthread_t tid;
	struct threadMetaDataNode* head;
	struct threadMetaDataNode* rear;
	struct threadsLL* next;
	int size;
} threadsLL;


//Suggestion: prototype a mergesort function
void mergeSort(struct movieLine** ptrHead, char *strInput, char *numInput);

/*
void numMergeSort(int arr[], int l, int r);     //mergeSort for int array

void strMergeSort(char *arr[], int l, int r);   //mergeSort for string array
*/

#endif // simpleCSVsorter
