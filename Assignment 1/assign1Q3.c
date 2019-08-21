
/** @file assign1.c
 */


#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/** @brief This function removes the particular shades
  * from all the pixels of image
	*
	* @param intensity_of_red_colour
  * @param intensity_of_green_colour
  * @param intensity_of_blue_colour
  * @param choice_of_colour_to_be_deleted
  * @param total_no_of_pixels
	*
	* @return nothing
	*/
void remove(int* redArray, int* greenArray, int* blueArray, int choice, int size) {
        for(int i=0;i<size;i++){
            if(choice == 1){
                if(redArray[i] > greenArray[i] && redArray[i] > blueArray[i]){
                    redArray[i] = 0;
                }
            }else if(choice == 2){
                if(greenArray[i] > redArray[i] && greenArray[i] > blueArray[i]){
                    greenArray[i] = 0;
                }
            }else if(choice == 3){
                if(blueArray[i] > redArray[i] && blueArray[i] > greenArray[i]){
                    blueArray[i] = 0;
                }
            }else{
                printf("Invalid Choice!!!\n");
            }
        }
}

/** @brief This function preserves the particular shades
  * from all the pixels of image but remove all
  * other shades
	*
	* @param intensity_of_red_colour
  * @param intensity_of_green_colour
  * @param intensity_of_blue_colour
  * @param choice_of_colour_to_be_deleted
  * @param total_no_of_pixels
	*
	* @return nothing
	*/
void preserve(int* redArray, int* greenArray, int* blueArray, int choice, int size) {
    for(int i=0;i<size;i++){
            if(choice == 1){
                if(greenArray[i] > redArray[i] && greenArray[i] > blueArray[i]){
                    greenArray[i] = 0;
                }
                if(blueArray[i] > redArray[i] && blueArray[i] > greenArray[i]){
                    blueArray[i] = 0;
                }
            }else if(choice == 2){
                if(redArray[i] > greenArray[i] && redArray[i] > blueArray[i]){
                    redArray[i] = 0;
                }
                if(blueArray[i] > redArray[i] && blueArray[i] > greenArray[i]){
                    blueArray[i] = 0;
                }
            }else if(choice == 3){
                if(redArray[i] > greenArray[i] && redArray[i] > blueArray[i]){
                    redArray[i] = 0;
                }
                if(greenArray[i] > redArray[i] && greenArray[i] > blueArray[i]){
                    greenArray[i] = 0;
                }
            }else{
                printf("Invalid Choice!!!\n");
            }
        }
}

/** @brief This function prints the intensity of colours
  * at a particular pixel
	*
  * @param intensity_of_red_colour
  * @param intensity_of_green_colour
  * @param intensity_of_blue_colour
  * @param height
  * @param width
  * @param row_of_particular_pixel
  * @param column_of_particular_pixel
	*
	* @return nothing
	*/
void printPixel(int* redArray, int* greenArray, int* blueArray, int height, int width, int x, int y){
  if(((x-1) < height) && ((y-1) < width)){
    int index = (x-1)*(width) + (y-1);
    printf("Blue Pixel value: %d\n", blueArray[index]);
    printf("Green Pixel value: %d\n", greenArray[index]);
    printf("Red Pixel value: %d\n", redArray[index]);
    printf("\n");
  }else{
    printf("Enter proper pixel values!!!\n");
  }

}

/** @brief This is the main function of the program.
	* In this function, we are retriving the intensities of red, blue and green from
  * the input files given and are performing different actions like removing, preserving
  * and printing the pixel value.
	*/
int main() {

    int width, height, channels;
    stbi_info("Q3_ip.jpg", &width, &height, &channels);
    int size = width*height;

    int *ipBlueArr = (int*) malloc(sizeof(int)*size);
    int *ipGreenArr = (int*) malloc(sizeof(int)*size);
    int *ipRedArr = (int*) malloc(sizeof(int)*size);

    FILE *blueFile = fopen("Q3_ip_Blue.dat", "r");
    FILE *greenFile = fopen("Q3_ip_Green.dat", "r");
    FILE *redFile = fopen("Q3_ip_Red.dat", "r");

    if(blueFile == NULL){
        printf("Error loading file\n");
        exit(0);
    }

    if(greenFile == NULL){
        printf("Error loading file\n");
        exit(0);
    }

    if(redFile == NULL){
        printf("Error loading file\n");
        exit(0);
    }


    for(int i=0;i<size-1;++i){
        fscanf(blueFile, "%d,", &ipBlueArr[i]);
    }

    fscanf(blueFile, "%d,", &ipBlueArr[size-1]);
    fclose(blueFile);

    for(int i=0;i<size-1;++i){
        fscanf(greenFile, "%d,", &ipGreenArr[i]);
    }

    fscanf(greenFile, "%d,", &ipGreenArr[size-1]);
    fclose(greenFile);

    for(int i=0;i<size-1;++i){
        fscanf(redFile, "%d,", &ipRedArr[i]);
    }

    fscanf(redFile, "%d,", &ipRedArr[size-1]);
    fclose(redFile);


    while(1){
      printf("Enter 1 for removing\n");
      printf("Enter 2 for preserving\n");
      printf("Enter 3 for printing the value at particular pixel\n");
      printf("Enter 4 to terminate the program\n");
      int choice1;
      scanf("%d", &choice1);
      int choice = 0;
      if(choice1 == 1){
          printf("Enter the value for the shade to be removed\n");
          printf("Enter 1 for red\n");
          printf("Enter 2 for green\n");
          printf("Enter 3 for blue\n");
          scanf("%d", &choice);
          printf("\n");

          remove(ipRedArr, ipGreenArr, ipBlueArr, choice, size);
      }else if(choice1 == 2){
          printf("Enter the value for the shade to be preserved\n");
          printf("Enter 1 for red\n");
          printf("Enter 2 for green\n");
          printf("Enter 3 for blue\n");
          scanf("%d", &choice);
          printf("\n");

          preserve(ipRedArr, ipGreenArr, ipBlueArr, choice, size);
      }else if(choice1 == 3){
        int x,y;
        printf("Enter the pixel row index\n");
        scanf("%d", &x);
        printf("Enter the pixel column index\n");
        scanf("%d", &y);
        printf("\n");

        printPixel(ipRedArr, ipGreenArr, ipBlueArr, height, width, x, y);
      }else if(choice1 == 4){
        break;
      }else{
          printf("Enter valid option!!!!\n");
      }
    }
}
