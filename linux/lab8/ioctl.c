#include "chardev.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

const static int INTERNAL_ERROR = -1;
const static int SUCCESS = 0;
const static int BUFFER_SIZE = 100;

ioctl_set_msg(int fileDescriptor, char * message)
{
  int returnCode = ioctl(fileDescriptor, IOCTL_SET_MSG, message);

  if(returnCode < 0) 
  {
    printf("Error when calling ioctl_set_ms. Return code: %d\n", returnCode);
    exit(INTERNAL_ERROR);
  }
}

ioctl_get_msg(int fileDescriptor)
{
  char message[BUFFER_SIZE];
  int returnCode = ioctl(fileDescriptor, IOCTL_GET_MSG, message);
  if(returnCode < 0) 
  {
    printf("ioctl_get_msg() has failed. Return code: %d\n", returnCode);
    exit(INTERNAL_ERROR);
  }
  printf("The message is: %s\n", message);
}

ioctl_delete_msg(int fileDescriptor)
{
  int returnCode = ioctl(fileDescriptor, IOCTL_DELETE_MSG);
 
  if(returnCode < 0) 
  {
    printf("ioctl_delete_msg has failed. Return code: %d\n", returnCode);
    exit(INTERNAL_ERROR);
  }
}

main(int argc, char * argv[])
{
  static const int ARGUMENTS_NUMBER =2;
  const int fileNameIndex = 1;

  if(argc < ARGUMENTS_NUMBER) 
  {
    printf("There should be %d arguments.\n",ARGUMENTS_NUMBER);
    exit(INTERNAL_ERROR);
  }

  char * fileName = argv[fileNameIndex];

  FILE * msg_file = fopen(fileName, "r+");
  
  if(msg_file == NULL) 
  {
    printf("Couldn't open the file.\n");
    exit(INTERNAL_ERROR);
  }
  
  char str1[BUFFER_SIZE];
  char str2[BUFFER_SIZE];
  char * my_direction = fgets(str1, BUFFER_SIZE, msg_file);
  char * message   = fgets(str2, BUFFER_SIZE, msg_file);
  strcat(my_direction, message);

  fclose(msg_file);
  
  if(strlen(message) > BUFFER_SIZE) 
  {
    printf("The message can't be longer than %d characters.\n", BUFFER_SIZE);
    exit(INTERNAL_ERROR);
  }

  int fileDescriptor = open(DEVICE_FILE_NAME, 0);
  if(fileDescriptor < 0) 
  {
    printf("Error when opening the device file: %s\n", DEVICE_FILE_NAME);
    exit(INTERNAL_ERROR);
  }
  
  ioctl_set_msg(fileDescriptor, my_direction);
  ioctl_get_msg(fileDescriptor);
  ioctl_delete_msg(fileDescriptor);
  close(fileDescriptor);
}
