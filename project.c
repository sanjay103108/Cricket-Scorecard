#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_BATSMEN 11

void createHTML();

int run = 0;
int over = 0;
int ball = 0;
int wicket = 0;

char content[255] = "";

char scoreStr[10];
char wicketStr[10];
char overStr[100];
char ballStr[10];
char runRateStr[6];
char* batsmen[30];
char*batter[30];
int currentBatsman = 0;
int totalBatsman=2;
char newBatsman[100];
char outBatsman[100];

int topOut=-1,topNotOut=-1;

typedef struct {
    int front, rear, size;
    char* array[MAX_BATSMEN];
} CircularQueue;

typedef struct {
    char* array[MAX_BATSMEN];
    int top;
}Stack;

CircularQueue* initializeQueue() {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->front = queue->rear = -1;
    queue->size = 0;
    return queue;
}

int isEmpty(CircularQueue* queue) {
    return queue->size == 0;
}

int isFull(CircularQueue* queue) {
    return queue->size == MAX_BATSMEN;
}

void enqueue(CircularQueue* queue, char* batsman) {
    if (isFull(queue))
        return;

    if (isEmpty(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % MAX_BATSMEN;
    queue->array[queue->rear] = batsman;
    queue->size += 1;
}

char* dequeue(CircularQueue* queue) {
    if (isEmpty(queue))
        return NULL;

    char* batsman = queue->array[queue->front];
    queue->front = (queue->front + 1) % MAX_BATSMEN;
    queue->size -= 1;

    return batsman;
}

Stack* initializeStack() {
    Stack*stack=(Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

int isStackFull(Stack* stack) {
    return stack->top == MAX_BATSMEN - 1;
}

void push(Stack* stack, char* batsman) {
    if (isStackFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = batsman;
}

char* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        exit(0);
    }
    return stack->array[stack->top--];
}

void rotateBatsmen(CircularQueue* queue) {
    if (isEmpty(queue))
        return;

    char* rotatedBatsman = dequeue(queue);
    enqueue(queue, rotatedBatsman);
    currentBatsman = (currentBatsman + 1) % MAX_BATSMEN;
}


// void createHTML() {
//     FILE* pFile = fopen("score.html", "w");
//     fprintf(pFile, "<html><head>");
//     fprintf(pFile, "<link rel='stylesheet' type='text/css' href='styles.css'>");
//     fprintf(pFile, "</head><body>");

//     fprintf(pFile, "<h3>Runs - %s</h3>", scoreStr);
//     fprintf(pFile, "<h3>Overs - %s.%s</h3>", overStr, ballStr);
//     fprintf(pFile, "<h3>Wickets - %s</h3>", wicketStr);
//     fprintf(pFile, "<h3>Run Rate - %s</h3>", runRateStr);
//     fprintf(pFile, "<img src='virat.jpg' alt='Virat Kohli Meme' class='meme'>");
//     fprintf(pFile, "<h3>Batsmen:</h3>");

//     CircularQueue* batsmenQueue = initializeQueue();
//     CircularQueue* printbatsmen=initializeQueue();
//     for (int i = 0; i < MAX_BATSMEN; i++) {
//         enqueue(batsmenQueue, batsmen[i]);
//         enqueue(printbatsmen,batsmen[i]);
//     }

//     int index = currentBatsman;
//     for (int i = 0; i < MAX_BATSMEN; i++) {
//         if (index == MAX_BATSMEN) {
//             index = 0;
//         }
//         if (index == currentBatsman) {
//             fprintf(pFile, "<p><b>%s</b></p>", printbatsmen->array[index]);
//         } else {
//             fprintf(pFile, "<p>%s</p>",printbatsmen->array[index]);
//         }
//         index++;
//     }
//     fprintf(pFile, "</body></html>");
//     fclose(pFile);
//     free(printbatsmen); // Free the allocated memory
// }

void createHTML() {
    FILE* pFile = fopen("score.html", "w");
    fprintf(pFile, "<html><head>");
    fprintf(pFile, "<link rel='stylesheet' type='text/css' href='styles.css'>");
    fprintf(pFile, "</head><body>");

    fprintf(pFile, "<h3>Runs - %s</h3>", scoreStr);
    fprintf(pFile, "<h3>Overs - %s.%s</h3>", overStr, ballStr);
    fprintf(pFile, "<h3>Wickets - %s</h3>", wicketStr);
    fprintf(pFile, "<h3>Run Rate - %s</h3>", runRateStr);
    fprintf(pFile, "<img src='virat.jpg' alt='Virat Kohli Meme' class='meme'>");
    fprintf(pFile, "<h3>Batsmen:</h3>");

    // Loop to print all the players who have batted
    for (int i = 0; i <totalBatsman; i++) {
        if (batsmen[i] != NULL) {
            if(i==currentBatsman)
            {
                fprintf(pFile, "<p><b>%s</b></p>", batsmen[i]);
            }
            else
            {
                fprintf(pFile, "<p>%s</p>", batsmen[i]);
            }
        }
    }

    fprintf(pFile, "</body></html>");
    fclose(pFile);
}


int main()
{
	int score;
    batsmen[0] = "Rohit Sharma";
    batsmen[1] = "Shubman Gill";
	CircularQueue* batsmenQueue = initializeQueue();
    CircularQueue* printbatsmen=initializeQueue();
    Stack* notOutBatsmen = initializeStack();
    Stack*OutBatsmen=initializeStack();
    currentBatsman = 0;

    for (int i = 0; i <2; i++) 
	{
        enqueue(batsmenQueue, batsmen[i]);
        enqueue(printbatsmen,batsmen[i]);
    }
    batsmen[2] = "Virat Kohli";
    batsmen[3] = "Shreyas Iyer";
    batsmen[4] = "K L Rahul";
    batsmen[5] = "SuryaKumar Yadav";
    batsmen[6] = "Ravindra Jadeja";
    batsmen[7] = "Kuldeep Yadav";
    batsmen[8] = "Jasprit Bumrah";
    batsmen[9] = "Mohammed Shami";
    batsmen[10] = "Mohammed Siraj";
    for(int i=10;i>=2;i--)
    {
        push(notOutBatsmen,batter[i]);
    }
	
	while(1){
		printf("\nEnter Score : ");
		scanf("%d", &score);
		getchar();
		  if (ball == 6) 
		{
            rotateBatsmen(batsmenQueue);
            ball = 0; 
        }
		switch(score){
			case 0 : {
				char dot;
				printf("Enter Type of Dot Ball\n");
				printf("'W' for a wicket\n'D' for a Dot Ball\n");
				scanf(" %c", &dot);
				switch(dot){
					case 'W':{
						wicket += 1;
						ball += 1;
						printf("Wicket\n");
						char*outBatmen= dequeue(batsmenQueue);
                        char* newBatsman = pop(notOutBatsmen);
                        enqueue(batsmenQueue, newBatsman);
						enqueue(printbatsmen,newBatsman);
                        totalBatsman += 1;
						break;
					}
					case 'D': {
						ball += 1;
						printf("Dot ball\n");
						break;
					}
				}
				break;
			}
			
			case 1: {
				char single;
				printf("Enter the type of single taken\n");
				printf("'S' for a Single\n'W' for a wide ball\n'N' for a No Ball\n'R' for a Run out\n");
				scanf("%c", &single);
				switch(single){
					case 'S': {
						run += 1;
						ball += 1;
						printf("Rotating the strike\n");
                        rotateBatsmen(batsmenQueue);
						break;
					}
					case 'W': {
						run += 1;
						printf("Wide ball\n");
						break;
					}
					case 'N': {
						run += 1;
						printf("No ball, Free hit\n");	
						break;
					}
					case 'R': {
						run += 1;
						ball += 1;
						wicket -= 1;
						printf("Wicket gone\n");	
						char*outBatsman=dequeue(batsmenQueue);
                        push(OutBatsmen,outBatsman);
                        char* newBatsman = pop(notOutBatsmen);
                        enqueue(batsmenQueue, newBatsman);
						enqueue(printbatsmen,newBatsman);
                        totalBatsman += 1;
						break;
					}

					default:
						printf("Invalid Input\n");
				}
				
				break;
			}
			case 2:{
				char doubles;
				printf("Enter the type of double taken\n");
				printf("'D' for a Double\n'W' for a wide ball\n'N' for a No Ball\n'R' for a Run out\n");
				scanf("%c", &doubles);
				switch(doubles){
					case 'D': {
						run += 2;
						ball += 1;   
						break;
					}
					case 'W': {
						run += 2;
	
						printf("Wide ball\n");
						break;
					}
					case 'N': {
						run += 2;
						ball -= 1;
						printf("No ball, Free hit\n");	
						break;
					}
					case 'R': {
						run += 2;
						ball += 1;
						wicket += 1;
						printf("Wicket gone\n");	
						char*outBatsman=dequeue(batsmenQueue);
                        push(OutBatsmen,outBatsman);
                        char* newBatsman = pop(notOutBatsmen);
                        enqueue(batsmenQueue, newBatsman);
						enqueue(printbatsmen,newBatsman);
                        totalBatsman+= 1;
						break;
					}

					default:
						printf("Invalid Input\n");
				}
				
				break;
			}
			case 3:{
				char triple;
				printf("Enter the type of triple taken\n");
				printf("'T' for a Triple\n'W' for a wide ball\n'N' for a No Ball\n'R' for a Run out\n");
				scanf("%c", &triple);
				switch(triple){
					case 'T': {
						run += 3;
						ball += 1;
						printf("Rotating the strike\n");
                        rotateBatsmen(batsmenQueue);
						break;
					}
					case 'W': {
						run += 3;
						printf("Wide ball\n");
						break;
					}
					case 'N': {
						run += 3;
						ball -= 1;
						printf("No ball, Free hit\n");	
						break;
					}
					case 'R': {
						run += 3;
						ball += 1;
						wicket += 1;
						printf("Wicket gone\n");	
						char*outBatsman=dequeue(batsmenQueue);
                        push(OutBatsmen,outBatsman);
                        char* newBatsman = pop(notOutBatsmen);
                        enqueue(batsmenQueue, newBatsman);
						enqueue(printbatsmen,newBatsman);
                        totalBatsman += 1;
						break;
					}

					default:
						printf("Invalid Input\n");
				}
				
				break;
			}
			case 4:{
				char boundary;
				printf("Enter the type of boundary taken\n");
				printf("'B' for a Boundary\n'W' for a wide ball\n'N' for a No Ball\n'R' for a Run out\n");
				scanf("%c", &boundary);
				switch(boundary){
					case 'B': {
						run += 4;
						ball += 1;
						printf("It's a four\n");
						break;
					}

					default:
						printf("Invalid Input\n");
				}

				break;
			}
			case 5:{
				char fiver;
				printf("Enter the type of fiver taken\n");
				printf("'W' for a wide ball\n'N' for a No Ball\n");
				scanf("%c", &fiver);
				switch(fiver){
					case 'W': {
						run += 5;
						printf("Wide ball and a four\n");
						break;
					}
					case 'N': {
						run += 5;
						ball -= 1;
						printf("No ball, Free hit and a four\n");	
						break;
					}
					
					default:
						printf("Invalid Input\n");
				}
				
				break;
			}
			case 6:{
				char sixer;
				printf("Enter the type of sixer taken\n");
				printf("'S' for a Sixer\n");
				scanf("%c", &sixer);
				switch(sixer){
					case 'S': {
						run += 6;
						ball += 1;
						printf("It's a Six\n");
						break;
					}
					default:
						printf("Invalid Input\n");
				}
				break;
			}
			
			
			case -1:{
				exit(1);
				break;
			}
			
			default:{
				printf("This is an invalid input\n");		
			}
		}
		
		itoa(run, scoreStr, 10);
		itoa(wicket, wicketStr, 10);
		itoa(over, overStr, 10);
		itoa(ball, ballStr, 10);

        float runRate = (float)run / (over + (float)ball / 6);
        sprintf(runRateStr, "%.2f", runRate);
		
		strcat(content, "Runs - ");
		strcat(content, scoreStr);
		strcat(content, "\n");
		strcat(content, "Wickets - ");
		strcat(content, wicketStr);
		strcat(content, "\n");
		strcat(content, "Overs - ");
		strcat(content, overStr);
		strcat(content, ".");
		strcat(content, ballStr);
		strcat(content, "\n");
        strcat(content, runRateStr);
		
		createHTML();
		
		if(ball == 6){
			over += 1;
			ball = 0;
		}
		
		if(wicket == 10){
			printf("Innings Ended");
			break;	
		}
		
		if(over == 2){
			printf("Innings Ended");

			break;
		}
		
		strcpy(content, "");
        
	}
    free(notOutBatsmen);
    return 0;
}