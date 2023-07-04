#pragma once
#include <json-c/json.h>
#include <stdio.h>
#include <cstring>
#define MAXBUFFERSIZE 65532
#define _DB_DRAMA 1
#define _DB_COMED 2
#define _DB_THRIL 4
#define _DB_HORRO 8
#define _DB_MANUA 16
#define _DB_BIOGR 32
#define _DB_ABIOG 64
#define _DB_CHILD 128
#define _DB_ACTIO 256
#define _DB_FANTA 512
#define _DB_ROMAN 1024
#define _DB_ALLGN 2047

/**
 * [DEPRECATED]
 * Macro used to convert from string to flag
 * 
 * Returns the flag of the given genre string
 */
#define _isInGenreFlag(givenGenre) \
(\
    if(!strcmp(givenGenre, "drama"))\
         _DB_DRAMA;\
    if(!strcmp(givenGenre, "comedy"))\
         _DB_COMED;\
    if(!strcmp(givenGenre, "thriller"))\
         _DB_THRIL;\
    if(!strcmp(givenGenre, "horror"))\
         _DB_HORRO;\
    if(!strcmp(givenGenre, "manual"))\
         _DB_MANUA;\
    if(!strcmp(givenGenre, "biography"))\
         _DB_BIOGR;\
    if(!strcmp(givenGenre, "autobiography"))\
         _DB_ABIOG;\
    if(!strcmp(givenGenre, "children"))\
         _DB_CHILD;\
    if(!strcmp(givenGenre, "action"))\
        _DB_ACTIO;\
)


/**
 * @brief External function used to convert from string to flag
 * 
 * @param givenGenre = string containing the genre name
 * 
 * @return Returns the flag of the given gerne string
 */
int isInGenreFlag(const char* givenGenre)
{
    if(!strcmp(givenGenre, "drama"))
        return _DB_DRAMA;
    if(!strcmp(givenGenre, "comedy"))
        return _DB_COMED;
    if(!strcmp(givenGenre, "thriller"))
        return _DB_THRIL;
    if(!strcmp(givenGenre, "horror"))
        return _DB_HORRO;
    if(!strcmp(givenGenre, "manual"))
        return _DB_MANUA;
    if(!strcmp(givenGenre, "biography"))
        return _DB_BIOGR;
    if(!strcmp(givenGenre, "autobiography"))
        return _DB_ABIOG;
    if(!strcmp(givenGenre, "children"))
        return _DB_CHILD;
    if(!strcmp(givenGenre, "action"))
        return _DB_ACTIO;
    if(!strcmp(givenGenre, "romance"))
        return _DB_ROMAN;
    if(!strcmp(givenGenre, "fantasy"))
        return _DB_FANTA;
}

/**
 * @brief Structure describing a search filter, used for database querry
 */ 
struct DBFilter{
    /**
     * @brief /which page does the user request?
     */
    int page;
    /**
     * @brief How many entries does the user Request?
     */
    int entriesPerPage;
    /**
     * @brief What title does the user look for?
     */
    char *bookName;
    /**
     * @brief authorName = Which author's work does the user look for?
     */
    char *authorName;
    /**
     * @brief publications after [minYear] age
     */
    int minYear;
    /**
     * @brief publications before [maxYear] age
     */
    int maxYear;
    /**
     * @brief which genres does the user look for?
     *
     *      genres are stored in a flag which is in base 2, i.e.
     *      - user is looking for both thriller and horror books, thriller flag is 4 (100), horror flag is 8 (1000), therefore
     *      - what he is looking for can be described as 12 (1100)
     */
    int typeFlags;
    /**
     * @brief above what rating does the user want entries to be?
     */
    int rating;
};


/**
 * @brief Structure which describes/contains an entry in a query result
 */
struct DBResult
{
    /**
     * @brief the title of the book
     */
    char bookName[128];
    /**
     * @brief the name of the author of the book
     */
    char authorName[128];
    /**
     * @brief the year in which the book was published
     */
    int year;
    /**
     * @brief the name of the genre of the book
     */
    char genre[64];
    /**
     * @brief the rating of the book (i out of 5)
     */
    int rating;
    /**
     * @brief the ISBN of the book (international standard book number)
     */
    int ISBN;
    /**
     * @brief the absolute path of the file containing the book contents on the disk
     */
    char diskPath[256];
};

/**
 * @brief Database Class
 * 
 * Handles database objects required in the server application
 */
class Database
{
    private:

        /**
         * String containing the relative path of the opened database
         */
        char* linkedDatabaseRelativePath;
        /**
         * Address to the database file the current object is linked to.
        */
        FILE* dbDescriptor{nullptr};

        /**
         * Parsed database string, type json_object, converted from buffer
         */
        json_object *parsed_json{nullptr};

        /**
         * Buffer used throughout the class functions, mostly to read from database file.
         */
        char* buffer{nullptr};
    public:

        /**
          * @brief Constructor of the Database object.
          *    
          * @param filepath contains the relative/absolute path of the database file [.json]
          * 
          * @param bufferLength contains the max buffer size, defaulted to MAXBUFFERSIZE = 64 bytes. Contains database file max size, change for larger databases.
        */
        Database(const char*, const int& = MAXBUFFERSIZE);

        /**
         * @brief Function used to decode a filter from char* (client filter format request) to DBFilter*, a structure containing filter variables
         * 
         * @param givenFilter address of the filter in which the settings will be saved
         * 
         * @param givenInfo given string containing coded filter
         */
        void DecodeFilter(DBFilter *, const char*);

        /**
         * @brief Function used to decode the recommended books filter to DBFilter*, a structure containing filter variables
         * 
         * @param givenFilter address of the filter in which the settings will be saved
         */
        void DecodeRecommendedFilter(DBFilter*);

        /**
         * @brief Function used to request a query from the database
         * 
         * @param givenArray address of the result array (DBResult*) in which the results will be saved
         * @param arrayLen max size of the result array
         * @param givenFilter address to the filter structure given to create the query. Required.
         * 
         * @return Returns the number of entries saved in the result array
         */
        int HandleQuery(DBResult*, const int&, const DBFilter*);

        /**
         * @brief Function that looks into the users database and compares a client's login information to existing ones.
         * 
         * @param givenUsername string in which the given username is stored
         * @param givenPassword string in which the given password is stored
         * 
         * @return Returns true on login success (user and pass exist in the database), false otherwise
         */
        bool ConfirmLogon(const char*, const char *);

        /**
         * @brief Function called to add an entry into the database, called when an account is created
         * 
         * @param username string containing the username of the freshly created account
         * @param password string containing the password of the freshly created account
         */
        void AddEntry(const char*, const char*);

        /**
         * @brief Function that checks whether an account with the given username already exists
         * 
         * @param username string containing the username which will be looked for in the database
         * 
         * @return Returns true if the username already exists in the database, false otherwise
         */

        bool existsAccount(const char*);

        /**
         * @brief Database object destructor
         */
        ~Database();
};

int Database::HandleQuery(DBResult* givenArray, const int& arrayLen,const DBFilter* givenFilter)
{
    size_t index = 0;
    json_object *bookInfo, *bookTitle,  *bookAuthor, *bookYear, *bookGenre, *bookRating,
        *bookISBN, *bookDiskpath;
    
    for(size_t i = 0, length = json_object_array_length(this->parsed_json); i< length; i++)
    {
        bookInfo = json_object_array_get_idx(this->parsed_json, i);
        json_object_object_get_ex(bookInfo, "title", &bookTitle);
        json_object_object_get_ex(bookInfo, "author", &bookAuthor);
        json_object_object_get_ex(bookInfo, "year", &bookYear);
        json_object_object_get_ex(bookInfo, "genre", &bookGenre);
        json_object_object_get_ex(bookInfo, "rating", &bookRating);
        json_object_object_get_ex(bookInfo, "isbn", &bookISBN);
        json_object_object_get_ex(bookInfo, "diskPath", &bookDiskpath);
        if(givenFilter->minYear <= json_object_get_int(bookYear) && json_object_get_int(bookYear) <= givenFilter->maxYear)
        {
            if(givenFilter->rating <= json_object_get_int(bookRating))
            {
                if(isInGenreFlag(json_object_get_string(bookGenre)) & givenFilter->typeFlags)
                {
                    if(strstr(json_object_get_string(bookAuthor),givenFilter->authorName))
                    {
                        if(strstr(json_object_get_string(bookTitle), givenFilter->bookName))
                        {
                            if((givenFilter->page-1)*givenFilter->entriesPerPage <= index && 
                                index < givenFilter->page * givenFilter->entriesPerPage)
                            {
                                memset(givenArray[index].authorName, 0, sizeof(DBResult::authorName));
                                memset(givenArray[index].bookName, 0, sizeof(DBResult::bookName));
                                memset(givenArray[index].diskPath, 0, sizeof(DBResult::diskPath));
                                memset(givenArray[index].genre, 0, sizeof(DBResult::genre));
                                strcpy(givenArray[index].authorName, json_object_get_string(bookAuthor));
                                strcpy(givenArray[index].bookName, json_object_get_string(bookTitle));
                                strcpy(givenArray[index].genre, json_object_get_string(bookGenre));
                                strcpy(givenArray[index].diskPath, json_object_get_string(bookDiskpath));
                                givenArray[index].ISBN = json_object_get_int(bookISBN);
                                givenArray[index].rating = json_object_get_int(bookRating);
                                givenArray[index].year = json_object_get_int(bookYear);
                                index++;
                            }
                        }
                    }
                }
            }
        }
    }
    return index;
}


void Database::AddEntry(const char* username, const char* password)
{
    char* databaseBuffer = (char*)calloc(sizeof(char),MAXBUFFERSIZE);
    this->dbDescriptor = fopen(this->linkedDatabaseRelativePath, "r");
    fread(databaseBuffer, 1, MAXBUFFERSIZE, this->dbDescriptor);
    fclose(this->dbDescriptor);
    char* pointer;

    pointer = databaseBuffer;

    while(strchr(pointer, '}')) pointer = strchr(pointer, '}') + 1;

    sprintf(pointer, ",\n\t{\n\t\t\"username\" : \"%s\",\n\t\t\"password\" : \"%s\"\n\t}\n]", username, password);

    this->dbDescriptor = fopen(this->linkedDatabaseRelativePath, "w");

    fputs(databaseBuffer, this->dbDescriptor);

    fclose(this->dbDescriptor);

    free(databaseBuffer);
}

bool Database::existsAccount(const char* username)
{
    json_object *entry;
    json_object *entryName;
    for (size_t i = 0, length = json_object_array_length(this->parsed_json); i<length; i++)
    {
        entry = json_object_array_get_idx(this->parsed_json, i);
        json_object_object_get_ex(entry, "username", &entryName);
        if(!strcmp(username, json_object_get_string(entryName)))
            return true;
    }
    return false;
}


bool Database::ConfirmLogon(const char* givenUsername, const char* givenPassword)
{
    json_object* currUser;
    json_object* currUserName;
    json_object* currUserPass;
    for(size_t i = 0, length = json_object_array_length(this->parsed_json); i< length ;i++)
    {
        currUser = json_object_array_get_idx(this->parsed_json, i);
        json_object_object_get_ex(currUser, "username", &currUserName);
        json_object_object_get_ex(currUser, "password", &currUserPass);
        if(!strcmp(givenUsername, json_object_get_string(currUserName)) && 
            !strcmp(givenPassword, json_object_get_string(currUserPass)))
            return true;
    }
    return false;
}


void Database::DecodeRecommendedFilter(DBFilter* givenFilter)
{
    givenFilter->entriesPerPage = 10;
    givenFilter->page = 1;
    givenFilter->minYear = -1;
    givenFilter->maxYear = 999999;
    givenFilter->rating = -1;
    givenFilter->typeFlags = _DB_ALLGN;

    int numberOfDownloads = json_object_array_length(this->parsed_json) - 1;
    int numberOfSimillarGenres = 0;
    int numberOfSameAuthorAppereances = 0;
    int numberOfAuthors = 0;
    int numberOfGenres = 0;

    char * mostPopularGenre = (char*)malloc(256);
    char * mostPopularAuthor = (char*)malloc(256);

    memset(mostPopularAuthor, 0, 256);
    memset(mostPopularGenre, 0, 256);

    struct {
        int appereances;
        char* name;
    } genres[numberOfDownloads], authors[numberOfDownloads];

    json_object* authorNameObject, *genreNameObject;
    json_object* statusInfo;

    for(int i = 1, length = json_object_array_length(this->parsed_json); i < length; i++)
    {
        statusInfo = json_object_array_get_idx(this->parsed_json, i);
        json_object_object_get_ex(statusInfo, "author", &authorNameObject);
        json_object_object_get_ex(statusInfo, "genre", &genreNameObject);

        bool authorExists = false;
        bool genreExists = false;

        for(int j = 0; j < numberOfAuthors; j++)
        {
            fflush(stdout);
            if( !strcmp ( authors[j].name, json_object_get_string(authorNameObject) ) )
            {
                authorExists = true;
                authors[j].appereances++;
                break;
            }
        }

        if(authorExists == false)
        {
            authors[numberOfAuthors].name = (char*)malloc(256);
            strcpy(authors[numberOfAuthors].name, json_object_get_string(authorNameObject));
            authors[numberOfAuthors++].appereances = 1;
        }

        for(int j = 0; j < numberOfGenres; j++)
        {
            if( !strcmp( genres[j].name, json_object_get_string(genreNameObject) ) )
            {
                genreExists = true;
                genres[j].appereances++;
                break;
            }
        }

        if(genreExists == false)
        {
            genres[numberOfGenres].name = (char*)malloc(256);
            strcpy(genres[numberOfGenres].name, json_object_get_string(genreNameObject));
            genres[numberOfGenres++].appereances = 1;
        }
    }

    for(int i = 0; i < numberOfAuthors; i++)
    {
        if( authors[i].appereances > numberOfSameAuthorAppereances )
        {
            numberOfSameAuthorAppereances = authors[i].appereances;
            strcpy(mostPopularAuthor, authors[i].name);
        }
    }

    for(int i = 0; i < numberOfGenres; i++)
    {
        if( genres[i].appereances > numberOfSimillarGenres )
        {
            numberOfSimillarGenres = genres[i].appereances;
            strcpy(mostPopularGenre, genres[i].name);
        }
    }

    if( float( numberOfSameAuthorAppereances) / float(numberOfDownloads) >= 0.8 )
    {
        givenFilter->typeFlags = _DB_ALLGN;
        strcpy(givenFilter->authorName, mostPopularAuthor);
    }  
    else
    {
        memset(givenFilter->authorName, 0, 128);
        givenFilter->typeFlags = isInGenreFlag(mostPopularGenre);
    }
}


void Database::DecodeFilter(DBFilter* givenFilter, const char* givenInfo)
{
    char* infoCopy = (char*)malloc(1024), *p;
    memset(givenFilter->authorName,0 ,128);
    memset(givenFilter->bookName, 0 ,128);
    givenFilter->entriesPerPage = 20;
    givenFilter->page = 1;
    givenFilter->minYear = -1;
    givenFilter->maxYear = 999999;
    givenFilter->rating = -1;
    givenFilter->typeFlags = _DB_ALLGN;
    memset(infoCopy, 0, 1024);
    strcpy(infoCopy, givenInfo);
    p = infoCopy;
    *strchr(p, ';') = 0;
    if(*p)
        givenFilter->page = atoi(p);
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        givenFilter->entriesPerPage = atoi(p);
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        strcpy(givenFilter->authorName, p);   
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        strcpy(givenFilter->bookName, p);  
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        givenFilter->minYear = atoi(p); 
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        givenFilter->maxYear = atoi(p); 
    p = p + strlen(p) + 1;
    *strchr(p, ';') = 0;
    if(*p)
        givenFilter->typeFlags = atoi(p);
    p = p + strlen(p) + 1;
    if(*p)
        givenFilter->rating = atoi(p);
}

Database::Database(const char* filepath,const int& bufferLength)
{
    this->linkedDatabaseRelativePath = (char*)malloc(256);
    strcpy(this->linkedDatabaseRelativePath, filepath);
    this->buffer = (char*)malloc(bufferLength);
    this->dbDescriptor = fopen(this->linkedDatabaseRelativePath, "r");
    memset(this->buffer, 0, bufferLength * sizeof(char));
    fread(this->buffer, 1, bufferLength, this->dbDescriptor);
    fclose(this->dbDescriptor);
    this->parsed_json = json_tokener_parse(buffer);
}

Database::~Database()
{
    parsed_json = nullptr;
    dbDescriptor = nullptr;
}
