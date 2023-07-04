#pragma once
#include "Database.h"
#include <string>
#ifndef __APPLE__
#include <wait.h>
#endif
#define PORT 3000
#define MAX_THREADS 100
#define MAX_USERS 50
#define NO_DEFINED_PROTOCOL 0
#define MAX_CLIENTS_IN_QUEUE 10
#define MAXSTRLEN 256

/**
 * @brief  Enum containing report ids, used for readability.  
*/
enum reports{
    socketError, bindError, listenError, acceptError,
    serverPortWait, threadMessageWait, threadReadError,
    threadReadSuccess,threadWriteNotify,threadWriteError,
    threadWriteSuccess, threadLogonSuccessful, threadLogonFailCapacity,
    threadLogonFailLoggedIn, threadLogonTimedout
};

/*
    Container for specialized user stats updating thread structure
*/
namespace statusThread
{
    /*
        Structure used by specialized user stats thread

        [Mandatory] (char*) username = the username whose file will be accessed
        [Mandatory] (DBResult*) bookInfo = the book the user has just downloaded, will be used to update the user stats
    */
    struct statusThreadInfo
    {
        //the username whose file will be accessed
        char *username;
        //the book the user has just downloaded, will be used to update the user stats
        DBResult* bookInfo;
    };
};

/**
 * @brief Main Server Class
 * 
 */
class Server
{
    private:
        /*
            Structure containing thread id and linked client descriptor

            [Mandatory] (int) idThread = index of the thread
            [Mandatory] (int) clientDescriptor = the socket descriptor of the communication channel
            [Optional] (Server*) parentServer = address of the creator thread. Used to call functions that belong to the server (i.e. ReportLog())
            [Optional] (char*) linkedUser = name of the user the thread will be connected to. Used for reports, as ReportLog() can also log the user that wrote a specific command
        */

        struct thData
        {
            //index of the thread
            int idThread;
            //the socket descriptor of the communication channel
            int clientDescriptor;
            //address of the creator thread. Used to call functions that belong to the server (i.e. ReportLog())
            Server* parentServer;
            //linkedUser = name of the user the thread will be connected to. Used for reports, as ReportLog() can also log the user that wrote a specific command
            char * linkedUser;
        };
        
        //Array containing strings, each containing the name of a connected user.
        char** loggedUsers;

        //String containing the name of the log file.
        char * logName{nullptr};

        //Number of users connected to the server at this time.
        int nLoggedUsers;

        //The active server port. Needs to be the same for the connecting client.
        int serverPort;

        //The descriptor that will be passed to the clients needed for communication
        int socketDescriptor;

        //The descriptor of the log file
        int logFile{0};

        //Maximum number of book entries that can be sent to the requesting user.
        int maxEntries;

        //Address to the array containing the query entries resulted from the user's filter
        DBResult *sentInfo;
        
        //Array containing information on each thread that the server creates (pthread_t *). Used to kill/join attached threads
        pthread_t *threads;

        //Externally declared structure containing server IP, port, protocol family 
        sockaddr_in serverInfo;
        
        //Externally declared structure containing client IP, port, protocol family. Used to compare client connect information to server sockaddr_in structure
        sockaddr_in receivedInfo;

        /**
         * @brief Function called upon user disconnection
         * 
         * Removes the username of the user that has just disconnected from the server's connected users list
         * 
         * @param username string containing the name of the user who has just disconnected
         */
        void DisconnectUser(const char *);

        /**
         * @brief Prints query results from database in a readable format on the debug console
         * 
         *  [Optional]
         * [Debug function]
         * format is :
         * title:
         * author:
         * genre:
         * year:
         * rating:
         * ISBN:
         * 
         * @param array address to thr array containing the query entries from the filter application
         * @param length length of the array given through the array address
        */
        void PrintResults(DBResult*, const int &);

        /**
         * @brief Thread main() function
         *
         * It is called upon creating a new thread (pthread_create() argument 3), passing this as their main function, named Init in this context (ThreadINITcall)
         * 
         * Parameter is type void*, as it is the next argument in the pthread_create() function, will contain the address to the parameters given to the thread
         * through the thData structure. It will need to be casted back to thData in the function to properly use the parameter and copied into a local thread
         * variable as it is declared originally in Server, thus it is a shared resource
         * 
         * Function is static so that threads do not have to open another executable, just copy it from RAM
         * 
         * @param arg uncasted (void*) address to the parameters passed to the newly created thread
         */
        static void* ThreadInitCall(void*);

        /**
         * @brief Thread runtime function
         * 
         * It treats clients' requests past the login (only enters this function upon a successful login).
         * 
         * Parameter is no longer void*, it is a thData, as it will not be modified, so it must be casted before the function.
         *
         * @param threadDataLocal copy of the local variables passed onto the thread from the server
         */
        void ThreadRuntime(thData);

        /**
         * @brief Thread function called to treat the login protocol with the linked client (bootstrap)
         * 
         * Argument remains void* so that the original argument can be modified to contain the user that is connected to the thread, if the login protocol is
         * successful. On failure, the structure will remain unmodified.
         * 
         * returns true if the client succesfully logged in, otherwise returns false
         * 
         * @param arg address to the thread's local variables
         * 
         * @return Returns true upon user's successful login, false otherwise (crash, connection lost)
         */
        bool ThreadLoginBootstrap(void*);

        /**
         * @brief Function treating the vailidity of a login protocol, precisely whether the user is already logged in or not
         * 
         * Parameter is a char*, an address to the string containing the name of the used that attempts to log on
         * 
         * Returns true if the user is not logged in at the time, false otherwise
         * 
         * @param username the string containing the name of the user to be checked if logged in
         * 
         * @return Returns true if the user is already logged in, false otherwise
         */
        bool isUserLoggedIn(const char*);


        /**
         * @brief Function checking whether the user application linked to the thread is timed out or not
         * 
         * Will create a timeout if one does not exist, or return its' status otherwise
         * 
         * @param startDate string containing the date of when the timeout has started
         * @param seconds int containing the duration of the timeout, in seconds
         * @param secondsLeft refference to an int through which the remaining timeout seconds are returned
         * 
         * @return Returns whether or not the timeout has ended, true if yes, false otherwise
         */
        bool ThreadTimeout(const char*, const int&, int&);

        /**
         * @brief Function called to create the log file [Optional]
         * 
         * Created log file is in the following naming format:
         * log:[hour]-[minute][second]<->[day]:[month]:[year].txt
         * 
         * returns the descriptor of the log file.
        */
        int CreateLog();

        /**
         * @brief Function called to get the date given in seconds
         * 
         * @param givenDate string containing the date given
         * 
         * @return Returns the date in seconds
         */
        int GetDateInSeconds(const char*);

        /**
         * @brief  Writes a log line (this->logFile), if it exists. [Requires CreateLog()] [Optional]
         * 
         * Can be called from thread (outside the server class).
         * 
         * @param logId identifies the report, see enum reports;
         * @param threadId contains the id of the thread in which is is called
         * @param userId contains the name of the user to which the thread is connected to at the time of the function call
        */
        void ReportLog(const int  = -1,const int  = 0, const char* = nullptr);

        /**
         * @brief Function called to add the recently requested book to the user's stats
         * 
         * Function will create another thread so as to not interfere with the current thread's runtime
         * 
         * @param bookInfo address to the given book information
         * @param username strinng containing the username of the user that requested the book
         */
        void AddToStats(DBResult*, char*);

    public:

        /**
         * @brief Constructor of the Server object.
         * 
         * @param givenPort int, optional, only use if starting server on another port. Default is 3000 
         */
        Server(const int& = PORT);

        /**
         * @brief Function returns the server's current local time and date.
         * 
         * Used in CreateLog(), ReportLog(),...
         * 
         * @return Returns an address to the static string containing the time and date.
         */
        char *GetLocaltime();

        /**
         * @brief Function that treats the server initialisation
         * 
         * Sets up the required structures and procedures for internet connection. (socket, bind, listen)
         */
        void Init();

        /**
         * @brief Prints the names of the users that are logged in at the time of the function call [Optional] [Debug function]
         */
        void PrintLoggedUsers();

        /**
         * @brief Main server runtime, loop treating client connections and thread creation.
         */
        void Runtime();

        /**
         * @brief Server destructor
         */
        ~Server();
};

/**
 * @brief Specialised Thread start routine (a thread that will add an entry to a user's data)
 * 
 * @param argument uncasted (void*) address to the structure containing the information that the thread requires
 */
void* specialisedThreadStatusAdd(void*);

/**
 * @brief Function that returns an address to the user's data file
 * 
 * @param filePath string containing the relative path of the user file
 * 
 * @return FILE address pointing to the opened file
 */
FILE* getStatsFile(const char * );

void Server::DisconnectUser(const char* username)
{
    int index = 0;
    for(;index<this->nLoggedUsers;index++)
    {
        if(!strcmp(*(this->loggedUsers+index), username))
            break;
    }
    free(*(this->loggedUsers + index));
    for(; index < this->nLoggedUsers-1; index++)
        *(this->loggedUsers + index) = *(this->loggedUsers + index + 1);
    *(this->loggedUsers + nLoggedUsers-1) = nullptr;
    this->nLoggedUsers--;
}

void Server::PrintResults(DBResult* array, const int& length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("Title: %s\nAuthor: %s\nGenre: %s\nYear: %d\nRating: %d\nISBN: %d\n",
            array[i].bookName, array[i].authorName, array[i].genre, array[i].year, array[i].rating,
            array[i].ISBN);
    }
    
}

FILE* getStatsFile(const char * filePath)
{
    FILE* returnedFile;
    struct stat st;
    if( -1 == stat(filePath, &st) )
    {
        returnedFile = fopen(filePath, "w+");
        fprintf(returnedFile, "[\n\t{\n\t}\n]\n");
        fflush(returnedFile);
        return returnedFile;
    }
    returnedFile = fopen(filePath, "r+");
    return returnedFile;
}

void* specialisedThreadStatusAdd(void* argument)
{
    statusThread::statusThreadInfo locals = *((statusThread::statusThreadInfo*)argument);

    struct stat st;

    std::string statsFilePath = std::string(std::string("../src/Server/data/userStats") );

    if( -1 == stat( statsFilePath.c_str(), &st ) )
    {
        mkdir( statsFilePath.c_str(), 0700 );
    }

    statsFilePath += "/" + std::string(locals.username) + ".json";

    FILE* statsFile = getStatsFile(statsFilePath.c_str());

    char *readBuffer = (char*)malloc(65536);
    memset(readBuffer, 0, 65536);

    fread(readBuffer, 65536, 1, statsFile);

    if(strstr(readBuffer, locals.bookInfo->bookName))
    {
        fclose(statsFile);
        free(readBuffer);
        return NULL;
    }
    free(readBuffer);
    
    fseek(statsFile, -3, SEEK_END);

    char* writeBuffer = (char*)malloc(512);
    memset(writeBuffer,0,512);

    sprintf(writeBuffer, ",\n\t{\n\t\t\"title\" : \"%s\",\n\t\t\"author\" : \"%s\",\n\t\t\"genre\" : \"%s\"\n\t}\n]\n", locals.bookInfo->bookName,locals.bookInfo->authorName, locals.bookInfo->genre);

    free(writeBuffer);
    fclose(statsFile);

    pthread_cancel(pthread_self());
}

void Server::AddToStats(DBResult* bookInfo, char* username)
{
    pthread_t threadIdentifier = 0;
    statusThread::statusThreadInfo *parameter = (statusThread::statusThreadInfo*)malloc(sizeof(statusThread::statusThreadInfo));
    parameter->bookInfo = (DBResult*)malloc(sizeof(DBResult));
    parameter->username = (char*)malloc(256);

    strcpy(parameter->username, username);
    parameter->bookInfo = bookInfo;

    pthread_create(&threadIdentifier, NULL, specialisedThreadStatusAdd, (void*)parameter);
}

void Server::ThreadRuntime(thData threadDataLocal)
{
    int maxEntries = 0;
    DBFilter userFilter;
    userFilter.authorName = (char*)malloc(128);
    userFilter.bookName = (char*)malloc(128);
    char *request = (char*)malloc(1024);
    while(true)
    {
        memset(request, 0, 1024);
        if( 0 > read(threadDataLocal.clientDescriptor, request, 1024) )
            this->ReportLog(threadReadError, threadDataLocal.idThread, threadDataLocal.linkedUser);
        if(!strcmp(request, "CLIENTEVENTQUIT"))
        {
            this->DisconnectUser(threadDataLocal.linkedUser);
            break;
        }
        if(!strcmp(request, "CLIENTEVENTDISC"))
        {
            this->DisconnectUser(threadDataLocal.linkedUser);
            break;
        }
        if(!strcmp(request, "CLIENTEVENTQUER"))
        {
            if( 0 > read(threadDataLocal.clientDescriptor, request, 1024) )
                this->ReportLog(threadReadError, threadDataLocal.idThread, threadDataLocal.linkedUser);
            Database locationIndexer("../src/Server/data/libIndex.json");
            locationIndexer.DecodeFilter(&userFilter, request);
            if(sentInfo != nullptr)
                free(sentInfo);
            sentInfo = (DBResult *)malloc(sizeof(DBResult) * userFilter.entriesPerPage);
            memset(this->sentInfo, 0, sizeof(DBResult) * userFilter.entriesPerPage); 

            this->maxEntries = locationIndexer.HandleQuery(this->sentInfo, userFilter.entriesPerPage, &userFilter);
            if( 0 >= write(threadDataLocal.clientDescriptor, &this->maxEntries, 4))
                this->ReportLog(threadWriteError, threadDataLocal.idThread, threadDataLocal.linkedUser);
            for(int i = 0; i < this->maxEntries; i ++)
                if( 0 >= write(threadDataLocal.clientDescriptor ,&this->sentInfo[i], sizeof(DBResult)))
                    this->ReportLog(threadWriteError, threadDataLocal.idThread, threadDataLocal.linkedUser);
        }
        if(!strcmp(request, "CLIENTEVENTRECO"))
        {
            struct  stat st;
            
            if( -1 == stat( std::string(std::string("../src/Server/data/userStats/") + std::string(threadDataLocal.linkedUser) + std::string(".json")).c_str() ,&st ) )
                write(threadDataLocal.clientDescriptor, "FILENOTEXISTS", 64);
            else
            {
                write(threadDataLocal.clientDescriptor, "FILEEXISTS", 64);
            
                Database userInfoDatabase(std::string(std::string("../src/Server/data/userStats/") + std::string(threadDataLocal.linkedUser) + std::string(".json")).c_str());
                if(sentInfo != nullptr)
                    free(sentInfo);
                userInfoDatabase.DecodeRecommendedFilter(&userFilter);
                sentInfo = (DBResult*)malloc(sizeof(DBResult) * 5);
                memset(sentInfo, 0, sizeof(DBResult) * 5);
                Database locationIndexer("../src/Server/data/libIndex.json");

                this->maxEntries = locationIndexer.HandleQuery(this->sentInfo, 5, &userFilter);
                if( 0 >= write(threadDataLocal.clientDescriptor, &this->maxEntries, 4))
                    this->ReportLog(threadWriteError, threadDataLocal.idThread, threadDataLocal.linkedUser);
                for(int i = 0; i < this->maxEntries; i++)
                if( 0 >= write(threadDataLocal.clientDescriptor ,&this->sentInfo[i], sizeof(DBResult)))
                    this->ReportLog(threadWriteError, threadDataLocal.idThread, threadDataLocal.linkedUser);
            }
        }
        if(!strcmp(request, "CLIENTEVENTDOWN"))
        {
            int index = 0;
            if( 0 > read(threadDataLocal.clientDescriptor, &index, 4))
                this->ReportLog(threadReadError, threadDataLocal.idThread, threadDataLocal.linkedUser);

            this->AddToStats( this->sentInfo + index , threadDataLocal.linkedUser);

            char *tempPath = (char*)malloc(256);
            char* extension = (char*)malloc(256), *extensionPointer;
            memset(extension,0,10);
            strcpy(extension, (*(this->sentInfo + index)).diskPath);
            extensionPointer = extension;

            while(strchr(extensionPointer, '.')) extensionPointer = strchr(extensionPointer, '.') + 1;
            strcpy(tempPath, (*(this->sentInfo+index)).diskPath);
            
            char* temp = (char*) malloc(20);
            strcpy(temp, "temp.");
            temp[5] = 0;

            strcpy(strstr(tempPath, extensionPointer), strcat(temp, extensionPointer));

            if(!fork())
                execl("/bin/cp","cp",(*(this->sentInfo+index)).diskPath, tempPath, NULL);
            wait(NULL);
            int fd = open(tempPath, O_RDONLY, 0666);
            char *p;
            char *buffer = (char*)malloc(1024);
            memset(buffer, 0, 1024);
            strcpy(buffer, (*(this->sentInfo+index)).diskPath);
            p = strchr(strchr(strchr(buffer, '/')+1,'/')+1,'/') + 1;
            if( 0>= write(threadDataLocal.clientDescriptor, p, 1024))
                this->ReportLog(threadWriteError, threadDataLocal.idThread, threadDataLocal.linkedUser);
            struct stat st;
            memset(&st, 0, sizeof(struct stat));
            fstat(fd, &st);
            write(threadDataLocal.clientDescriptor,(long long*)&st.st_size, 8); 

            int bytesRead = 0;

            do
            {
                bytesRead = read(fd, buffer, 1024);
                write(threadDataLocal.clientDescriptor, &bytesRead, 4);
                write(threadDataLocal.clientDescriptor, buffer, 1024);
            } while (bytesRead > 0);
            
            close(fd);

            strcpy(tempPath, (*(this->sentInfo+index)).diskPath);
            strcpy(strstr(tempPath, extensionPointer), temp);

            free(temp);
            free(extension);
            strcpy(buffer, "rm ");
            strcat(buffer, tempPath);
            system(buffer);
            free(buffer);
            free(tempPath);
            fflush(stdout);
        }
    }
    free(request);
    free(userFilter.authorName);
    free(userFilter.bookName);
}

void* Server::ThreadInitCall(void* arg)
{
    Server::thData threadDataLocal;
    threadDataLocal = *((thData*)arg);
    threadDataLocal.parentServer->ReportLog(threadMessageWait, threadDataLocal.idThread);
    if(threadDataLocal.parentServer->ThreadLoginBootstrap((thData*)&threadDataLocal))
    {
        threadDataLocal.parentServer->ThreadRuntime(threadDataLocal);
    } 
    close(threadDataLocal.clientDescriptor);
    pthread_detach(pthread_self()); 
    pthread_cancel(pthread_self());
    return (NULL);

}

void Server::PrintLoggedUsers()
{
    for(size_t index = 0; index < this->nLoggedUsers; index++)
    {
        printf("%s\n", *(this->loggedUsers + index));
    }
}

bool Server::isUserLoggedIn(const char* username)
{
    for(size_t index = 0; index < this->nLoggedUsers; index++)
    {
        if(!strcmp(*(this->loggedUsers + index), username))
            return true;
    }
    return false;
}

int Server::GetDateInSeconds(const char* givenDate)
{
    char *date = (char*)malloc(64);
    strcpy(date, givenDate);   
    *strchr(date, '<') = 0;
    int seconds = atoi(strchr(strchr(date, '-') + 1, '-')+1);
    *strchr(strchr(date, '-') + 1,'-') = 0;
    int minutes = atoi(strchr(date, '-')+1);
    *strchr(date, '-') = 0;
    int hours = atoi(date);
    free(date);
    return hours * 3600 + minutes * 60 + seconds;
}

bool Server::ThreadTimeout(const char* startDate, const int& seconds, int& secondsLeft)
{
    if(*startDate == 0)
        return false;
    char *currentDate = (char*)malloc(64);
    strcpy(currentDate, this->GetLocaltime());
    int startSeconds = this->GetDateInSeconds(startDate);
    int currentSeconds = this->GetDateInSeconds(currentDate);
    free(currentDate);
    secondsLeft = seconds - (currentSeconds - startSeconds);
    if(secondsLeft <= 0)
        return false;
    return true;
}

bool Server::ThreadLoginBootstrap(void* arg)
{
    int timeoutSeconds = 0;
    int seconsToBeAddedToTimeout = 30;
    int timeoutSecondsLeft = 0;
    
    char *timeout = (char*)malloc(64);
    memset(timeout, 0, 64);
    int attempts = 0;
    char *clientRequest = (char*)malloc(256);
    char * username = (char*)malloc(128);
    memset(username, 0, 128);
    bool isLoggedOn = false;
    char *p;
    Server::thData threadDataLocal;
    threadDataLocal = *((Server::thData*)arg);
    do
    {
        Database usersDB("../src/Server/data/accounts.json", 8192);
        memset(clientRequest, 0, 256);
        int bytesRead = 0;
        if( 0 > (bytesRead = read(threadDataLocal.clientDescriptor, clientRequest, 256)))
            this->ReportLog(threadReadError, threadDataLocal.idThread);
        else if(bytesRead > 0)
            this->ReportLog(threadReadSuccess, threadDataLocal.idThread);
            else
            {
                this->ReportLog(threadLogonFailLoggedIn, threadDataLocal.idThread);
                free(clientRequest);
                free(username);
                free(timeout);
                return false;
            }
        if(!strcmp(clientRequest, "CLIENTEVENTQUIT"))
            return false;
        if(!strcmp(clientRequest, "CLIENTEVENTDISC"))
            return false;
        if(!strcmp(clientRequest, "CLIENTACCCREATE"))
        {
            if( 0 > (bytesRead = read(threadDataLocal.clientDescriptor, clientRequest, 256)))
                this->ReportLog(threadReadError, threadDataLocal.idThread);
            else if(bytesRead > 0)
                this->ReportLog(threadReadSuccess, threadDataLocal.idThread);
                else
                {
                    this->ReportLog(threadLogonFailLoggedIn, threadDataLocal.idThread);
                    free(clientRequest);
                    free(username);
                    free(timeout);
                    return false;
                }
            p = strtok(clientRequest, ";");
            isLoggedOn = usersDB.existsAccount(clientRequest);
            char* responseBuffer = (char*)malloc(12);
            memset(responseBuffer, 0 , 12);
            strcpy(responseBuffer, isLoggedOn ? "ACCOUEXISTS" : "ACCONEXISTS");
            isLoggedOn = 0;
            this->ReportLog(threadWriteNotify, threadDataLocal.idThread);
            if( 0 >= write(threadDataLocal.clientDescriptor, responseBuffer, 12))
            {
                this->ReportLog(threadWriteError, threadDataLocal.idThread);
            }
            else
            {
                this->ReportLog(threadWriteSuccess, threadDataLocal.idThread);
            }
            p = strtok(NULL, ";");
            usersDB.AddEntry(clientRequest, p);
            free(responseBuffer);
            continue;
        }
        p = strtok(clientRequest, ";");
        p = strtok(NULL, ";");



        isLoggedOn = usersDB.ConfirmLogon(clientRequest, p);

        strcpy(username, clientRequest);
        strcpy(clientRequest,  isLoggedOn ? "LOGONACCMPL" : "LOGONFAILED"); 

        if(ThreadTimeout(timeout, timeoutSeconds, timeoutSecondsLeft))
        {
            this->ReportLog(threadWriteNotify, threadDataLocal.idThread);
            if( 0 >= write(threadDataLocal.clientDescriptor, "ERRTIMEDOUT", 12))
                this->ReportLog(threadWriteError, threadDataLocal.idThread);
            else
                this->ReportLog(threadWriteSuccess, threadDataLocal.idThread);

            this->ReportLog(threadWriteNotify, threadDataLocal.idThread);
            if( 0 >= write(threadDataLocal.clientDescriptor, &timeoutSecondsLeft, 4))
                this->ReportLog(threadWriteError, threadDataLocal.idThread);
            else
                this->ReportLog(threadWriteSuccess, threadDataLocal.idThread);

            usersDB.~Database();
            continue;
        }
        if(isLoggedOn)
        {
            if(this->isUserLoggedIn(username))
            {
                strcpy(clientRequest, "ERRLOGGEDIN");
                this->ReportLog(threadLogonFailLoggedIn, threadDataLocal.idThread, username);
                isLoggedOn = false;
            }
            if(this->nLoggedUsers == MAX_USERS)
            {
                strcpy(clientRequest, "LGERRCAPHIT");
                this->ReportLog(threadLogonFailCapacity,threadDataLocal.idThread, username);
                isLoggedOn = false;
            }
        }
        this->ReportLog(threadWriteNotify, threadDataLocal.idThread);
        if( 0>= write(threadDataLocal.clientDescriptor, clientRequest, 12))
            this->ReportLog(threadWriteError, threadDataLocal.idThread);
        else
            this->ReportLog(threadWriteSuccess, threadDataLocal.idThread);

        if(!isLoggedOn && ThreadTimeout(timeout, timeoutSeconds, timeoutSecondsLeft) == false)
            attempts++;
        
        if(attempts == 3)
        {
            strcpy(timeout, this->GetLocaltime());
            timeoutSeconds = seconsToBeAddedToTimeout;
            seconsToBeAddedToTimeout *= 2;
            attempts = 0;
        }

    } while (isLoggedOn == false && attempts < 3);
    if(isLoggedOn == false)
    {
        free(clientRequest);
        free(username);
        free(timeout);
        return false;
    }
    *(this->loggedUsers + nLoggedUsers) = (char*)malloc(128);
    memset(*(this->loggedUsers + nLoggedUsers), 0 ,128);
    strcpy(*(this->loggedUsers + nLoggedUsers++), username);
    fflush(stdout);
    this->ReportLog(threadLogonSuccessful, threadDataLocal.idThread, username);
    (*((thData*)arg)).linkedUser = (char*)malloc(128);
    strcpy((*((thData*)arg)).linkedUser, username);
    free(clientRequest);
    free(username);
    free(timeout);
    return true;
}


void Server::Runtime()
{
    int client;
    char * serverInput = (char* )malloc(128);
    memset(serverInput,0 ,128);
    unsigned int addrLen;
    int threadIndex = 0;
    Server::thData *threadData;
    while(true)
    {
        addrLen = sizeof(this->receivedInfo);
        this->ReportLog(serverPortWait);
        if( 0 > (client = accept(this->socketDescriptor, (sockaddr*)&this->receivedInfo,(socklen_t*) &addrLen)))
        {
            this->ReportLog(acceptError);
            continue;
        }
        threadData = (thData*)malloc(sizeof(thData));
        threadData->idThread = threadIndex;
        threadData->clientDescriptor = client;
        threadData->parentServer = this;
        pthread_create(&this->threads[threadIndex++], NULL, this->ThreadInitCall, (void*)threadData);
    }
}

void Server::Init()
{
    this->logFile = this->CreateLog();
    if(-1 == (this->socketDescriptor = socket(AF_INET, SOCK_STREAM, NO_DEFINED_PROTOCOL)))
        this->ReportLog(socketError);
    int on = 1;
    setsockopt(this->socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    if(-1 == bind(this->socketDescriptor, (sockaddr *)&this->serverInfo, sizeof(sockaddr)))
        this->ReportLog(bindError);
    if(-1 == listen(this->socketDescriptor, MAX_CLIENTS_IN_QUEUE)) 
        this->ReportLog(listenError);
}

Server::Server(const int& givenPort)
{
    this->sentInfo = nullptr;
    this->nLoggedUsers = 0;
    this->socketDescriptor = 0;
    this->serverPort = givenPort;
    this->threads = (pthread_t *)malloc(sizeof(pthread_t) * MAX_THREADS);
    this->loggedUsers = (char**)malloc(MAX_USERS * sizeof(size_t));
    memset(this->loggedUsers, 0, MAX_USERS * sizeof(size_t));
    memset(this->threads, 0, MAX_THREADS*sizeof(pthread_t));
    memset(&this->serverInfo, 0, sizeof(sockaddr_in));
    memset(&this->receivedInfo, 0, sizeof(sockaddr_in));
    this->serverInfo.sin_family = AF_INET;
    this->serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);
    this->serverInfo.sin_port = htons(this->serverPort);
}

Server::~Server()
{
    this->socketDescriptor = 0;
    this->serverPort = 0;
    free(this->threads);
    close(this->logFile);
    this->logFile = 0;
}

char* Server::GetLocaltime()
{
    static char* timeString = (char*)malloc(256);
    memset(timeString,0,256);
    time_t t = time(NULL);
    tm timeStruct = *localtime(&t);
    sprintf(timeString,"%d-%d-%d<->%d:%d:%d", timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec,
        timeStruct.tm_mday, timeStruct.tm_mon, timeStruct.tm_year);
    return timeString;
}



void Server::ReportLog(const int logId, const int threadId,const char* userId)
{
    char* logLine = (char*)malloc(MAXSTRLEN);
    memset(logLine ,0 ,MAXSTRLEN);
    struct flock fileLock;
    fileLock.l_type = F_WRLCK;
    fileLock.l_len = MAXSTRLEN;
    fileLock.l_start = 0;
    fileLock.l_whence = SEEK_CUR;
    fcntl(this->logFile, F_SETLK, &fileLock);
    switch(logId)
    {
        case socketError:
            sprintf(logLine, "[Server][%s]socket() function error!\nServer exited with code 1.\n",this->GetLocaltime());
            write(this->logFile, logLine, strlen(logLine));
            close(this->logFile);
            exit(1);         
        case bindError:
            sprintf(logLine,"[Server][%s]bind() function error!\nServer exited with code 2.\n",this->GetLocaltime());
            write(this->logFile, logLine, strlen(logLine));
            close(this->logFile);
            exit(2);
        case listenError:
            sprintf(logLine,"[Server][%s]listen() function error!\nServer exited with code 3.\n",this->GetLocaltime());
            write(this->logFile, logLine, strlen(logLine));
            close(this->logFile);
            exit(3);
        case acceptError:
            sprintf(logLine,"[Server][%s]accept() function error!\nContinuing Server program.\n",this->GetLocaltime());
            break;
        case serverPortWait:
            sprintf(logLine, "[Server][%s]Waiting @ port %d...\n", this->GetLocaltime(), this->serverPort);
            break;
        case threadMessageWait:
            sprintf(logLine, "[Thread - %d][%s]Waiting for message...\n", threadId, this->GetLocaltime());
            break;
        case threadReadError:
            sprintf(logLine,"[Thread - %d][%s]read() function error!\nContinuing program.\n",threadId, this->GetLocaltime());
            break;
        case threadWriteError:
            sprintf(logLine,"[Thread - %d][%s]write() function error!\nContinuing program.\n",threadId, this->GetLocaltime());
            break;
        case threadWriteNotify:
            sprintf(logLine,"[Thread - %d][%s]Writing message to client.\n",threadId, this->GetLocaltime());
            break;
        case threadWriteSuccess:
            sprintf(logLine,"[Thread - %d][%s]Wrote message to client.\n",threadId, this->GetLocaltime());
            break;
        case threadReadSuccess:
            sprintf(logLine,"[Thread - %d][%s]Received message from client.\n",threadId, this->GetLocaltime());
            break;
        case threadLogonFailCapacity:
            sprintf(logLine,"[Thread - %d][%s]Users capacity reached!\nUser %s failed to log on.\n", threadId, this->GetLocaltime(), userId);
            break;
        case threadLogonFailLoggedIn:
            sprintf(logLine,"[Thread - %d][%s]User %s already logged in!\n", threadId, this->GetLocaltime(), userId);
            break;
        case threadLogonSuccessful:
            sprintf(logLine,"[Thread - %d][%s]User %s has logged into the server!\n", threadId, this->GetLocaltime(), userId);
            break;
        default:
            sprintf(logLine,"[Server][%s]Unknown Log Request!!\n",this->GetLocaltime());
    }
    write(this->logFile, logLine, strlen(logLine));
    fileLock.l_type = F_UNLCK;
    fcntl(this->logFile, F_SETLK, &fileLock);
    close(this->logFile);
    this->logFile = open(this->logName, O_WRONLY,0666);
    lseek(this->logFile, 0, SEEK_END);
}

int Server::CreateLog()
{
    int fileDesc;
    this->logName = (char*)malloc(256);
    memset(this->logName, 0, 256);
    sprintf(this->logName,"./logs/server/log:%s.txt", this->GetLocaltime());
    fileDesc = open(this->logName, O_WRONLY | O_CREAT | O_TRUNC,0666);
    return fileDesc;
}
