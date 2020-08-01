#include "mongocpp.h"
using namespace std;
int main()
{
MongoClient *mongoClient=new MongoClient("mongodb://localhost:27017");
DBCollection *Collection=mongoClient->getCollection("tmdb","prakash");
BasicDBObjectBuilder *objectBuilder=new BasicDBObjectBuilder();
objectBuilder->start();
objectBuilder->Append("_id",101);
objectBuilder->Append("firstName","Pandey");
objectBuilder->Append("lastName","Prakash");
DBObject *document=objectBuilder->get();
objectBuilder->start();
objectBuilder->Append("_id",101);
DBObject *queryobject=objectBuilder->get();
Collection->update(queryobject,document);
delete objectBuilder;
delete mongoClient;
cout<<"done";
return 0;
}