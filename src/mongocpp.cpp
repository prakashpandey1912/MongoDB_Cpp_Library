#include<mongoc.h>
#include<bits/stdc++.h>
#include "mongocpp.h"
using namespace std;

DBCursor::DBCursor(mongoc_cursor_t * cursor)
{
this->cursor=cursor;
}
DBCursor::~DBCursor()
{
mongoc_cursor_destroy (cursor);
}
bool DBCursor::hasNext()
{
if(mongoc_cursor_next (cursor, &document))
{
bson_iter_init(&iterator,document);
return true;
}
return false;
}
char * DBCursor::next()
{
str = bson_as_json (document, NULL);
return str;
//bson_free (str);
}
int DBCursor::getInt(const char *k)
{
int32_t valINT32;
if(bson_iter_next(&iterator))
{
const char * key=bson_iter_key(&iterator);
if(!strcmp(key,k)) valINT32=bson_iter_int32(&iterator);
}
return valINT32;
}
const char * DBCursor::getChar(const char *k)
{
const char *valUTF8;
if(bson_iter_next(&iterator))
{
const char * key=bson_iter_key(&iterator);
if(!strcmp(key,k)) valUTF8=bson_iter_utf8(&iterator,NULL);
}
return valUTF8;
}

DBObject::DBObject(bson_t * doc)
{
this->doc=doc;
}
DBObject::~DBObject()
{
bson_destroy(doc);
}
bson_t * DBObject::get()
{
return doc;
}


DBCollection::DBCollection(mongoc_collection_t * collection)
{
this->collection=collection;
}
DBCollection::~DBCollection()
{
bson_destroy(querydoc);
bson_destroy(doc);
mongoc_cursor_destroy (cursor);
mongoc_collection_destroy(collection);
}
DBCursor * DBCollection::find()
{
cursor = mongoc_collection_find_with_opts (collection,&query, NULL, NULL);
DBCursor * dbcursor=new DBCursor(cursor);
return dbcursor;
}
void DBCollection::insert(DBObject *document)
{
doc=document->get();
if(!mongoc_collection_insert_one(collection,doc,NULL,NULL,&error))
{
printf("%s\n",error.message);
}
}
void DBCollection::update(DBObject *querydocument,DBObject *document)
{
doc=document->get();
querydoc=querydocument->get();
if(!mongoc_collection_update(collection,MONGOC_UPDATE_NONE,querydoc,doc,NULL,&error))
{
printf("%s\n",error.message);
}
else
{
printf("updated\n");
}
}
void DBCollection::remove(DBObject *document)
{
doc=document->get();
if(!mongoc_collection_remove(collection,MONGOC_REMOVE_NONE,doc,NULL,&error))
{
printf("%s\n",error.message);
}
else
{
printf("removed\n");
}
}


MongoClient::MongoClient(const char * uri)
{
//uri="mongodb://localhost:27017";
mongoc_init();
client=mongoc_client_new(uri);
}
MongoClient::~MongoClient()
{
mongoc_collection_destroy(collection);
mongoc_client_destroy(client);
mongoc_cleanup();
}
DBCollection * MongoClient::getCollection(const char *dbName,const char *collectionName)
{
this->dbName=dbName;
this->collectionName=collectionName;
collection=mongoc_client_get_collection(client,dbName,collectionName);
DBCollection *db=new DBCollection(collection);
return db;
}

BasicDBObjectBuilder::~BasicDBObjectBuilder()
{
bson_destroy(doc);
}
void BasicDBObjectBuilder::start()
{
doc=bson_new();
}
void BasicDBObjectBuilder::Append(const char * fieldName,int value)
{
BSON_APPEND_INT32(doc,fieldName,value);
}
void BasicDBObjectBuilder::Append(const char * fieldName,const char * value)
{
BSON_APPEND_UTF8(doc,fieldName,value);
}
DBObject * BasicDBObjectBuilder::get()
{
DBObject *document=new DBObject(doc);
return document;
}