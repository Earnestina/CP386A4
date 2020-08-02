//Gulnar Saharya & Earnestina Petergeorge
 //GitHub Login ID: TinaPetergeorge
 //160673540
 //GitHub Repository: https://github.com/TinaPetergeorge/CP386A4
 //August 1 2020
 //CP386: Assignment 4




#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdbool.h>

#define Size 10 
pthread_mutex_t lock; 
int max[Size][Size]; 
int available[Size]; 
int allocate[Size][Size]; 
int needed[Size][Size]; 
int used[Size];
int available_b[Size]; 
bool Finish[Size]; 
struct dimentions{ 
    int r;
    int o;
}temp;
typedef struct thread// used to represent a single thread.
{
    int thread_id;
    int state;
    pthread_t handle;
    int retVal;
} Thread;

// must used variables
int readInput(void);
int readFile(void);
int safe_state(void);
void matrix_p(void); 
int executed(void); 
void* run_thread(void* t);

int main(int argc, const char * argv[]) {
// main function to utilize the inputs and be able to output message
   // count to loop in 
    int count;
	// count = 0;
// start of if statements so that we can check if there will be an input    
if(argc < 3){ 
        printf(" Invalid exiting code\n");
        return -1;
    }else{ 
      // this is where we will be collecting the data   
        for(count=0;count<argc-1;count++)
            available[count] = atoi(argv[count+1]);
    }
    // doing threading the pthread_mutex helps us create the first parameter which will //then be pointing to the very first index
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        //initialize mutex lock for null 
        printf("\n failed mutex initialize \n");
        return 1;
// ensure that you are returning a variable or else will have errors
    }
    // this is in order to help the users be able to see the number of customers when they // ask for this input 
    printf("number of customers: %d \n", count);
   // when doing this ensure that you will collect the data by using following
    readFile(); 
   // this is another key information for users
  printf("max resources available:\n");
// we must do this by creating a double for loop ensuring that the array has a value for //both column and row  
  for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
// after we have come out of this we are displaying the resources available by once //again going into a for loop    
printf(" resources available: :\n");
    for (int j = 0; j < temp.o; j++) {
        printf("%d ", available[j]);
    }
    printf("\n");
    readInput(); 
    // ensuring that we do the one of the most vital pieces checking if it is safe or unsafe
    if(safe_state() == 1){
        return 0;
    }
   
/* uncomment this if we’re not using checkCompletion() and allocate()
For (i-0;i<resources;i++)
if(Request[i]>Available[i])
return;// this process has to wait
for(i=0;i<resources;i++)
Available[i]-=Request[i];
Allocation[proess][i]+=Request[i];
Need[process][i] -=Request[i];
}
*/
//allocate the resource to the process

    executed(); 
    // make sur mutex very key or code will not run 
    pthread_mutex_destroy(&lock);
    return 0;
}
// ensuring the readFile is there so we can grab and extract data

//printf("Banker's Algorithm");
// assume unsafe state
//int safe = FALSE;
//  Work array
	//int *Work;
	//if (!(Work = malloc(resources * sizeof(int))))
		//return -1;

int readFile(){
    int c;
    FILE *file;
    int r = 0;
    int o = 0;
    file = fopen("sample4_in.txt", "r");
    if (file) {
         
        while ((c = getc(file)) != EOF){
            if(r == 0 && c==','){
                o++;
            }
            if(c=='\n'){
                r++;
            }
        }
        r++;
        o++;
        temp.r = r;
        temp.o = c;
        fseek(file, 0, SEEK_SET);
        int i=0;
        int j=0;
        while ((c = getc(file)) != EOF){
            if(c>='0' && c<='9'){
                 max[i][j] = c-48;
            }else if( c==','){
                j++;
            }else if(c=='\n'){
                i++;
                j=0;
            }
        }
        fclose(file);
    }
    return 0;
}
//allocate array
int readInput(){ 
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            allocate[i][j] = 0;
        }
    }
    bool check = true;
    while(check){
    char string[Size+3];
    char *test = string;
    printf("please specify the command: ");
    scanf("%s",test);
        if(*test == '*'){
            check = false;
            matrix_p();
            //print here
        }else if((*(test+2)-48)>=temp.r){ 
            printf("incorrect\n");
        //add new
        }else if(*(test+1) == 'Q'){ 
            int r = *(test+2)-48;
            for(int i = 3; i<temp.o+3; i++){
                allocate[r][i-3] += *(test+i)-48;
            }
            printf("done\n");
            
        }else if(*(test+1) == 'L'){ 
            int r = *(test+2)-48;
            for(int i = 3; i<temp.o+3; i++){
                allocate[r][i-3] -= *(test+i)-48;
            }
            printf("done\n");
        }
        
    }
    return 0;
}
//safe state here
int safe_state(){
    for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            needed[i][j] = max[i][j]-allocate[i][j];
        }
    }
    
    printf("Resource needed:\n");
    for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            printf("%d ", needed[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            if(needed[i][j]<0){
                printf("unsafe");
                return 1;
            }
        }
    }
    
    printf("Resources available:\n");
        for (int j = 0; j < temp.o; j++) {
            available_b[j] = available[j];
             printf("%d ", available_b[j]);
        }
        for (int j = 0; j < temp.o; j++) {
            Finish[j] = false;
        }
    return 0;
}
void matrix_p(){ 
    printf("Resources allocated:\n");
    for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            printf("%d ", allocate[i][j]);
        }
        printf("\n");
    }
    printf("max Resources:\n");
    for (int i = 0; i < temp.r; i++) {
        for (int j = 0; j < temp.o; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}




int executed(void){// bankers algorithm
    printf("\nEnter Command: Run\n");
    int count_a = 0;
    bool st_saf; 
    while(count_a < temp.r){ 
        for (int i = 0; i < temp.r; i++) {
            st_saf = true;
            int j;
            for (j = 0; j < temp.o && st_saf; j++) {
                if(!Finish[i]){
                    if(needed[i][j] > available_b[j]){
                        st_saf = false;
                    }
                }else{
                    st_saf = false;
                    break;
                }
            }
            if(st_saf){
                Thread *thread = NULL;
                thread = (Thread*)malloc(sizeof(Thread));
                thread->thread_id = i;
                thread->state = 1;
                thread->retVal = pthread_create(&(thread->handle),NULL,run_thread,thread); 
                sleep(1); 
                Finish[i] = true;
                count_a++;
                
            }
        }
    }
    printf("\nPlease specify your Command: \n");
    return 0;
}
void logStart(int thread_ID)
{
    printf("\n\t start thread %d .", thread_ID);
}

void logFinish(int thread_ID)
{
    printf("\n\t thread %d finished.", thread_ID);
}

void* run_thread(void* t)
{
    pthread_mutex_lock(&lock); 
    
    int i = ((Thread*)t)->thread_id;
    printf("customer number is  %d :\n",i);
    printf("\t resources to be allocated: ");
    for (int j = 0; j < temp.o; j++) {
        printf("%d ",allocate[i][j]);
    }
    printf("\n");
    
    printf("\t resources that are needed: ");
    for (int j = 0; j < temp.o; j++) {
        printf("%d ",needed[i][j]);
    }
    printf("\n");
    
    printf("\t available Resources: ");
    for (int j = 0; j < temp.o; j++) {
        printf("%d ",available_b[j]);
    }
    logStart(((Thread*)t)->thread_id);
    logFinish(((Thread*)t)->thread_id);
    printf("\n");
    printf("\t Thread is releasing resources...\n");
    
    for (int j = 0; j < temp.o; j++) {
        available_b[j] += allocate[i][j];
    }
    printf("\t New available Resources: ");
    for (int j = 0; j < temp.o; j++) {
        printf("%d ",available_b[j]);
    }
    printf("\n");
    
    pthread_mutex_unlock(&lock); 
    pthread_exit(0);
}





