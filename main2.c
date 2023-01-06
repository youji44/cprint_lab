
/* main2.c file
 * Template file for the solution to part 2
 * Use the included print statements in your code at appropriate times.
 * Do not adjust the format of the print statements.
 * Do not submit a final solution with additional print statements.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define calculating average values
int get_average(int * grades,int len);
// define correcting grade values
int correcting_grade(int student_id, int grade, int th);

// main function
// print and writing output file
int main( int argc, char **argv ) {

  // command line arguments
  char* input_filename;
  int i_student_id = 0;
  int i_len;
  
  int* i_grades = malloc(sizeof(int));
  // checking command line arguments
  if(argc == 2 || argc == 3){

    input_filename = argv[argc-1];

  }else if( argc > 3 || argc < 13) {

    input_filename = argv[argc-1];
    sscanf(argv[1], "%d", &i_student_id);

    for (int i = 2; i < argc-1; i++)
    {
      i_len++;
      int tmp;
      sscanf(argv[i], "%d", &tmp);
      i_grades[i - 2] = correcting_grade(i_student_id, tmp, i - 1);
    }
  }
  else {
    printf("Arguments is needed. Exiting.\n");
    exit(0);
  }

  // reading from file
  printf("Input file. Opening.\n");
  FILE* input_file;
  input_file = fopen(input_filename, "r");

  // writing to file
  printf("Output file. Opening.\n");
  FILE* output_file;
  output_file = fopen("averages.txt","w+");

  if (NULL == input_file) {
      printf("Input file does not exist. Exiting.\n");
      exit(0);
  }

  if (output_file == NULL)
  {
      printf("Error opening the average.txt file\n");
      exit(0);
  }

  // writing for the inputted values
  // writing into average.txt file with student id
  if(argc > 3){
    if(i_student_id < 2022000 || i_student_id > 2022099){
      //printf("Student_id value should be 2022000 ~ 2022099\n"); 
      printf("Found an invalid student id: %d. Exiting.\n",i_student_id); 
      exit(0);
    }
    fprintf(output_file,"%d ",i_student_id);
    fprintf(output_file,"%d\n", get_average(i_grades, i_len));
  }
  free(i_grades);

  // character by character using loop.
  char line[256];

  while (fgets(line, sizeof(line), input_file) != NULL)
  {
    // student id value
    char *student_data = strtok(line, " ");
    int student_id;
    // convert char * to int
    sscanf(student_data, "%d", &student_id);

    // checking avaibable value for student id
    // requires student id
    printf("Checking data.\n");
    if(student_id < 2022000 || student_id > 2022099){
      //printf("Student_id value should be 2022000 ~ 2022099\n"); 
      printf("Found an invalid student id: %d. Exiting.\n",student_id); 
      exit(0);
    }

    // writing into average.txt file with student id
    fprintf(output_file,"%s ",student_data);

    // grade values 
    student_data = strtok(NULL, " ");
    int count = 0;   
    // compute averages
    printf("Computing averages.\n");

    int* grades = malloc(sizeof(int));
  
    while (student_data != NULL)
    {
      // calculate the average grade
      int grade;
      count++;
      // convert char * to int
      sscanf(student_data, "%d", &grade);
    
      grades[count-1] = correcting_grade(student_id, grade, count);;
      
      // get next grade values in a line
      student_data = strtok(NULL, " ");
    }

    int average = get_average(grades,count);
   
    // writing into average.txt file with average value
    fprintf(output_file, "%d\n",average);
    free(grades);
  }
  
  // Closing the file
  printf("Input file. Closing.\n");
  fclose(input_file);
  
  printf("Output file. Closing.\n");
  fclose(output_file);

  return 0;
}

// Get average value function with rounded feature
int get_average(int* grades, int len){

  int sum;
  int average;
  // calculating sum with grades
  for (int i = 0; i < len; i++)
  {
    sum += grades[i];
  }

  float f_avg = (float)sum / len;
  int i_avg = (int)f_avg;
  average = i_avg;
  
  // Rounded average value with integer value
  // Round Rule: (grade < g+0.5) = g, (grade >= g+0.5) = g+1
  if(f_avg < i_avg + 0.5){ 
    average = i_avg;
  }else if(f_avg >= i_avg + 0.5) {
    average = i_avg + 1;
  }
  return average;
}

// checking grade values and print errors
int correcting_grade(int student_id, int grade, int th){

  // checking for available value for grade
  // requires student id and relevant grade

  if(grade < 0 || grade > 100){
    //printf("Grade values should be 0 ~ 100");
    printf("Found an invalid grade: id %d grade %d. Exiting.\n", th, grade);
    exit(0);
  }

  // Constraints for Any grade
  if(grade < 20) {
    printf("Correcting student %d grade %d\n",student_id,grade);
    grade = 20;
    
  }
  else if(grade > 90) {
    printf("Correcting student %d grade %d\n",student_id,grade);
    grade = 90;
  }
  return grade;
}
