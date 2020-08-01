#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define MAX_INPUT_SIZE 256
#define FILE_NAME "sample4_in.txt"
/* Variables that must be defined outside the functions in order to be used as a universal variable in this program
*/
int customer_sum;
int resource_sum;
int b,t
int **max;
int **allocate;
int **need_array;
int *available;
int *s_array;
int safety_count;
void *thread_run(void *t);
int *getS_array();
int **readFile(char *fileName);
// Now must define pointers, defining two for the single and double pointers
void printDoublePointerData(int **data, int m, int n);
void printSinglePointerData(int *data, int m);
// Programming the main function that will access and run the set algorithm that will help //users to simulate the bankers algorithm as though they are using the bank outsourcing //the investments and etc
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ERROR\n");
        return -1;
    }
    resource_sum = argc - 1;
    
    available = malloc(sizeof(int) * resource_sum);
    for (int g = 1; g < argc; g++)
    {
        available[g - 1] = atoi(argv[g]);
    }
// this will help store the array that we will need to use 
   // we must read the file
    max = readFile(FILE_NAME);
// this helps put the max number inside the file 
    allocate = malloc(sizeof(int *) * customer_sum);
    need_array = malloc(sizeof(int *) * customer_sum);
    for (int g = 0; g < customer_sum; g++)
    {
        allocate[g] = malloc(sizeof(int) * resource_sum);
        need_array[g] = malloc(sizeof(int) * resource_sum);
    }

    safety_count = 0;
  //intialie as a var with it base num
    char *userCommand = malloc(sizeof(char) * MAX_INPUT_SIZE);
    printf("The amount of customers would therefore be: %d\n", customer_sum);
    printf("This is the avaible resources presented: ");
    printSinglePointerData(available, resource_sum);
    printf("Max :\n");
    printDoublePointerData(max, customer_sum, resource_sum);
   
    while (1)
    {
        printf("What is the command that you would like to enter: ");
        fgets(userCommand, MAX_INPUT_SIZE, stdin);
        // Replace new line character with end of line character
        if (strlen(userCommand) > 0 && userCommand[strlen(userCommand) - 1] == '\n')
        {
            userCommand[strlen(userCommand) - 1] = '\0';
        }
        /**
         * 
         * HANDLE USER INPUT CASES BELOW
         * 
         * */
        if (strstr(userCommand, "RQ"))
        {
           //split and store
            int count = 0;
            int *inputArray = malloc(sizeof(int) * (resource_sum + 1));
            char *token = NULL;
            token = strtok(userCommand, " ");
            while (token != NULL)
            {
                if (count > 0)
                {
                    inputArray[count - 1] = atoi(token);
                }
                token = strtok(NULL, " ");
                count++;
            }
            int customerToAllocate = inputArray[0];
      
            if (customerToAllocate < customer_sum && count == resource_sum + 2)
            {
                for (int g = 0; g < resource_sum; g++)
                {
                    allocate[customerToAllocate][g] = inputArray[g + 1];
                    need_array_array[customerToAllocate][g] = max[customerToAllocate][g] - allocate[customerToAllocate][g];
                    
                    if (need_array[customerToAllocate][g] < 0)
                    {
                        need_array[customerToAllocate][g] = 0;
                    }
               //ERROR CHECKING DONE
			    }
            }
            else
            {
                if (customerToAllocate >= customer_sum)
                {
                    printf("ERROR \n");
                }
                else
                {
                    printf("ERROR TRY AGAIN.\n");
                }
            }
            free(inputArray);
            // ALGORITHM START
            s_array = getS_array();
      
            if (s_array[0] == -1)
            {
                safety_count = 0;
                printf("UNSAFE\n");
            }
            else
            {
                safety_count = 1;
                printf("SAFE\n");
            }
        }
        else if (strstr(userCommand, "RL"))
        {
          
            int count = 0;
            int *inputArray = malloc(sizeof(int) * (resource_sum + 1));
            char *token = NULL;
            token = strtok(userCommand, " ");
            while (token != NULL)
            {
                if (count > 0)
                {
                    inputArray[count - 1] = atoi(token);
                }
                token = strtok(NULL, " ");
                count++;
            }
			 //ensure the tokenize process split get var repeat
			 //inputAray[0];
			 //customerToAllocate = 0;
            int customerToAllocate = inputArray[0];
          


/*
parse second line number of instances of each resource type
fgets (buffer,MAX,fike);
i=0;
we’ll use a tokenizer to split the string on spaces
tmp = strtok(buffer,” “);
while (tmp!= NULL){
Available[i] = atoi(tmp);
tmp = strtok(NULL,” “);
i++;
}

*/

            if (customerToAllocate < customer_sum && count == resource_sum + 2)
            {
                for (int g = 0; g < resource_sum; g++)
                {
                    if (inputArray[g + 1] <= allocate[customerToAllocate][g])
                    {
                        allocate[customerToAllocate][g] -= inputArray[g + 1];
                        need_array[customerToAllocate][g] = max[customerToAllocate][g] - allocate[customerToAllocate][g];
                    }
                    else
                    {
                     
                        break;
                    }
                }
            }
            else
            {
                if (customerToAllocate >= customer_sum)
                {
                    printf("ERROR TRY AGAIN\n");
                }
                else
                {
                    printf("ERROR NUMBER TRY AGAIN.\n");
                }
            }
            free(inputArray);
            
            s_array = getS_array();
       
            if (s_array[0] == -1)
            {
                safety_count = 0;
                printf("UNSAFE");
            }
            else
            {
                safety_count = 1;
                printf("SAFE");
            }
        }
        else if (strstr(userCommand, "*"))
        {
            printf("These are the resources you can use:\n");
            printSinglePointerData(available, resource_sum);
            printf("Max number of resources:\n");
            printDoublePointerData(max, customer_sum, resource_sum);
            printf("These are the resources that have been allocated:\n");
            printDoublePointerData(allocate, customer_sum, resource_sum);
            printf("These are the resources that you need:\n");
            printDoublePointerData(need_array, customer_sum, resource_sum);
        }
        else if (strstr(userCommand, "Run"))
        {
            s_array = getS_array();
            if (safety_count == 1)
            {
                for (int g = 0; g < customer_sum; g++)
                {
                    int threadToRun = s_array[g];
                    pthread_t tid;
                    pthread_attr_t attr;
                    pthread_attr_init(&attr);
                    pthread_create(&tid, &attr, thread_run, (void *)&threadToRun);
                    pthread_join(tid, NULL);
                }
            }
            else
            {
                printf("UNSAFE\n");
            }
        }
        else if (strstr(userCommand, "exit"))
        {
            free(max);
            free(allocate);
            free(need_array);
            free(available);
            free(s_array);
            return 0;
        }
        else
        {
            printf("ERROR TRY AGAIN WITH VALID INPTUS");
        }
    }
    return 0;
}
void *thread_run(void *t)
{
    int *threadId = (int *)t;
    printf("ID", *threadId);
    printf(" Number of resources that are allocated ");
    for (int g = 0; g < resource_sum; g++)
    {
        printf("%d ", allocate[*threadId][g]);
    }
  
    printf(" These are the number of resources that are needed ");
    for (int g = 0; g < resource_sum; g++)
    {
        printf("%d ", need_array[*threadId][g]);
    }
  
    printf(" These are the present resources available");
    for (int g = 0; g < resource_sum; g++)
    {
        printf("%d ", available[g]);
    }

   // Thread Starts
    sleep(1);
  // Thread is finished
    sleep(1);
// thread released
    sleep(1);
// this is what is available in present
    for (int g = 0; g < resource_sum; g++)
    {
        available[g] += allocate[*threadId][g];
        printf("%d ", available[g]);
    }


    sleep(1);
    pthread_exit(NULL);
}
int *getS_array()
{

        int *work = malloc(sizeof(int) * resource_sum);
    int *finished = malloc(sizeof(int) * customer_sum);
	int *s_array = malloc(sizeof(int) * customer_sum);


    for (int g = 0; g < resource_sum; g++)
    {
        work[g] = available[g];
    }
  
    int count = 0;
    while (count < customer_sum)
    {
        int isSafe = 0;
        for (int g = 0; g < customer_sum; g++)
        {
            if (finished[g] == 0)
            {
                int safeIteration = 1;
                for (int y = 0; y < resource_sum; y++)
                {
                    if (need_array[g][y] > work[y])
                    {
                        safeIteration = 0;
                        break;
                    }
                }
                if (safeIteration == 1)
                {
                    s_array[count] = g;
                    finished[g] = 1;
                    count++;
                    isSafe = 1;
                    for (int y = 0; y < resource_sum; y++)
                    {
                        work[y] += allocate[g][y];
                    }
                }
            }
        }

        if (isSafe == 0)
        {
            for (int u = 0; u < customer_sum; u++)
            {
                s_array[u] = -1;
            }
            free(work);
            free(finished);
            return s_array;
        }
		//ERROR CHECKING DISTRIBUTION ENSURE SAFE STATE
    }
    free(work);
    free(finished);
    return s_array;
}


/*
int bankers(){
printf(“BANKERS ALGO”);
// assume the state is unsafe
//add bankers algorithm
int safe = FALSE;
//set up work array
//initialize work array 
int *Work;
if ( !(Work = malloc(resources *sizeof(int) )))
return -1 ;
//copy the Available array into the temporary array
for ( i = 0;i<processes;i++){
//...Finish[i] == FALSEand… 
if (Finish[i] ==FALSE){
//...Need[i] <=Work[j]){
printf(“UNSAFE”);
printResources();
return safe;
}
}
for(j=0;j< resources; j ++) {
Work [j] += Allocation[i][j];
//Finish[j] = TRUE
}
//FIXME; does this go here?
safe = TRUE;
}
}
printf(“distribution as %s\n”, safe?”SAFE”: “UNSAFE”);
printResources();
return safe;
}
*/


void printDoublePointerData(int **data, int m, int n)
{
    for (int g = 0; g < m; g++)
    {
        for (int y = 0; y < n; y++)
        {
            printf("%d", data[g][y]);
            if (y < n - 1)
                printf(" ");
        }
        printf("\n");
    }
}
void printSinglePointerData(int *data, int m)
{
    for (int g = 0; g < m; g++)
    {
        printf("%d", data[g]);
        if (g < m - 1)
            printf(" ");
    }
    printf("\n");
}
int **readFile(char *fileName)
{
    FILE *in = fopen(fileName, "r");
    if (!in)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return NULL;
    }
    struct stat st;
    fstat(fileno(in), &st);
    char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
    fileContent[0] = '\0';
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            strncat(fileContent, line, strlen(line));
        }
    }
    fclose(in);
    char *command = NULL;
    char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
    strcpy(fileCopy, fileContent);
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        customer_sum++;
        command = strtok(NULL, "\r\n");
    }
    strcpy(fileCopy, fileContent);
    char *lines[customer_sum];
    int g = 0;
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        lines[g] = malloc(sizeof(command) * sizeof(char));
        strcpy(lines[g], command);
        g++;
        command = strtok(NULL, "\r\n");
    }
    int **max = malloc(sizeof(int *) * customer_sum);
    for (int y = 0; y < customer_sum; y++)
    {
        int *temp = malloc(sizeof(int) * resource_sum);
        char *token = NULL;
        int u = 0;
        token = strtok(lines[y], ",");
        while (token != NULL)
        {
            temp[u] = atoi(token);
            u++;
            token = strtok(NULL, ",");
        }
        max[y] = temp;
    }
    return max;
}
