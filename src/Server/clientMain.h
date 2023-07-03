#pragma once

struct DBResult
{
    char bookName[128];
    char authorName[128];
    int year;
    char genre[64];
    int rating;
    int ISBN;
    char diskPath[256];
};

enum logs
{
    socketError, connectError, writeError, readError
};

class Client
{
    private:
        FILE* logFile{nullptr};
        bool isLoggedOn{false};
        int socketDescriptor;
        sockaddr_in serverInfo;
        void ReportLog(const int = -1);
        FILE* CreateLog();
    public:
        char* GetLocaltime();
        Client(int = 0,char ** = nullptr);
        void Init();
        void LoginRequest();
        void PrintResults(DBResult*, const int&);
        void Runtime();
        ~Client();
};

void Client::PrintResults(DBResult* array, const int& length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("Title: %s\nAuthor: %s\nGenre: %s\nYear: %d\nRating: %d\nISBN: %d\n",
            array[i].bookName, array[i].authorName, array[i].genre, array[i].year, array[i].rating,
            array[i].ISBN);
    }
    
}
//1;20;;;1555;;;2
void Client::Runtime()
{
    char *command = (char*)malloc(1024);
    char *p;
    int noEntries = 0;
    while(true)
    {
        memset(command, 0 ,1024);
        printf("Input format [pageindex;numberperpage;author;title;minYear;maxYear;category;rating]\nClient: ");
        read(0, command, 1024);
        if( 0 >= write(socketDescriptor, command, 1024))
            this->ReportLog(writeError);
        //perror("0");  
        p = strchr(command, ';')+1;
        *strchr(strchr(command,';')+1,';') = 0;
        if(*p)
        noEntries = atoi(p);
        else   
        noEntries = 20;
        
        DBResult *entries = (DBResult*)malloc(noEntries*sizeof(DBResult));
        memset(entries, 0, sizeof(DBResult) * noEntries);
        *(strchr(command,';') +strlen(strchr(command,';')) + 1)= ';';
        // ?printf("%d %s\n",errno, command);
        if( 0 > read(socketDescriptor, entries, sizeof(DBResult) * noEntries))
            this->ReportLog(readError);
            //perror("a");
            //fflush(stdout);
        if( 0 > read(socketDescriptor, &noEntries, 4))
            this->ReportLog(readError);
            //perror("b");
            //fflush(stdout);
            printf("%d\n", noEntries);
        printf("%s %d\n", p, noEntries);
        this->PrintResults(entries, noEntries);
        free(entries);
    }
    free(command);
}

void Client::LoginRequest()
{
    int attempts = 0;
    char * username = (char*)malloc(128);
    char * password = (char*)malloc(128);
    char * request = (char*)malloc(256);
    char * received = (char*)malloc(256);
    do
    {
        memset(username, 0 ,128);
        memset(password,0,128);
        memset(request, 0, 256);
        memset(received, 0, 256);
        printf("Login: ");
        fflush(stdout);
        read(0, username, 128);
        printf("Password: ");
        fflush(stdout);
        read(0, password, 128);
        username[strlen(username)-1]=password[strlen(password)-1]=0;
        sprintf(request, "%s;%s", username, password);
        if( 0>= write(this->socketDescriptor, request, 256) )
            this->ReportLog(writeError);
        if( 0 > read(this->socketDescriptor, received, 11))
            this->ReportLog(readError);
        if(!strcmp(received, "LOGONACCMPL"))
        {
            printf("Logged on!\n");
            isLoggedOn = true;
        }    
        if(!strcmp(received, "LOGONFAILED"))
        {
            printf("Logon failed!\n");
            attempts++;
        }    
        if(!strcmp(received, "LGERRCAPHIT"))
        {
            printf("Logon failed!\nUsers capacity hit!\n");
            attempts++;
        }
          
        if(!strcmp(received, "ERRLOGGEDIN"))
        {
            printf("Logon failed!\nAlready logged in!\n");
            attempts++;
        }
    } while (this->isLoggedOn == false && attempts < 3);
    free(username);
    free(password);
    free(request);
    free(received);
}

Client::Client(int noOfParams,char ** strings)
{
    memset(&this->serverInfo, 0 , sizeof(sockaddr_in));
    this->serverInfo.sin_family = AF_INET;
    switch(noOfParams)
    {
        case 3 : 
            this->serverInfo.sin_addr.s_addr = inet_addr(strings[1]);
            this->serverInfo.sin_port = htons(atoi(strings[2]));
            break;
        case 2 :
            this->serverInfo.sin_port = htons(atoi("3000"));
            this->serverInfo.sin_addr.s_addr = inet_addr(strings[1]);
            break;
        default :
            this->serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
            this->serverInfo.sin_port = htons(atoi("3000"));
    }
}

void Client::Init()
{
    this->logFile = this->CreateLog();
    if(-1 == (this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)))
        this->ReportLog(socketError);
    if(-1 == connect(this->socketDescriptor, (struct sockaddr *)&this->serverInfo, sizeof(struct sockaddr)))
        this->ReportLog(connectError);
}

Client::~Client()
{
    close(this->socketDescriptor);
    fflush(this->logFile);
    this->socketDescriptor = 0;
    memset(&this->serverInfo, 0 , sizeof(sockaddr_in));
    fclose(this->logFile);
    this->logFile = nullptr;
}


char* Client::GetLocaltime()
{
    static char* timeString = (char*)malloc(256);
    memset(timeString,0,256);
    time_t t = time(NULL);
    tm timeStruct = *localtime(&t);
    sprintf(timeString,"%d-%d-%d<->%d:%d:%d", timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec,
        timeStruct.tm_mday, timeStruct.tm_mon, timeStruct.tm_year);
    return timeString;
}

void Client::ReportLog(const int logId)
{
    switch(logId)
    {
        case socketError:
            fprintf(this->logFile,"[Client][%s]socket()function error.\nApplication exited with code 2.\n",this->GetLocaltime());
            exit(2);
        case connectError:
            fprintf(this->logFile,"[Client][%s]connect() function error.\nProgram exited with code 3.\n", this->GetLocaltime());
            exit(3);
        case writeError:
            this->logFile,"[Client][%s]write() function error.\nContinuing program.\n",this->GetLocaltime();
            break;
        case readError:
            this->logFile,"[Client][%s]read() function error.\nContinuing program.\n",this->GetLocaltime();
            break;
        default:
            fprintf(this->logFile,"[Client][%s]Unknown Log Request!!\n",this->GetLocaltime());
            return;
    }
}

FILE* Client::CreateLog()
{
    static FILE* fileName;
    char* logName = (char*)malloc(256);
    memset(logName, 0, 256);
    sprintf(logName,"./logs/client/log:%s", this->GetLocaltime());
    fileName = fopen(logName, "w");
    free(logName);
    return fileName;
}
