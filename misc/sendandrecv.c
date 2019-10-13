// void recv_file()
// {
//     char buffer[256];
//     int file_size;
//     FILE *received_file;
//     int remain_data = 0;
//     ssize_t len;

//      /* Receiving file size */
//     recv(cli_addr,buffer, 256, 0);
//     file_size = atoi(buffer);
//     //fprintf(stdout, "\nFile size : %d\n", file_size);

//     received_file = fopen(FILENAME, "w");
//     if (received_file == NULL)
//     {
//             fprintf(stderr, "Failed to open file foo --> %s\n", strerror(errno));

//             exit(EXIT_FAILURE);
//     }

//     remain_data = file_size;

//     while ((remain_data > 0) && ((len = recv(cli_addr, buffer, 256, 0)) > 0))
//     {
//             fwrite(buffer, sizeof(char), len, received_file);
//             remain_data -= len;
//             fprintf(stdout, "Receive %d bytes and we hope :- %d bytes\n", len, remain_data);
//     }
//     fclose(received_file);
// }



// void send_file()
// {

//         int fd;
//         int sent_bytes = 0;
//         char file_size[256];
//         struct stat file_stat;
//         int offset;
//         int remain_data;

//         /* Declaring File pointer */

//         fd = open(FILE_TO_SEND, O_RDONLY);
//         if (fd == -1)
//         {
//                 fprintf(stderr, "Error opening file --> %s", strerror(errno));

//                 exit(EXIT_FAILURE);
//         }

//         /* Sending file size */

//         sprintf(file_size, "%d", file_stat.st_size);

//         send(server, file_size, sizeof(file_size), 0);
//         if (len < 0)
//         {
//               fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));

//               exit(EXIT_FAILURE);
//         }

//         offset = 0;
//         remain_data = file_stat.st_size;

//         /* Sending file data */
//         while (((sent_bytes = sendfile(server, fd, &offset, BUFSIZ)) > 0) && (remain_data > 0))
//         {
//                 fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
//                 remain_data -= sent_bytes;
//                 fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
//         }
// }