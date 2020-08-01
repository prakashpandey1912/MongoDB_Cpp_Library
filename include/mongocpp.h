#include <mongoc.h>
#include <bits/stdc++.h>
#include <stdbool.h> 
class DBCursor
{
char *str;
const bson_t *document;
mongoc_cursor_t *cursor;
bson_iter_t iterator;
public:
DBCursor(mongoc_cursor_t * cursor);
~DBCursor();
bool hasNext();
char * next();
int getInt(const char *);
const char * getChar(const char *);
};

class DBObject
{
bson_t *doc;
public:
DBObject(bson_t * doc);
~DBObject();
bson_t * get();
};

class DBCollection
{
mongoc_cursor_t *cursor;
bson_error_t error;
const bson_t query=BSON_INITIALIZER;
bson_t * doc;
bson_t * querydoc;
mongoc_collection_t *collection;
public:
DBCollection(mongoc_collection_t * collection);
~DBCollection();
DBCursor * find();
void insert(DBObject *);
void update(DBObject *,DBObject *);
void remove(DBObject *);
};
class MongoClient
{
mongoc_collection_t *collection;
const char *dbName;
const char *collectionName;
mongoc_client_t *client;
public:
MongoClient(const char *);
~MongoClient();
DBCollection * getCollection(const char *,const char *);
};
class BasicDBObjectBuilder 
{
bson_t *doc;
public:
~BasicDBObjectBuilder();
void start();
void Append(const char *,int);
void Append(const char *,const char *);
DBObject * get();
};