#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// struct that stores letters and count
struct LetterCount
{
    char letter;
    int count;
} 
LetterCount;

// Function that updates the letter count
void updateCount(struct LetterCount count[], char c)
{
    if(isalpha(c)){
        c = tolower(c); //counts lower and uppercase as the same
        int y = c - 'a'; //
        count[y].count++;
    }

}
int main()
{
    // accesses file and displays letter count
   FILE *fptr;
   fptr = fopen("alice.txt", "r");
   if(fptr == NULL){
    printf("Error: Could not open file.\n");
    return 1; //Show if there is an error in opening file
   }
   LetterCount count[ALPHABET_SIZE];
   for(int i = 0; i < ALPHABET_SIZE; i++){
    count[i].letter = 'a'+ i;
    count[i].count = 0;
   }
   int c;
   while((c = fgetc(fptr)) != EOF){
    updateCount(count,c);
   }
   fclose(fptr);

   for(int i = 0; i < ALPHABET_SIZE; i++){
    printf("%c: %d\n", count[i].letter, count[i].count);
   }
   return 0;
   }