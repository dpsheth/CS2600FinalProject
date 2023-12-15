#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>
#include <mosquitto.h>
#include "mosquitto.h"

#define PORT 8080
#define MAX_PATH_LENGTH 1024
#define FILENAME "description.txt"
#define MQTT_BROKER "darshilpsheth.duckdns.org" // Replace with your MQTT broker address
#define MQTT_PORT 1883       // Replace with your MQTT broker port
#define MQTT_TOPIC "game"

// Function prototypes
int mosquitto_lib_init(void);
struct mosquitto *mosquitto_new(const char *id, bool clean_session, void *userdata);
int mosquitto_connect(struct mosquitto *mosq, const char *host, int port, int keepalive);
int mosquitto_publish(struct mosquitto *mosq, int *mid, const char *topic, int payloadlen, const void *payload, int qos, bool retain);
int mosquitto_disconnect(struct mosquitto *mosq);
void mosquitto_destroy(struct mosquitto *mosq);
int mosquitto_lib_cleanup(void);
struct mosquitto *mosq = NULL;

void printContents(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        printf("Contents of '%s':\n", path);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        printf("\n");
        closedir(dir);
    } else {
        printf("Unable to open directory '%s'\n", path);
    }
}

void printDescription(const char *path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Unable to open description.txt in %s\n", path);
    }
}

void sendMQTTMessage(const char *message) {
  mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(message), message, 1, false);
printf("Message \"%s\" published to MQTT topic \"%s\"\n", message, MQTT_TOPIC);
}

void sendDescriptionFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            sendMQTTMessage(buffer);
        }
        fclose(file);
    } else {
        printf("Unable to open description.txt in %s\n", path);
    }
}

int main() {
        pid_t pid, sid;
        pid = fork();

    // If fork fails, exit
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    umask(0);

    // Create a new SID for the child process
    sid = setsid();
    if (sid < 0) {
        perror("SID creation failed");
        exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if ((chdir("/")) < 0) {
        perror("Change directory failed");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int sock;
   struct sockaddr_in server;
    char buffer[128];
    char currentPath[MAX_PATH_LENGTH] = "/home/darshilsheth491/startroom/north";

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Mosquitto setup
    mosquitto_lib_init();
    mosq = mosquitto_new("ExampleClient", true, NULL);
    if (!mosq) {
        fprintf(stderr, "Failed to initialize Mosquitto library\n");
        exit(EXIT_FAILURE);
    }

    if (mosquitto_connect(mosq, MQTT_BROKER, MQTT_PORT, 20) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Failed to connect to the MQTT broker\n");
        exit(EXIT_FAILURE);
    }

   sendDescriptionFile("/home/darshilsheth491/startroom/north/");
 
    while (1) {
char tempPath[MAX_PATH_LENGTH];
        strcpy(tempPath, currentPath);

        memset(buffer, 0, sizeof(buffer));

        // Receive data
        if (recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL) == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        printf("\nReceived message: %s\n", buffer);

        char newPath[MAX_PATH_LENGTH];
        snprintf(newPath, sizeof(newPath), "%s/%s", currentPath, buffer);
        printf("Current path:%s", newPath);

        printContents(newPath);
        // Check for symbolic link 'back'
        char linkPath[PATH_MAX];
        snprintf(linkPath, sizeof(linkPath), "%s/back", newPath);
        if (access(linkPath, F_OK) != -1) {
            // 'back' symbolic link found, navigate into it
            if (chdir(linkPath) == 0) {
                printf("Navigated to '%s'\n", linkPath);
                strcpy(newPath, linkPath);
                DIR *dir = opendir(newPath);
                if (chdir(newPath) == 0) {
                    if (access(FILENAME, F_OK) == 0) {
                        printf("File '%s' found in directory '%s'. Contents:\n", FILENAME, newPath);
                        printDescription(FILENAME);
                        strcpy(currentPath, newPath);
                        sendDescriptionFile(FILENAME); // Send description file to MQTT
                    }
                }
                continue; // Skip further processing in this iteration
            }
        }
        printContents(newPath);

        DIR *dir = opendir(newPath);
        if (dir) {
            closedir(dir);
            if (chdir(newPath) == 0) {
                if (access(FILENAME, F_OK) == 0) {
                    printf("File '%s' found in directory '%s'. Contents:\n", FILENAME, newPath);
                    printDescription(FILENAME);
                    strcpy(currentPath, newPath);
                    sendDescriptionFile(FILENAME); // Send description file to MQTT
                }
            } else {
                printf("You cannot go that way!\n");
                strcpy(newPath, tempPath);
            }
        } else {
            printf("You cannot go that way!\n");
        strcpy(newPath, tempPath);
        }
    }

    // Cleanup and close Mosquitto
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    close(sock);
    return 0;
}
